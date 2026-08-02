SET(ThirdPartyLibraries
)

SET(PrivateDependPlugins
)

SET(PublicDependPlugins
    RoxySTD
    RoxyLog
)

ADD_LIBRARY(RoxyChrono STATIC
    RoxyChrono.h
    RoxyChrono.cpp
)

TARGET_INCLUDE_DIRECTORIES(RoxyChrono
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

TARGET_LINK_LIBRARIES(RoxyChrono
    PRIVATE ${PrivateDependPlugins}
    PUBLIC  ${PublicDependPlugins}
    PUBLIC  ${ThirdPartyLibraries}
)

# Unit Test
ADD_EXECUTABLE(RoxyChrono_UnitTest
    RoxyChrono_UnitTest.cpp
)

TARGET_LINK_LIBRARIES(RoxyChrono_UnitTest
    PRIVATE RoxyChrono doctest::doctest
)
