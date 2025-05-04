#include "app.h"

static char* findFontPath() {
  // TODO: actually try to find a font in the system
  return "/usr/share/fonts/liberation/LiberationMono-Regular.ttf";
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
  
  // NOTE: probably not the best way to handle all events, but...
  // it'll do for now.
  
  for (size_t i = 0; i < app->appWidgets.usedSlots; ++i) {
    BaseWidget currentWidget = ((BaseWidget*)app->appWidgets.actualData)[i];

    switch (currentWidget.widgetType) {
      case WT_BUTTON:
        buttonHandleEvent(&currentWidget, e);
        break;
      default:
        break;
    }
  }

}

// NOTE: not needed right now?
// void appFreeWidgets(App *app) {
//
  // for (size_t i = 0; i < app->appWidgets.usedSlots; ++i) {
    // BaseWidget currentWidget = ((BaseWidget*)app->appWidgets.actualData)[i];
    // SDL_free(currentWidget.widgetSurface);
  // }
//
// }

AppErrors appInit(App *app) {
  
  if (SDL_Init(SDL_INIT_VIDEO) == false) {
    return AE_INIT_ERROR;
  }
  
  if (!TTF_Init()) {
    return AE_TTF_INIT_ERROR;
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
  app->mainFontPath = findFontPath();
  app->mainFontDefaultSize = (float)11.0f; 
  
  app->mainFont = TTF_OpenFont(app->mainFontPath, app->mainFontDefaultSize);
  
  if (app->mainFont == NULL) {
    return AE_OPEN_FONT_ERROR; 
  }
  
  app->textEngine = TTF_CreateSurfaceTextEngine();
  if (app->textEngine == NULL) {
    return AE_TEXT_ENGINE_ERROR;
  }

  return AE_NO_ERROR;
}

AppErrors appRun(App* app) {
  
  AppErrors appResult = AE_NO_ERROR;
  
  // NOTE: Load basic app configuration
  appResult = appRenderBackground(app);
  
  BaseWidget myButton;
  buttonGenerate(&myButton, app->mainFont, app->textEngine, 15, "Load File", 0, 0, 25, 100, 255, 0, 0);
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

    SDL_Delay(1000/60);
  }
  
  // NOTE: not needed right now?
  // appFreeWidgets(app);

  dynListFree(&app->appWidgets);
  
  SDL_Quit();

  return AE_NO_ERROR;
}
