#include "Map.h"

Map::Map(string BaseFolder, Chunk::RenderMode mode, void *params) :
img(NULL)
{
    Load(BaseFolder, mode, params);
}

Map::~Map()
{
    for(list<Chunk*>::iterator it = chunks.begin(); it != chunks.end(); it++)
    {
        delete *it;
    }
    
    if(img != NULL)
        delete [] img;
}

void Map::SaveImage(string filename)
{

    cout << "Creating " << filename << " (" << (max_x - min_x + 1) * 16 << " X " << (max_z - min_z + 1) * 16 << ")..." << endl;
    
    if(img != NULL)
        delete [] img;
        
    img = new Color[(max_x - min_x + 1) * (max_z - min_z + 1) * 16 * 16];
    
    if(img == NULL)
        cout << "Error allocating image data..." << endl;
    
    for(int i = 0; i < (max_x - min_x + 1) * (max_z - min_z + 1) * 16 * 16; i++)
    {
        img[i].a = 0;
    }

    for(list<Chunk*>::iterator it = chunks.begin(); it != chunks.end(); it++)
    {
        Chunk* ptr = *it;
        
        ptr->GetImage(img, (max_x - min_x + 1) * 16, (max_z - min_z + 1) * 16, min_x, min_z);
    }
    
    cout << "Saving image to " << filename << "..." << endl;
    
    ilInit();
    ilEnable(IL_FILE_OVERWRITE);
    
    ilTexImage( (max_x - min_x + 1) * 16, (max_z - min_z + 1) * 16, 0, 4, IL_RGBA, IL_UNSIGNED_BYTE, img);

    ilSaveImage( filename.c_str());
}

void Map::Load(string BaseFolder, Chunk::RenderMode mode, void *params)
{
    cout << "Rendering map in: " + BaseFolder + " ... " << endl;

    list<string> dirs = GetDirectories(BaseFolder);
    bool first = true;
    
    #pragma omp parallel firstprivate(mode)
    {
        #pragma omp master
        {
            //list<Chunk*> cache;

            if(dirs.size() != 0)
            {
                for(list<string>::iterator it = dirs.begin(); it != dirs.end(); it++)
                {
                    list<string> dirs2 = GetDirectories(*it);
                    
                    for(list<string>::iterator it2 = dirs2.begin(); *it != "Players" && it2 != dirs2.end(); it2++)
                    {
                        list<string> files = GetFiles(*it2);
                        
                        for(list<string>::iterator fit = files.begin(); *it2 != "Players" && fit != files.end(); fit++)
                        {
                            if((*fit).find(".dat") != string::npos)
                            {
                                //cout << "Loading: " + *fit + " ... " << endl;
                            
                                //Chunk *ptr = new Chunk(*fit);

                                Chunk *ptr = new Chunk();
                                string filename = *fit;

                                #pragma omp task untied default(none) firstprivate(ptr, mode, filename, params)
                                {
                                    ptr->Load(filename);
                                    ptr->Render(mode, params);
                                    ptr->free();
                                }
                                
                                /* if(first)
                                {
                                    first = false;
                                    
                                    min_x = ptr->x_pos;
                                    max_x = ptr->x_pos;
                                    min_z = ptr->z_pos;
                                    max_z = ptr->z_pos;
                                }
                                else
                                {
                                    if(ptr->x_pos < min_x)
                                        min_x = ptr->x_pos;
                                    else if(ptr->x_pos > max_x)
                                        max_x = ptr->x_pos;
                                        
                                    if(ptr->z_pos < min_z)
                                        min_z = ptr->z_pos;
                                    else if(ptr->z_pos > max_z)
                                        max_z = ptr->z_pos;
                                } */
                                
                                chunks.push_back(ptr);
                                //cache.push_back(ptr);

/*                                if(cache.size() > omp_get_num_procs() * 4)
                                {
                                    for(list<Chunk*>::iterator cit = cache.begin(); cit != cache.end(); cit++)
                                    {
                                        ptr = *cit;
                                        #pragma omp task untied default(none) firstprivate(ptr, mode)
                                        {
                                            ptr->Render(mode);
                                            ptr->free();
                                        }
                                    }

                                    cache.clear();
                                } */
                            }
                        }
                    }
                }
            }
/*
            Chunk* ptr;

            for(list<Chunk*>::iterator cit = cache.begin(); cit != cache.end(); cit++)
            {
                ptr = *cit;
                #pragma omp task untied default(none) firstprivate(ptr, mode)
                {
                    ptr->Render(mode);
                    ptr->free();
                }
            }

            cache.clear(); */
        }
        
        #pragma omp taskwait
    }

    for(list<Chunk*>::iterator it = chunks.begin(); it != chunks.end(); it++)
    {
        Chunk *ptr = *it;

        if(first)
        {
            first = false;

            min_x = ptr->x_pos;
            max_x = ptr->x_pos;
            min_z = ptr->z_pos;
            max_z = ptr->z_pos;
        }
        else
        {
            if(ptr->x_pos < min_x)
                min_x = ptr->x_pos;
            else if(ptr->x_pos > max_x)
                max_x = ptr->x_pos;

            if(ptr->z_pos < min_z)
                min_z = ptr->z_pos;
            else if(ptr->z_pos > max_z)
                max_z = ptr->z_pos;
        }
    }
}
