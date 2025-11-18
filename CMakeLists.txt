cmake_minimum_required(VERSION 3.20.0)

message(STATUS "Found ZEPHYR_BASE env: $ENV{ZEPHYR_BASE}")
set(CMAKE_MODULE_PATH
  "$ENV{ZEPHYR_BASE}/share/zephyr-package/cmake"
  )

# Configure board and required zephyr modules.
# Assumption here is that if not explicitly specified the zephyr modules are
# installed alongside the ZEPHYR_BASE directory.
if(NOT BOARD)
  set(BOARD "customboard/stm32h562xx")
  message(STATUS "Use default board: ${BOARD}")
endif()
if(NOT ZEPHYR_MODULES_BASE)
  set(ZEPHYR_MODULES_BASE "$ENV{ZEPHYR_BASE}/../modules")
endif()
list(APPEND ZEPHYR_MODULES
  ${ZEPHYR_MODULES_BASE}/hal/cmsis
  ${ZEPHYR_MODULES_BASE}/hal/stm32
  ${CMAKE_CURRENT_SOURCE_DIR}/modules
  )
list(APPEND BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(zephyr_test)

list(APPEND app_sources
  src/main.c
  src/utils/threads.c
  src/utils/threads.h
  )
target_sources(app PRIVATE ${app_sources})

# vim: set sw=2 sts=2 et :
