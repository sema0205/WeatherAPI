cmake_minimum_required(VERSION 3.12)
set(CMAKE_EXE_LINKER_FLAGS "-static")

project(
        labwork10
        VERSION 1.0
        DESCRIPTION "C++ Year 2022 Labwork10"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS OFF)

add_subdirectory(lib)
add_subdirectory(bin)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git GIT_TAG 1.10.2)
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

FetchContent_Declare(ftxui GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui GIT_TAG v4.0.0)
FetchContent_MakeAvailable(ftxui)