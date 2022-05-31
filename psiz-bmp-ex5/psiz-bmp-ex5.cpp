#include "pch.h"

struct FileHeader {
    short bfType;
    int bfSize;
    short bfReserved1;
    short bfReserved2;
    int bfOffBits;
} File;

struct PictureHeader {
    int biSize;
    int biWidth;
    int biHeight;
    short biPlanes;
    short biBitCount;
    int biCompression;
    int biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    int biClrUsed;
    int biClrImportant;
} Picture;

struct ColourRGB {
    char R;
    char G;
    char B;
} Rgb;

int main(int arc, char * argv[])
{
    FILE* f = fopen(argv[1], "rb");

    if (f == nullptr)
    {
        printf("\n\n Can't open the file");
        return -1;
    }
    else
    {
        printf("\n\n File f opened!");
    }

    printf("\n INFORMACJE O BITMAPIE\n\n");

    fread(&File.bfType, sizeof(File.bfType), 1, f);
    printf(" Typ: %x", File.bfType);

    fread(&File.bfSize, sizeof(File.bfSize), 1, f);
    printf("\n Rozmiar pliku: %d bajtow", File.bfSize);

    fread(&File.bfReserved1, sizeof(File.bfReserved1), 1, f);
    printf("\n Zarezerwowane 1: %d", File.bfReserved1);

    fread(&File.bfReserved2, sizeof(File.bfReserved2), 1, f);
    printf("\n Zarezerwowane 2: %d", File.bfReserved2);

    fread(&File.bfOffBits, sizeof(File.bfOffBits), 1, f);
    printf("\n Pozycja danych obrazkowych: %d", File.bfOffBits);

    printf("\n");
}


