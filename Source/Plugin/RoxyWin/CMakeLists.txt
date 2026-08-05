SET(ThirdPartyLibraries
    RGFW::RGFW
)

SET(PrivateDependPlugins
)

SET(PublicDependPlugins
    RoxySTD
)

ADD_LIBRARY(RoxyWin STATIC
    RoxyWin/RoxyWin.h
    RoxyWin/RoxyWin.cpp
)

TARGET_INCLUDE_DIRECTORIES(RoxyWin
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

TARGET_LINK_LIBRARIES(RoxyWin
    PRIVATE ${PrivateDependPlugins}
    PUBLIC  ${PublicDependPlugins}
    PUBLIC  ${ThirdPartyLibraries}
)

IF(ROXY_BUILD_TEST)
# Unit Test
ADD_EXECUTABLE(RoxyWin_UnitTest
    RoxyWin/RoxyWin_UnitTest.cpp
)

TARGET_LINK_LIBRARIES(RoxyWin_UnitTest
    PRIVATE RoxyWin doctest::doctest
)

ADD_TEST(NAME RoxyWin_UnitTest COMMAND RoxyWin_UnitTest)
ENDIF()
