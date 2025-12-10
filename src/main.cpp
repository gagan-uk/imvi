#include "raylib.h"
#include "zoom.h"
#include <cstring>




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

  //directory handler
  char directory[512]= {0};
  const char* workingDir { GetWorkingDirectory()};
  strncpy(directory,workingDir,sizeof(directory)-1);
  FilePathList currentDir {LoadDirectoryFilesEx(directory,".png;.jpg;.jpeg;.webp;.bmp",false)};
  if (currentDir.count == 0)
  {
    TraceLog(LOG_ERROR,"No Image found / Unsupported file type");
    CloseWindow(); 
    return -1;
  };
  TraceLog(LOG_INFO, "Found %d image files", currentDir.count); 


  Image image {LoadImage(currentDir.paths[0])};

  // image renderer
  
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
  UnloadDirectoryFiles(currentDir);
  CloseWindow();
  return 0;
}
