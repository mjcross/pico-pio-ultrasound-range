set(LibName ultrasound_lib)

add_library(${LibName} INTERFACE)

target_sources(${LibName} INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/tx.c
        ${CMAKE_CURRENT_SOURCE_DIR}/rx.c
        )

# invoke pio_asm to assemble the state machine programs
#
pico_generate_pio_header(${LibName} ${CMAKE_CURRENT_LIST_DIR}/tx.pio)
pico_generate_pio_header(${LibName} ${CMAKE_CURRENT_LIST_DIR}/rx.pio)

target_link_libraries(${LibName} INTERFACE
        pico_stdlib
        hardware_pio
        )

# add the `binary` directory so that the generated headers are included in the project
#
target_include_directories(${LibName} INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
	)