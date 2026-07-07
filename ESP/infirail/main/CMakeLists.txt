idf_component_register(SRCS "startracer_esp.c"
                    PRIV_REQUIRES spi_flash
                    INCLUDE_DIRS "")
target_compile_options(${COMPONENT_LIB} PRIVATE -Wno-bool-operation)