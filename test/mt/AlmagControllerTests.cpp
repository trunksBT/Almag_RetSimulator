#include <TestUtils/Fixtures/BaseFixtureWithDBAndHDLC.hpp>

#include <Controller/AlmagController.hpp>
#include <Controller/IController.hpp>

#include <PluginSpecifics/CmdConstraints/AlmagConstraints.hpp>
#include <PluginSpecifics/RetCommandFactory.hpp>

#include <TestUtils/Hardcodes.hpp>
#include <TestUtils/StructsForParametrizedTests.hpp>
#include <TestUtils/HDLC/DataLinkLayerCommunicators/RoundTripHDLCCommunicatorStub.hpp>
#include <Utils/Utils.hpp>

using namespace command;
using namespace defaultVals;
using namespace constraints::almag;
using namespace hardcodes::IOPaths;

namespace mt
{
class AlmagControllerShouldPar:
   public BaseFixtureWithDBAndHDLC,
   public ::testing::WithParamInterface<CommandsToExpectedFrame>
{
protected:
   AlmagControllerShouldPar()
      : BaseFixtureWithDBAndHDLC({}, {std::make_shared<test::RoundTripHDLCCommunicatorStub>()})
      , ctrl_(std::make_shared<AlmagController>(db_, std::make_shared<RetCommandFactory>(hdlcCommunicators_)))
   {};

   IAlmagControllerPtr ctrl_;
};

TEST_P(AlmagControllerShouldPar, Execute_Command_Expect_ResultCode)
{
   ctrl_->addCommands(GetParam().inCommands);
   ctrl_->executeCommand();

   ASSERT_THAT(ctrl_->getFinalResultCode(), StrEq(GetParam().expectedHdlcFrame));
}

INSTANTIATE_TEST_CASE_P(BaseFixtureWithDBAndHDLC,
        AlmagControllerShouldPar,
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

