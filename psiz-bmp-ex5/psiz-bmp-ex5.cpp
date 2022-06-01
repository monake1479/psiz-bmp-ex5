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
        printf("\n\n Nie mozna otworzyć pliku!");
        return -1;
    }
    else
    {
        printf("\n\n Plik f otworzony!");
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

    fseek(f, 14, SEEK_SET);
    fread(&Picture.biSize, sizeof(Picture.biSize), 1, f);
    printf("\n Wielkosc naglowka informacyjnego: %d", Picture.biSize);

    fread(&Picture.biWidth, sizeof(Picture.biWidth), 1, f);
    printf("\n Szerokosc: %d pikseli", Picture.biWidth);

    fread(&Picture.biHeight, sizeof(Picture.biHeight), 1, f);
    printf("\n Wysokosc: %d pikseli", Picture.biHeight);

    fread(&Picture.biPlanes, sizeof(Picture.biPlanes), 1, f);
    printf("\n Liczba platow: %d", Picture.biPlanes);

    
}


