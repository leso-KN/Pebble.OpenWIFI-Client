#include <pebble.h>
#include <ui.c>
#include <wifi.h>

int main(void)
{
  initWifi();
  creaWin();
  app_event_loop();
  dtryWin();
}