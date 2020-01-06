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

set(PLUGIN_SPECIFICS
#    ${PROJECT_SOURCE_DIR}/src/PluginSpecifics/CmdConstraints/AlmagConstraints.hpp
#    ${PROJECT_SOURCE_DIR}/src/PluginSpecifics/CmdConstraints/DatabaseConstraints.hpp
#    ${PROJECT_SOURCE_DIR}/src/PluginSpecifics/UICmdValidators/AlmagCommandValidationManager.cpp
#    ${PROJECT_SOURCE_DIR}/src/PluginSpecifics/UICmdValidators/AlmagCommandValidationManager.hpp
    ${PROJECT_SOURCE_DIR}/src/PluginSpecifics/RetCommandFactory.cpp
    ${PROJECT_SOURCE_DIR}/src/PluginSpecifics/RetCommandFactory.hpp
    ${PROJECT_SOURCE_DIR}/src/PluginSpecifics/HDLCRespFrameBodyFactory.cpp
    ${PROJECT_SOURCE_DIR}/src/PluginSpecifics/HDLCRespFrameBodyFactory.hpp
    ${PROJECT_SOURCE_DIR}/src/PluginSpecifics/HDLCFrameToResponseCommandTranslator.cpp
    ${PROJECT_SOURCE_DIR}/src/PluginSpecifics/HDLCFrameToResponseCommandTranslator.hpp
)

set(EXTERNAL_LIBRARIES_HDLC
    ${PROJECT_SOURCE_DIR}/externalLibraries/HDLC/HDLCCommunicator.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/HDLC/HDLCCommunicator.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/HDLC/HDLCFrame.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/HDLC/HDLCFrame.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/HDLC/HDLCParametersValues.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/HDLC/HDLCParametersValues.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/HDLC/HDLCFrameBody.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/HDLC/HDLCFrameBody.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/HDLC/IHDLCCommunicator.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/HDLC/MessagesHelpers.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/HDLC/HDLCFrameBodyInterpreter.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/HDLC/HDLCFrameBodyInterpreter.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/HDLC/FrameTypes/FrameI.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/HDLC/FrameTypes/FrameI.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/HDLC/FrameTypes/FrameU.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/HDLC/FrameTypes/FrameU.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/HDLC/FrameTypes/FrameXID.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/HDLC/FrameTypes/FrameXID.hpp
)

set(EXTERNAL_LIBRARIES_DATABASE
    ${PROJECT_SOURCE_DIR}/externalLibraries/Database/Database.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Database/Objects/IOPaths.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Database/Database.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Database/Objects/IOPaths.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Database/Utils/KeyWithValue.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Database/DatabaseConstraints.hpp
)

set(EXTERNAL_LIBRARIES_USER_INTERFACE
    ${PROJECT_SOURCE_DIR}/externalLibraries/UserInterface/CMenu.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/UserInterface/CMenu.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/UserInterface/Database/CDatabaseCommand.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/UserInterface/Database/CDatabaseCommand.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/UserInterface/Database/Brokers/Broker_IOPaths.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/UserInterface/Database/Brokers/Broker_IOPaths.hpp
)

set(EXTERNAL_LIBRARIES_UTILS
    ${PROJECT_SOURCE_DIR}/externalLibraries/Utils/Utils.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Utils/Utils.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Utils/TypeAliases.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Utils/Functions.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Utils/Functions.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Utils/PrintUtils.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Utils/PrintUtils.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Utils/UserCommandParser.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Utils/UserCommandParser.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Utils/Logger.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Utils/Logger.hpp
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

    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/HDLC/DataLinkLayerCommunicators/ZeroMqUtils.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/HDLC/DataLinkLayerCommunicators/ZeroMqUtils.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/HDLC/DataLinkLayerCommunicators/ZMqCommunicator.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/HDLC/DataLinkLayerCommunicators/ZMqCommunicator.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/HDLC/DataLinkLayerCommunicators/ZMqReqRespCommunicator.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/HDLC/DataLinkLayerCommunicators/ZMqReqRespCommunicator.hpp
)

set(EXTERNAL_LIBRARIES_TESTUTILS_COMMUNICATORS
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/HDLC/DataLinkLayerCommunicators/RoundTripHDLCCommunicatorStub.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/HDLC/DataLinkLayerCommunicators/RoundTripHDLCCommunicatorStub.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/HDLC/DataLinkLayerCommunicators/ZMqCommunicator.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/HDLC/DataLinkLayerCommunicators/ZMqCommunicator.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/HDLC/DataLinkLayerCommunicators/ZMqPubSubCommunicator.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/HDLC/DataLinkLayerCommunicators/ZMqPubSubCommunicator.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/HDLC/DataLinkLayerCommunicators/ZMqReqRespCommunicator.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/HDLC/DataLinkLayerCommunicators/ZMqReqRespCommunicator.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/HDLC/DataLinkLayerCommunicators/ZeroMqUtils.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/HDLC/DataLinkLayerCommunicators/ZeroMqUtils.hpp
)

set(EXTERNAL_LIBRARIES_TESTUTILS_HDLC_FRAMESFACTORIES
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/HDLC/FramesFactories/FrameStrFactory.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/HDLC/FramesFactories/SRetHDLCReqFrameBodyStrFactory.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/HDLC/FramesFactories/SRetHDLCReqFrameBodyStrFactory.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/HDLC/FramesFactories/SRetHDLCRespFrameBodyStrFactory.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/TestUtils/HDLC/FramesFactories/SRetHDLCRespFrameBodyStrFactory.hpp
)

set(EXTERNAL_LIBRARIES_CONTROLLER
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/AlmagController.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/AlmagController.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/AlmagControllerNull.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/AlmagControllerNull.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/IController.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/Commands/AISGProtocolVersion.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/Commands/AISGProtocolVersion.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/Commands/AddressAssignment.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/Commands/AddressAssignment.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/Commands/Calibrate.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/Commands/Calibrate.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/Commands/DeviceScan.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/Commands/DeviceScan.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/Commands/HDLCParameters.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/Commands/HDLCParameters.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/ICommand.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/ICommand.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/Commands/HDLCCommand.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/Commands/HDLCCommand.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/IHDLCFrameBodyFactory.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/ICommandFactory.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/Commands/LinkEstablishment.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/Commands/LinkEstablishment.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/Commands/ThreeGPPReleaseID.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/Commands/ThreeGPPReleaseID.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/CmdValidationRules/AlmagCommandValidationManager.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/CmdValidationRules/AlmagCommandValidationManager.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/CmdValidationRules/DatabaseCommandValidationManager.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/CmdValidationRules/DatabaseCommandValidationManager.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/CmdValidationRules/DummyScanValidationStrategy.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/CmdValidationRules/DummyScanValidationStrategy.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/CmdValidationRules/ICmdValidationManager.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/CmdValidationRules/ICommandValidationStrategy.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/CmdValidationRules/ICommandValidationStrategy.hpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/CmdValidationRules/NullValidationStrategy.cpp
    ${PROJECT_SOURCE_DIR}/externalLibraries/Controller/CmdValidationRules/NullValidationStrategy.hpp
)

add_subdirectory(3rdparty/googletest/googlemock)
add_subdirectory(test)
add_subdirectory(src)
