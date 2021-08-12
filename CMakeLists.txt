#--------------------------------------
#	MIN_VERSION
#--------------------------------------

cmake_minimum_required (VERSION 3.18)


#--------------------------------------
#	SET PROJECT
#--------------------------------------

set (PROJECT PROJECT_OPENGL)
project (${PROJECT})


#--------------------------------------
#	DETERMINATE HEAD- AND 
#	SOURCES-FILES
#--------------------------------------

set (ENTRYPOINT
	src/main.cpp
) 

set (HEADERS
	src/include/visvamp.hpp
	src/include/visvamp/vampparse.hpp
	src/include/visvamp/vampsample.hpp
)

set (SOURCES
	src/src/visvamp/vampparse.cpp
	src/src/visvamp/vampsample.cpp
)

#--------------------------------------
#	EXECUTABLE
#--------------------------------------

add_executable (${PROJECT} 
	${ENTRYPOINT} 
	${HEADERS} 
	${SOURCES}
)

set_target_properties(${PROJECT} PROPERTIES
	LANGUAGES CXX
	CXX_STANDART 17
	CXX_STANDART_REQUIRED ON
)

#--------------------------------------
# 
#--------------------------------------

target_include_directories(${PROJECT}
	PRIVATE ${PROJECT_SOURCE_DIR}/src/include
	PRIVATE ${PROJECT_SOURCE_DIR}/src/include/freeglut
)

target_link_directories(${PROJECT}
	PRIVATE ${PROJECT_SOURCE_DIR}
)

#--------------------------------------
# 
#--------------------------------------