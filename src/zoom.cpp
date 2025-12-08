#include "zoom.h"
#include <raylib.h>

float zoom{1.0f};
const float zoomMin{0.25f};
const float zoomMax{5.0f};

void InitZoom()
{
    zoom = 1.0f;
};

void UpdateZoom()
{
    
if (IsKeyPressed(KEY_EQUAL))
{
    zoom += 0.25f;
    if (zoom > zoomMax) zoom = zoomMax;
}

if (IsKeyPressed(KEY_MINUS))
{
    zoom -= 0.25f;
    if (zoom < zoomMin) zoom = zoomMin;
}

if (IsKeyPressed(KEY_R))
{
    zoom = {1.0f};
}
}

float GetZoomLevel()
{
    return zoom;
}

void ResetZoom() 
{
    zoom = 1.0f;
}