set(SRCS
	animation.cpp
	construct.cpp
	gfx_manager.cpp
	scene.cpp
	sprite.cpp
	text.cpp
	)

set(HEADERS
	animation.h
	construct.h
	gfx_manager.h
	scene.h
	sprite.h
	text.h
	)


add_library(Graphics STATIC ${SRCS} ${HEADERS})

target_link_libraries(Graphics ${SDL_LIBRARY} ${SDL_IMAGE_LIBRARY} ${SDL_TTF_LIBRARY} ${OPENGL_gl_LIBRARY})
