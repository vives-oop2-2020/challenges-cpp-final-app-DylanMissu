#include "TetrisBlock.h"
#include "resources/Shapes.h"

TetrisBlock::TetrisBlock(Graphics *thisgraphics)
{
    //game = thisGame;
    graphics = thisgraphics;
}

void TetrisBlock::generateRandomBlock()
{
    Shapes shapes;

    blockx = 0;
    blocky = 0;

    switch (std::rand() % 7)
    {
    case 0:
        for (int i=0; i<16; i++) 
        {
            _block[i] = shapes.blueRicky[i];
        }
        break;
    case 1:
        for (int i=0; i<16; i++) 
        {
            _block[i] = shapes.clevelandZ[i];
        }
        break;
    case 2:
        for (int i=0; i<16; i++) 
        {
            _block[i] = shapes.hero[i];
        }
        break;
    case 3:
        for (int i=0; i<16; i++) 
        {
            _block[i] = shapes.orangeRicky[i];
        }
        break;
    case 4:
        for (int i=0; i<16; i++) 
        {
            _block[i] = shapes.rhodeIsland[i];
        }
        break;
    case 5:
        for (int i=0; i<16; i++) 
        {
            _block[i] = shapes.smashBoy[i];
        }
        break;
    default:
        for (int i=0; i<16; i++) 
        {
            _block[i] = shapes.teewave[i];
        }
        break;
    }
   
    setAbsolutePosition(graphics->getWidth()/2 - 2, 0);
}

void TetrisBlock::left() 
{
    if (!stopLeft)
    {
        blockx -= 1;
    }
}

void TetrisBlock::right() 
{
    if (!stopRight)
    {
        blockx += 1;
    }
}

void TetrisBlock::down() 
{
    if (!stopDown)
    {
        blocky += 1;
    }
}

void TetrisBlock::rotate()
{
    int rotatedBlock[16] = {};

    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            //https://stackoverflow.com/questions/20149783/rotating-a-2d-converted-1d-array-90-degrees-clockwise
            rotatedBlock[j + 4*i] = _block[i + 4*(4 - 1 - j)];
        }
    }

    rotateHelper(rotatedBlock);
}

void TetrisBlock::rotateHelper(int block[16])
{
    bool collidingLeft = false;
    bool collidingRight = false;

    for (int i=0; i<16; i++)
    {
        if (graphics->hasBlockAt((i%4 + blockx) - 1, (i/4 + blocky)))
        {
            right();
            rotateHelper(block);
            collidingLeft = true;
        }

        if (graphics->hasBlockAt((i%4 + blockx) + 1, (i/4 + blocky)))
        {
            left();
            rotateHelper(block);
            collidingRight = true;
        }
    }

    if (!(collidingLeft && collidingRight))
    {
        for (int i=0; i<16; i++)
        {
            _block[i] = block[i];
        }
    }
}

void TetrisBlock::setAbsolutePosition(int x, int y)
{
    blockx = x;
    blocky = y;
}

void TetrisBlock::setRelativePosition(int x, int y)
{
    blockx += x;
    blocky += y;
}

bool TetrisBlock::show() 
{
    stopDown = false;
    stopLeft = false;
    stopRight = false;
    bool stopGame = false;
    for (int i=0; i<16; i++) 
    {
        if(_block[i] != 0)
        {
            int blockX = (blockx + i%4);
            int blockY = (blocky + i/4);

            // check for collisions
            stopDown += graphics->hasBlockAt(blockX, blockY + 1);
            stopLeft += graphics->hasBlockAt(blockX - 1, blockY);
            stopRight += graphics->hasBlockAt(blockX + 1, blockY);

            graphics->drawPixel(blockX,  blockY, _block[i]);
        }
    }

    if (stopDown)
    {
        if (blocky == 0){
            stopGame = true;
        }
        graphics->bake();
        generateRandomBlock();
    }

    return stopGame;
}