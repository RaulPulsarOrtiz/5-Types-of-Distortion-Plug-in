/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"






//==============================================================================
TypesofDistortionAudioProcessorEditor::TypesofDistortionAudioProcessorEditor(TypesofDistortionAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), 
    inputMeterL([&]() { return audioProcessor.getInputSignal(0); }), inputMeterR([&]() { return audioProcessor.getInputSignal(1); }),
    outputMeterL([&]() { return audioProcessor.getOutputSignal(0); }), outputMeterR([&]() { return audioProcessor.getOutputSignal(1); })
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(800, 400);

    hardClipGUI.setHardClip(audioProcessor.getHardClip());
    softClipGUI.setSoftClip(audioProcessor.getSoftClip());
   //No GUI for QuarterCicle?
    asymmetricalGUI.setAsymmetrical(audioProcessor.getAsymmetrical());
   
    guiPosition.setInterceptsMouseClicks(false, false);
    addAndMakeVisible(guiPosition);//Just for paint()???? It need to be first to don't cover the rest of Components

    distortionTypeMenu.addItem("Off", 1);
    distortionTypeMenu.addItem("Hard Clipping", 2);
    distortionTypeMenu.addItem("Soft Clipping", 3);
    distortionTypeMenu.addItem("Quarter Circle", 4);
    distortionTypeMenu.addItem("Asymmetrical", 5);
    distortionTypeMenu.setText("Distortion Type", dontSendNotification);
    distortionTypeMenu.setColour(juce::ComboBox::backgroundColourId, juce::Colours::black);
    distortionTypeMenu.setColour(juce::ComboBox::outlineColourId, juce::Colours::white);
    distortionTypeMenu.setColour(juce::ComboBox::arrowColourId, juce::Colours::red);
    distortionTypeMenu.setColour(juce::ComboBox::textColourId, juce::Colours::yellow);
    distortionTypeMenu.setLookAndFeel(&menuLookAndFeel);
    distortionTypeMenu.addListener(this);
    addAndMakeVisible(distortionTypeMenu);
   
    addAndMakeVisible(hardClipGUI);
    addAndMakeVisible(softClipGUI);
    softClipGUI.isAlwaysOnTop();
    //QuarterCicle
    addAndMakeVisible(asymmetricalGUI);

    outputGainSldr.setSliderStyle(Slider::Rotary);
    outputGainSldr.setRange(0.f, 1.1f, 0.05);
    outputGainSldr.setValue(1.f);
    outputGainSldr.setTextBoxStyle(Slider::TextBoxAbove, true, 60, 15);
    //outputGainSldr.mouseDoubleClick(MouseEvent mouse);
    outputGainSldr.setLookAndFeel(&twentyTwoStepsLookAndFeel);
    outputGainSldr.addListener(this);
    addAndMakeVisible(outputGainSldr);

    
    cutoffSldr.setSliderStyle(Slider::Rotary);
    cutoffSldr.setRange(20, 20000, 1);
    cutoffSldr.setValue(20000);
    cutoffSldr.setTextBoxStyle(Slider::TextBoxAbove, true, 60, 15);
    //cutoffSldr.mouseDoubleClick(MouseEvent mouse);
    cutoffSldr.setTextValueSuffix("Hz");
    cutoffSldr.setLookAndFeel(&twentyTwoStepsLookAndFeel);
    cutoffSldr.addListener(this);
    addAndMakeVisible(cutoffSldr);

    dryWetSldr.setSliderStyle(Slider::Rotary);
    dryWetSldr.setRange(0, 100, 1);
    dryWetSldr.setValue(100);
    dryWetSldr.setTextBoxStyle(Slider::TextBoxAbove, true, 40, 15);
    //cutoffSldr.mouseDoubleClick(MouseEvent mouse);
    dryWetSldr.setTextValueSuffix("%");
    dryWetSldr.setLookAndFeel(&twentyTwoStepsLookAndFeel);
    dryWetSldr.addListener(this);
    addAndMakeVisible(dryWetSldr);

    outputGainText.setText("Output Gain", dontSendNotification);
    outputGainText.setColour(Label::ColourIds::outlineColourId, Colours::wheat);
    addAndMakeVisible(outputGainText);
    
    filterTypeMenu.addItem("LPF", 1);
    filterTypeMenu.addItem("HPF", 2);
    filterTypeMenu.setSelectedId(1, juce::dontSendNotification);
    filterTypeMenu.setText("Filter Type:", dontSendNotification);
    filterTypeMenu.setLookAndFeel(&invertedMenuLookAndFeel);
    filterTypeMenu.addListener(this);
    addAndMakeVisible(filterTypeMenu);

    cutoffText.setText("Cutoff Freq", dontSendNotification);
    cutoffText.setColour(Label::ColourIds::outlineColourId, Colours::wheat);
    addAndMakeVisible(cutoffText);

    dryWetText.setText("Dry/Wet", dontSendNotification);
    dryWetText.setColour(Label::ColourIds::outlineColourId, Colours::wheat);
    addAndMakeVisible(dryWetText);
  
    addAndMakeVisible(inputMeterL);
    addAndMakeVisible(inputMeterR);
    addAndMakeVisible(outputMeterL);
    addAndMakeVisible(outputMeterR);
}

