# MAKES LIBRARY
# MIN VERSION
cmake_minimum_required(VERSION 3.18)

# SET PROJECT
project(EXCEPTIO_CPP_LIBRARY)

# set (ENTRYPOINT
# 	./example/main.cpp
# )

set (HEADERS 
    ./include/exceptio.hpp
    ./include/assert.hpp
)

set (SOURCES 
    ./src/exceptio.cpp
)

# add_executable(${PROJECT_NAME}
# 	${ENTRYPOINT}
# 	${HEADERS}
# 	${SOURCES}
# )

add_library ( ${PROJECT_NAME}
    STATIC 
    ${HEADERS}
    ${SOURCES}
)