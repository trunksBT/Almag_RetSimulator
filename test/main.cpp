#include <gmock/gmock.h>

#include <Utils/Logger.hpp>

int main(int argc, char **argv)
{
   init_logger(!IS_LOG_TO_FILE, IS_LOG_ON_STD_OUT,
               boost::log::trivial::trace);

   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
