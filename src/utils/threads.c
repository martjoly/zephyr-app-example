#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(thread_info, LOG_LEVEL_DBG);

#include <zephyr/kernel.h>

void threads_print_cb(const struct k_thread *cthread, void *user_data)
{
  char state_str[32];

  struct k_thread *thread = (struct k_thread *) cthread;

  const char *tname = k_thread_name_get(thread);

  LOG_PRINTK("%s%p %-10s\n",
             (thread == k_current_get()) ? "*" : " ",
             thread,
             tname ? tname : "NA");

  LOG_PRINTK("\tID: %p, options: 0x%x, priority: %d timeout: %lld\n",
             thread,
             thread->base.user_options,
             thread->base.prio,
             (int64_t)thread->base.timeout.dticks);

  LOG_PRINTK("\tstate: %s, entry: %p\n",
             k_thread_state_str(thread, state_str, sizeof(state_str)),
             thread->entry.pEntry);
}


void threads_print(void)
{
  LOG_INF("Threads list:");
  k_thread_foreach(threads_print_cb, NULL);
}

// vim: set sw=2 sts=2 et :

