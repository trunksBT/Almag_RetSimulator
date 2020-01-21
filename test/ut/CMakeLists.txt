set(PROJECT_TESTS_NAME KorytkoMag_RetSimulator_UT)
message(${CMAKE_CURRENT_SOURCE_DIR})
message(status "KorytkoMag_RetSimulator utCMakeLists")

set(UT
    ${PROJECT_SOURCE_DIR}/test/ut/HDLCRespFrameBodyTests.cpp
    ${PROJECT_SOURCE_DIR}/test/ut/HDLCFrameToResponseCommandTranslator.cpp
    ${PROJECT_SOURCE_DIR}/test/ut/HDLCRespFrameBodyInterpreterTests.cpp
)

add_executable(${PROJECT_TESTS_NAME}
    ${PROJECT_SOURCE_DIR}/test/main.cpp
    ${UT}
    ${EXTERNAL_LIBRARIES_TESTUTILS}
    ${EXTERNAL_LIBRARIES_TESTUTILS_FIXTURES}
    ${EXTERNAL_LIBRARIES_TESTUTILS_HDLC_FRAMESFACTORIES}

    ${PLUGIN_SPECIFICS}
    ${EXTERNAL_LIBRARIES_HDLC}
    ${EXTERNAL_LIBRARIES_UTILS}
)

add_dependencies(${PROJECT_TESTS_NAME} gmock_main)

target_link_libraries(${PROJECT_TESTS_NAME}
    gmock_main
    gmock
    ${Boost_LIBRARIES}
    # /usr/lib/gcc/x86_64-linux-gnu/8/libstdc++fs.a # uncomment on UBUNTU, I know it sucks
    /usr/lib64/libstdc++fs.a # uncomment on Manjaro, I know it sucks
)
