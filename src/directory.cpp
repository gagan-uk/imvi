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
    if (index >= 0 && index < fileList.count) {
        return fileList.paths[index];
    }
    return NULL;
}