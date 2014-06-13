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

//==============================================================================
/*
*/
class PythonFilter    : public Component
{
public:
    PythonFilter();
    ~PythonFilter();

    void paint (Graphics&);
    void resized();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PythonFilter)
};


#endif  // __PYTHONFILTER_H_71926ECE__
