function(AddTargetIncludes TARGET_NAME)
    target_include_directories(${TARGET_NAME}
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/Source
            ${CMAKE_CURRENT_LIST_DIR}/Source/ARA
            ${CMAKE_CURRENT_LIST_DIR}/submodules/JUCE/modules/juce_audio_plugin_client/ARA
            ${CMAKE_CURRENT_LIST_DIR}/submodules/ARA_SDK
            ${CMAKE_CURRENT_LIST_DIR}/submodules/ARA_SDK/ARA_API
            ${CMAKE_CURRENT_LIST_DIR}/submodules/ARA_SDK/ARA_Library/PlugIn
    )
endfunction()
