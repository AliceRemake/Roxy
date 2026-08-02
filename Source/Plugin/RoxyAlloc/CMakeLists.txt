SET(ThirdPartyLibraries
)

SET(PrivateDependPlugins
    RoxyLog
)

SET(PublicDependPlugins
    RoxySTD
)

ADD_LIBRARY(RoxyAlloc STATIC
    RoxyAlloc.h
    RoxyAlloc.cpp
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
ADD_EXECUTABLE(RoxyAlloc_UnitTest
    RoxyAlloc_UnitTest.cpp
)

TARGET_LINK_LIBRARIES(RoxyAlloc_UnitTest
    PRIVATE RoxyAlloc doctest::doctest
)
