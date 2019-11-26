cmake_minimum_required (VERSION 3.8)

project (Almag_RetSimulator)
message(status "Almag_RetSimulator MainCMakeLists")

find_package(Boost 1.71.0 REQUIRED COMPONENTS log date_time)

# options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g") # create debug symbols
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe") # optimize hardware usage during compilation
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a") 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread") # for using threads
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pipe")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finline-functions") # helps considering about inlining functions
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -freorder-blocks") # helps compiler with compilation

# warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic") # warning if violates ISO standard
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic-errors") # error if violates ISO standard
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall") # enables all compiler's warning messages
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra") # enables extra compiler's warning messages
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnon-virtual-dtor")

# size optimizations flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--sort-common") # sort symbols by size
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--gc-sections") # enable gc of unused input sections
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections") # remove unused data/functions during linking time

# suppresses
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter") # disables warning about unused parameter 

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,-lstdc++fs")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lzmq")

message("** Boost Include: ${Boost_INCLUDE_DIR}")
message("** Boost Libraries: ${Boost_LIBRARY_DIRS}")
message("** Boost Libraries: ${Boost_LIBRARIES}")

# BINARY BOTH
include_directories(${Boost_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src)

link_directories(${Boost_LIBRARY_DIRS})
add_definitions( -DBOOST_ALL_DYN_LINK)

# External libraries
include_directories(${PROJECT_SOURCE_DIR}/externalLibraries)

set(DATABASE
        ${PROJECT_SOURCE_DIR}/externalLibraries/Database/Database.hpp
        ${PROJECT_SOURCE_DIR}/externalLibraries/Database/Objects/IOPaths.cpp
        ${PROJECT_SOURCE_DIR}/externalLibraries/Database/Database.cpp
        ${PROJECT_SOURCE_DIR}/externalLibraries/Database/Objects/IOPaths.hpp
        ${PROJECT_SOURCE_DIR}/externalLibraries/Database/Utils/KeyWithValue.hpp
)

set(UTILS
        ${PROJECT_SOURCE_DIR}/src/Utils/Logger.cpp
        ${PROJECT_SOURCE_DIR}/src/Utils/Logger.hpp
)

add_subdirectory(3rdparty/googletest/googlemock)
add_subdirectory(test)
add_subdirectory(src)
