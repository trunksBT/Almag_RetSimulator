#include <TestUtils/Fixtures/BaseFixtureWithDBAndHDLC.hpp>

#include <Controller/KorytkoMagController.hpp>
#include <Controller/IController.hpp>

#include <PluginSpecifics/CmdConstraints/KorytkoMagConstraints.hpp>
#include <PluginSpecifics/RetCommandFactory.hpp>

#include <TestUtils/Hardcodes.hpp>
#include <TestUtils/StructsForParametrizedTests.hpp>
#include <TestUtils/HDLC/DataLinkLayerCommunicators/RoundTripHDLCTestCommunicatorStub.hpp>
#include <Utils/Utils.hpp>

using namespace command;
using namespace defaultVals;
using namespace constraints::korytkomag;
using namespace hardcodes::IOPaths;

namespace mt
{
class KorytkoMagControllerShouldPar:
   public BaseFixtureWithDBAndHDLC,
   public ::testing::WithParamInterface<CommandsToExpectedFrame>
{
protected:
   KorytkoMagControllerShouldPar()
      : BaseFixtureWithDBAndHDLC({}, {std::make_shared<test::RoundTripHDLCTestCommunicatorStub>()})
      , ctrl_(std::make_shared<KorytkoMagController>(db_, std::make_shared<RetCommandFactory>(hdlcCommunicators_)))
   {};

   IKorytkoMagControllerPtr ctrl_;
};

TEST_P(KorytkoMagControllerShouldPar, Execute_Command_Expect_ResultCode)
{
   ctrl_->addCommands(GetParam().inCommands);
   ctrl_->executeCommand();

   ASSERT_EQ(ctrl_->getFinalResultCode(), GetParam().expectedHdlcFrame);
}

INSTANTIATE_TEST_CASE_P(BaseFixtureWithDBAndHDLC,
        KorytkoMagControllerShouldPar,
        ::testing::Values(
        CommandsToExpectedFrame{
                {{ L2::DEVICE_SCAN, BUFFER_TO_SEND_VAL_1 }},
                L2::DEVICE_SCAN + DELIMITER
        },
        CommandsToExpectedFrame{
                {{ L2::ADDRESS_ASSIGNMENT, BUFFER_TO_SEND_VAL_1 }},
                L2::ADDRESS_ASSIGNMENT + DELIMITER
        },
        CommandsToExpectedFrame{
                {{ L2::LINK_ESTABLISHMENT, BUFFER_TO_SEND_VAL_1 }},
                L2::LINK_ESTABLISHMENT + DELIMITER
        },
        CommandsToExpectedFrame{
                {{ L2::HDLC_PARAMETERS, BUFFER_TO_SEND_VAL_1 }},
                L2::HDLC_PARAMETERS + DELIMITER
        },
        CommandsToExpectedFrame{
                {{ L2::THREEGPP_RELEASE_ID, BUFFER_TO_SEND_VAL_1 }},
                L2::THREEGPP_RELEASE_ID + DELIMITER
        },
        CommandsToExpectedFrame{
                {{ L2::AISG_PROTOCOL_VERSION, BUFFER_TO_SEND_VAL_1 }},
                L2::AISG_PROTOCOL_VERSION + DELIMITER
        },
        CommandsToExpectedFrame{
                {{ L7::CALIBRATE, BUFFER_TO_SEND_VAL_1 }},
                L7::CALIBRATE + DELIMITER
        }
   )
);

}  // namespace mt

