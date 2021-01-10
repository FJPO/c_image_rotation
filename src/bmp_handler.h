//
// Created by Ilya on 05.01.2021.
//



#ifndef IMAGE_ROTATION_BMP_HANDLER_H
#define IMAGE_ROTATION_BMP_HANDLER_H



enum read_status from_bmp( FILE* in, struct image* img );
enum write_status to_bmp( FILE* out, struct image const* img );

#endif //IMAGE_ROTATION_BMP_HANDLER_H
