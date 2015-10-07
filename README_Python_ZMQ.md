# Extending Open-Ephys with Python and ZeroMQ

### Francesco P. Battaglia 


The philosophy (and indeed, the utility) of Open Ephys is based on openness, the ability of extending and modifying an experimental setup according to the most diverse requirements. 

To make interacting and extending this software even easier and faster, the "Python Plugin" and "Zmq interface" offer ways to write extension code in Python and other languages, isolating the programmer from the complications of C++ and the Juce frameworks, and enabling previously difficult workflows. 

Python Plugin enables loading dynamic  libraries written in [Cython](http://cython.org) (a C compiled version of Python ) directly in the signal chain, providing the functionalities that would ordinarily be implemented in a processor. This is meant for developing new data filters, as well as for semi-fast closed-loop manipulations. 

Zmq interface broadcasts all data and events to a ZeroMQ socket, and allows an application to send events via another ZeroMQ connection. This is specifically suited for providing  tailored visualizations, as well as "slow" data analysis and feedback, experimental parameter optimization, and so on.

At the moment, both modules are still experimental, but have been already been used successfully in experimental situations. Python Plugin requires a Python installations, most likely with the relevant scientific packages. I have done most of the testing with Anaconda Python 3.4. I have figured out a way to compile and link the executable under Mac OS and Linux. It will probably take a very short time to somebody with Windows development experience (not me), to figure out the dependencies and a couple more requirements (see below) under Windows. 


## Python Plugin 
Python Plugin is a processor that loads a .so (or DLL) file including a Cython module that exposes a specific C API. It allows the user to change parameters for the Cython module (tresholds, channel numbers and the like) via an editor that is dynamically generated. It may be loaded as a Source, Filter or Sink, even though it is probably mostly useful as a filter. 
In our tests, for simple closed loop paradigms, the round trip latency is around 20 ms (with the jitter to be expected in non-Real Time OSs). 

####Installation

###### Mac OS 

* install the latest HDF5 from source code with 
`./configure --prefix=/usr/local --enable-cxx`
`make; make install`

* install ZeroMQ from source, standard install (these two steps are the same as with standard compiling of Open-Ephys)

* Install Anaconda Python 3 from https://store.continuum.io/cshop/anaconda/ . In what follows we'll assume that Anaconda is installed under /usr/local/anaconda. In any case, Anaconda Python should be the default python interpreter on your path at the time of compilation, so that the dependencies are correctly captured.

* After that, compilation should work in XCode as usual, with the provided Xcode roject file. 

* If the project needs to be edited by Jucer (e.g. to add more files), an extra step is required after saving the project in Jucer. In XCode, click on the open-ephys project tab, then on the "Build phases" tab, and add a "Run Script" phase. In the space for shell script code, paste or type 
```
install_name_tool -change libpython3.4m.dylib /usr/local/anaconda3/anaconda/lib/libpython3.4m.dylib "$TARGET_BUILD_DIR/$TARGET_NAME.app/Contents/MacOS/$PRODUCT_NAME"
```

* after this step, compilation should take place normally

###### Linux

These steps have been tested on Ubuntu 14.04, on other distributions things will probably be quite similar. 

* install the latest HDF5 from source code with 
`./configure --prefix=/usr/local --enable-cxx`
`make; make install`

* install ZeroMQ from source, standard install (these two steps are the same as with standard compiling of Open-Ephys)

* Install Anaconda Python 3 from https://store.continuum.io/cshop/anaconda/ . In what follows we'll assume that Anaconda is installed under /usr/local/anaconda. In any case, Anaconda Python should be the default python interpreter on your path at the time of compilation, so that the dependencies are correctly captured.

* If you want to install the serial module (for example to control a stimulator) you can do that by `sudo -H /usr/local/anaconda/bin/conda install -c https://conda.anaconda.org/anaconda pyserial`

* The Jucer file includes some environment variables that take care of the Python dependencies. It's important that we end up linking the Python interpreter from the distribution we intend to use and not a different one (e.g. the system Python installation). These variables are set up in the script `build-linux.sh`, which calls `make` and should be used for compilation. *Do not* attempt to compile Open-Ephys with the standard make command, as that will fail. 

* Thus, if changes to the project are needed, open the IntroJucer and edit as needed, but leaving in place the Python related stuff. If no changes to the project are needed, this step may be omitted.

* from the GUI root directory, type 
`./build-linux.sh` and if all goes well compilation should take place. 

###### Windows

At the moment, Windows it's not supported, however, all it should be required for compilation is to make sure that libpython3.4m.dll is linked, and that the PYTHONHOME variable is set to the anaconda home directory, both at compilation and run time. 



#### Writing a plugin 

A plugin is written in Cython, that is a version of python with data types (essentially), that can be translated into C and compiled. In any event, all the Cython specific code that is needed to interface with the C++ application is contained in the `Plugins/plugin.cyx` file so that a plugin may be written in pure Python (or almost so) if desired. An example is given in the file `Plugins/spwfinder.cyx` (assuming that the file is in the `Plugins/my_plugin_object` directory and is named `my_plugin_object.cyx`)

The structure of a plugin file will be 

```python 
import numpy as np
cimport numpy as np
import blahblah

isDebug = False 

class MyPluginObject(object):
	def __init__(self):
		blahblah
		
	def startup(self):
		blahblah

	def plugin_name(self):
		return "My Plugin"
		
	def is_ready(self):
		return True|False
		
    def param_config(self):
        chan_labels = range(32)
        return (("toggle", "enabled", True),
                ("int_set", "chan_in", chan_labels),
                ("float_range", "threshold", self.thresh_min, self.thresh_max, self.thresh_start),
        
    def bufferfunction(self, n_arr):
		# n_arr is a n_channels x n_samples numpy array and will contain the data from one data frame. 
		# the content may be modified and the modifications will be seen by the signal chain downstream
		# you can also send out signals to a serial port to drive stimulators, etc.
		
	def any_other_function_you_may_need:
		blahblah
		
pluginOp = MyPluginObject
include "../plugin.pyx"
```

The last two lines are important as they import the interface with the C++ code (which doesn't need to be modified) 

Note that the object is persistent, so it is possible to save state (e.g. buffer data for a desired length) in the plugin object members.

After that, you can compile the plugin by 
```
cd GUI/Plugins
make -f Makefile.OSX my_plugin_object/my_plugin_object.so 
```
(for Linux please use Makefile.Linux)
the Makefiles expect that the cyx files and the directory have the same name. Under Mac OS X and Linux the file my_plugin_object.so will be generated, this is your plugin.

the function `param_config` tells the GUI which parameters need to be user-modifiable. There are three types of parameters

* "toggle" is a Boolean one, it's specified with a tuple `("toggle", "name", default_boolean)` (see example above). A Toggle button will be generated in the editor

* "int_set" is a list of integers to choose from (for example to select a channel), specified by `("int_set", "name", list_of_integers)` for example a list of channels to select from. A ComboBox will be generated in the editor

* "float_range" is a float parameter that may vary in a range, defined by `("float_range", range_min, range_max, default)` . A slider will be generated in the editor


#### Using the plugin

Add the "Python Filter" to your signal. Click on "Set File" and choose your plugin (e.g. `my_plugin_object_so`). The controls that are defined in param_config should appear and the plugin should work in your signal chain.

##ZmqInterface

Visualization and plotting in python is very powerful using matplotlib and other libraries. It is however difficult to implement in an embedded context such as the Python Plugin, because of Python's Global Interpreter Lock, which prevents to have more than one thread in the Python interpreter at any given time. 
In this sense, it is easiest to implement visualization in a separate application, that receives data through a pipe or a network (unix) socket.
Zmq Interface enables data/event broadcasting and interacting with the GUI (by sending events to it) via a network connection. 

[ZeroMQ](http://zeromq.org) is a protocol/API which makes writing network applications incredibly easy. 
The ZmqInterface processor provides the interface, and has no parameters to set. 
An example of a simple plotting application is to be found in `ZMQPlugins/simple_plotter_zmq.py` 
Applications may be written in any language if the networking protocol is fulfilled. 
In python, it is enough to subclass PlotProcess (in `ZMQPlugins/plot_process_zmq.py`) which contains the networking code. 
In practice, one needs to override:
* `startup`: create all the plotting, GUI stuff there, then create a timer which calls `callback` every n milliseconds. `callback` will read the data and update the plot via 

* `update_plot`: which receives all data packets as nChans x nSamples numpy array, which may be used to update the visualization 

* `update_plot_event`: which gets called each time an event is received.

Events may be sent to open-ephys by using the function `send_event`
The example should be fairly straightforward hopefully 


#### The networking protocol

`ZMQPlugins/plot_process_zmq.py` implements the protocol and should be referred to for the details. Here is a brief discussion (which requires some knowledge of ZeroMQ. If you plan to stick to python and not writing bindings to a different language, you can skip this safely).
The protocol uses two ZMQ socket pairs. a PUB/SUB pairs is used to transmit data from open-ephys to the application(s). As many applications as desired may connect to open-ephys PUB socket. 
A second REQ/REP socket pairs is used to the application to send back events to open-ephys, as well as a heartbeat signal, for open-ephys to keep track of which applications are connected, and whether they are alive. When an application is connected, its name is reported in green in the ZmqInterface editor. If no heartbeat from the application is detected for 10 seconds, the name turns red. Each instance of the application should have a unique UUID in order to keep track of each one with open-ephys

##### data formats

The PUB socket sends 2 or 3 frame messages. The first one only contains one of the words "DATA", "EVENT" or "PARAM" (which allows the SUB socket to e.g. only subscribe to events, or data, or parameter settings, which have so far no use)
The data are transfered as binary format, preceded by a JSON formatted header (the second frame) . Events are JSON (also the second frame), if there is data is transferred as binary in a successive frame. The format is :

```
{ "messageNo": number,
 "type": "data"|"event"|"parameter",
 "content":
 (for data)
 { "nChannels": nChannels,
 "nSamples": nSamples
 }
 (for event)
 {
 "eventType": number,
 "sampleNum": sampleNum (number),
 "eventId": id (number),
 "eventChannel": channel (number),
 }
 (for parameter)
 {
 "param_name1": param_value1,
 "param_name2": param_value2,
 ...
 }
 "dataSize": size (if size > 0 it's the size of binary data coming in in the next frame (multi-part message)
 }
 
```

The data come in the third packet, it's the application responsibility to convert them into a numpy array or whatever is useful. 


Events are send back also in JSON format, from these python dicts 
```python
               de = {'type': event_type, 'sample_num': sample_num, 'event_id': event_id ,
                      'event_channel': event_channel}
                d = {'application': self.app_name, 'uuid': self.uuid, 'type': 'event', 'event': de}
```

Messages of type 'heartbeat' and without an 'event' field should be sent out approx. every 2 seconds, or the editor in open-ephys  will signal a problem.

#### The example plugin 
in order to run the example Zmq plugin, that will display one channel of data, and will exchange some random events with Open Ephys (just for the sake of demonstration), please run the `run_simple_plotter.py` script in Plugins script like this 
```
export PYTHONPATH=${OPENEPHYSSOURCEDIR}/Plugins
python run_simple_plotter.py
```

#### Installation 
ZeroMQ is already a dependency of the core Open-Ephys system, so no further steps are required to compile this part. This source tree excluding PythonPlugin has been successfully compiled as is under Windows. 
In order to use the Example Plugin you have to add the `Plugins` folder to the `PYTHONPATH`



