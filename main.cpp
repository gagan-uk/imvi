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


  while (!WindowShouldClose()){

    float screenX {(float)GetScreenWidth()/current.width};
    float screenY{(float)GetScreenHeight()/current.height};
    float scale{};

    if (screenX   >  screenY){ scale = screenX;}
    else{scale = screenY;}

    // scaling
    float newWidth {current.width * scale};
    float newHeight { current.height * scale};
    
    // centering the image
    int imageX ((GetScreenWidth() - newWidth) / 2);
    int imageY ((GetScreenHeight() - newHeight) / 2);


    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTextureEx(current,
      (Vector2){(float)imageX,(float)imageY} ,
      0,scale,
      WHITE);

    EndDrawing();

  };
  
  CloseWindow();
  return 0;
}
