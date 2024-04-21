/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class SimpleEQPluginAudioProcessor : public juce::AudioProcessor
{
public:
    //==============================================================================
    SimpleEQPluginAudioProcessor();
    ~SimpleEQPluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    const juce::String getName() const override { return JucePlugin_Name; }
    bool hasEditor() const override { return false; }
    //juce::AudioProcessorEditor* createEditor() override { return new GananciaPluginAudioProcessorEditor(*this); }
    juce::AudioProcessorEditor* createEditor() override { return new juce::GenericAudioProcessorEditor(*this); }

    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    //==============================================================================
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String&) override {}

    //==============================================================================
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

private:
    juce::AudioParameterFloat* lowCutFreq;
    juce::AudioParameterFloat* highCutFreq;
    juce::AudioParameterFloat* peakFreq;
    juce::AudioParameterFloat* peakGain;
    juce::AudioParameterFloat* peakQuality;
    juce::AudioParameterChoice* lowCutSlope;
    juce::AudioParameterChoice* highCutSlope;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SimpleEQPluginAudioProcessor)
};
