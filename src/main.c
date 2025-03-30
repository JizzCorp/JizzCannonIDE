#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include<SDL3/SDL.h>

#define EDITOR_TITLE "JizzCannonIDE"

enum MiscarriageEnum {
  MISCARRIAGE_GENERAL = -1,
};

void handleMiscarriage(const int miscarriageCode);
void miscarriage(const char* message, const char* sdlError);

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char** argv) {

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    handleMiscarriage(1);
    exit(MISCARRIAGE_GENERAL);
  }

  SDL_Window *window = SDL_CreateWindow(
        EDITOR_TITLE,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );
  
  if (window == NULL) {
    handleMiscarriage(2);
    exit(MISCARRIAGE_GENERAL);
  }

  SDL_Surface *screenSurface = SDL_GetWindowSurface(window);

  const SDL_PixelFormatDetails *surfacePxFmtDetails = SDL_GetPixelFormatDetails(screenSurface->format);
  
  if (surfacePxFmtDetails == NULL) {
    handleMiscarriage(3);
    exit(MISCARRIAGE_GENERAL);
  }

  bool fillRect = SDL_FillSurfaceRect(
      screenSurface,
      NULL,
      SDL_MapRGB(
          surfacePxFmtDetails, NULL, 0xFF, 0xFF, 0xFF
        )
    );

  if (fillRect == false) {
    handleMiscarriage(4);
    exit(MISCARRIAGE_GENERAL);
  }
  
  bool updateWindow = SDL_UpdateWindowSurface(window);
  
  if (updateWindow == false) {
    handleMiscarriage(5);
    exit(MISCARRIAGE_GENERAL);
  }

  SDL_Event e;
  bool quit = false;
  while (quit == false) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_EVENT_QUIT) {
        quit = true;
      }
    }
  }
  
  // Quitting everything
  SDL_DestroySurface(screenSurface);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

void handleMiscarriage(const int miscarriageCode) {
  
  char* miscarriageMessage = "";
  
  switch (miscarriageCode) {
    case 1:
      miscarriageMessage = "Could not init SDL.";
      break;
    case 2:
      miscarriageMessage = "Could not create window.";
      break;
    case 3:
      miscarriageMessage = "Could not get PixelFormatDetails.";
      break;
    case 4:
      miscarriageMessage = "Could not fill rectangle with color.";
      break;
    case 5:
      miscarriageMessage = "Could not update window surface.";
      break;
    default:
      miscarriageMessage = "NaE.";
  }

  printf("Miscarriage: %s. Miscarriage cause: %s", miscarriageMessage, SDL_GetError());
}
