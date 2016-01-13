cmake_minimum_required(VERSION 2.8.11)

project(gel)

find_package(SDL REQUIRED)
if (SDL_FOUND)
    include_directories(${SDL_INCLUDE_DIRS})
else()
    message(STATUS "SDL not found.")
endif()

find_package(SDL_image REQUIRED)
if (SDL_IMAGE_FOUND)
    include_directories(${SDL_IMAGE_INCLUDE_DIRS})
else()
    message(STATUS "SDL Image not found.")
endif()

find_package(SDL_ttf REQUIRED)
if (SDL_TTF_FOUND)
    include_directories(${SDL_TTF_INCLUDE_DIRS})
else()
    message(STATUS "SDL TTF not found.")
endif()

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIRS})
else()
    message(STATUS "OpenGL not found.")
endif()

add_subdirectory(Source)
