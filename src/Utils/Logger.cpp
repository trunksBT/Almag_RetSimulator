#include "Logger.hpp"

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>

namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;
namespace sinks = boost::log::sinks;

void init_logger(bool isLogToFile, bool isLogOnStdOut, boost::log::trivial::severity_level minSeverity)
{
   boost::log::add_common_attributes();
   boost::log::core::get()->set_filter
           (
                   boost::log::trivial::severity >= minSeverity
           );
   if (isLogToFile)
   {
      boost::log::add_file_log
              (
                      keywords::rotation_size = 10 * 1024 * 1024,
                      keywords::file_name = "logs/Log_%m-%d_%H-%M-%S.log",
                      keywords::format =
                              (
                                      expr::stream
                                              << "<"
                                              << expr::format_date_time< boost::posix_time::ptime >(
                                                      "TimeStamp", "%H:%M:%S.%f")
                                              << "> "
                                              << boost::log::trivial::severity
                                              << " " << expr::smessage
                              )
              );
   }

   if (isLogOnStdOut)
   {
      boost::log::add_console_log(std::cout, keywords::format =
              expr::stream
                      << "<"
                      << expr::format_date_time< boost::posix_time::ptime >(
                              "TimeStamp", "%H:%M:%S.%f")
                      << "> "
                      << boost::log::trivial::severity
                      << " " << expr::smessage
      );
   }
}

