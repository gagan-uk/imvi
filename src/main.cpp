#include "raylib.h"
#include "zoom.h"

int main(void){
  //window variables 
  const int screenW {900};
  const int screenH {600};
  const char* windowTitle {"ImvI"};
  const char* iconPath{"images/ico.png"};
  
  InitWindow(screenW, screenH, windowTitle);
  InitZoom(); // sets zoom to 1
  SetWindowState(FLAG_WINDOW_RESIZABLE);
  SetWindowMinSize(400,400);
  
  
  Image icon {LoadImage(iconPath)};
  SetWindowIcon(icon);
  UnloadImage(icon);

  // image renderer
  Image image{LoadImage("images/test.jpg")};
  Texture current{LoadTextureFromImage(image)};
  UnloadImage(image);


  while (!WindowShouldClose()){
    //functions
    UpdateZoom();

    float screenX {(float)GetScreenWidth()/current.width};
    float screenY{(float)GetScreenHeight()/current.height};
    float scale{};

    if (screenX < screenY){ scale = screenX;}
    else{scale = screenY;}

    // scaling
    float finalScale {scale*GetZoomLevel()};
    float newWidth {current.width * finalScale};
    float newHeight { current.height * finalScale};
    
    // centering the image
    int imageX ((GetScreenWidth() - newWidth) / 2);
    int imageY ((GetScreenHeight() - newHeight) / 2);


    BeginDrawing();
    ClearBackground(BLACK);
    DrawTextureEx(current,
      (Vector2){(float)imageX,(float)imageY} ,
      0,finalScale,
      WHITE);

    EndDrawing();

  };
  UnloadTexture(current);
  CloseWindow();
  return 0;
}
