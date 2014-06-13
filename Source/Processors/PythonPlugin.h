/*
  ==============================================================================

    PythonPlugin.h
    Created: 13 Jun 2014 5:56:17pm
    Author:  fpbatta

  ==============================================================================
*/

#ifndef __PYTHONPLUGIN_H_2DB70FC9__
#define __PYTHONPLUGIN_H_2DB70FC9__

#include <Python.h>

#ifndef __PYX_EXTERN_C
  #ifdef __cplusplus
    #define __PYX_EXTERN_C extern "C"
  #else
    #define __PYX_EXTERN_C extern
  #endif
#endif


extern "C" typedef  void (*initfunc_t)(void);

typedef DL_IMPORT(void) (*cythonfunc_t)(void);

#ifdef _WIN32
#include <Windows.h>
#endif

#include "../../JuceLibraryCode/JuceHeader.h"
#include "GenericProcessor.h"



//=============================================================================
/*
*/
class PythonPlugin    : public GenericProcessor
{
public:
    /** The class constructor, used to initialize any members. */
    PythonPlugin(const String &processorName = "Python Plugin");

    /** The class destructor, used to deallocate memory */
    virtual ~PythonPlugin();

    /** Determines whether the processor is treated as a source. */
    virtual bool isSource()
    {
        return false;
    }

    /** Determines whether the processor is treated as a sink. */
    virtual bool isSink()
    {
        return false;
    }

    /** Defines the functionality of the processor.

        The process method is called every time a new data buffer is available.

        Processors can either use this method to add new data, manipulate existing
        data, or send data to an external target (such as a display or other hardware).

        Continuous signals arrive in the "buffer" variable, event data (such as TTLs
        and spikes) is contained in the "events" variable, and "nSamples" holds the
        number of continous samples in the current buffer (which may differ from the
        size of the buffer).
         */
    void process(AudioSampleBuffer& buffer, MidiBuffer& events, int& nSamples);

    /** Any variables used by the "process" function _must_ be modified only through
        this method while data acquisition is active. If they are modified in any
        other way, the application will crash.  */
    void setParameter(int parameterIndex, float newValue);

    AudioProcessorEditor* createEditor();

    bool hasEditor() const
    {
        return true;
    }

    void updateSettings();

    void setFile(String fullpath);
    String getFile();
    bool isReady();
private:

    String filePath;
    void *plugin;
    // private members and methods go here
    //
    // e.g.:
    //
    // float threshold;
    // bool state;


    cythonfunc_t pluginFunction;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PythonPlugin);

};



#endif  // __PYTHONPLUGIN_H_2DB70FC9__
