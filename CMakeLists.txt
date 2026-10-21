cmake_minimum_required(VERSION 3.22)
project(BlackSaltBusMixClone VERSION 1.0.0)

include(FetchContent)
FetchContent_Declare(JUCE
  GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
  GIT_TAG 8.0.6
  GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(JUCE)

juce_add_plugin(BlackSaltBusMixClone
    COMPANY_NAME "StudioTools"
    BUNDLE_ID "com.studiotools.blacksaltbusmixclone"
    PLUGIN_MANUFACTURER_CODE StTl
    PLUGIN_CODE BsMx
    FORMATS VST3 Standalone
    PRODUCT_NAME "BlackSalt Bus Mix Clone"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
)
target_sources(BlackSaltBusMixClone PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h
)
target_compile_features(BlackSaltBusMixClone PRIVATE cxx_std_17)
target_compile_definitions(BlackSaltBusMixClone PUBLIC
    JUCE_WEB_BROWSER=0 JUCE_USE_CURL=0 JUCE_VST3_CAN_REPLACE_VST2=0)
target_link_libraries(BlackSaltBusMixClone PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp
    PUBLIC juce::juce_recommended_config_flags
           juce::juce_recommended_lto_flags
           juce::juce_recommended_warning_flags)
