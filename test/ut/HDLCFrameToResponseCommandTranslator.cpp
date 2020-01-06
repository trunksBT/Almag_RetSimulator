#include <gmock/gmock.h>

#include <PluginSpecifics/CmdConstraints/AlmagConstraints.hpp>
#include <PluginSpecifics/HDLCFrameToResponseCommandTranslator.hpp>
#include <HDLC/HDLCFrameBodyInterpreter.hpp>
#include <TestUtils/HDLC/FramesFactories/SRetHDLCReqFrameBodyStrFactory.hpp>
#include <TestUtils/HDLC/FramesFactories/FrameStrFactory.hpp>
#include <TestUtils/StructsForParametrizedTests.hpp>

using testing::Eq;
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
   ASSERT_THAT(cmdTranslator.translate(recFrame),Eq(GetParam().respCommandStr));
}

INSTANTIATE_TEST_CASE_P(HDLCFrameToResponseCommandTranslatorTests,
        HDLCFrameToResponseCommandTranslatorTests,
        ::testing::Values(
        ReceivedFrameStr_RespCommandStr{
            retDeviceStrFactory->get_FrameXID_AddressAssignment(),
            L2::ADDRESS_ASSIGNMENT
        },
        ReceivedFrameStr_RespCommandStr{
           retDeviceStrFactory->get_FrameXID_DeviceScan(),
           L2::DEVICE_SCAN
        }
//        ReceivedFrameStr_RespCommandStr{
//            toString(hdlcFrameBodyFactory->get_FrameXID_3GPPReleaseId()->build()),
//            retDeviceStrFactory->get_FrameXID_3GPPReleaseId()
//        },
//        ReceivedFrameStr_RespCommandStr{
//            toString(hdlcFrameBodyFactory->get_FrameXID_AISGProtocolVersion()->build()),
//            retDeviceStrFactory->get_FrameXID_AISGProtocolVersion()
//        },
//        ReceivedFrameStr_RespCommandStr{
//                toString(hdlcFrameBodyFactory->get_FrameXID_HDLCParameters()->build()),
//                retDeviceStrFactory->get_FrameXID_HDLCParameters()
//        },
//        ReceivedFrameStr_RespCommandStr{
//            toString(hdlcFrameBodyFactory->get_FrameU_LinkEstablishment()->build()),
//            retDeviceStrFactory->get_FrameU_LinkEstablishment()
//        },
//        ReceivedFrameStr_RespCommandStr{
//            toString(hdlcFrameBodyFactory->get_FrameI_Calibrate()->build()),
//            retDeviceStrFactory->get_FrameI_Calibrate()
//        }
    )
);
