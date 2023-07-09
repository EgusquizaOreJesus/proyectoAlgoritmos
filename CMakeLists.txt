cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(examples)
set(example_dirs
        audio
        core
        models
        others
        shaders
        shapes
        text
        textures
        )
set(CMAKE_REQUIRED_DEFINITIONS -D_POSIX_C_SOURCE=199309L)
include(CheckSymbolExists)
check_symbol_exists(CLOCK_MONOTONIC time.h HAVE_CLOCK_MONOTONIC)
check_symbol_exists(QueryPerformanceCounter windows.h HAVE_QPC)
set(CMAKE_REQUIRED_DEFINITIONS)
# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include_directories(BEFORE SYSTEM others/external/include)
include_directories(textures)

# Dependencies
set(RAYLIB_VERSION 4.2.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

# Our Project

add_executable(${PROJECT_NAME} main.cpp src/BlockChain.h src/ChainHash.h src/ForwardList.h src/hash.h src/transaccion.h src/patricia.h src/BPPTree.h src/Btree.h src/node.h src/boyer.h)
#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)

set(example_sources)
set(example_resources)
foreach (example_dir ${example_dirs})
    # Get the .c files
    file(GLOB sources ${example_dir}/*.c)
    list(APPEND example_sources ${sources})

    # Any any resources
    file(GLOB textures/resources ${example_dir}/resources/*)
    list(APPEND example_resources ${resources})
endforeach ()
foreach (example_source ${example_sources})
    # Create the basename for the example
    get_filename_component(example_name ${example_source} NAME)
    string(REPLACE ".c" "" example_name ${example_name})

    # Setup the example
    add_executable(${example_name} ${example_source} src/ForwardList.h src/transaccion.h)

    target_link_libraries(${example_name} raylib)

    string(REGEX MATCH ".*/.*/" resources_dir ${example_source})
    string(APPEND resources_dir "textures/resources")

    if (${PLATFORM} MATCHES "Web" AND EXISTS ${resources_dir})
        # The local resources path needs to be mapped to /resources virtual path
        string(APPEND resources_dir "@resources")
        set_target_properties(${example_name} PROPERTIES LINK_FLAGS "--preload-file ${resources_dir}")
    endif ()
endforeach ()
# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()