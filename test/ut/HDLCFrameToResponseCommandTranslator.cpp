#include <gmock/gmock.h>

#include <PluginSpecifics/CmdConstraints/AlmagConstraints.hpp>
#include <PluginSpecifics/HDLCFrameToResponseCommandTranslator.hpp>
#include <HDLC/HDLCFrameBodyInterpreter.hpp>
#include <TestUtils/HDLC/FramesFactories/SRetHDLCReqFrameBodyStrFactory.hpp>
#include <TestUtils/HDLC/FramesFactories/FrameStrFactory.hpp>
#include <TestUtils/StructsForParametrizedTests.hpp>

using namespace constraints::almag;

namespace
{
FrameStrFactoryPtr retDeviceStrFactory = std::make_shared<SRetHDLCReqFrameBodyStrFactory>();
}

class HDLCFrameToResponseCommandTranslatorTests : public ::testing::TestWithParam<ReceivedFrameStr_RespCommandStr>
{
public:
   HDLCFrameToResponseCommandTranslatorTests()
   : cmdTranslator{}
   , frameInterpreter{}
   {}

   HDLCFrameToResponseCommandTranslator cmdTranslator;
   HDLCFrameBodyInterpreter frameInterpreter;
};

TEST_P(HDLCFrameToResponseCommandTranslatorTests, BuiltFrame)
{
   auto recFrame{HDLCFrameBodyInterpreter().apply(GetParam().receivedFrameStr) };
   ASSERT_EQ(cmdTranslator.translate(recFrame),GetParam().respCommandStr);
}

INSTANTIATE_TEST_CASE_P(HDLCFrameToResponseCommandTranslatorTests,
        HDLCFrameToResponseCommandTranslatorTests,
        ::testing::Values(
        ReceivedFrameStr_RespCommandStr{
            retDeviceStrFactory->get_FrameXID_DeviceScan(),
            L2::DEVICE_SCAN
        },
        ReceivedFrameStr_RespCommandStr{
            retDeviceStrFactory->get_FrameXID_AddressAssignment(),
            L2::ADDRESS_ASSIGNMENT
        },
        ReceivedFrameStr_RespCommandStr{
            retDeviceStrFactory->get_FrameU_LinkEstablishment(),
            L2::LINK_ESTABLISHMENT
        },
        ReceivedFrameStr_RespCommandStr{
            retDeviceStrFactory->get_FrameXID_HDLCParameters(),
            L2::HDLC_PARAMETERS
        },
        ReceivedFrameStr_RespCommandStr{
            retDeviceStrFactory->get_FrameXID_3GPPReleaseId(),
            L2::THREEGPP_RELEASE_ID
        },
        ReceivedFrameStr_RespCommandStr{
            retDeviceStrFactory->get_FrameXID_AISGProtocolVersion(),
            L2::AISG_PROTOCOL_VERSION
        },
        ReceivedFrameStr_RespCommandStr{
            retDeviceStrFactory->get_FrameI_Calibrate(),
            L7::CALIBRATE
        }
    )
);
