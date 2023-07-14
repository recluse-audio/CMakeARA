
# This is a variable called 'JuceARAFiles' that represents a necessary include
# Seems overkill, but it maintains a neater looking CMakeLists.txt
# Either I will expand and use this for other includes, or find a way to avoid doing this without upsetting my CMakeLists.txt aesthetic

set(JuceARAFiles 
    submodules/JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_ARA.cpp
)
