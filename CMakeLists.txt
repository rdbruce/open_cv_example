cmake_minimum_required(VERSION 3.15)
    project(opencv_example)

    find_package(opencv REQUIRED CONFIG)

    file(GLOB SOURCES "src/*.cpp")
    add_executable(${PROJECT_NAME} ${SOURCES})

    target_link_libraries(${PROJECT_NAME} opencv::opencv)