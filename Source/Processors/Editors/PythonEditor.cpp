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
    // TODO adjust to something meaningful or remove
    UtilityButton *triggerButton = new UtilityButton("trigger", Font("Small Text", 10, Font::plain));
    triggerButton->addListener(this);
    triggerButton->setRadius(3.0f);
    triggerButton->setBounds(5,50,55,20);
    addAndMakeVisible(triggerButton);
    
    repaint();
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
