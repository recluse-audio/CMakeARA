#include <PluginProcessor.h>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include "Test_Utils/TestUtils.h"

TEST_CASE("one is equal to one", "[dummy]")
{
  REQUIRE(1 == 1);
}



TEST_CASE("Plugin instance name", "[name]")
{
	TestUtils::SetupAndTeardown setupAndTeardown;

  PluginProcessor testPlugin;

  CHECK_THAT(testPlugin.getName().toStdString(), Catch::Matchers::Equals("CMakeARA"));
         
}

#ifdef PAMPLEJUCE_IPP
#include <ipps.h>

TEST_CASE("IPP version", "[ipp]")
{
  CHECK_THAT(ippsGetLibVersion()->Version, Catch::Matchers::Equals("2021.7 (r0xa954907f)"));
}
#endif




