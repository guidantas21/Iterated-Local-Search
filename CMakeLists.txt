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

# Set compiler flags (example flags, replace with your desired flags)
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -O2
)

# Set linker flags (example flags, replace with your desired flags)
target_link_options(${PROJECT_NAME} PRIVATE
    -pthread  # Example: Link with pthread library
)
