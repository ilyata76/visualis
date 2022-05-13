cmake_minimum_required (VERSION 3.18)

set (PROJECT_VISUALIS visualis_freeglut) 
project (${PROJECT_VISUALIS})

# ----------- |  | ----------- 

set (ENTRYPOINT_VISUALIS
	source/main.cpp
) 

set (HEADERS_VISUALIS
	source/include/defines.hpp
	source/include/parser-converter/parser-v5.hpp
	source/include/parser-converter/converter-v5.hpp
#	source/include/parser-converter/vvis-parser.hpp
	source/include/sample/creator_of_vertex_arr.hpp
	source/include/sample/point-spin.hpp
	source/include/sample/shape.hpp
	source/include/sample/color_class.hpp
	source/include/sample/drawing_shape_opengl.hpp
)

set (SOURCES_VISUALIS
	source/parser-v5.cpp
	source/converter-v5.cpp
#	source/vvis-parser.cpp
	source/point-spin.cpp
	source/creator_of_vertex_arr.cpp
	source/shape.cpp
	source/color_class.cpp
	source/drawing_shape_opengl.cpp
)

# ----------- |  | ----------- 

message("CALLING TO EXCEPTIO SUBDIRECTORY")

add_subdirectory(source/libraries/tia-Exceptio/)
add_subdirectory(source/libraries/freeglut)

message("CREATING EXECUTABLE FILE")

add_executable (${PROJECT_VISUALIS}
	${ENTRYPOINT_VISUALIS} 
	${HEADERS_VISUALIS} 
	${SOURCES_VISUALIS}
)

# ----------- | LINKING LIBRARIES: Exceptio | ----------- 

message("LINKING LIBRARIES")

find_library(FREGL freeglut)

target_link_libraries(${PROJECT_VISUALIS} 
	EXCEPTIO_CPP_LIBRARY
	freeglut
	freeglut_static
)


# ----||----

set (PROJECT_CONVERTER_VAMPIRE5 converter_v5) 
project (${PROJECT_CONVERTER_VAMPIRE5})

set (ENTRYPOINT_CONVERTER_VAMPIRE5
	source/main_converter_vampire5.cpp
) 

set (HEADERS_CONVERTER_VAMPIRE5
	source/include/parser-converter/parser-v5.hpp
	source/include/parser-converter/converter-v5.hpp
	source/include/defines.hpp
)

set (SOURCES_CONVERTER_VAMPIRE5
	source/parser-v5.cpp
	source/converter-v5.cpp
)

add_executable (${PROJECT_CONVERTER_VAMPIRE5}
	${ENTRYPOINT_CONVERTER_VAMPIRE5}
	${HEADERS_CONVERTER_VAMPIRE5} 
	${SOURCES_CONVERTER_VAMPIRE5}
)

target_link_libraries(${PROJECT_CONVERTER_VAMPIRE5} 
	EXCEPTIO_CPP_LIBRARY
)
