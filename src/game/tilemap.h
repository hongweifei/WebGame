



#ifndef TILEMAP
#define TILEMAP

typedef struct
{
    short width;//地图宽，32bit，4byte，4字节
    short height;//地图高，32bit，4byte，4字节
    short tile_width;//瓦片宽，4字节
    short tile_height;//瓦片高，4字节
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
