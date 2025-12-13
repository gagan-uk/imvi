#include "directory.h"
#include <cstring>
#include <raylib.h>

FilePathList LoadImageFiles(const char* directoryPath) {
    return LoadDirectoryFilesEx(directoryPath, ".png;.jpg;.jpeg;.webp;.bmp", false);
}

void UnloadImageFiles(FilePathList fileList) {
    UnloadDirectoryFiles(fileList);
}

int GetImageCount(FilePathList fileList) {
    return fileList.count;
}

const char* GetImagePath(FilePathList fileList, int index) {
    if (index >= 0 && index < (int)fileList.count) {
        return fileList.paths[index];
    }
    return NULL;
}

int GetNextImage(int currentIndex, int totalImages, bool next)
{
    if(next) ///sets to first image
    {
        currentIndex++;
        if (currentIndex >= totalImages) currentIndex = 0; 
    }   
    else ///sets to last image
    {
        currentIndex--;
        if(currentIndex < 0) currentIndex = totalImages-1;
    }
    return currentIndex;
}