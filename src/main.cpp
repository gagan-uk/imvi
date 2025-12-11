#include "raylib.h"
#include <cstring>
#include "zoom.h"
#include "directory.h"

//// Prgm loop //////
int main(void){
  //window variables 
  const int screenW {900};
  const int screenH {600};
  const char* windowTitle {"ImvI"};
  
  const char* iconPath;
  if (FileExists("/usr/share/imvi/ico.png")) 
  {
    iconPath = "/usr/share/imvi/ico.png";  // System installation
  } else
  {
    iconPath = "images/ico.png";           // Development/local
  }

  InitWindow(screenW, screenH, windowTitle);
  InitZoom(); // sets zoom to 1
  SetWindowState(FLAG_WINDOW_RESIZABLE);
  SetWindowMinSize(400,400);
    
  Image icon {LoadImage(iconPath)};
  SetWindowIcon(icon);
  UnloadImage(icon);

  ///////////////directory handler ///////////////
  FilePathList currentDir = LoadImageFiles(GetWorkingDirectory());
  
  if (GetImageCount(currentDir) == 0) {
      TraceLog(LOG_ERROR, "No Image found / Unsupported file type");
      CloseWindow(); 
      return -1;
  }
  
  TraceLog(LOG_INFO, "Found %d image files", GetImageCount(currentDir)); 
  int currentIndex{0};



  // loading first image in directory
  Image image = LoadImage(GetImagePath(currentDir, 0));
  
  if (image.data == NULL) {
      TraceLog(LOG_ERROR, "Failed to load image: %s", GetImagePath(currentDir, 0));
      UnloadImageFiles(currentDir);
      CloseWindow();
      return -1;
  }

  // texture renderer
  
  Texture current{LoadTextureFromImage(image)};
  UnloadImage(image);
  SetTextureFilter(current, TEXTURE_FILTER_ANISOTROPIC_16X);


  while (!WindowShouldClose()){
    //functions
    UpdateZoom();
    bool updateImage = false; //checks arrow key state

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

//////////////////////////navigation//////////////////////////////////
    if (IsKeyPressed(KEY_RIGHT))
    {
      currentIndex = GetNextImage(currentIndex,GetImageCount(currentDir),true);
      updateImage = true;
    }
    if (IsKeyPressed(KEY_LEFT))
    {
      currentIndex = GetNextImage(currentIndex,GetImageCount(currentDir),false);
      updateImage = true;
    }

     // loads the next image
      if (updateImage) {
          UnloadTexture(current);
          ResetZoom(); 
          
      Image newImage = LoadImage(GetImagePath(currentDir, currentIndex));
        
      if (newImage.data != NULL) {
              current = LoadTextureFromImage(newImage);
              UnloadImage(newImage);
              SetTextureFilter(current, TEXTURE_FILTER_ANISOTROPIC_16X);
              TraceLog(LOG_INFO, "Loaded: %s", GetImagePath(currentDir, currentIndex));
          }
      }
///////////////////////////////////////////////////////////////////////////

    BeginDrawing();
    ClearBackground(BLACK);
    DrawTextureEx(current,
      (Vector2){(float)imageX,(float)imageY} ,
      0,finalScale,
      WHITE);

    EndDrawing();

  };
  /// unloading memory
  UnloadTexture(current);
  UnloadDirectoryFiles(currentDir);
  CloseWindow();
  return 0;
}
