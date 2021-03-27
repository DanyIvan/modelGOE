cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

project(modelGOE)

# Find all executables
file(GLOB project_SRCS src/*.cpp) #src/*.h

# Add project executable
add_executable(${PROJECT_NAME} ${project_SRCS})


