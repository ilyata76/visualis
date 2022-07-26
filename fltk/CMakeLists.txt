cmake_minimum_required(VERSION 3.0)

set (VISUALIS_GUI vvis_gui) 

project(${VISUALIS_GUI} VERSION 0.1.0)

option (FLTK_BUILD_TEST     "Build test/demo programs" OFF)

# ----------- | VISUALIS PROJECT FILES | ----------- 

set (ENTRYPOINT_VISUALIS_GUI
	source/main.cpp
) 

set (HEADERS_VISUALIS_GUI
    source/fltk/widgetlist.hpp
    source/fltk/application.hpp

)
set (SOURCES_VISUALIS_GUI
    source/fltk/widgetlist.cpp
    source/fltk/application.cpp

)
set (RESOURCES_VISUALIS_GUI)

# ----------- | SUBDIRECTORIES | ----------- 

add_subdirectory(source/libraries/fltk)

# ----------- | includes | ----------- 

include_directories(${CMAKE_CURRENT_BINARY_DIR}/source/libraries/fltk fltk) # для config.h

# ----------- | EXECUTABLE | ----------- 

add_executable(${VISUALIS_GUI} 
    ${ENTRYPOINT_VISUALIS_GUI} 
    ${HEADERS_VISUALIS_GUI} 
    ${SOURCES_VISUALIS_GUI}
    ${RESOURCES_VISUALIS_GUI}
)

# ----------- | includes | ----------- 

target_include_directories( ${VISUALIS_GUI} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/source/libraries/fltk ) # для проекта
target_include_directories( ${VISUALIS_GUI} PUBLIC ${CMAKE_CURRENT_LIST_DIR} ) # для проекта

# ----------- | LINKING LIBRARIES | ----------- 

target_link_libraries(${VISUALIS_GUI} fltk)