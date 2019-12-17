#pragma once

#include <Controller/IHDLCFrameBodyFactory.hpp>

class HDLCRespFrameBodyFactory : public IHDLCFrameBodyFactory
{
public:
   HDLCFrameBodyPtr get_FrameI_Calibrate() const override;
   HDLCFrameBodyPtr get_FrameU_LinkEstablishment() const override;
   HDLCFrameBodyPtr get_FrameXID_DummyScan() const override;
   HDLCFrameBodyPtr get_FrameXID_DeviceScan() const override;
   HDLCFrameBodyPtr get_FrameXID_AddressAssignment() const override;
   HDLCFrameBodyPtr get_FrameXID_3GPPReleaseId() const override;
   HDLCFrameBodyPtr get_FrameXID_AISGProtocolVersion() const override;
   HDLCFrameBodyPtr get_FrameXID_HDLCParameters() const override;
   virtual ~HDLCRespFrameBodyFactory() = default;
};
using HDLCRespFrameBodyFactoryPtr = std::shared_ptr<HDLCRespFrameBodyFactory>;
