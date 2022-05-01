cmake_minimum_required (VERSION 3.18)

set (PROJECT VISUALIS_OPENGL) 
project (${PROJECT})

# ----------- |  | ----------- 

set (ENTRYPOINT
	source/main.cpp
) 

set (HEADERS
	source/include/defines.hpp
	source/include/parser-converter/parser-v5.hpp
	source/include/parser-converter/converter-v5.hpp
#	source/include/parser-converter/vvis-parser.hpp
	source/include/sample/creator_of_vertex_arr.hpp
	source/include/sample/point-spin.hpp
)

set (SOURCES
	source/parser-v5.cpp
	source/converter-v5.cpp
#	source/vvis-parser.cpp
	source/point-spin.cpp
	source/creator_of_vertex_arr.cpp
)

# ----------- |  | ----------- 

message("CALLING TO EXCEPTIO SUBDIRECTORY")

add_subdirectory(source/libraries/tia-Exceptio/)

message("CREATING EXECUTABLE FILE")

add_executable (${PROJECT}
	${ENTRYPOINT} 
	${HEADERS} 
	${SOURCES}
)

# ----------- | LINKING LIBRARIES: Exceptio | ----------- 

message("LINKING LIBRARIES")

target_link_libraries(${PROJECT} 
	EXCEPTIO_CPP_LIBRARY
)
