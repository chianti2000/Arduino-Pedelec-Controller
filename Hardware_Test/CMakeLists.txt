#=============================================================================#
# Author: Thomas Jarosch                                                      #
# Date:   24.04.2012                                                          #
#                                                                             #
# Description: Pedelec controller cmake project                               #
#                                                                             #
#=============================================================================#
include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR}
                    ${CMAKE_SOURCE_DIR}/Hardware_Test)

#configure_file(main.cpp testprogram.cpp COPYONLY)

# Hardware test program
set(TESTPROGRAM_NAME testprogram)
#set(${TESTPROGRAM_NAME}_BOARD ${FC_PROCESSOR})
#set(${TESTPROGRAM_NAME}_PORT /dev/ttyUSB0)

import_arduino_library(EEPROM)
import_arduino_library(SPI)
import_arduino_library(ILI9341_t3)


set(${TESTPROGRAM_NAME}_SRCS
        main.cpp
        PCD8544_charset.cpp
        PCD8544_nano.cpp
        VESC/buffer.cpp
        VESC/crc.cpp
        VESC/vesc_uart.cpp
        #Adafruit_PCD8544/Adafruit_PCD8544.cpp
    )

add_teensy_executable(${TESTPROGRAM_NAME} "${${TESTPROGRAM_NAME}_SRCS}")

#generate_arduino_firmware(${TESTPROGRAM_NAME})

# Dirty hack to solve compile error on Fedora 15
#target_link_libraries(${TESTPROGRAM_NAME} m)
#target_link_libraries(${TESTPROGRAM_NAME} c)
#target_link_libraries(${TESTPROGRAM_NAME} m)
