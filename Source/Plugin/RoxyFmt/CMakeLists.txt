SET(ThirdPartyLibraries
    fmt
)

SET(PrivateDependPlugins
)

SET(PublicDependPlugins
    RoxySTD
)

ADD_LIBRARY(RoxyFmt STATIC
    RoxyFmt.h
    RoxyFmt.cpp
)

TARGET_INCLUDE_DIRECTORIES(RoxyFmt
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

TARGET_LINK_LIBRARIES(RoxyFmt
    PRIVATE ${PrivateDependPlugins}
    PUBLIC  ${PublicDependPlugins}
    PUBLIC  ${ThirdPartyLibraries}
)

# Unit Test
ADD_EXECUTABLE(RoxyFmt_UnitTest
    RoxyFmt_UnitTest.cpp
)

TARGET_LINK_LIBRARIES(RoxyFmt_UnitTest
    PRIVATE RoxyFmt doctest::doctest
)
