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
    if (plugin == 0 )
    {
        sendActionMessage("No plugin selected in Python Plugin.");
        return false;
    }
    else if (pluginIsReady && !(*pluginIsReady)())
    {
        sendActionMessage("Plugin is not ready");
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

    (*pluginFunction)(*(buffer.getArrayOfChannels()), buffer.getNumChannels(), buffer.getNumSamples());

}


/* The complete API that the Cython plugin has to expose is
 void pluginStartup(void): a function to initialize the plugin data structures prior to start ACQ
 int isReady(void): a boolean function telling the processor whether the plugin is ready  to receive data
 int getParamNum(void) get the number of parameters that the plugin takes TODO
 ParamConfig *getParamConfig(void) this will allow generating the editor GUI TODO
 void setIntParameter(char *name, int value) set integer parameter TODO
 void set FloatParameter(char *name, float value) set float parameter TODO
 
 */
void PythonPlugin::setFile(String fullpath)
{
    filePath = fullpath;

    const char* path = filePath.getCharPointer();
    plugin = dlopen(path, RTLD_LAZY);
    if (!plugin)
      {
          std::cout << "Can't open plugin "
                    << '"' << path << "\""
                    << std::endl;
          return;
      }

    void *initializer = dlsym(plugin,"initplugin");
    std::cout << "initializer: " << initializer << std::endl;

    if (!initializer)
    {
    	std::cout << "Can't find init function in plugin "
        << '"' << path << "\"" << std::endl
        << dlerror()
        << std::endl;
    	plugin = 0;
    	return;
    }
    
    initfunc_t initF = (initfunc_t) initializer;

    
    void *cfunc = dlsym(plugin,"pluginisready");
    if (!cfunc)
    {
    	std::cout << "Can't find ready function in plugin "
        << '"' << path << "\"" << std::endl
        << dlerror()
        << std::endl;
    	plugin = 0;
    	return;
    }
    pluginIsReady = (isreadyfunc_t)cfunc;

    cfunc = dlsym(plugin,"pluginStartup");
    if (!cfunc)
    {
    	std::cout << "Can't find startup function in plugin "
        << '"' << path << "\"" << std::endl
        << dlerror()
        << std::endl;
        plugin = 0;
        return;
    }
    pluginStartupFunction = (startupfunc_t)cfunc;
    
    cfunc = dlsym(plugin,"getParamNum");
    if (!cfunc)
    {
    	std::cout << "Can't find getParamNum function in plugin "
        << '"' << path << "\"" << std::endl
        << dlerror()
        << std::endl;
        plugin = 0;
        return;
    }
    getParamNumFunction = (getparamnumfunc_t)cfunc;
    

    cfunc = dlsym(plugin,"getParamConfig");
    if (!cfunc)
    {
    	std::cout << "Can't find getParamNum function in plugin "
        << '"' << path << "\"" << std::endl
        << dlerror()
        << std::endl;
        //    	plugin = 0;
        //    	return;
    }
    getParamConfigFunction = (getparamconfigfunc_t)cfunc;

    
    cfunc = dlsym(plugin,"pluginFunction");
    // std::cout << "plugin:   " << cfunc << std::endl;
    if (!cfunc)
    {
    	std::cout << "Can't find plugin function in plugin "
        << '"' << path << "\"" << std::endl
        << dlerror()
        << std::endl;
    	plugin = 0;
    	return;
    }
    pluginFunction = (pluginfunc_t)cfunc;
    

    cfunc = dlsym(plugin,"setIntParam");
    // std::cout << "plugin:   " << cfunc << std::endl;
    if (!cfunc)
    {
    	std::cout << "Can't find setIntParam function in plugin "
        << '"' << path << "\"" << std::endl
        << dlerror()
        << std::endl;
    	plugin = 0;
    	return;
    }
    setIntParamFunction = (setintparamfunc_t)cfunc;
    
    cfunc = dlsym(plugin,"setFloatParam");
    // std::cout << "plugin:   " << cfunc << std::endl;
    if (!cfunc)
    {
    	std::cout << "Can't find setFloatParam function in plugin "
        << '"' << path << "\"" << std::endl
        << dlerror()
        << std::endl;
    	plugin = 0;
    	return;
    }
    setFloatParamFunction = (setfloatparamfunc_t)cfunc;

    
// now the API should be fully loaded

    // initialize the plugin
    (*initF)();
    (*pluginStartupFunction)();
    
    // load the parameter configuration
    numPythonParams = (*getParamNumFunction)();
    std::cout << "the plugin wants " << numPythonParams
        << " parameters" << std::endl;
    ParamConfig *params = (ParamConfig *)calloc(numPythonParams, sizeof(ParamConfig));
    (*getParamConfigFunction)(params);
    for(int i = 0; i < numPythonParams; i++)
    {
        std::cout << "param " << i << " is a " << params[i].type << std::endl;
        std::cout << "it is named: " << params[i].name << std::endl << std::endl;
        switch (params[i].type) {
            case TOGGLE:
                dynamic_cast<PythonEditor *>( getEditor())->addToggleButton(String(params[i].name), params[i].isEnabled);
                break;
                
            default:
                break;
        }
    }
}


String PythonPlugin::getFile()
{
    return filePath;
}

void PythonPlugin::updateSettings()
{

}

void PythonPlugin::setIntPythonParameter(String name, int value)
{
    // TODO pass it to python
    //std::cout << name << ": changed to" << value << std::endl;
    (*setIntParamFunction)(name.getCharPointer().getAddress(), value);
}

