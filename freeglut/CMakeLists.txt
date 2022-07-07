cmake_minimum_required (VERSION 3.16)

set (VISUALIS vvis) 

project (${VISUALIS} VERSION 0.2.0)

# ----------- | VISUALIS PROJECT : OPTIONS | ----------- 

option(USE_STATIC "Use static freeglut library" ON)
option(COMPILE_FREEGLUT_EXAMPLES "Compile freeglut examples?" OFF)

message("[visualis] : USE STATIC FREEGLUT LIBRARIES: " ${USE_STATIC})
message("[visualis] : COMPILE FREEGLUT EXAMPLES: " ${COMPILE_FREEGLUT_EXAMPLES})

if(USE_STATIC)
 	option(FREEGLUT_BUILD_SHARED_LIBS "USE SHARED FREEGLUT LIBRARY" OFF)
 	option(FREEGLUT_BUILD_STATIC_LIBS "USE STATIC_FREEGLUT LIBRARY" ON)
else()
 	option(FREEGLUT_BUILD_SHARED_LIBS "USE SHARED FREEGLUT LIBRARY" ON)
 	option(FREEGLUT_BUILD_STATIC_LIBS "USE STATIC_FREEGLUT LIBRARY" OFF)	
endif()

option(JSON_BuildTests "" OFF)

if (COMPILE_FREEGLUT_EXAMPLES)
	option(FREEGLUT_BUILD_DEMOS "freeglut demos" ON)
else()
	option(FREEGLUT_BUILD_DEMOS "freeglut demos" OFF)
endif()

# ----------- | VISUALIS PROJECT FILES | ----------- 

set (ENTRYPOINT_VISUALIS
	source/main.cpp
) 

set (HEADERS_VISUALIS
	source/helpful/global_defines.hpp
	
	source/helpful/useful_functions.hpp
	source/helpful/useful_classes.hpp
	source/color/RGB.hpp

	source/settings/global_settings.hpp
	source/settings/freeglut_settings.hpp
	source/settings/other_settings.hpp
	source/settings/settings.hpp

	
	source/console/defines_commands_codes.hpp
	source/console/console_interpretator.hpp

	source/vampire5/parser-converter.hpp

	source/vertex-shape/point.hpp
	source/vertex-shape/spin.hpp
	source/vertex-shape/vertex.hpp
	source/vertex-shape/shape.hpp

	source/console/freeglut_drawer.hpp

)

set (SOURCES_VISUALIS
	source/helpful/useful_classes.cpp
	source/helpful/useful_functions.cpp
	source/color/RGB.cpp

	source/settings/global_settings.cpp
	source/settings/freeglut_settings.cpp
	source/settings/other_settings.cpp
	source/settings/settings.cpp

	source/console/console_interpretator.cpp

	source/vampire5/parser-converter.cpp

	source/vertex-shape/vertex.cpp
	source/vertex-shape/shape.cpp

	source/console/freeglut_drawer.cpp

)

set (RESOURCES_VISUALIS
	source/rc/vvis.rc
)

# ----------- | SUBDIRECTORIES | ----------- 

message("[visualis] : CALLING TO EXCEPTIO SUBDIRECTORY")
add_subdirectory(source/libraries/exceptio)

message("[visualis] : CALLING TO FREEGLUT SUBDIRECTORY")
add_subdirectory(source/libraries/freeglut)

message("[visualis] : CALLING TO JSON SUBDIRECTORY")
add_subdirectory(source/libraries/json)

message("[visualis] : CREATING AN EXECUTABLE VISUALIS_FREEGLUT FILE")

# ----------- | EXECUTABLE | ----------- 

add_executable (${VISUALIS}
	${ENTRYPOINT_VISUALIS} 
	${HEADERS_VISUALIS} 
	${SOURCES_VISUALIS}
	${RESOURCES_VISUALIS}
)

# ----------- | LINKING LIBRARIES | ----------- 

message("[visualis] : LINKING LIBRARIES : exceptio")

SET(libs_glu ${OPENGL_glu_LIBRARY} ${LIBS})
#SET(libs_gl ${OPENGL_gl_LIBRARY} ${LIBS})

target_link_libraries( ${VISUALIS} 
	EXCEPTIO_CPP_LIBRARY
)

message("[visualis] : LINKING LIBRARIES : freeglut")

if(USE_STATIC)
	find_library(FREGL freeglut_static)
	target_link_libraries( ${VISUALIS} 
		freeglut_static
		${libs_glu}
		#${libs_gl}
	)
else()
	find_library(FREGL freeglut)
	target_link_libraries( ${VISUALIS} 
		freeglut
		${libs_glu}
		#${libs_gl}
	)
endif()
