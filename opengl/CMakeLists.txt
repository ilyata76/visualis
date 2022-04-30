cmake_minimum_required (VERSION 3.18)

set (PROJECT VISUALIS_OPENGL) 
project (${PROJECT})

set (ENTRYPOINT
	source/main.cpp
) 

set (HEADERS
	source/include/parser-converter/parser-v5.hpp
    source/include/parser-converter/converter.hpp
)


set (SOURCES
	source/converter.cpp
    source/parser-v5.cpp
)

add_executable (${PROJECT} 
	${ENTRYPOINT} 
	${HEADERS} 
	${SOURCES}
)