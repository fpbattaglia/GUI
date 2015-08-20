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
class PythonParameterButtonInterface;

class PythonEditor : public GenericEditor

{
public:
    PythonEditor(GenericProcessor* parentNode, bool useDefaultParameterEditors);
    virtual ~PythonEditor();

    void buttonEvent(Button* button);

    void setFile(String file);

    void saveCustomParameters(XmlElement*);

    void loadCustomParameters(XmlElement*);

    Component *addToggleButton(String, bool);
    
    Component *addComboBox(String, int, int*);
    
    Component *addSlider(String, float, float, float);
    
    
    
private:
    

    ScopedPointer<UtilityButton> fileButton;
    ScopedPointer<Label> fileNameLabel;

    OwnedArray<Component> parameterInterfaces;
    PythonPlugin* pythonPlugin;

    File lastFilePath;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PythonEditor);

};


class PythonParameterButtonInterface : public Component,  public Button::Listener
{
public:
    PythonParameterButtonInterface(String paramName_, int defaultVal, PythonPlugin *plugin_);
    virtual ~PythonParameterButtonInterface();
    void paint(Graphics& g);
    void buttonClicked(Button* button);
    void setToggleStateFromValue(int value);
    
private:
    String paramName;
    bool isEnabled;
    PythonPlugin *plugin;
    ScopedPointer<ToggleButton> theButton;
    
    
};

class PythonParameterComboBoxInterface : public Component,  public ComboBox::Listener
{
public:
    PythonParameterComboBoxInterface(String paramName_, int nEntries_, int *entries_, PythonPlugin *plugin_);
    virtual ~PythonParameterComboBoxInterface();
    void paint(Graphics& g);
    void comboBoxChanged(ComboBox* comboBox);
    void setEntryFromValue(int value);
    
private:
    String paramName;
    int nEntries;
    int *entries;
    bool lastState;
    bool isEnabled;
    PythonPlugin *plugin;
    ScopedPointer<ComboBox> theComboBox;
    
    
};

class PythonParameterSliderInterface : public Component,  public Slider::Listener
{
public:
    PythonParameterSliderInterface(String paramName_, double rangeMin, double rangeMax, double startValue, PythonPlugin *plugin_);
    virtual ~PythonParameterSliderInterface();
    void paint(Graphics& g);
    void sliderValueChanged(Slider* slider);
    void setSliderFromValue(float value);
    
private:
    String paramName;
    bool isEnabled;
    PythonPlugin *plugin;
    ScopedPointer<Slider> theSlider;
    
    
};



#endif  // __PYTHONEDITOR_H_5E135C2C__
