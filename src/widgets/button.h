#ifndef BUTTON_H
#define BUTTON_H

#include<SDL3/SDL.h>

typedef struct Button {
  
  SDL_Surface* buttonSurface;
  SDL_Rect buttonRect; // NOTE: tecnicamente poi creo questo e lo assegno alla struct in una funzione.
  uint8_t colorR;
  uint8_t colorG;
  uint8_t colorB;
} Button;

void buttonGenerate(
    Button* button, 
    int xc, 
    int yc, 
    int hv, 
    int wv, 
    uint8_t r, 
    uint8_t g, 
    uint8_t b
  );

void buttonAssignSurface(Button* button, SDL_Surface* surface);

void buttonRender(Button* button);

void buttonRefresh(Button* button, SDL_Surface* newSurface);

void buttonHandleEvent(Button* button, const SDL_Event *e);

void buttonHandleMouseMotion(Button* button, bool isIn);

void buttonHandleMouseButton(
    Button* button, 
    const SDL_MouseButtonEvent *mouseEvent, 
    bool isIn
  );

#endif
