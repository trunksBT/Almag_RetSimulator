message(status "Almag_RetSimulator testCMakeLists")

set(PROJECT_TESTS_NAME Almag_RetSimulator_Test)

include_directories(${PROJECT_SOURCE_DIR}/test)

add_subdirectory(mt)
add_subdirectory(ut)
