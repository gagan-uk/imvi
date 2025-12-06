#include "raylib.h"

int main(void){
  
  const int screenW {900};
  const int screenH {600};
  const int screenFont {20};
  const char* windowTitle {"ImvI"};
  const char* iconPath{"ico.png"};
  
  InitWindow(screenW, screenH, windowTitle);
  SetWindowState(FLAG_WINDOW_RESIZABLE);
  
  
  Image icon {LoadImage(iconPath)};
  SetWindowIcon(icon);
  UnloadImage(icon);

  const char* text {"Image here"};
  int textWidth { MeasureText(text, screenFont)};
  int screenC { (screenW - textWidth) / 2};  
  int screenCY { (screenH - screenFont) / 2};
  
  while (!WindowShouldClose()){

    BeginDrawing();
      ClearBackground(BLACK);
      DrawText(text, screenC, screenCY, screenFont, RAYWHITE);
    EndDrawing();

  };
  
  CloseWindow();
  return 0;
}
