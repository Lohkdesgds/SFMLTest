cmake_minimum_required(VERSION 3.28)

project(MainApp VERSION 1.0)

set(SFML_STATIC_LIBRARIES TRUE)

file(GLOB_RECURSE MAIN_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    main.cpp
)

add_executable(
    ${PROJECT_NAME} WIN32
    ${MAIN_SRCS}    
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/impl
    ${DEPS_INCLUDES}
#    ${CURL_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
#    ${CURL_LIBRARIES}
    SFML::Audio
    SFML::Graphics
    SFML::Network
    SFML::System
    SFML::Window    
)

# Embedded files
b_embed(${PROJECT_NAME} "assets/EMprint-Regular.ttf")
b_embed(${PROJECT_NAME} "assets/misu.png")