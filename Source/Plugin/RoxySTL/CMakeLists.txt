SET(ThirdPartyLibraries
)

SET(PrivateDependPlugins
)

SET(PublicDependPlugins
    RoxyMath
)

ADD_LIBRARY(RoxySTL STATIC
    RoxySTL/FixArray.h
    RoxySTL/FixArray.cpp
    RoxySTL/RoxySTL.h
    RoxySTL/RoxySTL.cpp
)

TARGET_INCLUDE_DIRECTORIES(RoxySTL
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

TARGET_LINK_LIBRARIES(RoxySTL
    PRIVATE ${ThirdPartyLibraries} ${PrivateDependPlugins}
    PUBLIC ${PublicDependPlugins}
)

IF(ROXY_BUILD_TEST)
# Unit Test
ADD_EXECUTABLE(RoxySTL_UnitTest
    RoxySTL/RoxySTL_UnitTest.cpp
)

TARGET_LINK_LIBRARIES(RoxySTL_UnitTest
    PRIVATE RoxySTL doctest::doctest
)

ADD_TEST(NAME RoxySTL_UnitTest COMMAND RoxySTL_UnitTest)
ENDIF()
