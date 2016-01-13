include_directories(.)

add_subdirectory(Core)
add_subdirectory(Graphics)
add_subdirectory(Input)

set(SRCS main.cpp)

add_executable(gel ${SRCS})
target_link_libraries(gel Input Graphics Core)
target_link_libraries(gel ${SDL_LIBRARY} ${OPENGL_gl_LIBRARY})
