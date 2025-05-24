cmake_minimum_required(VERSION 3.28)

# Check later
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(ProjectRoot)

# ==== SETUP BASE ==== #
message(STATUS "Executing GIT submodule update and init")
execute_process( COMMAND git submodule update --init --recursive )
# This didn't work directly. Perhaps I can fix this in the future.
#if(UNIX AND NOT APPLE)
#    message(STATUS "Installing needed libraries for SFML on Linux...")
#    execute_process(COMMAND "sudo apt update")
#    execute_process(COMMAND "sudo apt install libxrandr-dev libxcursor-dev libxi-dev libudev-dev libflac-dev libvorbis-dev libgl1-mesa-dev libegl1-mesa-dev libdrm-dev libgbm-dev libfreetype-dev")
#    #message(STATUS "Running apt-get install")
#    #execute_process(COMMAND sudo apt-get install libcurl4-openssl-dev)
#endif()


# ==== SETUP VARIABLES ==== #
file(GLOB_RECURSE DEPS_SRCS "deps/**/*.h")
set(DEPS_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/deps
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/json/single_include
    #${CMAKE_CURRENT_SOURCE_DIR}/deps/battery-embed/include
    #${CMAKE_CURRENT_SOURCE_DIR}/deps/battery-embed/src
    #${CMAKE_CURRENT_SOURCE_DIR}/deps/SFML/include
)


# ==== SETUP DEPENDENCIES ==== #
include(FetchContent)
message(STATUS "Fetching dependencies")

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
  battery-embed
  GIT_REPOSITORY https://github.com/batterycenter/embed.git
  GIT_TAG        v1.2.19
)
FetchContent_MakeAvailable(battery-embed)

# ==== SET CXX STANDARD ==== #
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==== INCLUDING CURL ==== #
#find_package(CURL REQUIRED)

# ==== ENABLING TESTING ==== #
enable_testing()

# ==== ADDING PROJECTS ==== #
add_subdirectory(main)
#add_subdirectory(test) # No need for now, this is just a test project