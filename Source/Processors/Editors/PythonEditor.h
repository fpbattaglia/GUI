/*
  ==============================================================================

    PythonEditor.h
    Created: 13 Jun 2014 4:21:01pm
    Author:  fpbatta

  ==============================================================================
*/

#ifndef __PYTHONEDITOR_H_5E135C2C__
#define __PYTHONEDITOR_H_5E135C2C__

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "GenericEditor.h"

class PythonPlugin;

class PythonEditor : public GenericEditor

{
public:
    PythonEditor(GenericProcessor* parentNode, bool useDefaultParameterEditors);
    virtual ~PythonEditor();

    void buttonEvent(Button* button);

    void setFile(String file);

    void saveEditorParameters(XmlElement*);

    void loadEditorParameters(XmlElement*);

private:

    ScopedPointer<UtilityButton> fileButton;
    ScopedPointer<Label> fileNameLabel;

    PythonPlugin* pythonPlugin;

    File lastFilePath;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PythonEditor);

};


#endif  // __PYTHONEDITOR_H_5E135C2C__
