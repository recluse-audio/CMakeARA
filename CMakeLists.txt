# 3.24.1 is bundled in Visual Studio 2022 v17.4
# 3.24.1 is also bundled in CLion as of 2023
cmake_minimum_required(VERSION 3.24.1)

set(Plugin_Name "CMakeARA")

project(${Plugin_Name} VERSION 0.0.1)


# JUCE is setup as a submodule in the /JUCE folder
add_subdirectory(submodules/JUCE)

# Set path(s) before adding targets via 'add_plugin' below
juce_set_ara_sdk_path("submodules/ARA_SDK")

set(CMAKE_OSX_ARCHITECTURES arm64 x86_64)

set(Plugin_Formats AU VST3 Standalone CACHE STRING "Formats to be built as part of target")
message(STATUS "PLUGIN_FORMATS: ${Plugin_Formats}")

# Check the readme at `docs/CMake API.md` in the JUCE repo
juce_add_plugin("${Plugin_Name}"
    COMPANY_NAME recluse-audio
    BUNDLE_ID com.recluseaudio.recluseaudio
    COPY_PLUGIN_AFTER_BUILD TRUE          # On MacOS, plugin will be copied to /Users/you/Library/Audio/Plug-Ins/
    PLUGIN_MANUFACTURER_CODE Recl         # This has to be one uppercase, rest lower for AU formats
    PLUGIN_CODE Cara           
    FORMATS "${Plugin_Formats}"
    PRODUCT_NAME "${Plugin_Name}"        # The name of the final executable, which can differ from the target name
    IS_ARA_EFFECT TRUE
    IS_PLUGIN_ARA_EFFECT TRUE
)

add_compile_definitions(JUCE_IS_ARA_EFFECT=1)
add_compile_definitions(JucePlugin_Enable_ARA=1)

include(cmake/Source_Files.cmake)   # defines ${Source_Files}
include(cmake/Juce_ARA_Files.cmake)  # defines ${Juce_ARA_Files}

target_sources("${Plugin_Name}" PRIVATE ${Source_Files})
target_sources("${Plugin_Name}" PRIVATE ${Juce_ARA_Files})

target_include_directories("${Plugin_Name}"
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Source
        ${CMAKE_CURRENT_LIST_DIR}/Source/ARA

        ${CMAKE_CURRENT_LIST_DIR}/submodules/JUCE/modules/juce_audio_plugin_client/ARA

        ${CMAKE_CURRENT_LIST_DIR}/submodules/ARA_SDK
        ${CMAKE_CURRENT_LIST_DIR}/submodules/ARA_SDK/ARA_API
        ${CMAKE_CURRENT_LIST_DIR}/submodules/ARA_SDK/ARA_Library/PlugIn
)


include(cmake/Link_Libraries.cmake) # defines ${Link_Libraries}
include(cmake/Juce_Flags.cmake) # defines ${Juce_Flags}

target_link_libraries("${Plugin_Name}"
    PRIVATE
        ${Link_Libraries}
    PUBLIC
        ${Juce_Flags}
)

set_target_properties("${Plugin_Name}" PROPERTIES OSX_ARCHITECTURES "arm64;x86_64")
# Require using namespace juce::
add_compile_definitions(DONT_SET_USING_JUCE_NAMESPACE=1)

# Let us use #include<Util/Juce_Header.h>
juce_generate_juce_header("${Plugin_Name}")



# C++20, please
target_compile_features("${Plugin_Name}" PRIVATE cxx_std_20)


target_compile_definitions("${Plugin_Name}"
    PUBLIC
    # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
    JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
    JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
    JUCE_VST3_CAN_REPLACE_VST2=0
    )

# Generate debug symbols (TODO: Make this debug only?)    
target_compile_options("${Plugin_Name}" PRIVATE -g)

###########
######
##          TESTING
######
###########
enable_testing()

# CONFIGURE_DEPENDS / Clion's CMake integration makes globbing absolutely fine
file(GLOB_RECURSE Test_Files CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Tests/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/Tests/*.h")
message(STATUS "Test Files In Glob: ${Test_Files}")

# Use Catch2 v3 on the devel branch
Include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_PROGRESS TRUE
    GIT_SHALLOW TRUE
    GIT_TAG v3.1.0)
FetchContent_MakeAvailable(Catch2) # find_package equivalent

# include(cmake/Test_Files.cmake) # Defines ${Test_Files}
# add_executable(Tests ${Test_Files}) # Setup the test executable
add_executable(Tests ${Test_Files})

# Our test executable also wants to know about our plugin code...
target_compile_features(Tests PRIVATE cxx_std_20)


##########################################
# All my attempts to get the Tests to find the tests and link properly

target_sources(Tests PRIVATE ${Juce_ARA_Files})


target_include_directories(Tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/build/CMakeARA_artefacts/JuceLibraryCode
        ${CMAKE_CURRENT_LIST_DIR}/Source
        ${CMAKE_CURRENT_LIST_DIR}/Source/ARA
        ${CMAKE_CURRENT_LIST_DIR}/submodules/JUCE/modules/juce_audio_plugin_client/ARA
        ${CMAKE_CURRENT_LIST_DIR}/submodules/ARA_SDK
        ${CMAKE_CURRENT_LIST_DIR}/submodules/ARA_SDK/ARA_API
        ${CMAKE_CURRENT_LIST_DIR}/submodules/ARA_SDK/ARA_Library/PlugIn
)

########################################

target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(Tests
    PRIVATE
        ${Plugin_Name} 
        ${Link_Libraries}
) # wh


set_target_properties(Catch2 PROPERTIES OSX_ARCHITECTURES "x86_64")
set_target_properties(Catch2WithMain PROPERTIES OSX_ARCHITECTURES "x86_64")
set_target_properties(Tests PROPERTIES OSX_ARCHITECTURES "x86_64")


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
        target_link_libraries("${Plugin_Name}" PUBLIC IPP::ipps IPP::ippcore IPP::ippi IPP::ippcv)
        message("IPP LIBRARIES FOUND")
        target_compile_definitions("${Plugin_Name}" PUBLIC PAMPLEJUCE_IPP=1)
    else()
        message("IPP LIBRARIES *NOT* FOUND")
    endif()
endif()


#add_custom_command(TARGET ${Plugin_Name}_Standalone
 #                  POST_BUILD
  #                 COMMAND open ${CMAKE_BINARY_DIR}/${Plugin_Name}_artefacts/Debug/Standalone/${Plugin_Name}.app
   #                COMMENT "Launching Standalone app...")
