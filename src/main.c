#include<stdio.h>
#include<stdlib.h>

#include<SDL3/SDL.h>

#include"widgets/button.h"

#define EDITOR_TITLE "JizzCannonIDE"

typedef enum AppErrors {
  NO_ERROR,
  INIT_ERROR,
  CREATE_WINDOW_ERROR,
  GET_SURFACE_ERROR,
  PXL_FMT_ERROR,
  FILL_BACKGROUND_ERROR,
  UPDATE_WINDOW_ERROR,
} AppErrors;

typedef struct App {
  int width;
  int height;
  char* windowTitle;
  SDL_WindowFlags flags;
  SDL_Window *window;
  SDL_Surface *surface;
  SDL_Color backgroundColor;
} App;

AppErrors appInit(App *app);
AppErrors appRenderBackground(App *app);
void appRefresh(App *myApp, Button *button);

int main(int argc, char** argv) {
  
  App myApp = {
    640, 
    480, 
    EDITOR_TITLE, 
    SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE, 
    NULL, 
    NULL, 
    {255, 255, 255, 1}
  };
  
  AppErrors appResult = NO_ERROR;

  appResult = appInit(&myApp);

  if (appResult != NO_ERROR) {
    printf("An Error Occurred: %s", SDL_GetError());
    exit(appResult); 
  }
  
  appResult = appRenderBackground(&myApp); 
  
  if (appResult != NO_ERROR) {
    printf("An Error Occurred: %s", SDL_GetError());
    exit(appResult);
  }
  
  Button myButton;

  buttonGenerate(&myButton, 50, 50, 50, 50, 255, 0, 0);
  buttonAssignSurface(&myButton, myApp.surface);
  buttonRender(&myButton);

  bool updateWindow = true; // true = NO ERROR
  SDL_Event e;
  bool quit = false;

  while (quit == false) {
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
        case SDL_EVENT_QUIT:
          quit = true;
          break;
        case SDL_EVENT_WINDOW_RESIZED:
          appRefresh(&myApp, &myButton);
          break;
      }

      buttonHandleEvent(&myButton, &e);
    }
    updateWindow = SDL_UpdateWindowSurface(myApp.window);
    if (updateWindow == false) {
      printf("An Error Occurred: %s", SDL_GetError());
      exit(UPDATE_WINDOW_ERROR);
    }
  }

  return 0;
}

AppErrors appInit(App *app) {
  
  if (SDL_Init(SDL_INIT_VIDEO) == false) {
    return INIT_ERROR;
  }
  
  app->window = SDL_CreateWindow(
        app->windowTitle,
        app->width,
        app->height,
        app->flags
      );
  
  if (app->window == NULL) {
    return CREATE_WINDOW_ERROR;
  }
  
  app->surface = SDL_GetWindowSurface(app->window);

  if (app->surface == NULL) {
    return GET_SURFACE_ERROR;
  }
  
  return NO_ERROR;
}

AppErrors appRenderBackground(App *app) {
  const SDL_PixelFormatDetails *surfacePxFmtDetails = SDL_GetPixelFormatDetails(app->surface->format);
  
  if (surfacePxFmtDetails == NULL) {
    return PXL_FMT_ERROR;
  }

  bool fillRect = SDL_FillSurfaceRect(
      app->surface, 
      NULL, // Lasciato null perche' deve essere tutta la finestra
      SDL_MapRGBA(
          surfacePxFmtDetails,
          NULL, // La palette per ora non mi interessa
          app->backgroundColor.r,
          app->backgroundColor.g,
          app->backgroundColor.b,
          app->backgroundColor.a
        ) 
      );

  if (fillRect == false) {
    return FILL_BACKGROUND_ERROR;
  }

  return NO_ERROR;
}

void appRefresh(App* app, Button* button) {
  
  app->surface = SDL_GetWindowSurface(app->window);
  appRenderBackground(app);
  buttonRefresh(button, app->surface);

}
