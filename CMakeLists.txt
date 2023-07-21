# 3.24.1 is bundled in Visual Studio 2022 v17.4
# 3.24.1 is also bundled in CLion as of 2023
cmake_minimum_required(VERSION 3.24.1)

project(CMake_ARA VERSION 0.0.1)


# JUCE is setup as a submodule in the /JUCE folder
add_subdirectory(submodules/JUCE)

# Set path(s) before adding targets via 'add_plugin' below
juce_set_ara_sdk_path("submodules/ARA_SDK")

set(PLUGIN_FORMATS "AU VST3 Standalone" CACHE STRING "Formats to be built as part of target")
message(STATUS "PLUGIN_FORMATS: ${PLUGIN_FORMATS}")

# Check the readme at `docs/CMake API.md` in the JUCE repo
juce_add_plugin(CMakeARA
    COMPANY_NAME recluse-audio
    BUNDLE_ID com.recluseaudio.recluseaudio
    COPY_PLUGIN_AFTER_BUILD TRUE          # On MacOS, plugin will be copied to /Users/you/Library/Audio/Plug-Ins/
    PLUGIN_MANUFACTURER_CODE Recl         # This has to be one uppercase, rest lower for AU formats
    PLUGIN_CODE Cara           
    FORMATS ${PLUGIN_FORMATS}
    PRODUCT_NAME "CMakeARA"        # The name of the final executable, which can differ from the target name
    IS_ARA_EFFECT TRUE
    IS_PLUGIN_ARA_EFFECT TRUE
)

add_compile_definitions(JUCE_IS_ARA_EFFECT=1)
add_compile_definitions(JucePlugin_Enable_ARA=1)

include(cmake/SourceFiles.cmake)   # defines ${SourceFiles}
include(cmake/JuceARAFiles.cmake)  # defines ${JuceARAFiles}

target_sources(CMakeARA PRIVATE ${SourceFiles})
target_sources(CMakeARA PRIVATE ${JuceARAFiles})

target_include_directories(CMakeARA
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Source
        ${CMAKE_CURRENT_LIST_DIR}/Source/ARA

         ${CMAKE_CURRENT_LIST_DIR}/submodules/JUCE/modules/juce_audio_plugin_client/ARA

        ${CMAKE_CURRENT_LIST_DIR}/submodules/ARA_SDK
        ${CMAKE_CURRENT_LIST_DIR}/submodules/ARA_SDK/ARA_API
        ${CMAKE_CURRENT_LIST_DIR}/submodules/ARA_SDK/ARA_Library/PlugIn
)


include(cmake/JuceDependencies.cmake) # defines ${JuceDependencies}
include(cmake/JuceFlags.cmake) # defines ${JuceFlags}

target_link_libraries(CMakeARA
    PRIVATE
        ${JuceDependencies}
    PUBLIC
        ${JuceFlags}
)

juce_generate_juce_header(CMakeARA)




# C++20, please
target_compile_features(CMakeARA PRIVATE cxx_std_20)


target_compile_definitions(CMakeARA
    PUBLIC
    # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
    JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
    JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
    JUCE_VST3_CAN_REPLACE_VST2=0
    )

# Generate debug symbols (TODO: Make this debug only?)    
target_compile_options(CMakeARA PRIVATE -g)


# Use Catch2 v3 on the devel branch
Include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_PROGRESS TRUE
    GIT_SHALLOW TRUE
    GIT_TAG v3.1.0)
FetchContent_MakeAvailable(Catch2) # find_package equivalent

include(cmake/TestFiles.cmake) # Defines ${TestFiles}
add_executable(Tests ${TestFiles}) # Setup the test executable


# Our test executable also wants to know about our plugin code...
target_compile_features(Tests PRIVATE cxx_std_20)
target_include_directories(Tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Source)
target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain CMakeARA ${JuceDependencies})


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


# When present, use Intel IPP for performance on Windows
if(MSVC)
    find_package(IPP)
    if(IPP_FOUND)
        target_link_libraries(CMakeARA PUBLIC IPP::ipps IPP::ippcore IPP::ippi IPP::ippcv)
        message("IPP LIBRARIES FOUND")
        target_compile_definitions(CMakeARA PUBLIC PAMPLEJUCE_IPP=1)
    else()
        message("IPP LIBRARIES *NOT* FOUND")
    endif()
endif()


#add_custom_command(TARGET ${PROJECT_NAME}_Standalone
 #                  POST_BUILD
  #                 COMMAND open ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_artefacts/Debug/Standalone/${PROJECT_NAME}.app
   #                COMMENT "Launching Standalone app...")
