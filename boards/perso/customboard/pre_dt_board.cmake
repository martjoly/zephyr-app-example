# STM32H562
# Suppress "spi_bus_bridge" warning because of:
#  "/soc/xspi@47001400: node name for SPI buses should be 'spi'"
list(APPEND EXTRA_DTC_FLAGS "-Wno-spi_bus_bridge")

# NRF9151
# Suppress "unique_unit_address_if_enabled" to handle the following overlaps:
# - flash-controller@39000 & kmu@39000
# - power@5000 & clock@5000
list(APPEND EXTRA_DTC_FLAGS "-Wno-unique_unit_address_if_enabled")
