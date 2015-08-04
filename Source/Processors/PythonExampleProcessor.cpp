/*
  ==============================================================================

    PythonExampleProcessor.cpp
    Created: 15 May 2014 1:21:28pm
    Author:  fpbatta

  ==============================================================================
*/

#include "PythonExampleProcessor.h"

#ifdef HAVE_PYTHON
#include <Python.h>
#include "pyprocessor1.h"
#endif
PythonExampleProcessor::PythonExampleProcessor()
    : GenericProcessor("Python Example Processor") //, threshold(200.0), state(true)

{
	std::cout << "in PythonExampleProcessor constructor " << std::endl;
#ifdef HAVE_PYTHON
    Py_SetProgramName ("OpenEphys");
	Py_InitializeEx (1);
	initpyprocessor1();
#endif
    //parameters.add(Parameter("thresh", 0.0, 500.0, 200.0, 0));

}

PythonExampleProcessor::~PythonExampleProcessor()
{
#ifdef HAVE_PYTHON
	Py_Finalize ();
#endif
}



void PythonExampleProcessor::setParameter(int parameterIndex, float newValue)
{
    editor->updateParameterButtons(parameterIndex);

    //Parameter& p =  parameters.getReference(parameterIndex);
    //p.setValue(newValue, 0);

    //threshold = newValue;

    //std::cout << float(p[0]) << std::endl;
    editor->updateParameterButtons(parameterIndex);
}

void PythonExampleProcessor::process(AudioSampleBuffer& buffer,
                               MidiBuffer& events,
                               int& nSamples)
{

//     for (int i = 0; i < nSamples; i++)
//     {
//
//         if ((*buffer.getSampleData(0, i) < -threshold) && !state)
//         {
//
//             // generate midi event
//             addEvent(events, TTL, i);
//
//             state = true;
//
//         } else if ((*buffer.getSampleData(0, i) > -threshold + bufferZone)  && state)
//         {
//             state = false;
//         }
//
//
//     }
	std::cout << "calling PEP with " << nSamples << " samples" << std::endl;
//	for (int i = 0; i < nSamples; i++)
//	{
//		if(*buffer.getSampleData(0, i) > maxSample)
//		{
//			maxSample = *buffer.getSampleData(0, i);
//			std::cout << "new max = " << maxSample << std::endl;
//		}
//	}
	std::cout << "Python initialized: " << Py_IsInitialized() << std::endl;
	pyprocess(buffer);

}
