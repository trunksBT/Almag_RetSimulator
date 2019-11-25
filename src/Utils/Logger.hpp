#ifndef SRC_UTILS_LOGGER
#define SRC_UTILS_LOGGER

#include <string_view>
#include <boost/log/trivial.hpp>

constexpr uint16_t SIZE_OF_FILE_EXTENSION_AND_TERMINATION_SIGN = 5;
constexpr bool IS_LOG_TO_FILE = true;
constexpr bool IS_LOG_ON_STD_OUT = true;

void init_logger(bool isLogToFile, bool isLogOnStdOut, boost::log::trivial::severity_level minSeverity);
// One must be true

template <size_t N>
constexpr std::string_view getFileName(const char (&fileNamePath)[N])
{
    std::string_view fileName(fileNamePath, N-SIZE_OF_FILE_EXTENSION_AND_TERMINATION_SIGN);
    auto lastSlash = fileName.rfind('/');
    if (lastSlash != fileName.npos)
    {
        fileName.remove_prefix(lastSlash + 1);
    }
    return fileName;
}

#define LOG(sv) BOOST_LOG_TRIVIAL(sv) \
    << "[" << getFileName(__FILE__) << "::" << __func__ << ":" << __LINE__ << "] "

#endif //  SRC_UTILS_LOGGER
