cmake_minimum_required(VERSION 3.20)
project("NearbyProtocols-Root")

option(NEARBYPROTOCOLS_ENABLE_DEVELOPMENT "Enable Development Environment of NearbyProtocols" ON)
option(NEARBYPORTOCOLS_ENABLE_TESTS "Enable Tests" ON)

if(NEARBYPROTOCOLS_ENABLE_DEVELOPMENT)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
endif(NEARBYPROTOCOLS_ENABLE_DEVELOPMENT)

add_subdirectory("NearbyUtils")
add_subdirectory("NearbyProtocols")

if(NEARBYPORTOCOLS_ENABLE_TESTS)
    add_subdirectory("NearbyTests")
endif(NEARBYPORTOCOLS_ENABLE_TESTS)