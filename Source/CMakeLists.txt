if(MSVC)
    ADD_COMPILE_OPTIONS(/GR- /W4 /WX /wd4530)
    ADD_COMPILE_DEFINITIONS("_HAS_EXCEPTIONS=0")
endif()

# Plugin
ADD_SUBDIRECTORY(Plugin)

# Roxy
ADD_EXECUTABLE(Roxy Roxy.h Roxy.cpp)

TARGET_LINK_LIBRARIES(Roxy PRIVATE
    RoxyLog
    RoxyFmt
    RoxyReflect
    RoxySTD
)
