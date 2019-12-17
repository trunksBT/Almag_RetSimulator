#include <Controller/AlmagController.hpp>
#include <Database/Database.hpp>
#include <HDLC/HDLCCommunicator.hpp>
#include <UserInterface/CMenu.hpp>

#include <Utils/Logger.hpp>

//#include <PluginSpecifics/CmdConstraints/AlmagConstraints.hpp>
#include <Database/DatabaseConstraints.hpp>
#include <PluginSpecifics/RetCommandFactory.hpp>
//#include <PluginSpecifics/UICmdValidators/AlmagCommandValidationManager.hpp>
#include <UserInterface/CtrlCommandsValidators/DatabaseCommandValidationManager.hpp>

#include <Utils/UserCommandParser.hpp>

using namespace std;

int main()
{
   init_logger(IS_LOG_TO_FILE, IS_LOG_ON_STD_OUT,
               boost::log::trivial::trace);

   LOG(trace) << "BEGIN";
   Database db({});
   std::vector<IHDLCCommunicatorPtr> hdlcCommunicators {{
      std::make_shared<HDLCCommunicator>(),
   }};
   ICommandFactoryPtr commandFactory = std::make_shared<RetCommandFactory>(hdlcCommunicators);
   AlmagControllerPtr ctrl = std::make_shared<AlmagController>(db, commandFactory);

//   CMenu ui{"AlmagRetUI", "_", db, ctrl,
////            std::make_shared<AlmagCommandValidationManager>(db),
////            std::make_unique<DatabaseCommandValidationManager>(db)
//   };
//
//   ui.setAlmagCommandsConstraints({
//      constraints::ret::values.begin(), constraints::ret::values.end()});
//   ui.setDatabaseCommandsConstraints({
//      constraints::database::values.begin(), constraints::database::values.end()});

//   ui.run({});

   LOG(trace) << "END";
   return 0;
}
