cimport qjuce_AudioSampleBuffer
from libc.stdio cimport printf
#import sys


#cdef extern from "../../JuceLibraryCode/JuceHeader.h":
#    cppclass AudioSampleBuffer:
#        int getNumChannels()
#        int getNumSamples()
#        float* getSampleData (int)
#        float* getSampleData (int, int)
#        float** getArrayOfChannels()


cdef public void pyprocess (AudioSampleBuffer buffer):
#    cdef char s[250]  = sys.path[0]
    
#    printf("%s\n", s)
    print ("we got %d channels \n" % buffer.getNumChannels())
