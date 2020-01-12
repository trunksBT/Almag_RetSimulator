#include <gmock/gmock.h>

#include <HDLC/HDLCFrameBodyInterpreter.hpp>
#include <TestUtils/StructsForParametrizedTests.hpp>
#include <TestUtils/HDLC/FramesFactories/FrameStrFactory.hpp>
#include <TestUtils/HDLC/FramesFactories/SRetHDLCRespFrameBodyStrFactory.hpp>
#include <Controller/IHDLCFrameBodyFactory.hpp>
#include <PluginSpecifics/HDLCRespFrameBodyFactory.hpp>

namespace
{
IHDLCFrameBodyFactoryPtr hdlcFrameBodyFactory = std::make_shared<HDLCRespFrameBodyFactory>();
FrameStrFactoryPtr retDeviceStr = std::make_shared<SRetHDLCRespFrameBodyStrFactory>();
}

class HDLCFrameInterpreterTests:
   public ::testing::TestWithParam<ExpectedValue_ReceivedString>
{
protected:
   HDLCFrameBodyInterpreter frameInterpreter;
};

TEST_P(HDLCFrameInterpreterTests, InterpretFrame)
{
   const auto interpretedFrame = frameInterpreter.apply(GetParam().receivedString);
   ASSERT_EQ(GetParam().expectedHexes,interpretedFrame->build());
}

INSTANTIATE_TEST_CASE_P(HDLCFrameInterpreterTests,
        HDLCFrameInterpreterTests,
        ::testing::Values(
        ExpectedValue_ReceivedString{
                hdlcFrameBodyFactory->get_FrameXID_DeviceScan()->build(),
                retDeviceStr->get_FrameXID_DeviceScan()
        },
        ExpectedValue_ReceivedString{
                hdlcFrameBodyFactory->get_FrameXID_AddressAssignment()->build(),
                retDeviceStr->get_FrameXID_AddressAssignment()
        },
        ExpectedValue_ReceivedString{
                hdlcFrameBodyFactory->get_FrameXID_3GPPReleaseId()->build(),
                retDeviceStr->get_FrameXID_3GPPReleaseId()
        },
        ExpectedValue_ReceivedString{
                hdlcFrameBodyFactory->get_FrameXID_AISGProtocolVersion()->build(),
                retDeviceStr->get_FrameXID_AISGProtocolVersion()
        },
        ExpectedValue_ReceivedString{
                hdlcFrameBodyFactory->get_FrameXID_HDLCParameters()->build(),
                retDeviceStr->get_FrameXID_HDLCParameters()
        },
        ExpectedValue_ReceivedString{
                hdlcFrameBodyFactory->get_FrameI_Calibrate()->build(),
                retDeviceStr->get_FrameI_Calibrate()
        },
        ExpectedValue_ReceivedString{
                hdlcFrameBodyFactory->get_FrameU_LinkEstablishment()->build(),
                retDeviceStr->get_FrameU_LinkEstablishment()
        }
)
);
