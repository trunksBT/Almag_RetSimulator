#include <iostream>

#include <Utils/Logger.hpp>

int main()
{
   init_logger(!IS_LOG_TO_FILE, IS_LOG_ON_STD_OUT,
               boost::log::trivial::trace);

   LOG(trace) << "BEGIN";
   LOG(trace) << "END";
   return 0;
}
