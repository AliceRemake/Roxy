SET(ThirdPartyLibraries
)

SET(PrivateDependPlugins
)

SET(PublicDependPlugins
    RoxySTD
)

ADD_LIBRARY(RoxyMT STATIC
    RoxyMT.h
    RoxyMT.cpp
)

TARGET_INCLUDE_DIRECTORIES(RoxyMT
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

TARGET_LINK_LIBRARIES(RoxyMT
    PRIVATE ${PrivateDependPlugins}
    PUBLIC  ${PublicDependPlugins}
    PUBLIC  ${ThirdPartyLibraries}
)

IF(ROXY_BUILD_TEST)
# Unit Test
ADD_EXECUTABLE(RoxyMT_UnitTest
    RoxyMT_UnitTest.cpp
)

TARGET_LINK_LIBRARIES(RoxyMT_UnitTest
    PRIVATE RoxyMT doctest::doctest
)

ADD_TEST(NAME RoxyMT_UnitTest COMMAND RoxyMT_UnitTest)
ENDIF()
