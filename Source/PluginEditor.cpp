#include "PluginEditor.h"
MonieEditor::MonieEditor (MonieProcessor& p) : juce::AudioProcessorEditor (p), proc (p), preview (p)
{
    addAndMakeVisible (preview); setResizable (true, true); setResizeLimits (640, 400, 4096, 2400); setSize (1280, 760);
    shotDir = juce::SystemStats::getEnvironmentVariable ("MONIE_SELFTEST", "");
    startTimerHz (4);
}
MonieEditor::~MonieEditor() { stopTimer(); }
void MonieEditor::resized() { preview.setBounds (getLocalBounds()); }
void MonieEditor::timerCallback()
{
    if (shotDir.isEmpty()) return;
    auto status = preview.status();
    if (preview.comp().thumbsReady() >= monie::kNumScenes && shotStage == 0)
    {
        shotStage = 1;
        const int cols = 6, rows = 5, tw = 256, th = 144;
        juce::Image sheet (juce::Image::ARGB, cols * tw, rows * th, true); juce::Graphics g (sheet);
        for (int i = 0; i < monie::kNumScenes; ++i)
        {
            auto t = preview.comp().sceneThumb (i); const int x = (i % cols) * tw, y = (i / cols) * th;
            g.drawImageAt (t, x, y); g.setColour (juce::Colours::black.withAlpha (.6f)); g.fillRect (x, y, tw, 16); g.setColour (juce::Colours::white); g.setFont (12.f);
            g.drawText (juce::String (i) + " " + monie::sceneCatalogue()[(size_t) i].name, x + 3, y, tw - 6, 16, juce::Justification::centredLeft);
        }
        juce::File out (shotDir + "/contact.png"); out.deleteFile(); juce::FileOutputStream fo (out); juce::PNGImageFormat().writeImageToStream (sheet, fo);
        juce::File (shotDir + "/status.txt").replaceWithText ("shaderError:\n" + status.shaderError + "\ngpu: " + status.gpu + "\n");
        std::fprintf (stderr, "SELFTEST: contact sheet written\n");
    }
}
