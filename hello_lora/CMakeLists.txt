# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

set(SDKCONFIG_DEFAULTS "${CMAKE_SOURCE_DIR}/sdkconfig.defaults")
set(IDF_TARGET "esp32c3")

# Disable minimal build to get JTAG console support
idf_build_set_property(MINIMAL_BUILD OFF)

project(hello_lora)
