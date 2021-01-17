//
// Created by Ilya on 05.01.2021.
//

#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include "app.h"
#include "bmp_handler.h"

#pragma pack(1)
struct //__attribute__ ((packed))
bmp_header{
    uint16_t bfType; //char - 2 bytes
    uint32_t  bfileSize; //размер
    uint32_t bfReserved; //useless
    uint32_t bOffBits; //how long into the file the actual data starts
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

enum read_status from_bmp( FILE* in, struct image* img ){
    if(!in) {
        return READ_NO_SUCH_FILE;
    }

    struct bmp_header header = (struct bmp_header){0};

    if(fread_s(&header, sizeof (struct bmp_header), sizeof(struct bmp_header), 1, in) != 1) return READ_INVALID_HEADER;

    img->height = header.biHeight;
    img->width = header.biWidth;

    struct pixel* data = malloc(sizeof (struct pixel) * header.biWidth * header.biHeight);
    int8_t* trashbean[4];

    for(size_t i = 0; i < header.biHeight; i++) {
        if(fread_s(data+i*header.biWidth, (sizeof(struct pixel) * header.biWidth * header.biHeight)-i*header.biWidth, sizeof(struct pixel), header.biWidth,
                   in) == 0) return READ_UNEXPECTED_END_OF_FILE;

        size_t count = (4-header.biWidth * 3 % 4)%4;
//        if(count != 0) count = 4 - count;
        if(fread_s(trashbean, (sizeof(int8_t) * 4), sizeof(uint8_t), count, in) == 0 && count != 0) return READ_UNEXPECTED_END_OF_FILE;
    }
    img->data = data;
    return READ_OK;

}


struct bmp_header  generate_header(FILE* out, struct image const* img){
    struct bmp_header header = (struct bmp_header){
            .bfType = 19778,
            .bfileSize = img->width * img->height + 54 + img->width%4*img->height,
            .bfReserved = 0,
            .bOffBits = 54, //how long into the file the actual data starts
            .biSize = 40,
            .biWidth = img->width,
            .biHeight = img->height,
            .biPlanes = 1,
            .biBitCount = 24,
            .biCompression = 0,
            .biSizeImage = 0,
            .biXPelsPerMeter = 0,
            .biYPelsPerMeter = 0,
            .biClrUsed = 0,
            .biClrImportant = 0,
    };
    return header;
}
/*  serializer   */
enum write_status to_bmp( FILE* out, struct image const* img ){
    struct bmp_header header = generate_header(out, img);
    fwrite(&header, sizeof (struct bmp_header), 1, out);
    uint8_t trash = {0};
    for(size_t i = 0; i < header.biHeight; i++) {
        fwrite(img->data+i*header.biWidth, sizeof(struct pixel), header.biWidth, out);
        if(header.biWidth%4 != 0)
            for(size_t t = 0; t < 4-header.biWidth*3%4; t++)
                fwrite(&trash, sizeof (uint8_t), 1, out);

    }
    return READ_OK;
}
