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
    RoxyLog.h
    RoxyLog.cpp
)

TARGET_INCLUDE_DIRECTORIES(RoxyLog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

TARGET_LINK_LIBRARIES(RoxyLog
    PRIVATE ${PrivateDependPlugins}
    PUBLIC  ${PublicDependPlugins}
    PUBLIC  ${ThirdPartyLibraries}
)

# Unit Test
ADD_EXECUTABLE(RoxyLog_UnitTest
    RoxyLog_UnitTest.cpp
)

TARGET_COMPILE_OPTIONS(RoxyLog_UnitTest PRIVATE /W4 /WX /wd4530)

TARGET_LINK_LIBRARIES(RoxyLog_UnitTest
    PRIVATE RoxyLog doctest::doctest
)
