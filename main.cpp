#include "raylib.h"

int main(void){
  //window variables 
  const int screenW {900};
  const int screenH {600};
  const int screenFont {20};
  const char* windowTitle {"ImvI"};
  const char* iconPath{"ico.png"};
  
  InitWindow(screenW, screenH, windowTitle);
  SetWindowState(FLAG_WINDOW_RESIZABLE);
  SetWindowMinSize(400,400);
  
  
  Image icon {LoadImage(iconPath)};
  SetWindowIcon(icon);
  UnloadImage(icon);

  // image renderer
  Image image{LoadImage("test.jpg")};
  Texture current{LoadTextureFromImage(image)};
  UnloadImage(image);

  int imageX{(GetScreenWidth() - current.width) / 2 };
  int imageY{(GetScreenHeight() - current.height) / 2};



  while (!WindowShouldClose()){

    BeginDrawing();
      DrawTexture(current,imageX,imageY,WHITE);      
    EndDrawing();

  };
  
  CloseWindow();
  return 0;
}
