cdef extern from "../../JuceLibraryCode/modules/juce_audio_basics/buffers/juce_AudiosampleBuffer.h":
    cppclass AudioSampleBuffer:
        int getNumChannels()
        int getNumSamples()
        float* getSampleData (int)
        float* getSampleData (int, int)
        float** getArrayOfChannels()



