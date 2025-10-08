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
    hardClipGUI.setAlwaysOnTop(true);
    addAndMakeVisible(softClipGUI);
    softClipGUI.setAlwaysOnTop(true);
    //QuarterCicle
    asymmetricalGUI.setAlwaysOnTop(true);
    addAndMakeVisible(asymmetricalGUI);

    outputGainSldr.setSliderStyle(Slider::Rotary);
    outputGainSldr.setRange(0.f, 1.1f, 0.05);
    outputGainSldr.setValue(1.f);
    outputGainSldr.setTextBoxStyle(Slider::TextBoxAbove, true, 60, 15);
    //outputGainSldr.mouseDoubleClick(MouseEvent mouse);
    outputGainSldr.setLookAndFeel(&twentyTwoStepsLookAndFeel);
    outputGainSldr.setAlwaysOnTop(true);
    outputGainSldr.addListener(this);
    addAndMakeVisible(outputGainSldr);

    outputGainText.setText("Output Gain", dontSendNotification);
    //  outputGainText.setColour(Label::ColourIds::outlineColourId, Colours::wheat);
    addAndMakeVisible(outputGainText);
    
    cutoffSldr.setSliderStyle(Slider::Rotary);
    cutoffSldr.setRange(20, 20000, 1);
    cutoffSldr.setValue(20000);
    //cutoffSldr.setSkewFactorFromMidPoint(1000.0);
    cutoffSldr.setTextBoxStyle(Slider::TextBoxBelow, true, 60, 15);
    //cutoffSldr.mouseDoubleClick(MouseEvent mouse);
    cutoffSldr.setTextValueSuffix("Hz");
    cutoffSldr.setLookAndFeel(&twentyTwoStepsLookAndFeel);
    cutoffSldr.setAlwaysOnTop(true);
    cutoffSldr.addListener(this);
    addAndMakeVisible(cutoffSldr);

    cutoffText.setText("Cutoff Freq", dontSendNotification);
    //  cutoffText.setColour(Label::ColourIds::outlineColourId, Colours::wheat);
    addAndMakeVisible(cutoffText);

    dryWetSldr.setSliderStyle(Slider::Rotary);
    dryWetSldr.setRange(0, 100, 1);
    dryWetSldr.setValue(100);
    dryWetSldr.setTextBoxStyle(Slider::TextBoxAbove, true, 40, 15);
    //cutoffSldr.mouseDoubleClick(MouseEvent mouse);
    dryWetSldr.setTextValueSuffix("%");
    dryWetSldr.setLookAndFeel(&twentyTwoStepsLookAndFeel);
    dryWetSldr.setAlwaysOnTop(true);
    dryWetSldr.addListener(this);
    addAndMakeVisible(dryWetSldr);

    dryWetText.setText("Dry/Wet", dontSendNotification);
    //dryWetText.setColour(Label::ColourIds::outlineColourId, Colours::wheat);
    addAndMakeVisible(dryWetText);
    
    filterTypeMenu.addItem("LPF", 1);
    filterTypeMenu.addItem("HPF", 2);
    filterTypeMenu.setSelectedId(1, juce::dontSendNotification);
    filterTypeMenu.setText("Filter Type:", dontSendNotification);
    filterTypeMenu.setLookAndFeel(&invertedMenuLookAndFeel);
    filterTypeMenu.addListener(this);
    addAndMakeVisible(filterTypeMenu); 

    addAndMakeVisible(inputMeterL);
    addAndMakeVisible(inputMeterR);
    addAndMakeVisible(outputMeterL);
    addAndMakeVisible(outputMeterR);

    //The next text are labeling a slider that is living inside their own GUI class
    driveText.setText("DRIVE", dontSendNotification);
    driveText.setColour(Label::ColourIds::textColourId, Colours::palevioletred);
    addAndMakeVisible(driveText);

    curveSoftClipText.setText("Curve Intensity", dontSendNotification);
    curveSoftClipText.setMinimumHorizontalScale(0.6);
    addAndMakeVisible(curveSoftClipText);

    curveAsymmetricText.setText("Curve Intensity", dontSendNotification);
    curveAsymmetricText.setMinimumHorizontalScale(0.6);
    addAndMakeVisible(curveAsymmetricText);
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

    wavesBackground = ImageCache::getFromMemory(BinaryData::_30_jpg, BinaryData::_30_jpgSize);
    g.drawImageWithin(wavesBackground, 0, 0, getWidth(), getHeight(), RectanglePlacement::stretchToFit);
}

