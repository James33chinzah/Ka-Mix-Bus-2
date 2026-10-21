#pragma once
#include <JuceHeader.h>
#include <juce_dsp/juce_dsp.h>

class BlackSaltBusMixCloneAudioProcessor : public juce::AudioProcessor
{
public:
    BlackSaltBusMixCloneAudioProcessor();
    ~BlackSaltBusMixCloneAudioProcessor() override = default;
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }
    const juce::String getName() const override { return "BlackSalt Bus Mix Clone"; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String&) override {}
    void getStateInformation(juce::MemoryBlock&) override;
    void setStateInformation(const void*, int) override;
    juce::AudioProcessorValueTreeState parameters;
private:
    juce::dsp::Compressor<float> compressor;
    juce::dsp::ProcessSpec spec{};
    juce::dsp::IIR::Filter<float> lowShelfL, lowShelfR, highShelfL, highShelfR;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BlackSaltBusMixCloneAudioProcessor)
};
