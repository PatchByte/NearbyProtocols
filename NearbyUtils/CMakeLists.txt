project("NearbyUtils")

file(GLOB NEARBYUTILS_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.c
)

add_library(${PROJECT_NAME} STATIC ${NEARBYUTILS_SOURCE_FILES})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)