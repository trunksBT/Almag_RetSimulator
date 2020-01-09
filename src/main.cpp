#include <Controller/AlmagController.hpp>
#include <Database/Database.hpp>
#include <Database/DatabaseConstraints.hpp>
#include <HDLC/HDLCCommunicator.hpp>

#include <UserInterface/CMenu.hpp>

#include <PluginSpecifics/CmdConstraints/AlmagConstraints.hpp>
#include <PluginSpecifics/RetCommandFactory.hpp>
#include <PluginSpecifics/HDLCFrameToResponseCommandTranslator.hpp>

#include <Controller/CmdValidationRules/AlmagCommandValidationManager.hpp>
#include <Controller/CmdValidationRules/DatabaseCommandValidationManager.hpp>

#include <Utils/Logger.hpp>
#include <Utils/UserCommandParser.hpp>
#include <MessagingPattern/ZMqPubSubSecondaryStrategy.hpp>
#include <MessagingPattern/ZMqReqRepSecondaryStrategy.hpp>

using namespace std;
using namespace constraints::almag;

int main()
{
   init_logger(IS_LOG_TO_FILE, IS_LOG_ON_STD_OUT,
       boost::log::trivial::debug);

   LOG(debug);

   Database db({});
   std::vector<IHDLCCommunicatorPtr> hdlcCommunicators {{
       std::make_shared<ZMqReqRepSecondaryStrategy>(zmq::socket_type::rep),
       std::make_shared<ZMqPubSubSecondaryStrategy>(zmq::socket_type::sub),
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

   HDLCFrameToResponseCommandTranslator frameTranslator{};
   const std::string PORT_NR_FOR_PUB_SUB{ "6666" };
   const std::string PORT_NR_FOR_REQ_REP{ "5555" };
   constexpr unsigned EXPECTED_NUMBER_OF_RECEIVED_DUMMY_SCANS = 6;
   constexpr unsigned IDX_OF_REQ_REP_COMM_STRATEGY{ 0 };
   constexpr unsigned IDX_OF_PUB_SUB_COMM_STRATEGY{ 1 };
   bool isPhysicalLayerEstablished{ false };
   unsigned receivedDummyScanCounter = 0;

   {
      hdlcCommunicators.at(IDX_OF_PUB_SUB_COMM_STRATEGY)->setupReceive(PORT_NR_FOR_PUB_SUB);
      while (not isPhysicalLayerEstablished)
      {
         auto receivedHdlcFrame{
            hdlcCommunicators.at(IDX_OF_PUB_SUB_COMM_STRATEGY)->receive(PORT_NR_FOR_PUB_SUB) };
         auto commandToExecute{
            frameTranslator.translate(receivedHdlcFrame->getFrameBody()) };
         if (L1::DUMMY_SCAN == commandToExecute)
         {
            receivedDummyScanCounter++;
            LOG(debug) << "Received Dummy Scan nr: " << receivedDummyScanCounter;
         }
         isPhysicalLayerEstablished |=
            EXPECTED_NUMBER_OF_RECEIVED_DUMMY_SCANS == receivedDummyScanCounter;
      }
      LOG(info) << "Link speed set on 9.6 kbps";
   }
   {
      hdlcCommunicators.at(IDX_OF_REQ_REP_COMM_STRATEGY)->setupReceive(PORT_NR_FOR_REQ_REP);
      while (true)
      {
         auto receivedHdlcFrame{
            hdlcCommunicators.at(IDX_OF_REQ_REP_COMM_STRATEGY)->receive(PORT_NR_FOR_REQ_REP) };
         auto commandToExecute{
            frameTranslator.translate(receivedHdlcFrame->getFrameBody()) };
         ui.runPredefinedCommands({{commandToExecute, PORT_NR_FOR_REQ_REP}});
      }
   }

   LOG(trace) << "END";
   return 0;
}