void TypesofDistortionAudioProcessorEditor::resized()
{
    auto area = getLocalBounds();

    guiPosition.setBounds(area);

    distortionTypeMenu.setBounds(guiPosition.getInnerArea().withSizeKeepingCentre(200, 30).withY(30));

    //Left Component is the half left area except the input meter
    auto leftComponentPos = guiPosition.getLeftComponentArea();
    auto softClipPos = leftComponentPos.removeFromTop(200);
    softClipPos.removeFromRight(100);
    softClipGUI.setBounds(softClipPos); //Delete the with once I can move it with the mouse
    
    juce::Rectangle<int> curveSoftClipTextPos = softClipPos.translated(0, 17);
    curveSoftClipText.setBounds(curveSoftClipTextPos);

    juce::Rectangle<int> curveAsymmetricTextPos = softClipPos.translated(13, 205);
    curveAsymmetricText.setBounds(curveAsymmetricTextPos);

    asymmetricalGUI.setBounds(leftComponentPos.removeFromLeft(100));
 
    //This is the central area where the Drive is going to be set
    auto hardClipGUIBounds = juce::Rectangle<int>(hardClipGUI.sliderWidth,
        hardClipGUI.sliderHeight)
        .withCentre(guiPosition.getCentre());

    hardClipGUI.setBounds(hardClipGUIBounds);
    juce::Rectangle<int> driveTextPos = hardClipGUIBounds.translated(50, 96);
    driveText.setBounds(driveTextPos);

    //Right Component is the half right area except the output meter
    auto outputGainSldrPos = guiPosition.getRightComponentArea();
    outputGainSldrPos = outputGainSldrPos.removeFromBottom(100);
    outputGainSldrPos = outputGainSldrPos.translated(40, 0);
    outputGainSldr.setBounds(outputGainSldrPos);

    juce::Rectangle<int> outputGainTextPos = outputGainSldrPos.translated(0, 62);
    outputGainText.setBounds(outputGainTextPos);

    auto dryWetSldrPos = outputGainSldrPos.translated(-100, 0);
    dryWetSldr.setBounds(dryWetSldrPos);

    juce::Rectangle<int> dryWetTextPos = dryWetSldrPos.translated(12, 62);
    dryWetText.setBounds(dryWetTextPos);


    auto cutoffSldrPos = guiPosition.getRightComponentArea();
    cutoffSldrPos = cutoffSldrPos.removeFromTop(120);
    cutoffSldrPos = cutoffSldrPos.translated(40, 0);
    cutoffSldr.setBounds(cutoffSldrPos);

    juce::Rectangle<int> cutoffTextPos = cutoffSldrPos.translated(0, -65);
    cutoffText.setBounds(cutoffTextPos);

    auto filterTypeMenuPos = guiPosition.getRightComponentArea();
    filterTypeMenuPos = filterTypeMenuPos.removeFromTop(50);
    filterTypeMenuPos = filterTypeMenuPos.translated(-60, 20);
    filterTypeMenu.setBounds(filterTypeMenuPos);
  
    //Meters area, most left for input and most right for output
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
            curveSoftClipText.setVisible(false);
            asymmetricalGUI.asymVariableSldr.setVisible(false);
            curveAsymmetricText.setVisible(false);
        }

        else if (distortionTypeMenu.getSelectedId() == 2) //HardClipping
        {
            audioProcessor.setDistortionType(audioProcessor.HardClipType);
            softClipGUI.softCurveSldr.setVisible(false);
            curveSoftClipText.setVisible(false);
            asymmetricalGUI.asymVariableSldr.setVisible(false);
            curveAsymmetricText.setVisible(false);
        }

        else if (distortionTypeMenu.getSelectedId() == 3) //SoftClipping
        {
            audioProcessor.setDistortionType(audioProcessor.SoftClipType); 
            softClipGUI.softCurveSldr.setVisible(true);
            curveSoftClipText.setVisible(true);
            asymmetricalGUI.asymVariableSldr.setVisible(false);
            curveAsymmetricText.setVisible(false);
        }

        else if (distortionTypeMenu.getSelectedId() == 4) //QuarterCicle
        {
            audioProcessor.setDistortionType(audioProcessor.QuarterCicleType);
            softClipGUI.softCurveSldr.setVisible(false);
            curveSoftClipText.setVisible(false);
            asymmetricalGUI.asymVariableSldr.setVisible(false);
            curveAsymmetricText.setVisible(false);
        }
       
        else if (distortionTypeMenu.getSelectedId() == 5) //Asymmetrical
        {
            audioProcessor.setDistortionType(audioProcessor.AsymmetricType);
            asymmetricalGUI.asymVariableSldr.setVisible(true);
            softClipGUI.softCurveSldr.setVisible(false);
            curveSoftClipText.setVisible(false);
            curveAsymmetricText.setVisible(true);
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