# 3.24.1 is bundled in Visual Studio 2022 v17.4
# 3.24.1 is also bundled in CLion as of 2023
cmake_minimum_required(VERSION 3.24.1)

# This is the name of your plugin (no spaces allowed)
set(PROJECT_NAME "CMakeARA")

# defines SourceFiles
include(cmake/SourceFiles.cmake)   

# Valid formats: AAX Unity VST AU AUv3 Standalone
set(FORMATS AU VST3 AUv3 Standalone)

# Reads in VERSION file and sticks in it CURRENT_VERSION variable
file(STRINGS VERSION CURRENT_VERSION)

# For simplicity, the name of the project is also the name of the target
project(${PROJECT_NAME} VERSION ${CURRENT_VERSION})


set(CMAKE_OSX_ARCHITECTURES arm64 x86_64)


set(CMAKE_OSX_DEPLOYMENT_TARGET "10.13" CACHE STRING "Support macOS down to High Sierra")

# Adds all the module sources so they appear correctly in the IDE
# Must be set before JUCE is added as a sub-dir (or any targets are made)
# https://github.com/juce-framework/JUCE/commit/6b1b4cf7f6b1008db44411f2c8887d71a3348889
set_property(GLOBAL PROPERTY USE_FOLDERS YES)


# JUCE is setup as a submodule in the /JUCE folder
add_subdirectory(submodules/JUCE)

juce_set_ara_sdk_path("submodules/ARA_SDK")

# Check the readme at `docs/CMake API.md` in the JUCE repo for full config
juce_add_plugin("${PROJECT_NAME}"
    # VERSION ...                               # Set this if the plugin version is different to the project version
    # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
    # ICON_SMALL ...
    COMPANY_NAME Recluse-Audio
    BUNDLE_ID com.recluseaudio.recluseaudio
    # IS_SYNTH TRUE/FALSE                       # Is this a synth or an effect?
    # NEEDS_MIDI_INPUT TRUE/FALSE               # Does the plugin need midi input?
    # NEEDS_MIDI_OUTPUT TRUE/FALSE              # Does the plugin need midi output?
    # IS_MIDI_EFFECT TRUE/FALSE                 # Is this plugin a MIDI effect?
    # EDITOR_WANTS_KEYBOARD_FOCUS TRUE/FALSE    # Does the editor need keyboard focus?
    COPY_PLUGIN_AFTER_BUILD TRUE # On MacOS, plugin will be copied to /Users/you/Library/Audio/Plug-Ins/
    PLUGIN_MANUFACTURER_CODE Recl               # This has to be one uppercase, rest lower for AU formats
    PLUGIN_CODE Recl                            # A unique four-character plugin id with at least one upper-case character
    FORMATS "${FORMATS}"
    PRODUCT_NAME "${PROJECT_NAME}"        # The name of the final executable, which can differ from the target name
    IS_ARA_EFFECT TRUE
    IS_PLUGIN_ARA_EFFECT TRUE

)

add_compile_definitions(JUCE_IS_ARA_EFFECT=1)
add_compile_definitions(JucePlugin_Enable_ARA=1)

juce_generate_juce_header(${PROJECT_NAME})

# C++20, please
target_compile_features("${PROJECT_NAME}" PRIVATE cxx_std_20)


target_include_directories(${PROJECT_NAME} 
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Source
        ${CMAKE_CURRENT_LIST_DIR}/Source/ARA

        # files created when you export from modified Projucer
        # todo - is there a way to not directly include this??
         ${CMAKE_CURRENT_LIST_DIR}/submodules/JUCE/modules/juce_audio_plugin_client/ARA

        ${CMAKE_CURRENT_LIST_DIR}/submodules/ARA_SDK
        ${CMAKE_CURRENT_LIST_DIR}/submodules/ARA_SDK/ARA_API
        ${CMAKE_CURRENT_LIST_DIR}/submodules/ARA_SDK/ARA_Library/PlugIn
)


set(ARASource submodules/JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_ARA.cpp)


target_sources("${PROJECT_NAME}" PRIVATE ${SourceFiles})
target_sources("${PROJECT_NAME}" PRIVATE ${ARASource})


# Set up Targets
foreach(target ${FORMATS} "All")
    if(TARGET ${PROJECT_NAME}_${target})
        set_target_properties(${PROJECT_NAME}_${target} PROPERTIES
            OSX_ARCHITECTURES "arm64;x86_64"    # Universal Binary
        )
    endif()
endforeach()



target_compile_definitions("${PROJECT_NAME}"
    PUBLIC
    # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
    JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
    JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
    JUCE_VST3_CAN_REPLACE_VST2=0)




# We'll need to link to these from our plugin as well as our tests
set(JUCE_DEPENDENCIES
    juce::juce_audio_utils
    juce::juce_core
    juce::juce_events
    juce::juce_graphics
    juce::juce_data_structures
    juce::juce_gui_basics
    juce::juce_gui_extra
    juce::juce_opengl
    juce::juce_audio_basics
    juce::juce_audio_devices
    juce::juce_audio_formats
    juce::juce_audio_processors
    juce::juce_audio_plugin_client
    juce::juce_audio_utils
    juce::juce_dsp)

target_link_libraries("${PROJECT_NAME}"
    PRIVATE
        ${JUCE_DEPENDENCIES}
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

# When present, use Intel IPP for performance on Windows
if(MSVC)
    find_package(IPP)
    if(IPP_FOUND)
        target_link_libraries("${PROJECT_NAME}" PUBLIC IPP::ipps IPP::ippcore IPP::ippi IPP::ippcv)
        message("IPP LIBRARIES FOUND")
        target_compile_definitions("${PROJECT_NAME}" PUBLIC PAMPLEJUCE_IPP=1)
    else()
        message("IPP LIBRARIES *NOT* FOUND")
    endif()
endif()


# "GLOBS ARE BAD" is brittle and silly dev UX, sorry CMake!
# CONFIGURE_DEPENDS / Clion's CMake integration makes globbing absolutely fine
file(GLOB_RECURSE TestFiles CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Tests/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/Tests/*.h")



# Use Catch2 v3 on the devel branch
Include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_PROGRESS TRUE
    GIT_SHALLOW TRUE
    GIT_TAG v3.1.0)
FetchContent_MakeAvailable(Catch2) # find_package equivalent

# Setup the test executable
add_executable(Tests ${TestFiles})

# Our test executable also wants to know about our plugin code...
target_compile_features(Tests PRIVATE cxx_std_20)
target_include_directories(Tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Source)
target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain "${PROJECT_NAME}" ${JUCE_DEPENDENCIES})


# Load and use the .cmake file provided by Catch2
# https://github.com/catchorg/Catch2/blob/devel/docs/cmake-integration.md
# We have to manually provide the source directory here for now
include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)
catch_discover_tests(Tests)

# Color our warnings and errors
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
   add_compile_options (-fdiagnostics-color=always)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
   add_compile_options (-fcolor-diagnostics)
endif ()



#add_custom_command(TARGET ${PROJECT_NAME}_Standalone
 #                  POST_BUILD
  #                 COMMAND open ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_artefacts/Debug/Standalone/${PROJECT_NAME}.app
   #                COMMENT "Launching Standalone app...")
