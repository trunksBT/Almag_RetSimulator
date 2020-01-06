#include "HDLCFrameToResponseCommandTranslator.hpp"
#include <PluginSpecifics/CmdConstraints/AlmagConstraints.hpp>
#include <Utils/Functions.hpp>
#include <Utils/Logger.hpp>
#include <Utils/Utils.hpp>
#include <TestUtils/HDLC/FramesFactories/SRetHDLCReqFrameBodyStrFactory.hpp>

using namespace convert;
using namespace constraints::almag;

HDLCFrameToResponseCommandTranslator::HDLCFrameToResponseCommandTranslator()
: knownResponseMessages_{std::make_shared<SRetHDLCReqFrameBodyStrFactory>()}
{
   LOG(trace);
}

HDLCFrameToResponseCommandTranslator::~HDLCFrameToResponseCommandTranslator()
{
   LOG(trace);
}

std::string HDLCFrameToResponseCommandTranslator::translate(const HDLCFrameBodyPtr& receivedFrame)
{
   LOG(debug);
   const auto receivedStrings = toString(receivedFrame->build());

   if (receivedStrings == knownResponseMessages_->get_FrameXID_DeviceScan())
   {
      return L2::DEVICE_SCAN;
   }
   else if (receivedStrings == knownResponseMessages_->get_FrameXID_AddressAssignment())
   {
      return L2::ADDRESS_ASSIGNMENT;
   }
   else if (receivedStrings == knownResponseMessages_->get_FrameU_LinkEstablishment())
   {
      return L2::LINK_ESTABLISHMENT;
   }
   else if (receivedStrings == knownResponseMessages_->get_FrameXID_HDLCParameters())
   {
      return L2::HDLC_PARAMETERS;
   }
   else if (receivedStrings == knownResponseMessages_->get_FrameXID_3GPPReleaseId())
   {
      return L2::THREEGPP_RELEASE_ID;
   }
   else if (receivedStrings == knownResponseMessages_->get_FrameXID_AISGProtocolVersion())
   {
      return L2::AISG_PROTOCOL_VERSION;
   }
   else if (receivedStrings == knownResponseMessages_->get_FrameI_Calibrate())
   {
      return L7::CALIBRATE;
   }

   LOG(error) << "Unknown response on " << receivedStrings;
   return defaultVals::FOR_STRING;
}
