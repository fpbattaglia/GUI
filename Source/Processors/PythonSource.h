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

//==============================================================================
/*
*/
class PythonSource    : public Component
{
public:
    PythonSource();
    ~PythonSource();

    void paint (Graphics&);
    void resized();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PythonSource)
};


#endif  // __PYTHONSOURCE_H_4A56EB1__
