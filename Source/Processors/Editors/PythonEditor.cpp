/*
  ==============================================================================

    PythonEditor.cpp
    Created: 13 Jun 2014 4:21:01pm
    Author:  fpbatta

  ==============================================================================
*/

#include "PythonEditor.h"


#include "../PythonProcessor/PythonPlugin.h"

#include <stdio.h>

PythonEditor::PythonEditor(GenericProcessor* parentNode, bool useDefaultParameterEditors=true)
    : GenericEditor(parentNode, useDefaultParameterEditors)

{

    pythonPlugin = (PythonPlugin*) parentNode;

    lastFilePath = File::getCurrentWorkingDirectory();

    fileButton = new UtilityButton("Select file",Font("Small Text", 13, Font::plain));
    fileButton->addListener(this);
    fileButton->setBounds(30,50,120,25);
    addAndMakeVisible(fileButton);

    fileNameLabel = new Label("FileNameLabel", "No file selected.");
    fileNameLabel->setBounds(20,80,140,25);
    addAndMakeVisible(fileNameLabel);

    desiredWidth = 180;

    setEnabledState(false);

}

PythonEditor::~PythonEditor()
{

}

void PythonEditor::setFile(String file)
{

    File fileToRead(file);
    lastFilePath = fileToRead.getParentDirectory();
    pythonPlugin->setFile(fileToRead.getFullPathName());
    fileNameLabel->setText(fileToRead.getFileName(), dontSendNotification);

    setEnabledState(true);
    removeChildComponent(fileButton);
    removeChildComponent(fileNameLabel);
    
    // TODO for the moment here, then in a new method
    
    //ToggleButton *tb = new ToggleButton("cucu");
    int *gg = new int[5];
    for(int i = 0;i < 5; i++)
    {
        gg[i] = i+1;
    }
    
    // addComboBox(String("baubau"), 5, gg);
    // addSlider(String("cane"), 0., 10., 5.);
    
    
    repaint();
}

void PythonEditor::addToggleButton(String paramName, bool isEnabled)
{
    PythonParameterButtonInterface *ppbi = new PythonParameterButtonInterface(paramName, isEnabled, (PythonPlugin *)getProcessor());
    parameterInterfaces.add(ppbi);
    int i = parameterInterfaces.size();
    ppbi->setBounds(10, 22 * i, 100 ,21);
    addAndMakeVisible(ppbi);
    std::cout << "Created button " << i << std::endl;

}

void PythonEditor::addComboBox(String paramName, int nEntries, int *entries)
{
    PythonParameterComboBoxInterface *ppcbi = new PythonParameterComboBoxInterface(paramName, nEntries, entries, (PythonPlugin *)getProcessor());
    parameterInterfaces.add(ppcbi);
    int i = parameterInterfaces.size();
    ppcbi->setBounds(10, 22 * i, 100 ,21);
    addAndMakeVisible(ppcbi);
    std::cout << "Created combobox " << i << std::endl;
    
}

void PythonEditor::addSlider(String paramName, float rangeMin, float rangeMax, float startValue)
{
    PythonParameterSliderInterface *ppsi = new PythonParameterSliderInterface(paramName, (double)rangeMin, (double)rangeMax, (double)startValue, (PythonPlugin *)getProcessor());
    parameterInterfaces.add(ppsi);
    int i = parameterInterfaces.size();
    ppsi->setBounds(10, 22 * i, 150 ,21);
    addAndMakeVisible(ppsi);
    std::cout << "Created slider " << i << std::endl;
    
}

void PythonEditor::buttonEvent(Button* button)
{

    if (!acquisitionIsActive)
    {

        if (button == fileButton)
        {
            //std::cout << "Button clicked." << std::endl;
            FileChooser choosePythonFile("Please select the file you want to load...",
                                             lastFilePath,
                                             "*");

            if (choosePythonFile.browseForFileToOpen())
            {
                // Use the selected file
                setFile(choosePythonFile.getResult().getFullPathName());
            }
        }

    }
}

void PythonEditor::saveEditorParameters(XmlElement* xml)
{

    // XmlElement* fileName = xml->createNewChildElement("FILENAME");
    // fileName->addTextElement(lastFilePath.getFullPathName());

}

void PythonEditor::loadEditorParameters(XmlElement* xml)
{

    // forEachXmlChildElement(*xml, xmlNode)
    //    {
    //       if (xmlNode->hasTagName("FILENAME"))
    //       {

    //           lastFilePath = File(xmlNode->getText());
    //           thread->setFile(lastFilePath.getFullPathName());
    //           fileNameLabel->setText(lastFilePath.getFullPathName(),false);
    //       }
    //   }

}

