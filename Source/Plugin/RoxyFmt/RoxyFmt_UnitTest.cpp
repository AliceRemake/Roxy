#define DOCTEST_CONFIG_NO_EXCEPTIONS_BUT_WITH_ALL_ASSERTS
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <RoxyFmt.h>

TEST_CASE("Print && Println")
{
    Roxy::Fmt::Print("Hello RoxyFmt!\n");
    Roxy::Fmt::Println("Hello RoxyFmt!");
}

TEST_CASE("Format")
{
    const FString Str = Roxy::Fmt::Format("Hello {}!\n", "RoxyFmt");
    DOCTEST_CHECK_EQ(Str, "Hello RoxyFmt!\n");
}
