#include "Chunk.h"

Chunk::Chunk() :
blocks(NULL), img(new Color[16 * 16]), nf(NULL)
{

}

Chunk::Chunk(string filename) :
blocks(NULL), img(new Color[16 * 16]), nf(NULL)
{
    Load(filename);
}

Chunk::Chunk(Chunk &c) :
blocks(NULL), img(new Color[16 * 16]), nf(NULL)
{
    x_pos = c.x_pos;
    z_pos = c.z_pos;
    
    blocks = c.blocks;
    
    for(int i = 0; i < 16 * 16; i++)
    {
        img[i] = c.img[i];
    }
}

Chunk::~Chunk()
{     
    delete [] img;
}

void Chunk::free()
{
    if(nf != NULL)
        nbt_free(nf);
        //nbt_free_byte_array(blocks);
}

void Chunk::Load(string filename)
{
    if (nbt_init(&nf) != NBT_OK)
    {
        fprintf(stderr, "nbt_init(): Failed.\n");
        cout << "nbt_init(): Failed." << endl;

        return;
    }
    
    /* Try parsing */
    if (nbt_parse(nf, filename.c_str()) != NBT_OK)
    {
        fprintf(stderr, "nbt_parse(): Failed\n");
        cout << "nbt_parse(): Failed" << endl;

        return;
    }
    
    nbt_tag *level = nbt_find_tag_by_name("Level", nf->root);

    nbt_tag *blocks_tag = nbt_find_tag_by_name("Blocks", level);

    blocks = nbt_cast_byte_array(blocks_tag);
    
    nbt_tag *pos_tag = nbt_find_tag_by_name("xPos", level);
    
    x_pos = *nbt_cast_int(pos_tag);
    
    pos_tag = nbt_find_tag_by_name("zPos", level);
    
    z_pos = *nbt_cast_int(pos_tag);
}

void Chunk::Render(int mode, void *params)
{
    switch(mode)
    {
    case TOP_DOWN_LOW_RES:
    case TOP_DOWN_LOW_RES_HEIGHT:
    case TOP_DOWN_LOW_RES_LIGHT:
            for (int x = 0; x < 16; x++)
            {
                for (int z = 0; z < 16; z++)
                {
                    for (int y = 127; y >= 0; y--)
                    {
                        int id = blocks->content[y + z * 128 + x * 128 * 16];

                        if(IsDrawable(id))
                        {
                            switch(mode)
                            {
                            case TOP_DOWN_LOW_RES_HEIGHT:
                                img[x + z * 16] = Color(y / 127.0f * 255, y / 127.0f * 255, y / 127.0f * 255);
                                break;
                            case TOP_DOWN_LOW_RES:
                            case TOP_DOWN_LOW_RES_LIGHT:
                                img[x + z * 16] = GetBlockColor(id);
                                break;
                            }
                            break;
                        }
                    }
                }
            }
            break;
            
        case OPEN_GL_RENDER:
            for (int x = 0; x < 16; x++)
            {
                //glPushMatrix();
                
                //glTranslatef(x / 16.0f, 0, 0);
                
                for (int z = 0; z < 16; z++)
                {
                
                    //glPushMatrix();

                    //glTranslatef(0, 0, z / 16.0f);
                    
                    for (int y = 0; y < 128; y++)
                    {
                        int id = blocks->content[y + z * 128 + x * 128 * 16];

                        if(IsDrawable(id))
                        {
                            //glPushMatrix();
                            
                            //glTranslatef(0, y / 16.0f, 0);
                            //glTranslatef(1/32.0, 1/32.0, 1/32.0);
                            
                            DrawBlock(id);
                            
                            //glPopMatrix();
                        }
                    }
                    
                    //glPopMatrix();
                    
                }
                
                //glPopMatrix();
            }
            
         case CAVES_LOW_RES:
         case CAVES_LOW_RES_HEIGHT:
         case CAVES_LOW_RES_LIGHT:
            for (int x = 0; x < 16; x++)
            {
                for (int z = 0; z < 16; z++)
                {
                    img[x + z * 16] = Color(0, 0, 0, 0);

                    bool cave = false;
                    bool exit = false;
                    bool first = true;
                    bool bottom = false;
                    for (int y = 127; y >= 0; y--)
                    {
                        int id = blocks->content[y + z * 128 + x * 128 * 16];

                        if(IsDrawable(id))
                        {
                            if(first && !cave)
                                img[x + z * 16] = GetBlockColor(id);

                            first = false;

                            if(cave)
                                bottom = true;

                            if(id != 17 && id != 18)
                            {
                                cave = true;
                            }
                            else
                            {
                                cave = false;
                                bottom = false;
                            }
                        }

                        Color c;

                        float alpha = *((float*)params);

                        if(cave && id == 50)
                        {
                            c = img[x + z * 16];
                            Color c2 = GetBlockColor(id);
                            img[x + z * 16] = Color((int)(c2.r * (1 - alpha) + c.r * alpha), (int)(c2.g * (1 - alpha) + c.g * alpha), (int)(c2.b * (1 - alpha) + c.b * alpha));
                            break;
                        }
                        
                        if(cave && bottom)
                        {
                            switch(id)
                            {
                                case 0:
                                    c = img[x + z * 16];
                                    switch(mode)
                                    {
                                    case CAVES_LOW_RES_HEIGHT:
                                        img[x + z * 16] = Color((int)((y / 127.0f) * 256 * (1 - alpha) + c.r * alpha), (int)((y / 127.0f) * 265 * (1 - alpha) + c.g * alpha), (int)((y / 127.0f) * 256 * (1 - alpha) + c.b * alpha));
                                        break;
                                    case CAVES_LOW_RES:
                                    case CAVES_LOW_RES_LIGHT:
                                        img[x + z * 16] = Color((int)(c.r * alpha), (int)(c.g * alpha), (int)(c.b * alpha));
                                        break;
                                    }
                                    exit = true;
                                    break;
                                    
                                //case 8: //Water
                                //case 9: //Water moving
                                    //img[x + z * 16] = Color(38, 92, 255);
                                    //exit = true;
                                    break;

                                case 10: //Lava
                                case 11: //Lava Moving
                                    c = img[x + z * 16];
                                    img[x + z * 16] = Color((int)(198 * (1 - alpha) + c.r * alpha), (int)(58 * (1 - alpha) + c.g * alpha), (int)(4 * (1 - alpha) + c.b * alpha));
                                    exit = true;
                                    break;                              
                            }
                        }
                        
                        if(exit)
                            break;
                    }
                }
            }
            break;                       
        break;
    }
}

