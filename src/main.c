#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#include "utils/threads.h"

// Configure push button and LED
#define SW0_NODE DT_ALIAS(sw0)
#if !DT_NODE_HAS_STATUS_OKAY(SW0_NODE)
  #error "sw0 devicetree alias is not defined"
#endif
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(SW0_NODE, gpios);
static struct gpio_callback button_cb_data; // holder for button callback

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
static int64_t blink_time = 0;


static void button_pressed(const struct device *dev,
                           struct gpio_callback *cb,
                           uint32_t pins)
{
  printk("Button pressed at %" PRIu32 "\n", k_cycle_get_32());
}

int main(void)
{
  int res;

  printk("Configure button and LED\n");
  if (0 != (res = gpio_pin_configure_dt(&button, GPIO_INPUT))) {
    printk("Error %d: failed to configure %s pin %d\n",
           res, button.port->name, button.pin);
    return 0;
  }
  res = gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_TO_ACTIVE);
  if (res) {
    printk("Error %d: failed to configure interrupt on %s pin %d\n",
           res, button.port->name, button.pin);
    return 0;
  }
  gpio_init_callback(&button_cb_data, button_pressed, BIT(button.pin));
  gpio_add_callback(button.port, &button_cb_data);
  printk("Set up button at %s pin %d\n", button.port->name, button.pin);

  // Test LEDs
  if (!gpio_is_ready_dt(&led)) {
    printk("Led not ready\n");
    return 0;
  }

  res = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
  if (res < 0) {
    printk("Error while configuring led: %d\n", res);
    return 0;
  }

  // Print all threads
  threads_print();

  while (1) {
    // Give some time to other threads
    k_msleep(1);
  }

  return 0;
}

// vim: set sw=2 sts=2 et :

