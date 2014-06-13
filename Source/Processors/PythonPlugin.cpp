/*
  ==============================================================================

    PythonPlugin.cpp
    Created: 13 Jun 2014 5:56:17pm
    Author:  fpbatta

  ==============================================================================
*/

#include "PythonPlugin.h"




#include "../../JuceLibraryCode/JuceHeader.h"
#include "PythonPlugin.h"
#include "Editors/PythonEditor.h"

#include <dlfcn.h>

PythonPlugin::PythonPlugin(const String &processorName)
    : GenericProcessor(processorName) //, threshold(200.0), state(true)

{

    //parameters.add(Parameter("thresh", 0.0, 500.0, 200.0, 0));
        filePath = "";
        plugin = 0;
        Py_SetProgramName ("PythonPlugin");
        Py_Initialize ();
}

PythonPlugin::~PythonPlugin()
{
	dlclose(plugin);
}

AudioProcessorEditor* PythonPlugin::createEditor()
{
        std::cout << "in PythonEditor::createEditor()" << std::endl;
    editor = new PythonEditor(this, true);

    return editor;

}


bool PythonPlugin::isReady()
{
    if (plugin == 0)
    {
        sendActionMessage("No plugin selected in Python Plugin.");
        return false;
    }
    else
    {
        return true;
    }
}

void PythonPlugin::setParameter(int parameterIndex, float newValue)
{
    editor->updateParameterButtons(parameterIndex);

    //Parameter& p =  parameters.getReference(parameterIndex);
    //p.setValue(newValue, 0);

    //threshold = newValue;

    //std::cout << float(p[0]) << std::endl;
    editor->updateParameterButtons(parameterIndex);
}

void PythonPlugin::process(AudioSampleBuffer& buffer,
                               MidiBuffer& events,
                               int& nSamples)
{

    // for (int i = 0; i < nSamples; i++)
    // {
    //
    //     if ((*buffer.getSampleData(0, i) < -threshold) && !state)
    //     {
    //
    //         // generate midi event
    //         addEvent(events, TTL, i);
    //
    //         state = true;
    //
    //     } else if ((*buffer.getSampleData(0, i) > -threshold + bufferZone)  && state)
    //     {
    //         state = false;
    //     }
    //
    //
    // }


}



void PythonPlugin::setFile(String fullpath)
{

	DL_IMPORT(void) (*cf)(void);
    filePath = fullpath;

    const char* path = filePath.getCharPointer();
    plugin = dlopen("/Users/fpbatta/src/cpython_plugin1/cpython_plugin1.so", RTLD_LAZY);
    if (!plugin)
      {
          std::cout << "Can't open plugin "
                    << '"' << path << "\""
                    << std::endl;
          return;
      }

    void *initializer = dlsym(plugin,"initPlugin");
    if (!initializer)
    {
    	std::cout << "Can't find init function in plugin "
    			<< '"' << path << "\""
    			<< std::endl;
    	plugin = 0;
    	return;
    }

    initfunc_t initF = (initfunc_t) initializer;

    void *cfunc = dlsym(plugin,"pluginFunction");
    (*initF)();
}


String PythonPlugin::getFile()
{
    return filePath;
}

void PythonPlugin::updateSettings()
{

}