void Chunk::GetImage(Color* dest, int width, int height, int min_x, int min_z)
{
    for (int z = 0; z < 16; z++)
    {
        for (int x = 0; x < 16; x++)
        {
            dest[((x + (x_pos - min_x) * 16)) + width * (height - (z + (z_pos - min_z) * 16) - 1)] = img[x + z * 16];
        }
    }
}

bool Chunk::IsDrawable(int blockID)
{
    switch (blockID)
    {
        case 0:
        case 6:
        case 20: //Glass
        case 37:
        case 38:
        case 39:
        case 40:
        case 55:
        case 59:
        case 63:
        case 64:
        case 65:
        case 68:
        case 69:
        case 71:
        case 77:
        case 53:
        case 85:
        case 90:
            return false;

        default:
            return true;
    }
}

Color Chunk::GetBlockColor(int blockId)
{
    switch (blockId)
    {
        case 1: //Stone
        case 14: //Gold Ore
        case 15: //Iron Ore
        case 16: //Coal
        case 43: //Double Stone Slab
        case 44: //Stone Slab
        case 56: //Diamond Ore
        case 61: //Fernace
        case 62: //Burning Furnace
        case 70: //Stone Pressure Plate
        case 73: //Redstone Ore
        case 74: //Glowing Redstone Ore
            return Color(143, 143, 143);

        case 2: //Grass
            return Color(108, 172, 66);

        case 3: //Dirt
        case 60: //Soil
            return Color(121, 85, 58);

        case 4: //Cobblestone
        case 67: //Cobblestone Stairs
            return Color(92, 92, 92);

        case 5: //Wood
        case 47: //Bokshelf
        case 53: //Wooden Stairs
        case 54: //Chest
        case 58: //Workbench
        case 72: //Wooden Pressure Plate
        case 84: //Jukebox
            return Color(180, 144, 90);

        case 7: //Bedrock
            return Color(0, 0, 0);

        case 8: //Water
        case 9: //Water moving
            return Color(38, 92, 255);

        case 10: //Lava
        case 11: //Lava Moving
            return Color(198, 58, 4);

        case 12: //Sand
            return Color(211, 204, 149);

        case 13: //Granite
            return Color(179, 140, 128);

        case 17: //Tree
            return Color(108, 87, 54);

        case 18: //Leaves
            return Color(85, 245, 53);

        case 19: //Sponge?
            return Color(206, 206, 70);

        case 35: //Wool
            return Color(186, 186, 186);

        case 41: //Gold
            return Color(255, 255, 98);

        case 42: //Iron
            return Color(197, 197, 197);

        case 45: //Brick
            return Color(122, 60, 43);

        case 46: //TNT
            return Color(219, 68, 26);

        case 48: //Moss Stone
            return Color(111, 111, 82);

        case 49: //Obsidian
            return Color(60, 48, 86);

        case 50: //Torch
            return Color(255, 255, 151);

        case 51: //Fire
            return Color(213, 137, 11);

        case 52: //Monster Spawner
            return Color(50, 79, 97);

        case 57: //Diamond
            return Color(165, 236, 233);

        case 66: //Minecart Tracks
            return Color(100, 79, 42);

        case 75: //Redstone Torch (off)
        case 76: //Redstone Torch (on)
            return Color(253, 0, 0);

        case 78: //Snow
        case 80: //Snow Block
            return Color(238, 255, 255);

        case 79: //Ice
            return Color(170, 203, 255);

        case 81: //Cactus
            return Color(15, 114, 26);

        case 82: //Clay
            return Color(183, 128, 128);

        case 86: //Pumpkin
        case 91: //Jack-O-Latern
            return Color(227, 144, 29);

        case 87: //Netherrack
            return Color(146, 86, 86);

        case 88: //Soul Sand
            return Color(145, 121, 106);

        case 89: //GlowStone
            return Color(192, 143, 70);

        default:
            return Color(0, 0, 0, 0);
    }
}

