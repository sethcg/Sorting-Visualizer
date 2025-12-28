IF(NOT TARGET googletest)

    INCLUDE(FetchContent)

    FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
    )
    FetchContent_MakeAvailable(googletest)

    # FOR WINDOWS: PREVENT OVERRIDING PARENT PROJECT COMPILER/LINKER SETTINGS
    SET(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    ADD_LIBRARY(googletest INTERFACE IMPORTED)

    TARGET_LINK_LIBRARIES(googletest INTERFACE gtest)

ENDIF()