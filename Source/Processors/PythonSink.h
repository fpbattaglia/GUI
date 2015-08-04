/*
  ==============================================================================

    PythonSink.h
    Created: 13 Jun 2014 5:37:25pm
    Author:  fpbatta

  ==============================================================================
*/

#ifndef __PYTHONSINK_H_4D2E4E29__
#define __PYTHONSINK_H_4D2E4E29__

#include "../../JuceLibraryCode/JuceHeader.h"
#include "PythonPlugin.h"


class PythonSink: public PythonPlugin
{
public:
    /** The class constructor, used to initialize any members. */
    PythonSink();

    /** The class destructor, used to deallocate memory */
    ~PythonSink();

    /** Determines whether the processor is treated as a source. */
    bool isSource()
    {
        return false;
    }

    /** Determines whether the processor is treated as a sink. */
    bool isSink()
    {
        return true;
    }



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PythonSink);

};




#endif  // __PYTHONSINK_H_4D2E4E29__
