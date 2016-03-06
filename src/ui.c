#include <pebble.h>
#include <wifi.c>

static Window *mainWindow;
static MenuLayer *mainMenu;
static char optionText[100];

typedef struct {
  char *text;
  void *cb;
} MenuOption;

static void opt_restartBasis()
{
  sendMsg("OpenWIFI:RestartBase");
}

static MenuOption options[] = {
  {"Basis neustarten", opt_restartBasis},
  {"Option 2", opt_restartBasis}
};

static void mainMenuSelect(struct MenuLayer *s_menu_layer, MenuIndex *cell_index, void *callback_context)
{
  void* optVoid = options[cell_index->row].cb;
}

static uint16_t getSelsCount(struct MenuLayer *menulayer, uint16_t section_index, void *callback_context)
{
  int count = sizeof(options) / sizeof(MenuOption);
  return count;
}

static void drawRow(GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *callback_context)
{
  char* text = options[cell_index->row].text;
  int text_gap_size = 14 - strlen(text);

  snprintf(optionText, sizeof(optionText), "%s",text);
  menu_cell_basic_draw(ctx, cell_layer, optionText, NULL, NULL);
}

static void uiWinLoad(Window *window)
{
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  mainMenu = menu_layer_create(bounds);
  menu_layer_set_callbacks(mainMenu, NULL, (MenuLayerCallbacks){
    .get_num_rows = getSelsCount,
    .get_cell_height = NULL,
    .draw_row = drawRow,
    .select_click = mainMenuSelect
  }); 
  menu_layer_set_click_config_onto_window(mainMenu,	window);
  layer_add_child(window_layer, menu_layer_get_layer(mainMenu));
}
static void uiWinUnload(Window *window)
{
  menu_layer_destroy(mainMenu);
}

static void creaWin(void)
{
  mainWindow = window_create();
  
  window_set_window_handlers(mainWindow, (WindowHandlers) {
    .load = uiWinLoad,
    .unload = uiWinUnload
  });

  window_stack_push(mainWindow, true);
}
static void dtryWin(void)
{
  window_destroy(mainWindow);
}