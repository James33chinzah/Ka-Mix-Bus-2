#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class BlackSaltBusMixCloneAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit BlackSaltBusMixCloneAudioProcessorEditor(BlackSaltBusMixCloneAudioProcessor&);
    void paint(juce::Graphics&) override;
    void resized() override;
private:
    BlackSaltBusMixCloneAudioProcessor& processor;
    juce::Label title, subtitle;
    juce::Slider threshold, ratio, attack, release, makeup, mix, drive, low, high;
    juce::Label labels[9];
    using Attachment=juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<Attachment> attachments[9];
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BlackSaltBusMixCloneAudioProcessorEditor)
};
