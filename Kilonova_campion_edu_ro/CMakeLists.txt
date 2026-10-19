cmake_minimum_required(VERSION 3.15.0)
project(Kilonova_campion_edu_ro VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g3 -ggdb")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -ggdb")

# Directory to search
set(SEARCH_DIR "${CMAKE_SOURCE_DIR}")
# Recursively find all .cpp files
file(GLOB_RECURSE cpp_files "${SEARCH_DIR}/*.cpp")

if(cpp_files)
    set(latest_file "")
    set(latest_time 0)

    foreach(file_path ${cpp_files})
        # Get modification time directly as UNIX timestamp
        file(TIMESTAMP "${file_path}" file_time "%s")

        # Compare and store the latest
        if(file_time GREATER latest_time)
            set(latest_time ${file_time})
            set(latest_file ${file_path})
        endif()
    endforeach()

    # Normalize path for Windows output
    file(TO_CMAKE_PATH "${latest_file}" latest_file_normalized)

    message(STATUS "Last modified .cpp file: ${latest_file_normalized} at ${latest_time}")
else()
    message(WARNING "No .cpp files found in ${SEARCH_DIR}")
endif()

get_filename_component(PROJECT_NAME "${latest_file_normalized}" NAME_WE)

# Add the executable with the same name as the project
add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp)

# debug not working!!!