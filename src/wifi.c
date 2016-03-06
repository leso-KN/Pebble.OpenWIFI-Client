#include <pebble.h>
#include <wifi.h>

static void sendMsg(char *msg)
{
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);
  dict_write_cstring(iter, 0, msg);
  app_message_outbox_send();
}

static void initWifi(void)
{
  app_message_open(128,128);
}