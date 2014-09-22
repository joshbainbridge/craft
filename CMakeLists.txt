CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
PROJECT( "craft" )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules/)

set( SRC src)
set( INC include)

SET( PROJ_SOURCES
	${SRC}/main.cpp
	${SRC}/shaderProgram.cpp
	${SRC}/settings.cpp
	${SRC}/simplex.c
	${SRC}/segment.cpp
	${SRC}/chunk.cpp
	${SRC}/chunkController.cpp
	${SRC}/character.cpp
	${SRC}/state.cpp
	${SRC}/stateGame.cpp
	${SRC}/stateController.cpp
	${SRC}/shaderVoxel.cpp
	${SRC}/plane.cpp
	${SRC}/octreeNode.cpp
	)
SET( PROJ_HEADERS
	${INC}/${CMAKE_PROJECT_NAME}/platformSpecification.hpp
	${INC}/${CMAKE_PROJECT_NAME}/shaderProgram.hpp
	${INC}/${CMAKE_PROJECT_NAME}/settings.hpp
	${INC}/${CMAKE_PROJECT_NAME}/simplex.hpp
	${INC}/${CMAKE_PROJECT_NAME}/segment.hpp
	${INC}/${CMAKE_PROJECT_NAME}/chunk.hpp
	${INC}/${CMAKE_PROJECT_NAME}/chunkController.hpp
	${INC}/${CMAKE_PROJECT_NAME}/character.hpp
	${INC}/${CMAKE_PROJECT_NAME}/state.hpp
	${INC}/${CMAKE_PROJECT_NAME}/stateGame.hpp
	${INC}/${CMAKE_PROJECT_NAME}/stateController.hpp
	${INC}/${CMAKE_PROJECT_NAME}/shaderVoxel.hpp
	${INC}/${CMAKE_PROJECT_NAME}/plane.hpp
	${INC}/${CMAKE_PROJECT_NAME}/octreeNode.hpp
	)

ADD_EXECUTABLE( ${CMAKE_PROJECT_NAME} ${PROJ_SOURCES} ${PROJ_HEADERS} )

FIND_PACKAGE( OpenGL REQUIRED )
FIND_PACKAGE( GLFW REQUIRED )
FIND_PACKAGE( GLM REQUIRED )

IF( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
	
	find_package( GLEW REQUIRED )
	if ( GLEW_FOUND )
		INCLUDE_DIRECTORIES( ${GLEW_INCLUDE_DIR} )
		TARGET_LINK_LIBRARIES ( ${CMAKE_PROJECT_NAME} ${GLEW_LIBRARY} )
	endif ( GLEW_FOUND )
	
ENDIF()

IF( ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )

    SET(CMAKE_CXX_FLAGS "-std=c++11")
    
endif()

INCLUDE_DIRECTORIES( include ${GLFW_INCLUDE_DIR} ${GLM_INCLUDE_DIRS} )

TARGET_LINK_LIBRARIES( ${CMAKE_PROJECT_NAME} ${GLFW_LIBRARIES} ${OPENGL_gl_LIBRARY})