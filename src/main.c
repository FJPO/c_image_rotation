#include <stdio.h>
#include <stdint.h>
#include "app.h"
#include "bmp_handler.h"


int main() {

    struct image im = {0};

    printf("File reading finished with exit code %d\n", from_file("Input.bmp", &im, from_bmp));

    struct image new = rotate(im);


    printf("File writing finished with exit code %d\n", to_file("Output.bmp", &new, to_bmp));

//    image_print(im);

    return 0;
}