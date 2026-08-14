SET(ThirdPartyLibraries
)

SET(PrivateDependPlugins
)

SET(PublicDependPlugins
    RoxySTD
)

ADD_LIBRARY(RoxyMath STATIC
    RoxyMath/RoxyMathQuat.h
    RoxyMath/RoxyMathQuat.cpp
    RoxyMath/SIMD/RoxyMathMatSIMD.h
    RoxyMath/SIMD/RoxyMathMatSIMD.cpp
    RoxyMath/RoxyMathMat.h
    RoxyMath/RoxyMathMat.cpp
    RoxyMath/SIMD/RoxyMathVecSIMD.h
    RoxyMath/SIMD/RoxyMathVecSIMD.cpp
    RoxyMath/RoxyMathVec.h
    RoxyMath/RoxyMathVec.cpp
    RoxyMath/RoxyMathCommon.h
    RoxyMath/RoxyMathCommon.cpp
    RoxyMath/RoxyMath.h
    RoxyMath/RoxyMath.cpp
)

TARGET_INCLUDE_DIRECTORIES(RoxyMath
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

TARGET_LINK_LIBRARIES(RoxyMath
    PRIVATE ${PrivateDependPlugins}
    PUBLIC  ${PublicDependPlugins}
    PUBLIC  ${ThirdPartyLibraries}
)

IF(ROXY_BUILD_TEST)
# Unit Test
ADD_EXECUTABLE(RoxyMath_UnitTest
    RoxyMath/RoxyMath_UnitTest.cpp
)

TARGET_LINK_LIBRARIES(RoxyMath_UnitTest
    PRIVATE RoxyMath RoxyChrono RoxyLog doctest::doctest
)

ADD_TEST(NAME RoxyMath_UnitTest COMMAND RoxyMath_UnitTest)
ENDIF()
