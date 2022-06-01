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

    fread(&Picture.biBitCount, sizeof(Picture.biBitCount), 1, f);
    printf("\n Liczba bitow na piksel: %d (1, 4, 8, or 24)", Picture.biBitCount);

    fread(&Picture.biCompression, sizeof(Picture.biCompression), 1, f);
    printf("\n Kompresja: %d (0=none, 1=RLE-8, 2=RLE-4)", Picture.biCompression);

    fread(&Picture.biSizeImage, sizeof(Picture.biSizeImage), 1, f);
    printf("\n Rozmiar samego rysunku: %d", Picture.biSizeImage);

    fread(&Picture.biXPelsPerMeter, sizeof(Picture.biXPelsPerMeter), 1, f);
    printf("\n Rozdzielczosc pozioma: %d", Picture.biXPelsPerMeter);

    fread(&Picture.biYPelsPerMeter, sizeof(Picture.biYPelsPerMeter), 1, f);
    printf("\n Rozdzielczosc pionowa: %d", Picture.biYPelsPerMeter);

    fread(&Picture.biClrUsed, sizeof(Picture.biClrUsed), 1, f);
    printf("\n Liczba kolorow w palecie: %d", Picture.biClrUsed);

    fread(&Picture.biClrImportant, sizeof(Picture.biClrImportant), 1, f);
    printf("\n Wazne kolory w palecie: %d", Picture.biClrImportant);



    FILE* negative = fopen("negative.bmp", "wb");
    if (negative == nullptr)
    {
        printf("\n\n Can't open the file");
        return -1;
    }
    else
    {
        printf("\n\n File negative opened!");
    }

    fseek(negative, 0, SEEK_SET);
    fwrite(&File.bfType, sizeof(File.bfType), 1, negative);
    fwrite(&File.bfSize, sizeof(File.bfSize), 1, negative);
    fwrite(&File.bfReserved1, sizeof(File.bfReserved1), 1, negative);
    fwrite(&File.bfReserved2, sizeof(File.bfReserved2), 1, negative);
    fwrite(&File.bfOffBits, sizeof(File.bfOffBits), 1, negative);

    fseek(negative, 14, SEEK_SET);
    fwrite(&Picture.biSize, sizeof(Picture.biSize), 1, negative);
    fwrite(&Picture.biWidth, sizeof(Picture.biWidth), 1, negative);
    fwrite(&Picture.biHeight, sizeof(Picture.biHeight), 1, negative);
    fwrite(&Picture.biPlanes, sizeof(Picture.biPlanes), 1, negative);
    fwrite(&Picture.biBitCount, sizeof(Picture.biBitCount), 1, negative);
    fwrite(&Picture.biCompression, sizeof(Picture.biCompression), 1, negative);
    fwrite(&Picture.biSizeImage, sizeof(Picture.biSizeImage), 1, negative);
    fwrite(&Picture.biXPelsPerMeter, sizeof(Picture.biXPelsPerMeter), 1, negative);
    fwrite(&Picture.biYPelsPerMeter, sizeof(Picture.biYPelsPerMeter), 1, negative);
    fwrite(&Picture.biClrUsed, sizeof(Picture.biClrUsed), 1, negative);
    fwrite(&Picture.biClrImportant, sizeof(Picture.biClrImportant), 1, negative);

    fseek(negative, sizeof(File.bfOffBits), SEEK_SET);

    int bmpImg;
    for (int i = File.bfOffBits; i < File.bfSize; i++)
    {
        fseek(f, i, SEEK_SET);
        fseek(negative, i, SEEK_SET);
        fread(&bmpImg, 3, 1, f);
        bmpImg = INT_MAX - bmpImg; 
        fwrite(&bmpImg, 3, 1, negative);
    }

    printf("\n");
    fclose(f);
    fclose(negative);

    return 0;
}


