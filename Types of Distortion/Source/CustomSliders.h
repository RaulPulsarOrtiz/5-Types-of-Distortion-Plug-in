/*
  ==============================================================================

    CustomSliders.h
    Created: 12 Sep 2025 6:38:38pm
    Author:  Raul

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

/** Class to take the knob images strip */

class FilmStripSlider
{
public:
    FilmStripSlider(juce::Image* _knobStrip, int _frameCount, int _frameSize, bool _isVerticalStrip);
    ~FilmStripSlider() {}

    /** This function workout the minimum and maximum values of the slider and it shows the corresponding frame of the image strip based on the current value */
    void drawFrame(juce::Graphics& g, int x, int y, int width, int height, juce::Slider& slider);

private:
    /** This image is a strip of the different images of the slider with every different value  */
    juce::Image* knobStrip = nullptr;

    /** Number of frame values on the slider */
    int frameCount = 0;

    /** Width of the image */
    int frameSize = 0;

    /** If that image is vertical or horizontal */
    bool isVerticalStrip = true;
};

/** Custom LookAndFeel class for delayTime and Feedback sliders */
class LookAndFeelDistortion : public juce::LookAndFeel_V4
{
public:
    LookAndFeelDistortion() //On the constructor we set up some default colours for different parts of the GUI
    {

    }
    ~LookAndFeelDistortion() {}

    /** Get Image (binary data) from memory
    * @param BinaryData::BinaryData::attackKnob_png is the Binary Data of image for the Attack and Release sliders
    * @param BinaryData::attackKnob_pngSize is the size of the frame of each slider image in the strip
    */
    Image knobDistort7Strip = ImageCache::getFromMemory(BinaryData::Distortion7Steps_png, BinaryData::Distortion7Steps_pngSize);

    /** This funcion draws the slider image for the delayTime and feedback, instead of drawing a standard JUCE slider */
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle,
        const float rotaryEndAngle, juce::Slider&) override; // (x, y, width, height) are passing from the slider's resize() function. 
                                                             //sliderPost is where the slider is from 0 to 1.
                                                             // rotaryAngle is the angle in radiants from the center of the slider to the start position or to the end position
};

/** Custom LookAndFeel class for delayTime and Feedback sliders */
class LookAndFeel22Steps : public juce::LookAndFeel_V4
{
public:
    LookAndFeel22Steps() //On the constructor we set up some default colours for different parts of the GUI
    {

    }
    ~LookAndFeel22Steps() {}

    /** Get Image (binary data) from memory
    * @param BinaryData::BinaryData::attackKnob_png is the Binary Data of image for the Attack and Release sliders
    * @param BinaryData::attackKnob_pngSize is the size of the frame of each slider image in the strip
    */
    Image knobDistort22Strip = ImageCache::getFromMemory(BinaryData::OutputGain221_png, BinaryData::OutputGain221_pngSize);

    /** This funcion draws the slider image for the delayTime and feedback, instead of drawing a standard JUCE slider */
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle,
        const float rotaryEndAngle, juce::Slider&) override; // (x, y, width, height) are passing from the slider's resize() function. 
                                                             //sliderPost is where the slider is from 0 to 1.
                                                             // rotaryAngle is the angle in radiants from the center of the slider to the start position or to the end position
};

struct MenuLookAndFeel : public juce::LookAndFeel_V4
{
    // --- ComboBox (the closed box) ---
    void drawComboBox(juce::Graphics& g, int width, int height, bool isButtonDown,
        int buttonX, int buttonY, int buttonW, int buttonH,
        juce::ComboBox& box) override
    {
        auto bounds = juce::Rectangle<int>(0, 0, width, height);

        // Background
        g.setColour(isButtonDown
            ? juce::Colours::darkgrey.darker(0.2f)
            : juce::Colours::darkgrey.brighter(0.1f));
        g.fillRoundedRectangle(bounds.toFloat(), 4.0f);

        // Border
        g.setColour(juce::Colours::black);
        g.drawRoundedRectangle(bounds.toFloat(), 4.0f, 2.0f);

        // Arrow
        juce::Path p;
        float arrowW = 10.0f, arrowH = 6.0f;
        float cx = buttonX + buttonW * 0.5f;
        float cy = buttonY + buttonH * 0.5f;

        p.addTriangle(cx - arrowW * 0.5f, cy - arrowH * 0.5f,
            cx + arrowW * 0.5f, cy - arrowH * 0.5f,
            cx, cy + arrowH * 0.5f);

        // Fill the triangle with same yellow as text outline
        g.setColour(juce::Colours::yellow);
        g.fillPath(p);

        // --- Draw the selected item text with yellow outline ---
        auto text = box.getText();
        auto font = juce::Font(18.0f, juce::Font::bold);
        g.setFont(font);

        juce::Rectangle<int> textBounds(2, 2, width - 20, height - 4);

        // Draw outline by painting text offset in 8 directions
        g.setColour(juce::Colours::yellow);
        for (int dx = -1; dx <= 1; ++dx)
            for (int dy = -1; dy <= 1; ++dy)
                if (dx != 0 || dy != 0)
                    g.drawFittedText(text, textBounds.translated(dx, dy),
                        juce::Justification::centred, 1);

        // Draw main text
        g.setColour(juce::Colours::black);
        g.drawFittedText(text, textBounds, juce::Justification::centred, 1);
    }

    void positionComboBoxText(juce::ComboBox& box, juce::Label& label) override
    {
        label.setBounds(2, 2, box.getWidth() - 20, box.getHeight() - 4);
        label.setFont(juce::Font(18.0f, juce::Font::bold));
        label.setJustificationType(juce::Justification::centred);
        label.setColour(juce::Label::textColourId, juce::Colours::black);
    }

