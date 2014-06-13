/*
  ==============================================================================

    PythonSink.cpp
    Created: 13 Jun 2014 1:51:19pm
    Author:  fpbatta

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "PythonSink.h"

PythonSink::PythonSink()
    : GenericProcessor("Python Sink") //, threshold(200.0), state(true)

{

    //parameters.add(Parameter("thresh", 0.0, 500.0, 200.0, 0));
	filePath = 0;
	plugin = 0;
}

PythonSink::~PythonSink()
{

}

AudioProcessorEditor* PythonSink::createEditor()
{
	std::cout << "in PythonEditor::createEditor()" << std::endl;
    editor = new PythonEditor(this, true);

    return editor;

}

bool PythonSink::isReady()
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

void PythonSink::setParameter(int parameterIndex, float newValue)
{
    editor->updateParameterButtons(parameterIndex);

    //Parameter& p =  parameters.getReference(parameterIndex);
    //p.setValue(newValue, 0);

    //threshold = newValue;

    //std::cout << float(p[0]) << std::endl;
    editor->updateParameterButtons(parameterIndex);
}

void PythonSink::process(AudioSampleBuffer& buffer,
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
