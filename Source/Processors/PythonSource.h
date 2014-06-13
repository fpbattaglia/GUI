/*
  ==============================================================================

    PythonSource.h
    Created: 13 Jun 2014 1:50:52pm
    Author:  fpbatta

  ==============================================================================
*/

#ifndef __PYTHONSOURCE_H_4A56EB1__
#define __PYTHONSOURCE_H_4A56EB1__

#include "../../JuceLibraryCode/JuceHeader.h"
#include "PythonPlugin.h"

class PythonSource    : public PythonPlugin
{
public:
    /** The class constructor, used to initialize any members. */
    PythonSource();

    /** The class destructor, used to deallocate memory */
    ~PythonSource();

    /** Determines whether the processor is treated as a source. */
    bool isSource()
    {
        return true;
    }

    /** Determines whether the processor is treated as a sink. */
    bool isSink()
    {
        return false;
    }



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PythonSource);

};

#endif  // __PYTHONSOURCE_H_4A56EB1__
