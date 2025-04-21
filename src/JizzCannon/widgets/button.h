#ifndef BUTTON_H
#define BUTTON_H

#include<SDL3/SDL.h>

#include"baseWidget.h"

// typedef struct BaseWidget {
//
  // SDL_Surface* buttonSurface;
  // SDL_Rect buttonRect;
  // uint8_t colorR;
  // uint8_t colorG;
  // uint8_t colorB;
// } BaseWidget;

void buttonGenerate(
    BaseWidget* button, 
    int xc, 
    int yc, 
    int hv, 
    int wv, 
    uint8_t r, 
    uint8_t g, 
    uint8_t b
  );

void buttonAssignSurface(BaseWidget* button, SDL_Surface* surface);

void buttonRender(BaseWidget* button);

void buttonRefresh(BaseWidget* button, SDL_Surface* newSurface);

void buttonHandleEvent(BaseWidget* button, const SDL_Event *e);

void buttonHandleMouseMotion(BaseWidget* button, bool isIn);

void buttonHandleMouseButton(
    BaseWidget* button, 
    const SDL_MouseButtonEvent *mouseEvent, 
    bool isIn
  );

#endif
