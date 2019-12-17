#include "RetCommandFactory.hpp"
#include <Controller/Commands/AISGProtocolVersion.hpp>
#include <Controller/Commands/AddressAssignment.hpp>
#include <Controller/Commands/Calibrate.hpp>
#include <Controller/Commands/DummyScan.hpp>
#include <Controller/Commands/DeviceScan.hpp>
#include <Controller/Commands/HDLCParameters.hpp>
#include <Controller/Commands/LinkEstablishment.hpp>
#include <Controller/Commands/ThreeGPPReleaseID.hpp>
#include <PluginSpecifics/CmdConstraints/AlmagConstraints.hpp>
//#include <PluginSpecifics/HDLCReqFrameBodyFactory.hpp>
#include <Utils/Logger.hpp>

using namespace constraints::almag;

namespace
{
constexpr int IDX_OF_COMMAND_OR_ACTION_NAME = 0;
constexpr int IDX_OF_REQUEST_RESPONSE_COMMUNICATOR = 0;
constexpr int IDX_OF_PUBLISH_SUBSCRIBE_COMMUNICATOR = 1;
constexpr uint8_t NUMBER_OF_DUMMY_SCANS_FOR_9_6_KBPS = 6;
constexpr uint8_t NUMBER_OF_DUMMY_SCANS_FOR_SINGLE_COMMAND = 1;
}

RetCommandFactory::RetCommandFactory(std::vector<IHDLCCommunicatorPtr>& hdlcCommunicators)
        : ICommandFactory()
        , hdlcCommunicators_{hdlcCommunicators}
{
   LOG(trace);
}

RetCommandFactory::~RetCommandFactory()
{
   LOG(trace);
}

ICommandPtr RetCommandFactory::interpretAndCreateCommand(std::vector<std::string> validatedInput)
{
   const auto& commandName = validatedInput[IDX_OF_COMMAND_OR_ACTION_NAME];

//   if (L2::DEVICE_SCAN == commandName)
//   {
//      return std::make_shared<DeviceScan>(std::make_shared<HDLCReqFrameBodyFactory>(),
//              hdlcCommunicators_.at(IDX_OF_REQUEST_RESPONSE_COMMUNICATOR), validatedInput);
//   }
//   else if (L2::ADDRESS_ASSIGNMENT == commandName)
//   {
//      return std::make_shared<AddressAssignment>(std::make_shared<HDLCReqFrameBodyFactory>(),
//              hdlcCommunicators_.at(IDX_OF_REQUEST_RESPONSE_COMMUNICATOR), validatedInput);
//   }
//   else if (L2::LINK_ESTABLISHMENT == commandName)
//   {
//      return std::make_shared<LinkEstablishment>(std::make_shared<HDLCReqFrameBodyFactory>(),
//              hdlcCommunicators_.at(IDX_OF_REQUEST_RESPONSE_COMMUNICATOR), validatedInput);
//   }
//   else if (L2::HDLC_PARAMETERS == commandName)
//   {
//      return std::make_shared<HDLCParameters>(std::make_shared<HDLCReqFrameBodyFactory>(),
//              hdlcCommunicators_.at(IDX_OF_REQUEST_RESPONSE_COMMUNICATOR), validatedInput);
//   }
//   else if (L2::THREEGPP_RELEASE_ID == commandName)
//   {
//      return std::make_shared<ThreeGPPReleaseID>(std::make_shared<HDLCReqFrameBodyFactory>(),
//              hdlcCommunicators_.at(IDX_OF_REQUEST_RESPONSE_COMMUNICATOR), validatedInput);
//   }
//   else if (L2::AISG_PROTOCOL_VERSION == commandName)
//   {
//      return std::make_shared<AISGProtocolVersion>(std::make_shared<HDLCReqFrameBodyFactory>(),
//              hdlcCommunicators_.at(IDX_OF_REQUEST_RESPONSE_COMMUNICATOR), validatedInput);
//   }
//   else if (L7::CALIBRATE == commandName)
//   {
//      return std::make_shared<Calibrate>(std::make_shared<HDLCReqFrameBodyFactory>(),
//               hdlcCommunicators_.at(IDX_OF_REQUEST_RESPONSE_COMMUNICATOR), validatedInput);
//   }
//   else
   {
      LOG(warning) << "Unknown command " << commandName;
      return {};
   }
}
