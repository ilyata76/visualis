cmake_minimum_required (VERSION 3.18)

set (PROJECT VISUALIS_OPENGL) 
project (${PROJECT})

set (ENTRYPOINT
	source/main.cpp
) 

set (HEADERS
	source/include/parser-converter/parser-v5.hpp
    source/include/parser-converter/converter-v5.hpp
	source/include/defines.hpp

)

set (SOURCES
	source/converter-v5.cpp
    source/parser-v5.cpp
)

add_subdirectory(source/libraries/tia-Exceptio/)

add_executable (${PROJECT}
	${ENTRYPOINT} 
	${HEADERS} 
	${SOURCES}
)
 target_link_libraries(${PROJECT} 
	EXCEPTIO_CPP_LIBRARY
)
