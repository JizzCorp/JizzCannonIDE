#ifndef BASE_WIDGET_H
#define BASE_WIDGET_H

#include<SDL3/SDL.h>
#include<SDL3_ttf/SDL_ttf.h>

typedef enum WidgetType {
  WT_BUTTON,
} WidgetType;

typedef struct BaseWidget {
  WidgetType widgetType;  
  SDL_Surface* widgetSurface;
  SDL_Rect widgetRect;
  uint8_t colorR;
  uint8_t colorG;
  uint8_t colorB;
  TTF_Font* widgetFont;
} BaseWidget;

#endif

