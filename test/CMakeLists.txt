message(status "Almag_RetSimulator testCMakeLists")

set(PROJECT_TESTS_NAME Almag_RetSimulator_Test)

include_directories(${PROJECT_SOURCE_DIR}/test)

set(EXTERNAL_LIBRARIES_TESTUTILS_FIXTURES
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/Fixtures/BaseFixtureWithDB.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/Fixtures/BaseFixtureWithDB.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/Fixtures/BaseFixtureWithDBAndHDLC.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/Fixtures/BaseFixtureWithDBAndHDLC.cpp
)

set(EXTERNAL_LIBRARIES_TESTUTILS
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/Hardcodes.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/ObjectTypes.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/StructsForParametrizedTests.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/UniqueKeys.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/HexesUtils.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/HexesUtils.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/MatcherUtils.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/MatcherUtils.hpp
)

set(EXTERNAL_LIBRARIES_TESTUTILS_HDLC_FRAMESFACTORIES
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/HDLC/FramesFactories/FrameStrFactory.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/HDLC/FramesFactories/SRetHDLCReqFrameBodyStrFactory.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/HDLC/FramesFactories/SRetHDLCReqFrameBodyStrFactory.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/HDLC/FramesFactories/SRetHDLCRespFrameBodyStrFactory.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/HDLC/FramesFactories/SRetHDLCRespFrameBodyStrFactory.hpp
)

add_subdirectory(mt)
add_subdirectory(ut)
