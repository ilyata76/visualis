# MAKES LIBRARY
# MIN VERSION
cmake_minimum_required(VERSION 3.18)

# SET PROJECT
project(EXCEPTIO_CPP_LIBRARY)

set (HEADERS 
    include/tia/exceptio.hpp
    include/tia/assert.hpp
)

set (SOURCES 
    src/exceptio.cpp
)

add_library ( ${PROJECT_NAME}
    STATIC 
    ${HEADERS}
    ${SOURCES}
)