#ifndef _MAP_H_
#define _MAP_H_

#include "Chunk.h"
#include "FileEnumeration.h"
#include "omp.h"

#include <list>
using namespace std;

#ifdef LINUX
#include <IL/il.h>
#else
#include <il.h>
#endif

class Map
{
private:
    list<Chunk*> chunks;
    Color* img;
    int min_x, max_x, min_z, max_z;
    
public:
    Map(string BaseFolder, Chunk::RenderMode mode, void *params = NULL);
    ~Map();
    
    void SaveImage(string filename);
    
private:
    void Load(string BaseFolder, Chunk::RenderMode mode, void *params = NULL);
};

#endif 
