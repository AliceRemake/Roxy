SET(ThirdPartyLibraries
)

SET(PrivateDependPlugins
)

SET(PublicDependPlugins
)

ADD_LIBRARY(RoxySTD STATIC
    RoxySTD/RoxyAlias.h
    RoxySTD/RoxyAlias.cpp
    RoxySTD/RoxyThreadSafety.h
    RoxySTD/RoxyThreadSafety.cpp
    RoxySTD/RoxyQueue.h
    RoxySTD/RoxyQueue.cpp
    RoxySTD/RoxySTD.h
    RoxySTD/RoxySTD.cpp
)

TARGET_INCLUDE_DIRECTORIES(RoxySTD
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

TARGET_LINK_LIBRARIES(RoxySTD
    PRIVATE ${ThirdPartyLibraries} ${PrivateDependPlugins}
    PUBLIC ${PublicDependPlugins}
)

IF(ROXY_BUILD_TEST)
# Unit Test
ADD_EXECUTABLE(RoxySTD_UnitTest
    RoxySTD/RoxySTD_UnitTest.cpp
)

TARGET_LINK_LIBRARIES(RoxySTD_UnitTest
    PRIVATE RoxySTD doctest::doctest
)

ADD_TEST(NAME RoxySTD_UnitTest COMMAND RoxySTD_UnitTest)
ENDIF()
