#ifndef APP_H
#define APP_H

#include<SDL3/SDL.h>

#include"utils/DynList/dynList.h"
#include"widgets/button.h"

typedef enum AppErrors {
  AE_NO_ERROR,
  AE_INIT_ERROR,
  AE_CREATE_WINDOW_ERROR,
  AE_GET_SURFACE_ERROR,
  AE_PXL_FMT_ERROR,
  AE_FILL_BACKGROUND_ERROR,
  AE_UPDATE_WINDOW_ERROR,
} AppErrors;

typedef struct App {
  int width;
  int height;
  char* windowTitle;
  SDL_WindowFlags flags;
  SDL_Window *window;
  SDL_Surface *surface;
  SDL_Color backgroundColor;
  DynList appWidgets;
} App;

AppErrors appInit(App *app);
// NOTE: will have to be static functions
// AppErrors appRenderBackground(App *app);
// void appRefresh(App *myApp, Button *button);
AppErrors appRun(App *app);

#endif
