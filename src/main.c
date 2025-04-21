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
  
  if (appResult != AE_NO_ERROR) {
    // TODO: implement better error handling 
    printf("An Error Occurred during app execution: %s", SDL_GetError());
    exit(appResult);
  }

  return 0;
}
