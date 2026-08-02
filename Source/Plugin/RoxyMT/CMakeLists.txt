SET(ThirdPartyLibraries
)

SET(PrivateDependPlugins
)

SET(PublicDependPlugins
    RoxySTD
)

ADD_LIBRARY(RoxyMT STATIC
    RoxyMT/RoxyLock.h
    RoxyMT/RoxyLock.cpp
    RoxyMT/RoxyQueue.h
    RoxyMT/RoxyQueue.cpp
    RoxyMT/RoxyMT.h
    RoxyMT/RoxyMT.cpp
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
    RoxyMT/RoxyMT_UnitTest.cpp
)

TARGET_LINK_LIBRARIES(RoxyMT_UnitTest
    PRIVATE RoxyMT RoxyChrono RoxyLog doctest::doctest
)

ADD_TEST(NAME RoxyMT_UnitTest COMMAND RoxyMT_UnitTest)
ENDIF()
