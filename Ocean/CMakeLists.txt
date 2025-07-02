project(Ocean VERSION 0.1 DESCRIPTION "The Core Engine")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ocean Files
globbert(
    Ocean_ROOT_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Ocean"
    GLOBAL_VAR Ocean_SOURCES
    GROUP_PREFIX "Core"
)

globbert(
    Ocean_PRIMITIVE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Ocean/Primitives"
    RECURSE
    GLOBAL_VAR Ocean_SOURCES
    GROUP_PREFIX "Primitive"
)

globbert(
    Ocean_TYPES_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Ocean/Types"
    RECURSE
    GLOBAL_VAR Ocean_SOURCES
    GROUP_PREFIX "Type"
)

globbert(
    Ocean_CORE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Ocean/Core"
    RECURSE
    GLOBAL_VAR Ocean_SOURCES
    GROUP_PREFIX "Core"
)

globbert(
    Ocean_PLATFORM_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Ocean/Platform"
    RECURSE
    GLOBAL_VAR Ocean_SOURCES
    GROUP_PREFIX "Platform"
)

globbert(
    Ocean_RENDERER_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Ocean/Renderer"
    RECURSE
    GLOBAL_VAR Ocean_SOURCES
    GROUP_PREFIX "Renderer"
)

# globbert(
#     Ocean_AUDIO_FILES
#     "${CMAKE_CURRENT_SOURCE_DIR}/src/Ocean/Audio"
#     RECURSE
#     GROUP_PREFIX "Audio"
#     GLOBAL_VAR Ocean_SOURCES
# )

# Vendor Files (Non-Libraries)
globbert(
    tlsf_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/tlsf"
    GLOBAL_VAR Ocean_VENDOR_SOURCES
    GROUP_PREFIX "tlsf"
)

globbert(
    stb_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb"
    GLOBAL_VAR Ocean_VENDOR_SOURCES
    GROUP_PREFIX "stb"
)

add_library(
    ${PROJECT_NAME}

    ${Ocean_SOURCES}
    ${Ocean_VENDOR_SOURCES}
)

target_include_directories(
    ${PROJECT_NAME}
    
    PUBLIC ${OCEAN_SRC_DIRECTORY}
)

target_include_directories(
    ${PROJECT_NAME} SYSTEM

    PRIVATE ${GLAD_DIRECTORY}
    PRIVATE ${TLSF_DIRECTORY}
    PRIVATE ${STB_DIRECTORY}
    PRIVATE ${CR_DIRECTORY}
    PUBLIC  ${GLM_DIRECTORY}

    PRIVATE ${OpenGL_INCLUDE_DIRS}
    PRIVATE ${Vulkan_INCLUDE_DIRS}
)

target_link_libraries(
    ${PROJECT_NAME}

    PRIVATE glfw
    PRIVATE glad
    PRIVATE SteamAudio
    PRIVATE flecs::flecs_static
    PRIVATE glslang
    PRIVATE Vulkan::Vulkan

    PUBLIC glm::glm-header-only
)

set_target_properties(
    ${PROJECT_NAME} PROPERTIES

    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}

    PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/src/Ocean/Ocean.hpp
)

target_compile_options(
    ${PROJECT_NAME} PRIVATE

    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>: ${OCEAN_COMPILE_FLAGS}>

    $<$<CXX_COMPILER_ID:MSVC>: /W4>
)

target_compile_definitions(
    ${PROJECT_NAME}

    PRIVATE $<$<PLATFORM_ID:Windows>: WIN32_LEAN_AND_MEAN>
    PUBLIC $<$<CONFIG:Debug>: OC_DEBUG>
    PUBLIC $<$<CONFIG:Release>: OC_RELEASE>
)
