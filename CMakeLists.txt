cmake_minimum_required(VERSION 3.5)

project(tetris LANGUAGES CXX)

IF (WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
ENDIF()

find_package(SFML 2.5.2 COMPONENTS graphics audio REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tetris main.cpp)

set(RESOURCE_FILES
    "resources/font/font.ttf"
    "resources/img/background.png"
    "resources/img/squares.png"
)

foreach(RESOURCE ${RESOURCE_FILES})
    configure_file(${CMAKE_SOURCE_DIR}/${RESOURCE} ${CMAKE_BINARY_DIR}/${RESOURCE} COPYONLY)
endforeach()

include(GNUInstallDirs)
install(TARGETS tetris
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_link_libraries(tetris sfml-graphics sfml-audio)
