#include<stdio.h>
#include<stdlib.h>

#include"JizzCannon/app.h"

#define EDITOR_TITLE "JizzCannonIDE"

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
  
  AppErrors appResult = AE_NO_ERROR;

  appResult = appInit(&myApp);
  
  if (appResult != AE_NO_ERROR) {
    printf("An Error Occurred: %s", SDL_GetError());
    exit(appResult);
  }
  
  appResult = appRun(&myApp);

  // appResult = appRenderBackground(&myApp);
//
  // if (appResult != NO_ERROR) {
    // printf("An Error Occurred: %s", SDL_GetError());
    // exit(appResult);
  // }
//
  // Button myButton;
//
  // buttonGenerate(&myButton, 50, 50, 50, 50, 255, 0, 0);
  // buttonAssignSurface(&myButton, myApp.surface);
  // buttonRender(&myButton);
//
  // bool updateWindow = true; // true = NO ERROR
  // SDL_Event e;
  // bool quit = false;
//
  // while (quit == false) {
    // while (SDL_PollEvent(&e)) {
      // switch (e.type) {
        // case SDL_EVENT_QUIT:
          // quit = true;
          // break;
        // case SDL_EVENT_WINDOW_RESIZED:
          // appRefresh(&myApp, &myButton);
          // break;
      // }
//
      // buttonHandleEvent(&myButton, &e);
    // }
    // updateWindow = SDL_UpdateWindowSurface(myApp.window);
    // if (updateWindow == false) {
      // printf("An Error Occurred: %s", SDL_GetError());
      // exit(UPDATE_WINDOW_ERROR);
    // }
  // }

  return 0;
}
