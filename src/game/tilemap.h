



#ifndef TILEMAP
#define TILEMAP

typedef struct
{
    short width;//地图宽，16bit，2byte，2字节
    short height;//地图高，16bit，2byte，2字节
    short tile_width;//瓦片宽，2字节
    short tile_height;//瓦片高，2字节
}TileMapInformation;

typedef struct
{
    short tile_count;
    char **tile_image_path;
}TileMapSets;

typedef struct
{
    short *data;
}TileMapData;

typedef struct
{
    TileMapInformation information;
    TileMapSets sets;
    TileMapData map_data;
}TileMap;

void WriteTileMap(const char *path,TileMapInformation map_information,TileMapData map_data,short tile_count,...);
TileMap LoadTileMap(const char *path);



#endif
