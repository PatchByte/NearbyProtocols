project("NearbyProtocols" C)

file(GLOB NEARBYPROTOCOLS_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.c
)

add_library(${PROJECT_NAME} STATIC ${NEARBYPROTOCOLS_SOURCE_FILES})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC NearbyUtils::NearbyUtils)