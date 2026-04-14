#include "tafa.h"

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

void	FlipTextureHorizontal(Texture2D *tex)
{
	Image img = LoadImageFromTexture(*tex);
    
        Color *pixels = (Color *)img.data;
        int width = img.width;
        int height = img.height;
  
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width / 2; x++)
	        {
	        	int leftIndex = y * width + x;
	                int rightIndex = y * width + (width - 1 - x);
	                Color temp = pixels[leftIndex];
	                pixels[leftIndex] = pixels[rightIndex];
	                pixels[rightIndex] = temp;
	        }
	}
	
	UpdateTexture(*tex, img.data);
	
	UnloadImage(img);
}

// Dessine une courbe quadratique + une pointe de flèche au bout.
// start: point de départ (centre du bouton A/B/C/D)
// end: point d’arrivée (zone de la réponse)
// control: point de contrôle qui "tire" la courbe
void DrawArrowBezierQuad(Vector2 start, Vector2 control, Vector2 end, float thickness, Color color)
{
    const int steps = 24;
    Vector2 prev = start;

    for (int i = 1; i <= steps; i++)
    {
        float t = (float)i / (float)steps;

        // Bézier quadratique:
        // B(t) = (1-t)^2 * start + 2(1-t)t * control + t^2 * end
        float oneMinus = 1.0f - t;
        Vector2 p = (Vector2){
            oneMinus * oneMinus * start.x + 2.0f * oneMinus * t * control.x + t * t * end.x,
            oneMinus * oneMinus * start.y + 2.0f * oneMinus * t * control.y + t * t * end.y
        };

        DrawLineEx(prev, p, thickness, color);
        prev = p;
    }

    // --- pointe de flèche au bout ---
    Vector2 dir = (Vector2){ end.x - prev.x, end.y - prev.y };
    float len = sqrtf(dir.x*dir.x + dir.y*dir.y);
    if (len < 0.0001f) return;
    dir.x /= len; dir.y /= len;

    // angle "arrière" pour faire la tête
    float headLen = 10.0f;
    Vector2 right = (Vector2){ -dir.y, dir.x }; // vecteur perpendiculaire
    Vector2 tip1 = (Vector2){ end.x - dir.x * headLen + right.x * (headLen * 0.5f), end.y - dir.y * headLen + right.y * (headLen * 0.5f) };
    Vector2 tip2 = (Vector2){ end.x - dir.x * headLen - right.x * (headLen * 0.5f), end.y - dir.y * headLen - right.y * (headLen * 0.5f) };

    DrawLineEx(end, tip1, thickness, color);
    DrawLineEx(end, tip2, thickness, color);
}