TypesofDistortionAudioProcessorEditor::~TypesofDistortionAudioProcessorEditor()
{
    outputGainSldr.setLookAndFeel(nullptr); //This components are using a custom LookAndFeel class that is destroyed when the Editor is still calling that class. So they need to be set to a nullptr to don't throw an exception
    dryWetSldr.setLookAndFeel(nullptr);
    cutoffSldr.setLookAndFeel(nullptr);
    distortionTypeMenu.setLookAndFeel(nullptr);
    filterTypeMenu.setLookAndFeel(nullptr);
}

//==============================================================================
void TypesofDistortionAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    //auto totalArea = getLocalBounds();
    //auto innerArea = totalArea.reduced(50);
    //auto halfLeftArea = innerArea.withWidth(innerArea.getWidth() / 2);
    //auto leftQuarterArea = innerArea.withWidth(innerArea.getWidth() / 4);
    //auto rightQuarterArea = innerArea.removeFromRight(innerArea.getWidth() / 4);
    //auto inputMeterArea = leftQuarterArea.withWidth(leftQuarterArea.getWidth() - 50);
    //auto outputMeterArea = rightQuarterArea.withWidth(rightQuarterArea.getWidth() - 50).withX(rightQuarterArea.getX() + 50);
    //auto leftComponentArea = halfLeftArea.removeFromRight(leftQuarterArea.getWidth());
    //auto rightComponentArea = innerArea.removeFromRight(rightQuarterArea.getWidth());
    //
    //g.setColour(juce::Colours::yellow);
    //g.drawRect(inputMeterArea);
    //g.drawRect(outputMeterArea);
    //
    //g.setColour(juce::Colours::aliceblue);
    //g.drawRect(leftComponentArea);
    //g.drawRect(rightComponentArea);
    wavesBackground = ImageCache::getFromMemory(BinaryData::_30_jpg, BinaryData::_30_jpgSize);
    g.drawImageWithin(wavesBackground, 0, 0, getWidth(), getHeight(), RectanglePlacement::stretchToFit);

    //juce::AffineTransform transform = juce::AffineTransform::scale(1.f).translated(-70, -30); // Scale 110%
    //g.drawImageTransformed(wavesBackground, transform);

}

void TypesofDistortionAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
  //  auto area = getWorkingArea();
  //  auto knobsArea = getKnobsArea();
  //  auto analyserArea = getAnalyserArea();
  //  auto menuArea = analyserArea.removeFromLeft(130);
  //  menuArea = menuArea.removeFromTop(40);


    auto area = getLocalBounds();

    guiPosition.setBounds(area);

    distortionTypeMenu.setBounds(guiPosition.getInnerArea().withSizeKeepingCentre(200, 30).withY(30));

    auto leftComponentPos = guiPosition.getLeftComponentArea();
   // leftComponentPos.removeFromRight(100);
    auto softClipPos = leftComponentPos.removeFromTop(200);
    softClipPos.removeFromRight(100);
    softClipGUI.setBounds(softClipPos); //Delete the with once I can move it with the mouse
    //softClipGUI.setBounds(80, 100, 200, 150);
    asymmetricalGUI.setBounds(leftComponentPos.removeFromLeft(100));
    //juce::Rectangle<int> getInputMeterArea();
    //juce::Rectangle<int> getOuputMeterArea();
    //juce::Rectangle<int> getLeftComponentArea();
    //juce::Rectangle<int> getRightComponentArea();
   // auto totalArea = getLocalBounds();
   // auto innerArea = totalArea.reduced(50);
   // auto halfLeftArea = innerArea.withWidth(innerArea.getWidth() / 2);
   // auto leftQuarterArea = innerArea.withWidth(innerArea.getWidth() / 4);
   // auto rightQuarterArea = innerArea.removeFromRight(innerArea.getWidth() / 4);
   // auto inputMeterArea = leftQuarterArea.withWidth(leftQuarterArea.getWidth() - 50);
   // auto outputMeterArea = rightQuarterArea.withWidth(rightQuarterArea.getWidth() - 50).withX(rightQuarterArea.getX() + 50);
   // auto leftComponentArea = halfLeftArea.removeFromRight(leftQuarterArea.getWidth());
   // auto rightComponentArea = innerArea.removeFromRight(rightQuarterArea.getWidth());
   // auto middlePointX = innerArea.getCentreX();
   // auto middlePointY = innerArea.getCentreY();

    auto hardClipGUIBounds = juce::Rectangle<int>(hardClipGUI.sliderWidth,
        hardClipGUI.sliderHeight)
        .withCentre(guiPosition.getCentre());

    hardClipGUI.setBounds(hardClipGUIBounds);


   // hardClipGUI.setBounds(middlePointX, middlePointY, 200, 200);
  //  softClipGUI.setBounds(leftComponentArea.removeFromTop(150));
    
   // auto softClipGUIPos = leftComponentArea.removeFromTop(150);
   // softClipGUI.setBounds(softClipGUIPos);

   //
    auto outputGainSldrPos = guiPosition.getRightComponentArea();
    outputGainSldrPos = outputGainSldrPos.removeFromBottom(100);
    outputGainSldrPos = outputGainSldrPos.translated(40, 0);
    outputGainSldr.setBounds(outputGainSldrPos);
    auto dryWetSldrPos = outputGainSldrPos.translated(-100, 0);
    dryWetSldr.setBounds(dryWetSldrPos);

    auto cutoffSldrPos = guiPosition.getRightComponentArea();
    cutoffSldrPos = cutoffSldrPos.removeFromTop(120);
    cutoffSldrPos = cutoffSldrPos.translated(40, 0);
    cutoffSldr.setBounds(cutoffSldrPos);

    auto filterTypeMenuPos = guiPosition.getRightComponentArea();
    filterTypeMenuPos = filterTypeMenuPos.removeFromTop(50);
    filterTypeMenuPos = filterTypeMenuPos.translated(-60, 20);
    filterTypeMenu.setBounds(filterTypeMenuPos);
   //
   // outputGainSldr.setSize(100, 100);
   //
   // Rectangle <int> outputSldrPos = outputGainSldr.getBounds();
   // int outPosX = outputSldrPos.getCentreX();
   // int outPosY = outputSldrPos.getCentreY();
   // outputGainText.setBounds((outPosX - 40), (outPosY + 50), 80, 15);
   //
    //auto distortionTypeMenuPos = guiPosition.getCentre();    

 ////   cutoffSldr.setBounds(rightComponentArea.removeFromLeft(150));
   // cutoffSldr.setSize(100, 100);
   // Rectangle <int> cutoffSldrPos = cutoffSldr.getBounds();
   // int cutPosX = cutoffSldrPos.getCentreX();
   // int cutPosY = cutoffSldrPos.getCentreY();
   // cutoffText.setBounds((cutPosX - 40), (cutPosY + 50), 80, 15);

     
    // filterTypeMenu.setSize(100, 40);

    //dryWetSldr.setBounds(rightComponentArea.removeFromBottom(150));
    //dryWetSldr.setBounds(rightComponentArea.removeFromLeft(150));
   
    //Rectangle <int> dryWetSldrPos = dryWetSldr.getBounds();
    //int dryPosX = dryWetSldrPos.getCentreX();
    //int dryPosY = dryWetSldrPos.getCentreY();
    //dryWetText.setBounds((dryPosX - 30), (dryPosY + 50), 60, 15);
    inputMeterL.setBounds(guiPosition.getInputMeterArea(0));
    inputMeterR.setBounds(guiPosition.getInputMeterArea(1));
    outputMeterL.setBounds(guiPosition.getOutputMeterArea(0));
    outputMeterR.setBounds(guiPosition.getOutputMeterArea(1));
    
}

