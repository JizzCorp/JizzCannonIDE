#include "button.h"

#include<stdio.h>

static bool isPointerIn(BaseWidget* button, const SDL_MouseMotionEvent* motion) {
  
  if (motion->x < button->widgetRect.x) return false;
  if (motion->x > button->widgetRect.x + button->widgetRect.w) return false;
  if (motion->y < button->widgetRect.y) return false;
  if (motion->y > button->widgetRect.y + button->widgetRect.h) return false;
  
  return true;
}

void buttonGenerate(
    BaseWidget* button, 
    TTF_Font* buttonFont,
    TTF_TextEngine* textEngine,
    float fontSize,
    char* buttonString,
    int xc, 
    int yc, 
    int hv, 
    int wv,
    uint8_t r, 
    uint8_t g,
    uint8_t b
  ) {
  button->widgetType = WT_BUTTON;
  button->widgetRect.x = xc;
  button->widgetRect.y = yc;
  button->widgetRect.h = hv;
  button->widgetRect.w = wv;
  button->colorR = r;
  button->colorG = g;
  button->colorB = b;
  
  button->widgetFont = TTF_CopyFont(buttonFont);
  if (button->widgetFont == NULL) {
    printf("copyFont: fucked some shit up...");
    return;
  }
  
  button->widgetString = buttonString;

  button->fontSize = fontSize;
  TTF_SetFontSize(button->widgetFont, button->fontSize); // NOTE: font size should be a widget's property
  TTF_SetFontStyle(button->widgetFont, TTF_STYLE_BOLD);

  button->textEngine = textEngine;
  button->widgetText = TTF_CreateText(
      button->textEngine, 
      button->widgetFont, 
      button->widgetString,
      strlen(button->widgetString)
      );

  if (button->widgetText == NULL) {
    SDL_Log("fucked some shit up");
    return;
  }
}

void buttonAssignSurface(BaseWidget* button, SDL_Surface* surface) {
  button->widgetSurface = surface;
}

void buttonRender(BaseWidget* button) {
  const SDL_PixelFormatDetails *pxFmtDetails = SDL_GetPixelFormatDetails(button->widgetSurface->format);
  
  if (pxFmtDetails == NULL) {
    printf("Fucked some shit up...");
    return;
  }

  bool fillRect = SDL_FillSurfaceRect(
        button->widgetSurface,
        &button->widgetRect,
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
  
  // NOTE: the button string should be a widget's property 
  TTF_Text* message = TTF_CreateText(button->textEngine, button->widgetFont, "Load file", strlen("Load file"));  
  if (message == NULL) {
    printf("Fucked some shit up n");
    return;
  }
  
  bool drawText = TTF_DrawSurfaceText(message, button->widgetRect.x, button->widgetRect.y, button->widgetSurface);
  if (drawText == false) {
    printf("fucked some shit up");
    return;
  }
}

void buttonRefresh(BaseWidget* button, SDL_Surface* newSurface) {
  button->widgetSurface = newSurface;
  buttonRender(button);
}

void buttonHandleEvent(BaseWidget* button, const SDL_Event *e) {
  switch (e->type) {
    case SDL_EVENT_MOUSE_MOTION:
      buttonHandleMouseMotion(button, isPointerIn(button, &e->motion));
      break;
  
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
      buttonHandleMouseButtonDown(button, &e->button, isPointerIn(button, &e->motion));
      break;
    
    case SDL_EVENT_MOUSE_BUTTON_UP:
      buttonHandleMouseMotion(button, isPointerIn(button, &e->motion));
      break;

    default:
      return;
  }

  buttonRender(button);
  
  return;
}

void buttonHandleMouseMotion(BaseWidget* button, bool isIn) {
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

void buttonHandleMouseButtonDown(
    BaseWidget* button, 
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
