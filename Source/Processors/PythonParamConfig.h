/*
  ==============================================================================

    PythonParamConfig.h
    Created: 20 Jul 2014 6:53:03pm
    Author:  Francesco Battaglia

  ==============================================================================
*/

#ifndef __PYTHONPARAMCONFIG_H_13EFE267__
#define __PYTHONPARAMCONFIG_H_13EFE267__

// a small header file so that Cython doesn't get confused by the juce headers

enum paramType {
    TOGGLE,
    INT_SET,
    FLOAT_RANGE
};


struct ParamConfig {
    enum paramType type;
    char *name;
    int isEnabled;
    int nEntries;
    int *entries;
};



#endif  // __PYTHONPARAMCONFIG_H_13EFE267__