void TypesofDistortionAudioProcessorEditor::sliderValueChanged(Slider* slider)
{

    if (slider == &outputGainSldr)
    {
        audioProcessor.setOutputGain(outputGainSldr.getValue());
    }
    
    else if (slider == &cutoffSldr)
    {
        audioProcessor.setFilterFreqCutoff(cutoffSldr.getValue());
    }
    
    else if (slider == &dryWetSldr)
    {
        audioProcessor.setDryWetAmount(dryWetSldr.getValue());
    }
}

void TypesofDistortionAudioProcessorEditor::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == &distortionTypeMenu)
    {
        if (distortionTypeMenu.getSelectedId() == 1) //Off
        {
            audioProcessor.setDistortionType(audioProcessor.Off);
            softClipGUI.softCurveSldr.setVisible(false);
            softClipGUI.softCurveText.setVisible(false);
            asymmetricalGUI.asymVariableSldr.setVisible(false);
            asymmetricalGUI.asymVariableText.setVisible(false);
        }

        else if (distortionTypeMenu.getSelectedId() == 2) //HardClipping
        {
            audioProcessor.setDistortionType(audioProcessor.HardClipType);
            softClipGUI.softCurveSldr.setVisible(false);
            softClipGUI.softCurveText.setVisible(false);
            asymmetricalGUI.asymVariableSldr.setVisible(false);
            asymmetricalGUI.asymVariableText.setVisible(false);
        }

        else if (distortionTypeMenu.getSelectedId() == 3) //SoftClipping
        {
            audioProcessor.setDistortionType(audioProcessor.SoftClipType); 
            softClipGUI.softCurveSldr.setVisible(true);
            softClipGUI.softCurveText.setVisible(true);
            asymmetricalGUI.asymVariableSldr.setVisible(false);
            asymmetricalGUI.asymVariableText.setVisible(false);
        }

        else if (distortionTypeMenu.getSelectedId() == 4) //QuarterCicle
        {
            audioProcessor.setDistortionType(audioProcessor.QuarterCicleType);
            softClipGUI.softCurveSldr.setVisible(false);
            softClipGUI.softCurveText.setVisible(false);
            asymmetricalGUI.asymVariableSldr.setVisible(false);
            asymmetricalGUI.asymVariableText.setVisible(false);
        }
       
        else if (distortionTypeMenu.getSelectedId() == 5) //Asymmetrical
        {
            audioProcessor.setDistortionType(audioProcessor.AsymmetricType);
            asymmetricalGUI.asymVariableSldr.setVisible(true);
            asymmetricalGUI.asymVariableText.setVisible(true);
            softClipGUI.softCurveSldr.setVisible(false);
            softClipGUI.softCurveText.setVisible(false);
        }
    }
    if (comboBoxThatHasChanged == &filterTypeMenu)
    {

        if (filterTypeMenu.getSelectedId() == 1) //LPF
        {
            audioProcessor.setFilterType(juce::dsp::StateVariableTPTFilterType::lowpass);
            cutoffSldr.setValue(20000);
        }

        else if (filterTypeMenu.getSelectedId() == 2) //HPF
        {
            audioProcessor.setFilterType(juce::dsp::StateVariableTPTFilterType::highpass);
            cutoffSldr.setValue(20);
        }
    }
}

void TypesofDistortionAudioProcessorEditor::mouseDoubleClick(const MouseEvent& event) //Doesnt Work
{
   // clippingGainSldr.setValue(1);
   // softCurveSldr.setValue(10);
   // asymVariableSldr.setValue(1.f);
   // outputGainSldr.setValue(1.f);
}