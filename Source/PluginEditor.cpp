#include "PluginEditor.h"
BlackSaltBusMixCloneAudioProcessorEditor::BlackSaltBusMixCloneAudioProcessorEditor(BlackSaltBusMixCloneAudioProcessor& p)
: AudioProcessorEditor(&p), processor(p)
{
    setSize(620,390);
    title.setText("BLACK SALT",juce::dontSendNotification);
    title.setFont(juce::Font(juce::FontOptions(30.f,juce::Font::bold)));
    title.setColour(juce::Label::textColourId,juce::Colour(0xffe5c78b));
    title.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(title);
    subtitle.setText("BUS MIX  •  STEREO GLUE / TONE",juce::dontSendNotification);
    subtitle.setFont(juce::Font(juce::FontOptions(12.f)));
    subtitle.setColour(juce::Label::textColourId,juce::Colours::lightgrey);
    subtitle.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(subtitle);
    juce::Slider* sliders[]={&threshold,&ratio,&attack,&release,&makeup,&mix,&drive,&low,&high};
    const char* names[]={"THRESHOLD","RATIO","ATTACK","RELEASE","MAKEUP","MIX","WARMTH","LOW SHELF","HIGH SHELF"};
    const char* ids[]={"threshold","ratio","attack","release","makeup","mix","drive","low","high"};
    for(int i=0;i<9;++i){
        sliders[i]->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        sliders[i]->setTextBoxStyle(juce::Slider::TextBoxBelow,false,72,20);
        sliders[i]->setColour(juce::Slider::rotarySliderFillColourId,juce::Colour(0xffc49a55));
        sliders[i]->setColour(juce::Slider::thumbColourId,juce::Colour(0xfff2e4c5));
        addAndMakeVisible(*sliders[i]);
        labels[i].setText(names[i],juce::dontSendNotification);
        labels[i].setJustificationType(juce::Justification::centred);
        labels[i].setColour(juce::Label::textColourId,juce::Colours::white);
        labels[i].setFont(juce::Font(juce::FontOptions(10.f,juce::Font::bold)));
        addAndMakeVisible(labels[i]);
        attachments[i]=std::make_unique<Attachment>(processor.parameters,ids[i],*sliders[i]);
    }
}
void BlackSaltBusMixCloneAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(0xff171717));
    g.setColour(juce::Colour(0xff3a3327)); g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(8),12.f,1.5f);
    g.setColour(juce::Colour(0xffc49a55)); g.drawLine(28.f,78.f,592.f,78.f,1.f);
}
void BlackSaltBusMixCloneAudioProcessorEditor::resized()
{
    title.setBounds(20,10,580,42); subtitle.setBounds(20,48,580,22);
    juce::Slider* sliders[]={&threshold,&ratio,&attack,&release,&makeup,&mix,&drive,&low,&high};
    for(int i=0;i<9;++i){ int col=i%5, row=i/5; int x=18+col*118; int y=92+row*143;
        sliders[i]->setBounds(x,y,108,105); labels[i].setBounds(x,y+102,108,20);
    }
}
