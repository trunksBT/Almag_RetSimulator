#pragma once

#include <string>
#include <HDLC/HDLCFrameBody.hpp>
#include <TestUtils/HDLC/FramesFactories/SRetHDLCRespFrameBodyStrFactory.hpp>

class FrameStrFactory;

class HDLCFrameToResponseCommandTranslator
{
public:
   HDLCFrameToResponseCommandTranslator();
   ~HDLCFrameToResponseCommandTranslator();
   std::string translate(const HDLCFrameBodyPtr& receivedFrame);
private:
   FrameStrFactoryPtr knownResponseMessages_;
};
