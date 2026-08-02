SET(ThirdPartyLibraries
)

SET(PrivateDependPlugins
    RoxyLog
)

SET(PublicDependPlugins
    RoxySTD
)

ADD_LIBRARY(RoxyAlloc STATIC
    RoxyAlloc/RoxyAlloc.h
    RoxyAlloc/RoxyAlloc.cpp
)

TARGET_INCLUDE_DIRECTORIES(RoxyAlloc
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

TARGET_LINK_LIBRARIES(RoxyAlloc
    PRIVATE ${PrivateDependPlugins}
    PUBLIC  ${PublicDependPlugins}
    PUBLIC  ${ThirdPartyLibraries}
)

# Unit Test
IF(ROXY_BUILD_TEST)
ADD_EXECUTABLE(RoxyAlloc_UnitTest
    RoxyAlloc/RoxyAlloc_UnitTest.cpp
)

TARGET_LINK_LIBRARIES(RoxyAlloc_UnitTest
    PRIVATE RoxyAlloc RoxyChrono RoxyLog doctest::doctest
)

ADD_TEST(NAME RoxyAlloc_UnitTest COMMAND RoxyAlloc_UnitTest)
ENDIF()
