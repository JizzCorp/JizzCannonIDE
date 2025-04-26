#ifndef BUTTON_H
#define BUTTON_H

#include<SDL3/SDL.h>
#include<SDL3_ttf/SDL_ttf.h>

#include"baseWidget.h"

void buttonGenerate(
    BaseWidget* button, 
    TTF_Font *buttonFont,
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

void buttonHandleMouseButtonDown(
    BaseWidget* button, 
    const SDL_MouseButtonEvent *mouseEvent, 
    bool isIn
  );

#endif
