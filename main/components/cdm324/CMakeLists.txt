set(srcs "cdm324.c")

idf_component_register(SRCS ${srcs}
                    INCLUDE_DIRS "include"
                	)

target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")