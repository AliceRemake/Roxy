SET(ThirdPartyLibraries
)

SET(PrivateDependPlugins
)

SET(PublicDependPlugins
    RoxySTD
)

ADD_LIBRARY(RoxyChrono STATIC
    RoxyChrono/RoxyChrono.h
    RoxyChrono/RoxyChrono.cpp
)

TARGET_INCLUDE_DIRECTORIES(RoxyChrono
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

TARGET_LINK_LIBRARIES(RoxyChrono
    PRIVATE ${PrivateDependPlugins}
    PUBLIC  ${PublicDependPlugins}
    PUBLIC  ${ThirdPartyLibraries}
)

IF(ROXY_BUILD_TEST)
# Unit Test
ADD_EXECUTABLE(RoxyChrono_UnitTest
    RoxyChrono/RoxyChrono_UnitTest.cpp
)

TARGET_LINK_LIBRARIES(RoxyChrono_UnitTest
    PRIVATE RoxyChrono RoxyLog doctest::doctest
)

ADD_TEST(NAME RoxyChrono_UnitTest COMMAND RoxyChrono_UnitTest)
ENDIF()
