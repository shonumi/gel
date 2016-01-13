set(SRCS
	input.cpp
	)

set(HEADERS
	input.h
	)


add_library(Input STATIC ${SRCS} ${HEADERS})

target_link_libraries(Input ${SDL_LIBRARY})
