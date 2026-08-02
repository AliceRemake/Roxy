SET(ThirdPartyLibraries
    spdlog::spdlog
)

SET(PublicDependPlugins
    RoxySTD
    RoxyFmt
)

SET(PrivateDependPlugins
)

ADD_LIBRARY(RoxyLog STATIC
    RoxyLog/RoxyLog.h
    RoxyLog/RoxyLog.cpp
)

TARGET_INCLUDE_DIRECTORIES(RoxyLog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

TARGET_LINK_LIBRARIES(RoxyLog
    PRIVATE ${PrivateDependPlugins}
    PUBLIC  ${PublicDependPlugins}
    PUBLIC  ${ThirdPartyLibraries}
)

IF(ROXY_BUILD_TEST)
# Unit Test
ADD_EXECUTABLE(RoxyLog_UnitTest
    RoxyLog/RoxyLog_UnitTest.cpp
)

TARGET_LINK_LIBRARIES(RoxyLog_UnitTest
    PRIVATE RoxyLog doctest::doctest
)

ADD_TEST(NAME RoxyLog_UnitTest COMMAND RoxyLog_UnitTest)
ENDIF ()
