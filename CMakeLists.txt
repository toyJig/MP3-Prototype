# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.3.1)
set(toolchainVersion 15_2_Rel1)
set(picotoolVersion 2.3.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Mp3-Prototype C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1
#yanks all files ending in cpp and .h in /src for build
file(GLOB SRC_FILES CONFIGURE_DEPENDS 
    "src/*.cpp" 
    "src/*.c" 
    "include/*.hpp"
    "include/*.h"
)

# Create the executable using that variable
add_executable(Mp3-Prototype ${SRC_FILES})
target_include_directories(Mp3-Prototype PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/src
    ${CMAKE_CURRENT_LIST_DIR}/include
)

#include helix mp3 decoder library folder
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/lib/picomp3lib/src)

#Include mp3 as binary object blobs
set(MP3_FILE "${CMAKE_CURRENT_SOURCE_DIR}/mp3_src/Breeze.mp3")
set(GENERATED_CPP "${CMAKE_CURRENT_SOURCE_DIR}/src/audio.cpp")
add_custom_command(
    OUTPUT "${GENERATED_CPP}"
    COMMAND ${CMAKE_COMMAND} -E echo "extern const unsigned char mp3_data[]\;" > "${GENERATED_CPP}"
    COMMAND ${CMAKE_COMMAND} -E echo "extern const unsigned int mp3_size\;" >> "${GENERATED_CPP}"
    DEPENDS "${MP3_FILE}"
    VERBATIM
)
if (MSVC)
    #Windows MSVC
    set(RC_FILE "${CMAKE_CURRENT_BINARY_DIR}/resources.rc")
    file(WRITE "${RC_FILE}" "MY_MP3_FILE RCDATA \"${MP3_FILE}\"\n")
    target_sources(Mp3-Prototype PRIVATE "${RC_FILE}")
else ()
    #GCC/Clang
    target_link_options(Mp3-Prototype PRIVATE "-W1,-b,binary,${MP3_FILE},-b,default")
endif()

# Run Python mp3 compactor and parser
# find_package(Python3 REQUIRED COMPONENTS Interpreter)
# add_custom_target(mp3_compactor_python ALL
#     OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/mp3-binary.h"
#     COMMAND Python3::Interpreter "${CMAKE_CURRENT_LIST_DIR}/src/Mp3-compactor.py"
#     DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/Mp3-compactor.py"
#     COMMENT "Running Mp3 compaction Python script before build..."
#     VERBATIM
# )
# add_dependencies(Mp3-Prototype mp3_compactor_python)

pico_set_program_name(Mp3-Prototype "Mp3-Prototype")
pico_set_program_version(Mp3-Prototype "0.1")

# Enable/disable output over UART/USB
pico_enable_stdio_usb(Mp3-Prototype 1)
pico_enable_stdio_uart(Mp3-Prototype 0)

# Add the standard library to the build
target_link_libraries(Mp3-Prototype
    pico_stdlib
    hardware_i2c
    hardware_spi
    hardware_adc
    pico_multicore
    picomp3lib #helix decoder lib
)

pico_add_extra_outputs(Mp3-Prototype)


