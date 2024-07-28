set(PROJECT_SOURCES
    control.cpp 
    card.cpp 
    player.cpp 
    map.cpp 
    purple.cpp
    yellow.cpp 
    leader.cpp 
    princes.cpp 
    virago.cpp 
    scarecrow.cpp
    drummer.cpp 
    dean.cpp
    winter.cpp 
    spring.cpp 
    main.cpp
    input.cpp
    horse.cpp
)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
)

set(RAYLIB_PATH "C:/raylib-5.0_win64_mingw-w64")

# Specify the directories where the headers and libraries are located

include_directories(${RAYLIB_PATH}/include)

link_directories(${RAYLIB_PATH}/lib)

target_link_libraries(${PROJECT_NAME} raylib)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} winmm)
endif()

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()