void Chunk::DrawBlock(int blockId)
{
    //glDisable ( GL_TEXTURE_2D );
    switch (blockId)
    {
        case 1: //Stone
        case 14: //Gold Ore
        case 15: //Iron Ore
        case 16: //Coal
        case 43: //Double Stone Slab
        case 44: //Stone Slab
        case 56: //Diamond Ore
        case 61: //Fernace
        case 62: //Burning Furnace
        case 70: //Stone Pressure Plate
        case 73: //Redstone Ore
        case 74: //Glowing Redstone Ore
            //glEnable ( GL_TEXTURE_2D );
            //glBindTexture ( GL_TEXTURE_2D, 1 );
            DrawBlock(Color(255, 255, 255));
            //DrawBlock(Color(143, 143, 143));
            return;

        case 2: //Grass
            DrawBlock(Color(108, 172, 66));
            return;

        case 3: //Dirt
        case 60: //Soil
            DrawBlock(Color(121, 85, 58));
            return;

        case 4: //Cobblestone
        case 67: //Cobblestone Stairs
            DrawBlock(Color(92, 92, 92));
            return;

        case 5: //Wood
        case 47: //Bokshelf
        case 53: //Wooden Stairs
        case 54: //Chest
        case 58: //Workbench
        case 72: //Wooden Pressure Plate
        case 84: //Jukebox
            DrawBlock(Color(180, 144, 90));
            return;

        case 7: //Bedrock
            DrawBlock(Color(0, 0, 0));
            return;

        case 8: //Water
        case 9: //Water moving
            DrawBlock(Color(38, 92, 255));
            return;

        case 10: //Lava
        case 11: //Lava Moving
            DrawBlock(Color(198, 58, 4));
            return;

        case 12: //Sand
            DrawBlock(Color(211, 204, 149));
            return;

        case 13: //Granite
            DrawBlock(Color(179, 140, 128));
            return;

        case 17: //Tree
            DrawBlock(Color(108, 87, 54));
            return;

        case 18: //Leaves
            DrawBlock(Color(85, 245, 53));
            return;

        case 19: //Sponge?
            DrawBlock(Color(206, 206, 70));
            return;

        case 35: //Wool
            DrawBlock(Color(186, 186, 186));
            return;

        case 41: //Gold
            DrawBlock(Color(255, 255, 98));
            return;

        case 42: //Iron
            DrawBlock(Color(197, 197, 197));
            return;

        case 45: //Brick
            DrawBlock(Color(122, 60, 43));
            return;

        case 46: //TNT
            DrawBlock(Color(219, 68, 26));
            return;

        case 48: //Moss Stone
            DrawBlock(Color(111, 111, 82));
            return;

        case 49: //Obsidian
            DrawBlock(Color(60, 48, 86));
            return;

        case 50: //Torch
            DrawBlock(Color(255, 255, 151));
            return;

        case 51: //Fire
            DrawBlock(Color(213, 137, 11));
            return;

        case 52: //Monster Spawner
            DrawBlock(Color(50, 79, 97));
            return;

        case 57: //Diamond
            DrawBlock(Color(165, 236, 233));
            return;

        case 66: //Minecart Tracks
            DrawBlock(Color(100, 79, 42));
            return;

        case 75: //Redstone Torch (off)
        case 76: //Redstone Torch (on)
            DrawBlock(Color(253, 0, 0));
            return;

        case 78: //Snow
        case 80: //Snow Block
            DrawBlock(Color(238, 255, 255));
            return;

        case 79: //Ice
            DrawBlock(Color(170, 203, 255));
            return;

        case 81: //Cactus
            DrawBlock(Color(15, 114, 26));
            return;

        case 82: //Clay
            DrawBlock(Color(183, 128, 128));
            return;

        case 86: //Pumpkin
        case 91: //Jack-O-Latern
            DrawBlock(Color(227, 144, 29));
            return;

        case 87: //Netherrack
            DrawBlock(Color(146, 86, 86));
            return;

        case 88: //Soul Sand
            DrawBlock(Color(145, 121, 106));
            return;

        case 89: //GlowStone
            DrawBlock(Color(192, 143, 70));
            return;

        default:
            return;
    }
}

void Chunk::DrawBlock(Color color)
{
    //glColor3f(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
    //glutSolidCube(1/16.0);
}
