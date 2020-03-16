cmake_minimum_required(VERSION 3.5)
project("test" C CXX ASM)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

# IDE settings
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 17)


# Source files for the library build
set(SRCS
        test.cpp				        
  )


SET(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -Wall -Werror -W")

add_executable(test ${SRCS} )

