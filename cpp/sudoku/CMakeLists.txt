# cmake 最低的版本要求
cmake_minimum_required(VERSION 3.15)

# 工程名
PROJECT(sudoku)

# 添加c++11标准支持
# set(CMAKE_CXX_FLAGS, "${CMAKE_CXX_FLAGS} -std=c++11")
add_definitions(-std=c++11)

set(CMAKE_BUILD_TYPE, "Debug")

# Debug模式下 gdb设置
set(CMAKE_CXX_FLAGS_DEBUG, "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
# Release模式下 gdb设置
set(CMAKE_CXX_FLAGS_RELEASE, "$ENV{CXXFLAGS} -O3 -Wall")

# 相当于代码中 #define DEBUG
add_definitions(-DDEBUG)
# 可执行文件输出目录
set(EXECUTABLE_OUTPUT_PATH, "${PROJECT_SOURCE_DIR}/bin")

# 头文件包含目录
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include")

# 区分操作系统
MESSAGE("Indentifying operating OS....")
if(WIN32)
    MESSAGE("This is Windows.")
elseif(APPLE)
    MESSAGE("This is MacOS.")
elseif(UNIX)
    MESSAGE("This is Linux.")
endif()

# 添加源代码文件夹
AUX_SOURCE_DIRECTORY(src DIR_SRCS)

# 输出可执行文件
add_executable(sudoku ${DIR_SRCS})