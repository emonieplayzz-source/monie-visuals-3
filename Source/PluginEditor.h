#pragma once
#include "PluginProcessor.h"
#include "UI/PreviewComponent.h"

// TEMPORARY minimal editor used while the full premium UI is being built (see docs/V3_STATUS.md for what exists today).
class MonieEditor : public juce::AudioProcessorEditor, private juce::Timer
{
public:
    explicit MonieEditor (MonieProcessor&);
    ~MonieEditor() override;
    void resized() override;
    void paint (juce::Graphics& g) override { g.fillAll (juce::Colours::black); }
private:
    void timerCallback() override;
    MonieProcessor& proc;
    PreviewComponent preview;
    int shotStage = 0; juce::String shotDir;
};
