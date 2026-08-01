#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <RoxyFmt.h>

TEST_CASE("Print && Println")
{
    RoxyFmt::Print("Hello RoxyFmt!\n");
    RoxyFmt::Println("Hello RoxyFmt!");
}

TEST_CASE("Format")
{
    const FString Str = RoxyFmt::Format("Hello {}!\n", "RoxyFmt");
    DOCTEST_CHECK_EQ(Str, "Hello RoxyFmt!\n");
}
