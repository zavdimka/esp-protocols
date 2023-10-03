
idf_component_register(SRCS "ap_to_pppos.c" 
                            "network_dce.c"
                            "board.c"
                    INCLUDE_DIRS "."
                   )

# Ignore strict prototypes, as the network_dce.h can used in both C and C++ compilation
target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-strict-prototypes")