    // --- PopupMenu (the dropdown list) ---
    void drawPopupMenuBackground(juce::Graphics& g, int width, int height) override
    {
        g.fillAll(juce::Colours::dimgrey); // calculator dark background
    }

    void drawPopupMenuItem(juce::Graphics& g, const juce::Rectangle<int>& area,
        bool isSeparator, bool isActive, bool isHighlighted,
        bool isTicked, bool hasSubMenu,
        const juce::String& text,
        const juce::String& shortcutKeyText,
        const juce::Drawable* icon, const juce::Colour* textColour) override
    {
        if (isSeparator)
        {
            g.setColour(juce::Colours::darkgrey);
            g.fillRect(area.reduced(4, area.getHeight() / 2 - 1).withHeight(2));
            return;
        }

        // --- Background: dark normally, lighter on hover ---
        auto bg = isHighlighted ? juce::Colours::grey.brighter(0.2f) : juce::Colours::grey.darker(0.2f);
        g.setColour(bg);
        g.fillRoundedRectangle(area.toFloat().reduced(2.0f), 4.0f);

        // --- Noise overlay (more noticeable) ---
        juce::Random rng;
        g.setColour(juce::Colours::black.withAlpha(0.08f)); // stronger specks

        int w = area.getWidth();
        int h = area.getHeight();

        for (int i = 0; i < w * h / 10; ++i) // density control
        {
            int x = area.getX() + rng.nextInt(w);
            int y = area.getY() + rng.nextInt(h);
            g.fillRect(x, y, 1, 1);
        }

        // --- Border ---
        g.setColour(juce::Colours::black);
        g.drawRoundedRectangle(area.toFloat().reduced(2.0f), 4.0f, 2.0f);

        // --- Text with orange outline ---
        juce::Font font(18.0f, juce::Font::bold);
        g.setFont(font);

        juce::Rectangle<int> textBounds = area.reduced(6);

        juce::Colour outline = juce::Colours::orange.brighter(0.8f);

        // Draw outline by offsetting in 8 directions
        for (int dx = -1; dx <= 1; ++dx)
            for (int dy = -1; dy <= 1; ++dy)
                if (dx != 0 || dy != 0)
                {
                    g.setColour(outline);
                    g.drawFittedText(text, textBounds.translated(dx, dy),
                        juce::Justification::centred, 1);
                }

        // Main text in black
        g.setColour(juce::Colours::black);
        g.drawFittedText(text, textBounds, juce::Justification::centred, 1);
    }
};

struct InvertedMenuLookAndFeel : public juce::LookAndFeel_V4
{
    // --- ComboBox (closed state) ---
    void drawComboBox(juce::Graphics& g, int width, int height, bool isButtonDown,
        int buttonX, int buttonY, int buttonW, int buttonH,
        juce::ComboBox& box) override
    {
        auto bounds = juce::Rectangle<int>(0, 0, width, height);

        // Light background instead of dark
        g.setColour(isButtonDown
            ? juce::Colours::lightgrey.darker(0.1f)
            : juce::Colours::lightgrey.brighter(0.1f));
        g.fillRoundedRectangle(bounds.toFloat(), 4.0f);

        // Dark outline
        g.setColour(juce::Colours::black);
        g.drawRoundedRectangle(bounds.toFloat(), 4.0f, 2.0f);

        // Arrow
        juce::Path p;
        float arrowW = 10.0f, arrowH = 6.0f;
        float cx = buttonX + buttonW * 0.5f;
        float cy = buttonY + buttonH * 0.5f;

        p.addTriangle(cx - arrowW * 0.5f, cy - arrowH * 0.5f,
            cx + arrowW * 0.5f, cy - arrowH * 0.5f,
            cx, cy + arrowH * 0.5f);

        g.setColour(juce::Colours::black);
        g.fillPath(p);
    }

    void positionComboBoxText(juce::ComboBox& box, juce::Label& label) override
    {
        label.setBounds(2, 2, box.getWidth() - 20, box.getHeight() - 4);
        label.setFont(juce::Font(18.0f, juce::Font::bold));
        label.setJustificationType(juce::Justification::centred);
        label.setColour(juce::Label::textColourId, juce::Colours::black);
    }

    // --- PopupMenu (dropdown) ---
    void drawPopupMenuBackground(juce::Graphics& g, int width, int height) override
    {
        g.fillAll(juce::Colours::lightgrey);
    }

    void drawPopupMenuItem(juce::Graphics& g, const juce::Rectangle<int>& area,
        bool isSeparator, bool isActive, bool isHighlighted,
        bool isTicked, bool hasSubMenu,
        const juce::String& text,
        const juce::String& shortcutKeyText,
        const juce::Drawable* icon, const juce::Colour* textColour) override
    {
        if (isSeparator)
        {
            g.setColour(juce::Colours::darkgrey);
            g.fillRect(area.reduced(4, area.getHeight() / 2 - 1).withHeight(2));
            return;
        }

        auto bg = isHighlighted ? juce::Colours::white : juce::Colours::lightgrey;
        g.setColour(bg);
        g.fillRoundedRectangle(area.toFloat().reduced(2.0f), 4.0f);

        g.setColour(juce::Colours::black);
        g.drawRoundedRectangle(area.toFloat().reduced(2.0f), 4.0f, 2.0f);

        g.setColour(textColour != nullptr ? *textColour : juce::Colours::black);
        g.setFont(juce::Font(18.0f, juce::Font::bold));
        g.drawFittedText(text, area.reduced(6), juce::Justification::centred, 1);
    }
};