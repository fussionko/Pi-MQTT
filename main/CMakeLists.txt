idf_component_register(SRCS "camera.c" "app_main.c" "mqtt.c" "wifi.c"
                    INCLUDE_DIRS "."
                    PRIV_REQUIRES cdm324)
#target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")
