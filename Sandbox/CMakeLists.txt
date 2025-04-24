project(Sandbox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

globbert(
    Sandbox_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    GROUP_PREFIX "Sandbox SRC"
)

add_executable(
    ${PROJECT_NAME} 

    ${Sandbox_SRC}
)

target_include_directories(
    ${PROJECT_NAME}
    
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

target_include_directories(
    ${PROJECT_NAME} SYSTEM

    PRIVATE ${Vulkan_INCLUDE_DIRS}
)

target_link_libraries(
    ${PROJECT_NAME}

    PRIVATE Ocean
)

target_compile_options(
    ${PROJECT_NAME} PRIVATE

    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>: ${OCEAN_COMPILE_FLAGS}>

    $<$<CXX_COMPILER_ID:MSVC>: /W4>
)
