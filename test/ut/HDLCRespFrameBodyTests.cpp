#include <gmock/gmock.h>

#include <Controller/IHDLCFrameBodyFactory.hpp>
#include <PluginSpecifics/HDLCRespFrameBodyFactory.hpp>
#include <TestUtils/HDLC/FramesFactories/SRetHDLCRespFrameBodyStrFactory.hpp>
#include <TestUtils/HDLC/FramesFactories/FrameStrFactory.hpp>
#include <TestUtils/StructsForParametrizedTests.hpp>
#include <Utils/Functions.hpp>

using testing::Eq;
using namespace convert;

namespace
{
IHDLCFrameBodyFactoryPtr hdlcFrameBodyFactory = std::make_shared<HDLCRespFrameBodyFactory>();
FrameStrFactoryPtr retDeviceStrFactory = std::make_shared<SRetHDLCRespFrameBodyStrFactory>();
}

class HDLCRespFrameBodyTests : public ::testing::TestWithParam<BuiltFrameStr_ExpectedFrameStr>
{};

TEST_P(HDLCRespFrameBodyTests, BuiltFrame)
{
   ASSERT_THAT(GetParam().builtFrameStr,Eq(GetParam().expectedFrameStr));
}

INSTANTIATE_TEST_CASE_P(HDLCRespFrameBodyTests,
    HDLCRespFrameBodyTests,
    ::testing::Values(
        BuiltFrameStr_ExpectedFrameStr{
            toString(hdlcFrameBodyFactory->get_FrameXID_AddressAssignment()->build()),
            retDeviceStrFactory->get_FrameXID_AddressAssignment()
        },
        BuiltFrameStr_ExpectedFrameStr{
            toString(hdlcFrameBodyFactory->get_FrameXID_DeviceScan()->build()),
            retDeviceStrFactory->get_FrameXID_DeviceScan()
        },
        BuiltFrameStr_ExpectedFrameStr{
            toString(hdlcFrameBodyFactory->get_FrameXID_3GPPReleaseId()->build()),
            retDeviceStrFactory->get_FrameXID_3GPPReleaseId()
        },
        BuiltFrameStr_ExpectedFrameStr{
            toString(hdlcFrameBodyFactory->get_FrameXID_AISGProtocolVersion()->build()),
            retDeviceStrFactory->get_FrameXID_AISGProtocolVersion()
        },
        BuiltFrameStr_ExpectedFrameStr{
                toString(hdlcFrameBodyFactory->get_FrameXID_HDLCParameters()->build()),
                retDeviceStrFactory->get_FrameXID_HDLCParameters()
        },
        BuiltFrameStr_ExpectedFrameStr{
            toString(hdlcFrameBodyFactory->get_FrameU_LinkEstablishment()->build()),
            retDeviceStrFactory->get_FrameU_LinkEstablishment()
        },
        BuiltFrameStr_ExpectedFrameStr{
            toString(hdlcFrameBodyFactory->get_FrameI_Calibrate()->build()),
            retDeviceStrFactory->get_FrameI_Calibrate()
        }
    )
);
