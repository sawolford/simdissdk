project(SIMDIS_SDK)

# Configure various version fields
set(SIMDIS_SDK_MAJOR_VERSION 1)
set(SIMDIS_SDK_MINOR_VERSION 18)
set(SIMDIS_SDK_REVISION_VERSION 0)
set(SIMDIS_SDK_SOVERSION 18)
set(SIMDIS_SDK_VERSION_STRING ${SIMDIS_SDK_MAJOR_VERSION}.${SIMDIS_SDK_MINOR_VERSION}.${SIMDIS_SDK_REVISION_VERSION} CACHE INTERNAL "SIMDIS SDK Version String" FORCE)

# Applies version data to static and shared library targets
macro(ApplySDKVersion TARGET)
    set_target_properties(${TARGET} PROPERTIES
        VERSION ${SIMDIS_SDK_VERSION_STRING}
        SOVERSION ${SIMDIS_SDK_SOVERSION}
    )
    # Apply a prefix of the SOVERSION on Windows platform to the DLL names
    if(WIN32)
        # Do not apply to static libraries
        get_target_property(TARGET_TYPE ${TARGET} TYPE)
        if(TARGET_TYPE STREQUAL "SHARED_LIBRARY")
            set_target_properties(${TARGET} PROPERTIES PREFIX "sdk${SIMDIS_SDK_SOVERSION}-")
        endif()
    endif()
endmacro()

# Include the definition for installing shared objects post-build
include(PostBuildInstallSharedObjects)

option(BUILD_SIMDATA "If off, simData SDK libraries are not compiled; if on, library is built if dependencies are satisfied." ON)
option(BUILD_SIMVIS "If off, simVis SDK libraries are not compiled; if on, library is built if dependencies are satisfied." ON)
option(BUILD_SIMUTIL "If off, simUtil SDK libraries are not compiled; if on, library is built if dependencies are satisfied." ON)
option(BUILD_SIMQT "If off, simQt SDK libraries are not compiled; if on, library is built if dependencies are satisfied." ON)

add_subdirectory(simNotify)
add_subdirectory(simCore)
if(BUILD_SIMDATA)
    add_subdirectory(simData)
endif()
if(BUILD_SIMVIS)
    add_subdirectory(simVis)
endif()
if(BUILD_SIMUTIL)
    add_subdirectory(simUtil)
endif()
if(QT_FOUND AND BUILD_SIMQT)
    add_subdirectory(simQt)
endif()
