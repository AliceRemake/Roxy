if(MSVC)
    ADD_COMPILE_OPTIONS(/GR- /W4 /WX /wd4530 /nologo)
    ADD_COMPILE_DEFINITIONS("_HAS_EXCEPTIONS=0")
else()
    ADD_COMPILE_OPTIONS(-fno-rtti -fno-exceptions -Wall -Wextra -Werror)
endif()

# Plugin
ADD_SUBDIRECTORY(Plugin)

# Roxy
ADD_EXECUTABLE(Roxy Roxy.cpp)

TARGET_LINK_LIBRARIES(Roxy PRIVATE
    RoxyAlloc
    RoxyChrono
    RoxyLog
    RoxyFmt
    RoxySTD
)
