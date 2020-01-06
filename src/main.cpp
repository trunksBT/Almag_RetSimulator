#include <Controller/AlmagController.hpp>
#include <Database/Database.hpp>
#include <HDLC/HDLCCommunicator.hpp>
#include <UserInterface/CMenu.hpp>

#include <Utils/Logger.hpp>

#include <PluginSpecifics/CmdConstraints/AlmagConstraints.hpp>
#include <Database/DatabaseConstraints.hpp>
#include <PluginSpecifics/RetCommandFactory.hpp>
#include <Controller/CmdValidationRules/AlmagCommandValidationManager.hpp>
#include <Controller/CmdValidationRules/DatabaseCommandValidationManager.hpp>

#include <Utils/UserCommandParser.hpp>
#include <TestUtils/HDLC/DataLinkLayerCommunicators/ZMqReqRespCommunicator.hpp>

using namespace std;

int main()
{
   init_logger(IS_LOG_TO_FILE, IS_LOG_ON_STD_OUT,
       boost::log::trivial::trace);

   LOG(debug);

   Database db({});
   std::vector<IHDLCCommunicatorPtr> hdlcCommunicators {{
       std::make_shared<ZMqReqRespCommunicator>(zmq::socket_type::rep),  // release mode
//      std::make_shared<HDLCCommunicator>(),  // debug mode
   }};
   ICommandFactoryPtr commandFactory = std::make_shared<RetCommandFactory>(hdlcCommunicators);
   AlmagControllerPtr ctrl = std::make_shared<AlmagController>(db, commandFactory);

   CMenu ui{"AlmagRetUI", "_", db, ctrl,
       std::make_shared<AlmagCommandValidationManager>(db),
       std::make_unique<DatabaseCommandValidationManager>(db)
   };

   ui.setAlmagCommandsConstraints({
       constraints::almag::values.begin(), constraints::almag::values.end()});
   ui.setDatabaseCommandsConstraints({
       constraints::database::values.begin(), constraints::database::values.end()});

   const auto receivedHdlcFrame = hdlcCommunicators.at(0)->receive("5555");  // release mode

   //  here for command interpreter
//   ui.run({HdlcFrameToResponseCommandTranslator(receivedHdlcFrame).execute()});

   LOG(trace) << "END";
   return 0;
}
