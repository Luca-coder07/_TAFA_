#include "raylib_utils.h"

Texture2D	LoadTextureFromFile(const char *path)
{
	Image		img = LoadImage(path);
	Texture2D	tex = LoadTextureFromImage(img);
	UnloadImage(img);
	return (tex);
}

void	FlipTextureVertical(Texture2D *tex)
{
	// Récupérer l'image liée à la texture
	Image img = LoadImageFromTexture(*tex);   // Charger l'image depuis la texture
    
        Color *pixels = (Color *)img.data;
        int width = img.width;
        int height = img.height;
  
	// Flip vertical: échanger ligne par ligne
	for (int y = 0; y < height / 2; y++)
	{
		for (int x = 0; x < width; x++)
	        {
	        	int topIndex = y * width + x;
	                int bottomIndex = (height - 1 - y) * width + x;
	                Color temp = pixels[topIndex];
	                pixels[topIndex] = pixels[bottomIndex];
	                pixels[bottomIndex] = temp;
	        }
	}
	
	// Mettre à jour la texture avec l'image modifiée
	UpdateTexture(*tex, img.data);
	
	// Libérer l'image (data est toujours alloué)
	UnloadImage(img);
}
