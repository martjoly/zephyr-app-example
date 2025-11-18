
if(CONFIG_BOARD_CUSTOMBOARD_STM32H562XX OR CONFIG_BOARD_CUSTOMBOARD_STM32H562XX_NS)
  # keep first
  board_runner_args(stm32cubeprogrammer "--port=swd" "--reset-mode=hw")

  board_runner_args(pyocd "--target=stm32h562vgtx")

  board_runner_args(jlink "--device=STM32H562VG" "--reset-after-load")

  board_runner_args(openocd "--tcl-port=6666")
  board_runner_args(openocd --cmd-pre-init "gdb_report_data_abort enable")
  board_runner_args(openocd "--no-halt")

  # keep first
  include(${ZEPHYR_BASE}/boards/common/stm32cubeprogrammer.board.cmake)
  include(${ZEPHYR_BASE}/boards/common/pyocd.board.cmake)
  include(${ZEPHYR_BASE}/boards/common/jlink.board.cmake)
  #include(${ZEPHYR_BASE}/boards/common/openocd.board.cmake)
  # FIXME: official openocd runner not yet available.

elseif(CONFIG_BOARD_CUSTOMBOARD_NRF9151 OR CONFIG_BOARD_CUSTOMBOARD_NRF9151_NS)
  if(CONFIG_BOARD_CUSTOMBOARD_NRF9151_NS)
    set(TFM_PUBLIC_KEY_FORMAT "full")
  endif()

  if(CONFIG_TFM_FLASH_MERGED_BINARY)
    set_property(TARGET runners_yaml_props_target
      PROPERTY hex_file tfm_merged.hex
      )
  endif()

  board_runner_args(jlink "--device=nRF9151_xxCA" "--speed=4000")
  include(${ZEPHYR_BASE}/boards/common/nrfjprog.board.cmake)
  include(${ZEPHYR_BASE}/boards/common/jlink.board.cmake)
endif()
