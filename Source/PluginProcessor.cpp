#include "PluginProcessor.h"
#include "PluginEditor.h"

BlackSaltBusMixCloneAudioProcessor::BlackSaltBusMixCloneAudioProcessor()
: AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true)
                                  .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
  parameters(*this, nullptr, "PARAMETERS", createParameterLayout()) {}

juce::AudioProcessorValueTreeState::ParameterLayout BlackSaltBusMixCloneAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout p;
    p.add(std::make_unique<juce::AudioParameterFloat>("threshold","Threshold",juce::NormalisableRange<float>(-36.f,0.f,0.1f),-12.f));
    p.add(std::make_unique<juce::AudioParameterFloat>("ratio","Ratio",juce::NormalisableRange<float>(1.f,8.f,0.1f),2.f));
    p.add(std::make_unique<juce::AudioParameterFloat>("attack","Attack",juce::NormalisableRange<float>(1.f,100.f,0.1f),20.f));
    p.add(std::make_unique<juce::AudioParameterFloat>("release","Release",juce::NormalisableRange<float>(20.f,500.f,1.f),150.f));
    p.add(std::make_unique<juce::AudioParameterFloat>("makeup","Makeup",juce::NormalisableRange<float>(-6.f,12.f,0.1f),0.f));
    p.add(std::make_unique<juce::AudioParameterFloat>("mix","Mix",juce::NormalisableRange<float>(0.f,100.f,1.f),100.f));
    p.add(std::make_unique<juce::AudioParameterFloat>("drive","Warmth",juce::NormalisableRange<float>(0.f,6.f,0.1f),1.f));
    p.add(std::make_unique<juce::AudioParameterFloat>("low","Low Shelf",juce::NormalisableRange<float>(-6.f,6.f,0.1f),0.f));
    p.add(std::make_unique<juce::AudioParameterFloat>("high","High Shelf",juce::NormalisableRange<float>(-6.f,6.f,0.1f),0.f));
    return p;
}
void BlackSaltBusMixCloneAudioProcessor::prepareToPlay(double sr,int block)
{
    spec = { sr, (juce::uint32)block, (juce::uint32)getTotalNumOutputChannels() };
    compressor.prepare(spec);
    compressor.setAttack(20.f); compressor.setRelease(150.f);
    auto coeffLow=juce::dsp::IIR::Coefficients<float>::makeLowShelf(sr,120.f,0.707f,1.f);
    auto coeffHigh=juce::dsp::IIR::Coefficients<float>::makeHighShelf(sr,8000.f,0.707f,1.f);
    *lowShelfL.coefficients=*coeffLow; *lowShelfR.coefficients=*coeffLow;
    *highShelfL.coefficients=*coeffHigh; *highShelfR.coefficients=*coeffHigh;
    lowShelfL.reset();lowShelfR.reset();highShelfL.reset();highShelfR.reset();
}
void BlackSaltBusMixCloneAudioProcessor::releaseResources() {}
bool BlackSaltBusMixCloneAudioProcessor::isBusesLayoutSupported(const BusesLayout& l) const
{
    return l.getMainInputChannelSet()==juce::AudioChannelSet::stereo()
        && l.getMainOutputChannelSet()==juce::AudioChannelSet::stereo();
}
void BlackSaltBusMixCloneAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer,juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    auto n=buffer.getNumSamples();
    juce::AudioBuffer<float> dry(buffer);
    compressor.setThreshold(*parameters.getRawParameterValue("threshold"));
    compressor.setRatio(*parameters.getRawParameterValue("ratio"));
    compressor.setAttack(*parameters.getRawParameterValue("attack"));
    compressor.setRelease(*parameters.getRawParameterValue("release"));
    auto low=*parameters.getRawParameterValue("low"), high=*parameters.getRawParameterValue("high");
    auto sr=getSampleRate();
    auto lc=juce::dsp::IIR::Coefficients<float>::makeLowShelf(sr,120.f,0.707f,juce::Decibels::decibelsToGain(low));
    auto hc=juce::dsp::IIR::Coefficients<float>::makeHighShelf(sr,8000.f,0.707f,juce::Decibels::decibelsToGain(high));
    *lowShelfL.coefficients=*lc; *lowShelfR.coefficients=*lc;
    *highShelfL.coefficients=*hc; *highShelfR.coefficients=*hc;
    for(int ch=0; ch<buffer.getNumChannels(); ++ch) {
        auto* x=buffer.getWritePointer(ch);
        for(int i=0;i<n;++i) {
            float v=x[i];
            v=(ch==0?lowShelfL:lowShelfR).processSample(v);
            v=(ch==0?highShelfL:highShelfR).processSample(v);
            float drive=juce::Decibels::decibelsToGain(*parameters.getRawParameterValue("drive"));
            v=std::tanh(v*drive)/std::tanh(drive);
            x[i]=v;
        }
    }
    juce::dsp::AudioBlock<float> blockAudio(buffer);
    juce::dsp::ProcessContextReplacing<float> context(blockAudio);
    compressor.process(context);
    float makeup=juce::Decibels::decibelsToGain(*parameters.getRawParameterValue("makeup"));
    float wet=*parameters.getRawParameterValue("mix")/100.f;
    for(int ch=0;ch<buffer.getNumChannels();++ch) {
        auto* w=buffer.getWritePointer(ch); const auto* d=dry.getReadPointer(ch);
        for(int i=0;i<n;++i) w[i]=d[i]*(1.f-wet)+w[i]*makeup*wet;
    }
}
void BlackSaltBusMixCloneAudioProcessor::getStateInformation(juce::MemoryBlock& dest)
{
    auto state=parameters.copyState(); std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml,dest);
}
void BlackSaltBusMixCloneAudioProcessor::setStateInformation(const void* data,int size)
{
    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data,size));
    if(xml && xml->hasTagName(parameters.state.getType())) parameters.replaceState(juce::ValueTree::fromXml(*xml));
}
juce::AudioProcessorEditor* BlackSaltBusMixCloneAudioProcessor::createEditor()
{ return new BlackSaltBusMixCloneAudioProcessorEditor(*this); }
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{ return new BlackSaltBusMixCloneAudioProcessor(); }