PythonParameterButtonInterface::PythonParameterButtonInterface(String paramName_, int defaultVal, PythonPlugin *plugin_)
:  paramName(paramName_), isEnabled(defaultVal), plugin(plugin_)
{
    std::cout << "creating a button with name " << paramName << std::endl;
    theButton = new ToggleButton(paramName);
    theButton->setToggleState(isEnabled, dontSendNotification);
    theButton->addListener(this);
    //    triggerButton->setRadius(3.0f);
    theButton->setBounds(1,1,55,20);
    addAndMakeVisible(theButton);
   
    
}

PythonParameterButtonInterface::~PythonParameterButtonInterface()
{
    
}

void PythonParameterButtonInterface::paint(Graphics& g)
{
    g.setColour(Colours::lightgrey);
    
    g.fillRoundedRectangle(0,0,getWidth(),getHeight(),4.0f);
    
    if (isEnabled)
        g.setColour(Colours::black);
    else
        g.setColour(Colours::grey);
    
    g.setFont(Font("Small Text", 10, Font::plain));
    
    //g.drawText(name, 5, 80, 200, 10, Justification::left, false);
}

void PythonParameterButtonInterface::buttonClicked(Button* button)
{
    // delegate to processor
    plugin->setIntPythonParameter(paramName, theButton->getToggleState());
//    std::cout << paramName << ": changed to" << String(theButton->getToggleState()) << std::endl;
}


PythonParameterComboBoxInterface::PythonParameterComboBoxInterface(String paramName_, int nEntries_, int *entries_, PythonPlugin *plugin_)
:  paramName(paramName_), nEntries(nEntries_), entries(entries_),  plugin(plugin_)
{
    std::cout << "creating a combobox with name " << paramName << std::endl;
    
    theComboBox = new ComboBox();
    theComboBox->setBounds(1, 1, 80, 20);
    theComboBox->addListener(this);
    theComboBox->addItem(paramName, 1);
 
    for(int i = 0; i < nEntries; i++)
    {
        theComboBox->addItem(String(entries[i]), i+2);
    }
    
    theComboBox->setSelectedId(1);
    addAndMakeVisible(theComboBox);
    
    
}

PythonParameterComboBoxInterface::~PythonParameterComboBoxInterface()
{
    
}

void PythonParameterComboBoxInterface::paint(Graphics& g)
{
    g.setColour(Colours::lightgrey);
    
    g.fillRoundedRectangle(0,0,getWidth(),getHeight(),4.0f);
    
    if (isEnabled)
        g.setColour(Colours::black);
    else
        g.setColour(Colours::grey);
    
    g.setFont(Font("Small Text", 10, Font::plain));
    
    //g.drawText(name, 5, 80, 200, 10, Justification::left, false);
}

void PythonParameterComboBoxInterface::comboBoxChanged(ComboBox* comboBox)
{
    int resp;
    
    resp = comboBox->getSelectedId();
    if (resp > 1) {
        // delegate to processor
        plugin->setIntPythonParameter(paramName, entries[resp-2]);
        std::cout << paramName << ": changed to " << String(entries[resp-2]) << std::endl;
    }
}



PythonParameterSliderInterface::PythonParameterSliderInterface(String paramName_, double rangeMin, double rangeMax, double startValue, PythonPlugin *plugin_)
:  paramName(paramName_),  plugin(plugin_)
{
    std::cout << "creating a slider with name " << paramName << std::endl;
    
    
    //fileNameLabel = new Label("FileNameLabel", "No file selected.");
    Label *titleLabel = new Label("Title label", paramName);
    titleLabel->setBounds(1, 1, 40, 20);
    addAndMakeVisible(titleLabel);
    theSlider = new Slider(paramName);
    theSlider->setBounds(41, 1, 110, 20);
    theSlider->setTextBoxStyle(Slider::TextBoxLeft, false, 40, 20);
    theSlider->setRange(rangeMin, rangeMax);
    theSlider->addListener(this);
    theSlider->setValue(startValue);
    addAndMakeVisible(theSlider);
    
    
}

PythonParameterSliderInterface::~PythonParameterSliderInterface()
{
    
}

void PythonParameterSliderInterface::paint(Graphics& g)
{
    g.setColour(Colours::lightgrey);
    
    g.fillRoundedRectangle(0,0,getWidth(),getHeight(),4.0f);
    
    if (isEnabled)
        g.setColour(Colours::black);
    else
        g.setColour(Colours::grey);
    
    g.setFont(Font("Small Text", 10, Font::plain));
    
    //g.drawText(name, 5, 80, 200, 10, Justification::left, false);
}

void PythonParameterSliderInterface::sliderValueChanged(Slider *slider)
{
    double resp;
    
    resp = slider->getValue();
    // delegate to processor
    plugin->setFloatPythonParameter(paramName, (float)resp);
    std::cout << paramName << ": changed to " << resp << std::endl;
}







