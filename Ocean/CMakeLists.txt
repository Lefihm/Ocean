project(Ocean VERSION 0.1 DESCRIPTION "The Core Engine")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GLob all of the following files in the directories.

# Root Files
file(GLOB Ocean_ROOT_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/src/Ocean/*.hpp)

file(GLOB Ocean_PRIMI_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/src/Ocean/Primitives/*.hpp)
file(GLOB Ocean_PRIMI_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/Ocean/Primitives/*.cpp)

file(GLOB Ocean_TYPES_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/src/Ocean/Types/*.hpp)
file(GLOB Ocean_TYPES_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/Ocean/Types/*.cpp)

# Core Files
file(GLOB Ocean_CORE_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/src/Ocean/Core/*.hpp)
file(GLOB Ocean_CORE_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/Ocean/Core/*.cpp)

file(GLOB Ocean_LAYER_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/src/Ocean/Core/Layers/*.hpp)
file(GLOB Ocean_LAYER_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/Ocean/Core/Layers/*.cpp)

# Platform Files
file(GLOB Ocean_PLAT_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/src/Ocean/Platform/*.hpp)
file(GLOB Ocean_PLAT_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/Ocean/Platform/*.cpp)

# Renderer Files
file(GLOB Ocean_REND_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/src/Ocean/Renderer/*.hpp)
file(GLOB Ocean_REND_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/Ocean/Renderer/*.cpp)

file(GLOB Ocean_CA_REND_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/src/Ocean/Renderer/Camera/*.hpp)
file(GLOB Ocean_CA_REND_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/Ocean/Renderer/Camera/*.cpp)

file(GLOB Ocean_GL_REND_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/src/Ocean/Renderer/OpenGL/*.hpp)
file(GLOB Ocean_GL_REND_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/Ocean/Renderer/OpenGL/*.cpp)

#Audio Files
file(GLOB Ocean_AUD_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/src/Audio/*.hpp)
file(GLOB Ocean_AUD_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/Audio/*.cpp)

# Vendor Files (Non-Libraries)
## TLSF
file(GLOB tlsf_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/vendor/tlsf/*.h)
file(GLOB tlsf_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/vendor/tlsf/*.c)

# STB
file(GLOB stb_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb/*.h)

# CR
file(GLOB cr_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/vendor/cr/*.h)

# Group all of the files per their source for IDE / Editor

source_group("Root Header" FILES ${Ocean_ROOT_HEADER})

source_group("Core Headers" FILES ${Ocean_CORE_HEADER})
source_group("Core Sources" FILES ${Ocean_CORE_SOURCE})

source_group("Primitive Headers" FILES ${Ocean_PRIMI_HEADER})
source_group("Primitive Sources" FILES ${Ocean_PRIMI_SOURCE})
source_group("Type Headers" FILES ${Ocean_TYPES_HEADER})
source_group("Type Sources" FILES ${Ocean_TYPES_SOURCE})
source_group("Input Headers" FILES ${Ocean_INPUT_HEADER})
source_group("Input Sources" FILES ${Ocean_INPUT_SOURCE})
source_group("Layer Headers" FILES ${Ocean_LAYER_HEADER})
source_group("Layer Sources" FILES ${Ocean_LAYER_SOURCE})

source_group("Platform Headers" FILES ${Ocean_PLAT_HEADER})
source_group("Platform Sources" FILES ${Ocean_PLAT_SOURCE})
source_group("Window Headers" FILES ${Ocean_WIND_HEADER})
source_group("Window Sources" FILES ${Ocean_WIND_SOURCE})

source_group("Renderer Headers" FILES ${Ocean_REND_HEADER})
source_group("Renderer Sources" FILES ${Ocean_REND_SOURCE})

source_group("OpenGL Renderer Headers" FILES ${Ocean_GL_REND_HEADER})
source_group("OpenGL Renderer Sources" FILES ${Ocean_GL_REND_SOURCE})

source_group("Vulkan Renderer Headers" FILES ${Ocean_VK_REND_HEADER})
source_group("Vulkan Renderer Sources" FILES ${Ocean_VK_REND_SOURCE})

source_group("Main Audio headers" FILES ${Ocean_AUD_HEADER})
source_group("Main Audio Sources" FILES ${Ocean_AUD_SOURCE})

source_group("tlsf Headers" FILES ${tlsf_HEADER})
source_group("tlsf Sources" FILES ${tlsf_SOURCE})

source_group("stb Headers" FILES ${stb_HEADER})

add_library(
    ${PROJECT_NAME}

    ${Ocean_ROOT_HEADER}

    ${Ocean_CORE_HEADER}    ${Ocean_CORE_SOURCE}
    ${Ocean_PRIMI_HEADER}   ${Ocean_PRIMI_SOURCE}
    ${Ocean_TYPES_HEADER}   ${Ocean_TYPES_SOURCE}
    ${Ocean_INPUT_HEADER}   ${Ocean_INPUT_SOURCE}
    ${Ocean_LAYER_HEADER}   ${Ocean_LAYER_SOURCE}

    ${Ocean_PLAT_HEADER}    ${Ocean_PLAT_SOURCE}
    ${Ocean_WIND_HEADER}    ${Ocean_WIND_SOURCE}

    ${Ocean_REND_HEADER}    ${Ocean_REND_SOURCE}
    ${Ocean_CA_REND_HEADER} ${Ocean_CA_REND_SOURCE}
    ${Ocean_GL_REND_HEADER} ${Ocean_GL_REND_SOURCE}
    ${Ocean_VK_REND_HEADER} ${Ocean_VK_REND_SOURCE}

    ${tlsf_HEADER} ${tlsf_SOURCE}
    ${stb_HEADER}
    ${cr_HEADER}
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
    PRIVATE ${OPENGL_LIBRARIES}

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
