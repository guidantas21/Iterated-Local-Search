cmake_minimum_required(VERSION 3.10)

project(Iterated-Local-Search)

# Add your include directory
include_directories(include)

# Gather all source files
file(GLOB SOURCES
    source/*.cpp
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})