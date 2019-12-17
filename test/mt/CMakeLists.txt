set(PROJECT_TESTS_NAME Almag_RetSimulator_MT)
message(${CMAKE_CURRENT_SOURCE_DIR})
message(status "Almag_RetSimulator mtCMakeLists")

add_executable(${PROJECT_TESTS_NAME}
    ${PROJECT_SOURCE_DIR}/test/main.cpp
)

add_dependencies(${PROJECT_TESTS_NAME} gmock_main)

target_link_libraries(${PROJECT_TESTS_NAME}
    gmock_main
    gmock
    ${Boost_LIBRARIES}
    # /usr/lib/gcc/x86_64-linux-gnu/8/libstdc++fs.a # uncomment on UBUNTU, I know it sucks
    /usr/lib64/libstdc++fs.a # uncomment on Manjaro, I know it sucks
)
