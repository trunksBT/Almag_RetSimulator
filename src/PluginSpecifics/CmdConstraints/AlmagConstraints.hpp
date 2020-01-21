#pragma once

#include <array>
#include <string>

namespace constraints
{
namespace korytkomag
{

namespace L1
{
const std::string DUMMY_SCAN = "DummyScan";
}

namespace L2
{
const std::string ADDRESS_ASSIGNMENT = "AddressAssignment";
const std::string DEVICE_SCAN = "DeviceScan";
const std::string LINK_ESTABLISHMENT = "LinkEstablishment";
const std::string HDLC_PARAMETERS = "HDLCParameters";
const std::string THREEGPP_RELEASE_ID = "3GPPReleaseID";
const std::string AISG_PROTOCOL_VERSION = "AISGProtocolVersion";
}

namespace L7
{
const std::string CALIBRATE = "Calibrate";
}

constexpr std::size_t NUMBER_OF_CONSTRAINTS = 8;

static const std::array<std::string, NUMBER_OF_CONSTRAINTS> values {{
    L1::DUMMY_SCAN,
    L2::DEVICE_SCAN,
    L2::ADDRESS_ASSIGNMENT,
    L2::LINK_ESTABLISHMENT,
    L2::HDLC_PARAMETERS,
    L2::THREEGPP_RELEASE_ID,
    L2::AISG_PROTOCOL_VERSION,
    L7::CALIBRATE,
}};
}
}
