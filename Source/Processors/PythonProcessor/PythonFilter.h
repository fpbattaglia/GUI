/*
  ==============================================================================

    PythonFilter.h
    Created: 13 Jun 2014 1:50:08pm
    Author:  fpbatta

  ==============================================================================
*/

#ifndef __PYTHONFILTER_H_71926ECE__
#define __PYTHONFILTER_H_71926ECE__

#include "../../JuceLibraryCode/JuceHeader.h"
#include "PythonPlugin.h"
//==============================================================================
/*
*/

class PythonFilter    : public PythonPlugin
{
public:
    /** The class constructor, used to initialize any members. */
    PythonFilter();

    /** The class destructor, used to deallocate memory */
    ~PythonFilter();

    /** Determines whether the processor is treated as a source. */
    bool isSource()
    {
        return false;
    }

    /** Determines whether the processor is treated as a sink. */
    bool isSink()
    {
        return false;
    }



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PythonFilter);

};



#endif  // __PYTHONFILTER_H_71926ECE__
