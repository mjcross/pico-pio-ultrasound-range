cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

set(ProjName pio_ultrasound_range)

project(${ProjName})

pico_sdk_init()

add_compile_options(
	-Wall
	-Wno-format
	-Wno-unused-function
	-Wno-maybe-uninitialized
	-Wextra    			# optional
)

add_executable(${ProjName})

target_sources(${ProjName} PRIVATE ultrasound_range.c)

add_subdirectory(squarewave)

target_link_libraries(${ProjName} PRIVATE
	pico_stdlib
	hardware_pio
	squarewave)

pico_add_extra_outputs(${ProjName})

pico_enable_stdio_usb(${ProjName} 0)
pico_enable_stdio_uart(${ProjName} 1)

# example_auto_set_url(${ProjName})
