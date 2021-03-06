#pragma once

#include <string>

class Graphics {
    public:
        Graphics(const int width, const int height);
        void clearRect(int x, int y, int width, int height);
        void drawPixel(int x, int y, int colorCode);
        int removeFullLines();
        const int getHeight();
        int *getBakedBuffer();
        const int getWidth();
        int *getBuffer();
        void clearAll();
        void bake();

    public:
        bool hasBlockAt(int x, int y);

    private:
        void drawGameBorder();
        bool hasFullLineAt(int y);
        void removeLine(int y);

    private:
        int *buffer;
        int *tempBuffer;
        int *bakedBuffer;
        int gameWidth;
        int gameHeight;

};