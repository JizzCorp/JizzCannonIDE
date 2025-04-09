#include "button.h"

#include<stdio.h>

static bool isPointerIn(Button* button, const SDL_MouseMotionEvent* motion) {
  
  if (motion->x < button->buttonRect.x) return false; // qui e' troppo a sinistra
  if (motion->x > button->buttonRect.x + button->buttonRect.w) return false; // qui e' troppo a destra
  if (motion->y < button->buttonRect.y) return false; // troppo sopra
  if (motion->y > button->buttonRect.y + button->buttonRect.h) return false; // troppo sotto
  
  return true;
}

void buttonGenerate(
    Button* button, 
    int xc, 
    int yc, 
    int hv, 
    int wv,
    uint8_t r, 
    uint8_t g,
    uint8_t b
  ) {
  button->buttonRect.x = xc;
  button->buttonRect.y = yc;
  button->buttonRect.h = hv;
  button->buttonRect.w = wv;
  button->colorR = r;
  button->colorG = g;
  button->colorB = b;
}

void buttonAssignSurface(Button* button, SDL_Surface* surface) {
  button->buttonSurface = surface;
}

void buttonRender(Button* button) {
  const SDL_PixelFormatDetails *pxFmtDetails = SDL_GetPixelFormatDetails(button->buttonSurface->format);
  
  if (pxFmtDetails == NULL) {
    printf("Fucked some shit up...");
    return;
  }
  
  bool fillRect = SDL_FillSurfaceRect(
        button->buttonSurface, 
        &button->buttonRect, 
        SDL_MapRGB(
          pxFmtDetails, 
          NULL, 
          button->colorR, 
          button->colorG,
          button->colorB
        )
    );
  
  if (fillRect == false) {
    printf("Fucked some shit up 2");
    return;
  }
}

void buttonRefresh(Button* button, SDL_Surface* newSurface) {
  button->buttonSurface = newSurface;
  buttonRender(button);
}

void buttonHandleEvent(Button* button, const SDL_Event *e) {
  switch (e->type) {
    case SDL_EVENT_MOUSE_MOTION:
      buttonHandleMouseMotion(button, isPointerIn(button, &e->motion));
      break;
  
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
      buttonHandleMouseButton(button, &e->button, isPointerIn(button, &e->motion));
      break;

    default:
      return;
  }

  buttonRender(button);
  
  return;
}

void buttonHandleMouseMotion(Button* button, bool isIn) {
  if (isIn) {
    button->colorR = 0;
    button->colorG = 255;
    button->colorB = 0;
  } else {
    button->colorR = 255;
    button->colorG = 0;
    button->colorB = 0;
  }

  return;
}

void buttonHandleMouseButton(
    Button* button, 
    const SDL_MouseButtonEvent *mouseEvent, 
    bool isIn
  ) {
  
  if (isIn == false) {
    return;
  }

  switch (mouseEvent->button) {
    case SDL_BUTTON_LEFT:
      button->colorR = 0;
      button->colorG = 0;
      button->colorB = 255;
      break;
    case SDL_BUTTON_RIGHT:
      break;
  }
  
}
