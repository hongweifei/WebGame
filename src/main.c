

#include "system.h"
#include "window/window.h"
#include "game/tilemap.h"


int main(int argc,char *argv[])
{
    SystemInit(INIT_VIDEO|INIT_EVENTS);

    Window *window1 = WindowInit("1",WINDOWPOS_CENTERED,WINDOWPOS_CENTERED,800,600);
    WindowCreate(window1,WINDOW_RESIZABLE|WINDOW_OPENGL);

    TileMapInformation information = {60,19,32,32};
    TileMapData data;

    data.data = (short*)calloc(60*19,sizeof(short));

    data.data[0] = 54;
    data.data[1] = 66;
    data.data[2] = 79;
    data.data[3] = 3;
    data.data[4] = 1;
    data.data[5] = 2;
    data.data[6] = 5;
    data.data[7] = 9;
    data.data[8] = 7;
    data.data[9] = 5;

    WriteTileMap("../map/map1",information,data,1,"../images/spr_wall_0.png");
    TileMap map = LoadTileMap("../map/map1");

    printf("%d\n",map.sets.tile_count);
    int i;
    for (i = 0; i < map.information.tile_width * map.information.tile_height; i++)
    {
        printf("%d\n",map.map_data.data[i]);
    }
    
    for (i = 0; i < map.sets.tile_count; i++)
    {
        printf("%s\n",map.sets.tile_image_path[i]);
    }

    WindowMainLoop(window1);

    return 0;
}
