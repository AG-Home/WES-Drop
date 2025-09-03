cmake_minimum_required(VERSION 3.22)

project(level)

set(SR04M_DIR SR04M)

# Set include directories and sources
set(INCLUDE_DIRS 
    ${SR04M_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(SOURCES
    ${SR04M_DIR}/src/sr04m.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sr04m_if.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/level.c
)

# Create static library
add_library(${PROJECT_NAME} STATIC ${SOURCES})

# Configure library compilation options
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})

# Configure additional compilation options, if needed
target_compile_options(${PROJECT_NAME} PRIVATE 
                                        -c 
                                        -mcpu=cortex-m0plus
                                        -std=c11 
                                        -Wall
                                        -mthumb
                                        -g
                                        )

# Configure linking options, if needed
target_link_libraries(${PROJECT_NAME} PUBLIC stm32l0xx_hal_st)

# Configure installation options, if needed
# install(TARGETS ${PROJECT_NAME} DESTINATION lib)
# install(FILES ... DESTINATION include)
