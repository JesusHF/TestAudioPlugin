/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleEQPluginAudioProcessor::SimpleEQPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    )
#endif
{
    addParameter(lowCutFreq = new juce::AudioParameterFloat(
        "lowCutFreq",
        "LowCut Freq",
        juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 1.f),
        20.f));

    addParameter(highCutFreq = new juce::AudioParameterFloat(
        "highCutFreq",
        "HighCut Freq",
        juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 1.f),
        20000.f));

    addParameter(peakFreq = new juce::AudioParameterFloat(
        "peakFreq",
        "Peak Freq",
        juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 1.f),
        750.f));

    addParameter(peakGain = new juce::AudioParameterFloat(
        "peakGain",
        "Peak Gain",
        juce::NormalisableRange<float>(-24.f, 24, 0.5f, 1.1f),
        0.0f));

    addParameter(peakQuality = new juce::AudioParameterFloat(
        "peakQuality",
        "Peak Quality",
        juce::NormalisableRange<float>(0.1f, 10.f, 0.05f, 1.f),
        1.f));

    juce::StringArray stringArray;
    for (int i = 0; i < 4; i++)
    {
        juce::String s;
        s << (12 + i * 12);
        s << " db/Oct";
        stringArray.add(s);
    }

    addParameter(lowCutSlope = new juce::AudioParameterChoice("lowCutSlope", "LowCut Slope", stringArray, 0));
    addParameter(highCutSlope = new juce::AudioParameterChoice("highCutSlope", "HighCut Slope", stringArray, 0));
}

SimpleEQPluginAudioProcessor::~SimpleEQPluginAudioProcessor()
{
}

//==============================================================================
void SimpleEQPluginAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void SimpleEQPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SimpleEQPluginAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    const auto& mainInLayout = layouts.getChannelSet(true, 0);
    const auto& mainOutLayout = layouts.getChannelSet(false, 0);
    return (mainInLayout == mainOutLayout && (!mainInLayout.isDisabled()));
}
#endif

void SimpleEQPluginAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        // ..do something to the data...
    }
}

//==============================================================================
void SimpleEQPluginAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
}

void SimpleEQPluginAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleEQPluginAudioProcessor();
}
