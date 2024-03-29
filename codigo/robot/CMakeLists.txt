# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/home/juan/pico/pico-sdk")

set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(robot C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add libraries
add_library(libs 
    libs/ultrasonico.c
    libs/l298.c
    libs/bt.c
    libs/actuadores.c
    libs/infrarrojo.c
)

# Include header files to library
target_include_directories(libs PUBLIC 
    libs/inc
)

# Link libraries with SDK
target_link_libraries(libs 
  pico_stdlib
  hardware_pwm
  hardware_uart
  hardware_adc
  )

# Add executable. Default name is the project name, version 0.1

add_executable(robot robot.c )

pico_set_program_name(robot "robot")
pico_set_program_version(robot "0.1")

pico_enable_stdio_uart(robot 1)
pico_enable_stdio_usb(robot 0)






# Add the standard library to the build
target_link_libraries(robot
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(robot PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)

# Add libraries (extra libraries should be included here)
target_link_libraries(${PROJECT_NAME} 
    pico_stdlib
    libs
    hardware_pwm
    hardware_uart
    hardware_adc
)

pico_add_extra_outputs(robot)

