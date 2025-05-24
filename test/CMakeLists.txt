cmake_minimum_required(VERSION 3.28)

project(TestApp VERSION 1.0)

file(GLOB_RECURSE TEST_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    main_test.cpp
)

add_executable(
    ${PROJECT_NAME}
    ${TEST_SRCS}
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
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

add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
)