#ifndef RAYLIB_UTILS_H
#define RAYLIB_UTILS_H

#include "types.h"

extern Texture2D LoadTextureFromFile(const char *path);
void FlipTextureVertical(Texture2D *tex);
void FlipTextureHorizontal(Texture2D *tex);
void DrawArrowBezierQuad(Vector2 start, Vector2 control, Vector2 end, float thickness, Color color);

#endif
