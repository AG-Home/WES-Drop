cmake_minimum_required(VERSION 3.22)

project(display)

set(SSD1309_DIR SSD1315-1309)

# Set include directories and sources
set(INCLUDE_DIRS 
    ${SSD1309_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(SOURCES
    ${SSD1309_DIR}/ssd1315.c
    ${SSD1309_DIR}/ssd1315_reg.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/display.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ssd1309_if.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/font.c
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
