cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
        HUNTER_CACHE_SERVERS
        "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
        CACHE STRING "Default cache server"
)

include("tools/gate/cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.23.214.tar.gz"
        SHA1 "e14bc153a7f16d6a5eeec845fb0283c8fad8c358"
)

project(Threads)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

hunter_add_package(Boost COMPONENTS filesystem log system thread)
find_package(Boost CONFIG REQUIRED filesystem log log_setup system thread)
find_package(Threads)

add_executable(
        ${PROJECT_NAME}
        sources/source.cpp

)

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(
        ${PROJECT_NAME}
        ${CMAKE_THREAD_LIBS_INIT}
        Boost::log_setup
        Boost::log
        Boost::thread
        Boost::filesystem
        Boost::system
)