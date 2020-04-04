

#include "tilemap.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

void WriteTileMap(const char *path,TileMapInformation map_information,TileMapData map_data,int tile_count,...)
{
    int *image_path_char_n = (int*)calloc(tile_count,sizeof(int));//图片路径字符串大小
    char *image_path[tile_count];//图片路径

    if(tile_count > 0)
    {
        va_list image_path_list;
        va_start(image_path_list,tile_count);

        int i;
        for (i = 0; i < tile_count; i++)
        {
            image_path[i] = va_arg(image_path_list,char*);//取出图片路径
            image_path_char_n[i] = strlen(image_path[i]);//计算图片路径字符串大小
        }
        
        va_end(image_path_list);
    }
    
    /*开始写出地图*/
    FILE *fp = fopen(path,"w");

    fseek(fp,0L,SEEK_SET);
    fwrite(&map_information,1,sizeof(TileMapInformation),fp);//写出地图信息

    fwrite(&tile_count,1,sizeof(tile_count),fp);//写出瓦片数量

    int i;
    for (i = 0; i < tile_count; i++)
    {
        fwrite(&image_path_char_n[i],1,sizeof(int),fp);//写出瓦片图片路径字符
        fwrite(&image_path[i],1,sizeof(char) * image_path_char_n[i],fp);
    }
    
    fwrite(map_data.data,sizeof(int),map_information.width * map_information.height,fp);

    fclose(fp);
}

TileMap LoadTileMap(const char *path)
{
    FILE *fp = fopen(path,"r");

    TileMapInformation tile_map_information;
    TileMapSets tile_sets;
    TileMapData tile_map_data;

    TileMap tile_map;

    fseek(fp,0L,SEEK_SET);//跳至第0字节处
    fread(&tile_map_information,1,sizeof(TileMapInformation),fp);//读入tile_map_information

    tile_map_data.data = (int*)calloc(tile_map_information.width * tile_map_information.height,sizeof(int));

    fread(&tile_sets,1,sizeof(int),fp);//读入tile_count

    if(tile_sets.tile_count > 0)
    {
        tile_sets.image_path_char_n = (int*)calloc(tile_sets.tile_count,sizeof(int));
        tile_sets.image_path = (char**)calloc(tile_sets.tile_count,sizeof(char*));

        int i;
        for (i = 0; i < tile_sets.tile_count; i++)
        {
            fread(&tile_sets.image_path_char_n[i],1,sizeof(int),fp);

            tile_sets.image_path[i] = (char*)malloc(sizeof(char) * tile_sets.image_path_char_n[i]);
            fread(&tile_sets.image_path[i],sizeof(char),tile_sets.image_path_char_n[i],fp);
        }
    }
    
    int i;
    for (i = 0; i < tile_map_information.width * tile_map_information.height; i++)
    {
        fread(&tile_map_data.data[i],1,sizeof(int),fp);
    }

    fclose(fp);
    
    tile_map.information = tile_map_information;

    tile_map.tile_count = tile_sets.tile_count;
    tile_map.map_data = tile_map_data.data;

    tile_map.tile_image_path = (char**)malloc(sizeof(char*) * tile_map.tile_count);
    for (i = 0; i < tile_map.tile_count; i++)
    {
        tile_map.tile_image_path[i] = tile_sets.image_path[i];
    }
    

    /*
    tile_map.tile_texture = (SDL_Texture**)malloc(sizeof(SDL_Texture) * tile_map.tile_count);
    
    for (i = 0; i < tile_map.tile_count; i++)
    {
        SDL_Surface *surface = IMG_Load(tile_sets.image_path[i]);
        tile_map.tile_texture[i] = SDL_CreateTextureFromSurface(renderer->r,surface);
        SDL_FreeSurface(surface);
    }
    */

    return tile_map;
}
