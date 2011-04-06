#ifndef _CHUNK_H_
#define _CHUNK_H_

#include <iostream>
#include <string>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//#include <GL/glut.h>

#include "nbt.h"

#include "Color.h"

class Chunk
{
private:
    nbt_byte_array *blocks;
    nbt_file *nf;
    Color *img;
    
public:
    int32_t x_pos, z_pos;
    
    enum RenderMode{ TOP_DOWN_LOW_RES, TOP_DOWN_LOW_RES_HEIGHT,
                     TOP_DOWN_LOW_RES_LIGHT, OPEN_GL_RENDER,
                     CAVES_LOW_RES, CAVES_LOW_RES_HEIGHT, CAVES_LOW_RES_LIGHT};

    Chunk();
    Chunk(string filename);
    Chunk(Chunk &c);
    ~Chunk();
    void free();
    void Load(string filename);
    void Render(int mode, void *params = NULL);
    void GetImage(Color* dest, int width, int height, int min_x, int min_z);
    
private:
    Color GetBlockColor(int blockId);
    bool IsDrawable(int blockID);
    void DrawBlock(int blockId);
    void DrawBlock(Color color);
    
};

#endif 
