#ifndef DIR_H
#define DIR_H
#include "raylib.h"

FilePathList LoadImageFiles(const char* directoryPath);
void UnloadImageFiles(FilePathList fileList);
int GetImageCount(FilePathList fileList);
const char* GetImagePath(FilePathList fileList, int index);
int GetNextImage(int currentIndex,int totalImages,bool next);

#endif
