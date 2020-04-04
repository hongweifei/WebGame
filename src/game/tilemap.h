



#ifndef TILEMAP
#define TILEMAP

typedef struct
{
    int width;//地图宽，32bit，4byte，4字节
    int height;//地图高，32bit，4byte，4字节
    int tile_width;//瓦片宽，4字节
    int tile_height;//瓦片高，4字节
}TileMapInformation;

typedef struct
{
    int tile_count;
    int *image_path_char_n;
    char **image_path;
}TileMapSets;

typedef struct
{
    int *data;
}TileMapData;

typedef struct
{
    TileMapInformation information;

    int tile_count;
    char **tile_image_path;
    //SDL_Texture **tile_texture;

    int *map_data;
}TileMap;

void WriteTileMap(const char *path,TileMapInformation map_information,TileMapData map_data,int tile_count,...);
TileMap LoadTileMap(const char *path);



#endif