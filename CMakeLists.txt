cmake_minimum_required(VERSION 3.25)
project(sfSnake LANGUAGES CXX)

# 设置构建输出目录为 build/，并保留生成的 Makefile
set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# 设置 CMake 生成文件存放目录为 Cmakefiles/

# 设置可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Cpp/OOP/sfsnake)

# 关闭共享库
option(BUILD_SHARED_LIBS OFF)

# 配置 _deps 文件夹路径
include(FetchContent)
set(FETCHCONTENT_BASE_DIR "${PROJECT_SOURCE_DIR}/_deps")

# 配置 SFML 库
FetchContent_Declare(SFML
    GIT_REPOSITORY https://gitee.com/mirrors_laurentgomila/sfml.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# 获取 sources 文件夹下所有 cpp 文件
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/sources/*.cpp")

# 添加可执行文件
add_executable(sfSnake ${SOURCES})

# 链接 SFML 库
target_link_libraries(sfSnake PRIVATE sfml-graphics sfml-audio sfml-window sfml-system sfml-network)

# 设置 C++ 编译标准为 C++23
target_compile_features(sfSnake PRIVATE cxx_std_23)

# Windows 下复制 OpenAL DLL
if(WIN32)
    add_custom_command(
        TARGET sfSnake
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:sfSnake>
        VERBATIM)
endif()

# 安装目标文件
install(TARGETS sfSnake)
