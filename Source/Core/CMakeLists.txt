set(SRCS
	init.cpp
	xgl.cpp
	)

set(HEADERS
	game_state.h
	init.h
	xgl.h
	)

add_library(Core STATIC ${SRCS} ${HEADERS})

target_link_libraries(Core ${SDL_LIBRARY} ${OPENGL_gl_LIBRARY}) 
