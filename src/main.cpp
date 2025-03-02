#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
int count, offset_x, offset_y = 0;
const int grid_cell_size = 10;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer("Mao - Window as revealer prototype", 320, 240, SDL_WINDOW_RESIZABLE,
                              &window, &renderer);
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  int win_w, win_h, win_x, win_y;
  SDL_GetWindowSize(window, &win_w, &win_h);
  SDL_GetWindowPosition(window, &win_x, &win_y);
  SDL_FRect rect;
  SDL_SyncWindow(window);

  SDL_SetRenderDrawColor(renderer, 220, 220, 220, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 180, 180, 180, SDL_ALPHA_OPAQUE);
  for (int i = 0; i <= win_h / grid_cell_size; i++) {
    SDL_RenderLine(renderer, 0, grid_cell_size * i - (win_y % 10), win_w, grid_cell_size *
    i - (win_y % 10));
  }

  for (int i = 0; i <= win_w / grid_cell_size; i++) {
    SDL_RenderLine(renderer, grid_cell_size * i - (win_x % 10), 0, grid_cell_size * i - (win_x % 10),
    win_h);
  }

  SDL_SetRenderDrawColor(renderer, 45, 12, 200, SDL_ALPHA_OPAQUE);

  // rect.x = rect.x - win_x

  rect.x = 300;
  // rect.x = rect.x - ((int)rect.x % 10) - win_x;
  rect.x = rect.x - ((int)rect.x % 10) - win_x;
  rect.y = 500;
  rect.y = rect.y - ((int)rect.y % 10) - win_y;
  rect.w = 100;
  rect.h = 100;
  SDL_RenderFillRect(renderer, &rect);

  SDL_SetRenderDrawColor(renderer, 180, 35, 35, SDL_ALPHA_OPAQUE);
  SDL_RenderDebugText(renderer, 500 - win_x, 500 - win_y, "Nobody can see me !");

  SDL_RenderPresent(renderer);
  return SDL_APP_CONTINUE;
}

void handle_window_movement(SDL_Event *event) {
  SDL_Log("win_id: %i", event->window.data1);
  offset_x = event->window.data1;
  offset_y = event->window.data2;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  switch (event->type) {
  case SDL_EVENT_QUIT:
    return SDL_APP_SUCCESS;
    break;
    // case SDL_EVENT_WINDOW_MOVED:
    //     handle_window_movement(event);
    //     break;
  }
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {}
