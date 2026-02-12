cmake_minimum_required(VERSION 3.16)

set(PICO_BOARD pico_w)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(cmake/pico_sdk_import.cmake)

project(LuaPicoTest C CXX ASM)

pico_sdk_init()

# Headers
include_directories(
    ${CMAKE_SOURCE_DIR}/lua-5.5.0
    ${CMAKE_SOURCE_DIR}/src/hal
    ${CMAKE_SOURCE_DIR}/src/lua_libraries
)

# Lua-källfiler
file(GLOB LUA_SOURCES
    ${CMAKE_SOURCE_DIR}/lua-5.5.0/*.c
)

file(GLOB LUA_LIB_SOURCES
    src/lua_libraries/*.c
)

file(GLOB HAL_LIB_SOURCES
    src/hal/*.c
)

# Skapa Lua-bibliotek
add_library(lua STATIC ${LUA_SOURCES})
target_include_directories(lua PUBLIC ${CMAKE_SOURCE_DIR}/lua-5.5.0)

# Alla C-källfiler för huvudprogrammet
set(SOURCES
    main.c
    ${LUA_LIB_SOURCES}
    ${HAL_LIB_SOURCES}
)

# Skapa programmet
add_executable(${PROJECT_NAME} ${SOURCES})

# Länka biblioteken
target_link_libraries(${PROJECT_NAME}
    lua
    m
    pico_stdlib
    hardware_gpio
)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 1)

pico_add_extra_outputs(${PROJECT_NAME})

# Lägg output i release/
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/release
)