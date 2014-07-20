/*
  ==============================================================================

    PythonEditor.cpp
    Created: 13 Jun 2014 4:21:01pm
    Author:  fpbatta

  ==============================================================================
*/

#include "PythonEditor.h"


#include "../PythonPlugin.h"

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
    
    
    addToggleButton(String("cucu1"), true);
    addToggleButton(String("cucu2"), true);
    addToggleButton(String("cucu3"), true);
    
    
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

                // lastFilePath = fileToRead.getParentDirectory();

                // thread->setFile(fileToRead.getFullPathName());

                // fileNameLabel->setText(fileToRead.getFileName(),false);
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
//    // TODO  decide later on action to be taken
//    std::cout << paramName << ": changed to" << String(theButton->getToggleState()) << std::endl;
}





