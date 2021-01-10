//
// Created by Ilya on 05.01.2021.
//

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <malloc.h>
#include "app.h"

struct image rotate( struct image const source ){
    struct image result = (struct image){.width = source.height, .height = source.width,
            .data = malloc(source.width*source.height*sizeof(struct pixel))};
    uint64_t col, row, newCol, newRow;

    for(size_t i = 0; i < source.width*source.height; i++) {
        row = i / source.width;
        col = i % source.width;
        newRow = col;
        newCol = source.height - row - 1;
        //printf("(%" PRIu8 ", %" PRIu8 ") -->> (%" PRIu8 ", %" PRIu8 ")", row, col, newRow, newCol);
        result.data[newRow * source.height + newCol] = source.data[i];
    }
    //return (struct mock_image){.width = source.height, .height = source.width, .data = data};
    return result;
}

void image_print(struct image const im){
    for(size_t i = 0; i < im.width * im.height; i++){
        printf("%" PRIu8, im.data[i].b);
        printf(" %" PRIu8, im.data[i].g);
        printf(" %" PRIu8 "\t", im.data[i].r);

        if((i+1) % im.width == 0) {
            printf("\n");
        }
    }
}

enum read_status from_file( char* name, struct image const* im, file_reader reader ){
    FILE* input = NULL;
    if(fopen_s(&input, name, "rb")) return READ_CANNOT_OPEN_FILE;
    enum read_status result = reader(input, im);
    fclose(input);
    return result;
}
enum write_status to_file( char* name, struct image const* im, file_writer writer ){
    FILE* output = NULL;
    if(fopen_s(&output, name, "wb")) return READ_CANNOT_OPEN_FILE;
    enum read_status result = writer(output, im);
    fclose(output);
    return result;
}


