/*
  ==============================================================================

    PythonSink.h
    Created: 13 Jun 2014 1:51:19pm
    Author:  fpbatta

  ==============================================================================
*/

#ifndef __PYTHONSINK_H_4D2E4E29__
#define __PYTHONSINK_H_4D2E4E29__

#ifdef _WIN32
#include <Windows.h>
#endif

#include "../../JuceLibraryCode/JuceHeader.h"
#include "GenericProcessor.h"

//==============================================================================
/*
*/
class PythonSink    : public GenericProcessor
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

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PythonSink);

};


#endif  // __PYTHONSINK_H_4D2E4E29__
