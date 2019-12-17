#pragma once

#include <Controller/ICommandFactory.hpp>
#include <HDLC/IHDLCCommunicator.hpp>

class RetCommandFactory final : public ICommandFactory
{
public:
   explicit RetCommandFactory(std::vector<IHDLCCommunicatorPtr>& hdlcCommunicators);
   ICommandPtr interpretAndCreateCommand(std::vector<std::string> validatedInput) override;
   virtual ~RetCommandFactory();
private:
   std::vector<IHDLCCommunicatorPtr> hdlcCommunicators_;
};
