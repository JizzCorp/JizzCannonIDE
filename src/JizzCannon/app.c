#include "app.h"

AppErrors appInit(App *app) {
  
  if (SDL_Init(SDL_INIT_VIDEO) == false) {
    return AE_INIT_ERROR;
  }
  
  app->window = SDL_CreateWindow(
        app->windowTitle,
        app->width,
        app->height,
        app->flags
      );
  
  if (app->window == NULL) {
    return AE_CREATE_WINDOW_ERROR;
  }
  
  app->surface = SDL_GetWindowSurface(app->window);

  if (app->surface == NULL) {
    return AE_GET_SURFACE_ERROR;
  }
  
  app->appWidgets = dynListInit(DL_WIDGET, 1);

  return AE_NO_ERROR;
}

static AppErrors appRenderBackground(App *app) {
  const SDL_PixelFormatDetails *surfacePxFmtDetails = SDL_GetPixelFormatDetails(app->surface->format);
  
  if (surfacePxFmtDetails == NULL) {
    return AE_PXL_FMT_ERROR;
  }

  bool fillRect = SDL_FillSurfaceRect(
      app->surface,
      NULL,
      SDL_MapRGBA(
          surfacePxFmtDetails,
          NULL,
          app->backgroundColor.r,
          app->backgroundColor.g,
          app->backgroundColor.b,
          app->backgroundColor.a
        ) 
      );

  if (fillRect == false) {
    return AE_FILL_BACKGROUND_ERROR;
  }

  return AE_NO_ERROR;
}

static void appRefresh(App* app) {
  
  app->surface = SDL_GetWindowSurface(app->window);
  appRenderBackground(app);
  // buttonRefresh(button, app->surface);
  for (size_t i = 0; i < app->appWidgets.usedSlots; ++i) {
    BaseWidget currentWidget = ((BaseWidget*)app->appWidgets.actualData)[i];

    switch (currentWidget.widgetType) {
      case WT_BUTTON:
        buttonRefresh(&currentWidget, app->surface);
        break;
      default:
        break;
    }
  }

}

static void handleWidgetsEvents(App *app, SDL_Event *e) {

}

AppErrors appRun(App* app) {
  
  AppErrors appResult = AE_NO_ERROR;
  
  // NOTE: Load basic app configuration
  appResult = appRenderBackground(app);
  
  BaseWidget myButton;
  buttonGenerate(&myButton, 50, 50, 50, 50, 255, 0, 0);
  buttonAssignSurface(&myButton, app->surface);
  buttonRender(&myButton);
  
  dynListPush(&app->appWidgets, &myButton);
   
  SDL_Event e;
  bool updateWindow = true, quit = false;

  while (quit == false) {
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
        case SDL_EVENT_QUIT:
          quit = true;
          break;

        case SDL_EVENT_WINDOW_RESIZED:
          appRefresh(app);
          break;
      }

      handleWidgetsEvents(app, &e);
    }

    updateWindow = SDL_UpdateWindowSurface(app->window);
    if (updateWindow == false) {
      printf("An Error Occurred: %s", SDL_GetError());
      exit(AE_UPDATE_WINDOW_ERROR);
    }
  }
  
  dynListFree(&app->appWidgets);
  
  return AE_NO_ERROR;
}
