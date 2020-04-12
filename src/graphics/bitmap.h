
#include <iostream>
#include <sys/types.h>

#ifndef BITMAP
#define BITMAP

//下面两个结构是位图的结构  
typedef struct
{   
    u_int16_t bfType;
    u_int32_t bfSize;
    u_int16_t bfReserved1;
    u_int16_t bfReserved2;
    u_int32_t bfOffBits;
}BitmapFileHeader;

typedef struct
{   
    u_int32_t biSize;
    u_int32_t biWidth;
    u_int32_t biHeight;
    u_int16_t biPlanes;
    u_int16_t biBitCount;
    u_int32_t biCompression;
    u_int32_t biSizeImage;
    u_int32_t biXPelsPerMeter;
    u_int32_t biYPelsPerMeter;
    u_int32_t biClrUsed;
    u_int32_t biClrImportant;
}BitmapInfoHeader;

typedef struct
{
    u_char blue;
    u_char green;
    u_char red;
    u_char reserved;
}__attribute__((packed)) BitmapPixel32;//颜色模式RGB

typedef struct
{
    u_char blue;
    u_char green;
    u_char red;
}__attribute__((packed)) BitmapPixel24;//颜色模式RGB

/*
typedef struct
{
    u_char blue;
    u_char green;
}__attribute__((packed)) BitmapPixel16;//颜色模式RGB
*/

void ShowBmpHead(BitmapFileHeader pBmpHead)
{
    std::cout<<"位图文件头:"<<std::endl;
    std::cout<<"文件头类型:"<<pBmpHead.bfType<<std::endl; 
    std::cout<<"文件大小:"<<pBmpHead.bfSize<<std::endl;
    std::cout<<"保留字_1:"<<pBmpHead.bfReserved1<<std::endl;
    std::cout<<"保留字_2:"<<pBmpHead.bfReserved2<<std::endl;
    std::cout<<"实际位图数据的偏移字节数:"<<pBmpHead.bfOffBits<<std::endl<<std::endl;
}

 void ShowBmpInfoHead(BitmapInfoHeader pBmpInforHead)
 {
    std::cout<<"位图信息头:"<<std::endl;
    std::cout<<"结构体的长度:"<<pBmpInforHead.biSize<<std::endl;
    std::cout<<"位图宽:"<<pBmpInforHead.biWidth<<std::endl;
    std::cout<<"位图高:"<<pBmpInforHead.biHeight<<std::endl;
    std::cout<<"biPlanes平面数:"<<pBmpInforHead.biPlanes<<std::endl;
    std::cout<<"biBitCount采用颜色位数:"<<pBmpInforHead.biBitCount<<std::endl;
    std::cout<<"压缩方式:"<<pBmpInforHead.biCompression<<std::endl;
    std::cout<<"biSizeImage实际位图数据占用的字节数:"<<pBmpInforHead.biSizeImage<<std::endl;  
    std::cout<<"X方向分辨率:"<<pBmpInforHead.biXPelsPerMeter<<std::endl;
    std::cout<<"Y方向分辨率:"<<pBmpInforHead.biYPelsPerMeter<<std::endl;
    std::cout<<"使用的颜色数:"<<pBmpInforHead.biClrUsed<<std::endl;
    std::cout<<"重要颜色数:"<<pBmpInforHead.biClrImportant<<std::endl;
}   

BitmapFileHeader GetBitmapFileHead(const char *path)
{
    FILE *fp = fopen(path,"r");

    BitmapFileHeader head;

    fseek(fp,0L,SEEK_SET);
    fread(&head,1,sizeof(BitmapFileHeader),fp);

    fclose(fp);

    return head;
}

BitmapInfoHeader GetBitmapInfoHead(const char *path)
{
    FILE *fp = fopen(path,"r");

    BitmapInfoHeader info;

    fseek(fp,14L,SEEK_SET);
    fread(&info,1,sizeof(BitmapInfoHeader),fp);

    fclose(fp);

    return info;
}

BitmapPixel32 *GetPixel(const char *path,int &w,int &h)
{
    FILE *fp = fopen(path,"r");

    u_int32_t off_bits;

    u_int32_t width;
    u_int32_t height;
    u_int16_t bit_count;
    
    BitmapPixel32 pixel32 = {0,0,0,0};
    BitmapPixel24 pixel24 = {0,0,0};
    u_char color_b = 0;
    u_char color_g = 0;
    u_char color_r = 0;
    u_char color_a = 0;

    fseek(fp,12L,SEEK_SET);
    fread(&off_bits,4,1,fp);

    fseek(fp,28L,SEEK_SET);
    fread(&bit_count,2,1,fp);

    fseek(fp,18L,SEEK_SET);
    fread(&width,4,1,fp);
    fread(&height,4,1,fp);

    w = width;
    h = height;

    BitmapPixel32 *p = (BitmapPixel32*)malloc(sizeof(BitmapPixel32) * width * height);

    fseek(fp,54L,SEEK_SET);

    printf("%d\n%d\n%d\n%d\n",width,height,bit_count,off_bits);

    for (int i = height - 1; i >= 0; i--)
    {
        for (int j = 0; j < width; j++)
        {
            if (bit_count == 32)
            {
                fread(&pixel32,1,sizeof(BitmapPixel32),fp);
                color_r = pixel32.red;
                color_g = pixel32.green;
                color_b = pixel32.blue;
                color_a = pixel32.reserved;
                p[i * width + j].red = color_r;
                p[i * width + j].green = color_g;
                p[i * width + j].blue = color_b;
                p[i * width + j].reserved = color_a;
            }
            else if (bit_count == 24)
            {
                fread(&pixel24,1,sizeof(BitmapPixel24),fp);
                color_r = pixel24.red;
                color_g = pixel24.green;
                color_b = pixel24.blue;
                p[i * width + j].red = color_r;
                p[i * width + j].green = color_g;
                p[i * width + j].blue = color_b;
                p[i * width + j].reserved = 0;
            }
        }
    }

    fclose(fp);

    return p;
}

#endif //BITMAP
