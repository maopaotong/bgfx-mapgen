#
cmake_minimum_required(VERSION 3.16)
option(BUILD_GAME "Build game" ON)

set(PROJECT_NAME, "game")
project(game LANGUAGES CXX)

# 设置全局标准（可选）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#  find_package
find_package(bgfx CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

# shaderc
set(SHADERC "D:/git/bgfx.cmake/build/cmake/bgfx/Debug/shaderc.exe")
set(SHADER_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/shaders)
set(GEN_DIR  ${CMAKE_CURRENT_BINARY_DIR}/generated)
set(FS_IN  ${SHADER_DIR}/vertex.sc)
set(VARYING  ${SHADER_DIR}/varying.def.sc)
set(FS_OUT  ${GEN_DIR}/shaders/fs_sc.h)
set(BGFX_SHADER_INCLUDE "${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include/bgfx")

file(MAKE_DIRECTORY  ${GEN_DIR}/shaders)

add_custom_command(
    OUTPUT  ${FS_OUT}
    COMMAND  ${SHADERC}
        -f  ${FS_IN}
        -o  ${FS_OUT}
        --type vertex
        --profile 130
        --platform windows
        -i ${SHADER_DIR}
        -i ${BGFX_SHADER_INCLUDE}
        --varyingdef  ${VARYING}
    DEPENDS  ${FS_IN}  ${VARYING}
    COMMENT "Compiling sc"
)

add_custom_target(shaders ALL DEPENDS  ${FS_OUT})

# source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
if(MSVC)
    add_compile_options(/Zc:__cplusplus)
    add_compile_options(/Zc:preprocessor)
    add_compile_options(/utf-8)
endif()

add_executable(game ${SOURCES})

get_target_property(COMPILE_FLAGS ${PROJECT_NAME} COMPILE_OPTIONS)

message(STATUS "C++ Compile Flags: ${COMPILE_FLAGS}")

bgfx_compile_shaders(
  TYPE FRAGMENT
  SHADERS material/vertex.sc
  VARYING_DEF ${CMAKE_SOURCE_DIR}/varying.def.sc
  OUTPUT_DIR ${CMAKE_BINARY_DIR}/include/generated/shaders
  AS_HEADERS
)

target_link_libraries(game PRIVATE fog-util bgfx::bgfx bgfx::bx bgfx::bimg bgfx::bimg_decode glfw imgui::imgui)        
#
target_compile_options(game PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/utf-8>
    $<$<CXX_COMPILER_ID:MSVC>:/bigobj>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-finput-charset=UTF-8 -fexec-charset=UTF-8>
)

target_include_directories(game PRIVATE include)

