SET(ThirdPartyLibraries
    fmt::fmt
)

SET(PrivateDependPlugins
)

SET(PublicDependPlugins
    RoxySTD
)

ADD_LIBRARY(RoxyFmt STATIC
    RoxyFmt/RoxyFmt.h
    RoxyFmt/RoxyFmt.cpp
)

TARGET_INCLUDE_DIRECTORIES(RoxyFmt
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

TARGET_LINK_LIBRARIES(RoxyFmt
    PRIVATE ${PrivateDependPlugins}
    PUBLIC  ${PublicDependPlugins}
    PUBLIC  ${ThirdPartyLibraries}
)

IF(ROXY_BUILD_TEST)
# Unit Test
ADD_EXECUTABLE(RoxyFmt_UnitTest
    RoxyFmt/RoxyFmt_UnitTest.cpp
)

TARGET_LINK_LIBRARIES(RoxyFmt_UnitTest
    PRIVATE RoxyFmt doctest::doctest
)

ADD_TEST(NAME RoxyFmt_UnitTest COMMAND RoxyFmt_UnitTest)
ENDIF()
