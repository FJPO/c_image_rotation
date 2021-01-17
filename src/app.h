//
// Created by Ilya on 05.01.2021.
//

#ifndef IMAGE_ROTATION_APP_H
#define IMAGE_ROTATION_APP_H

struct pixel { uint8_t b, g, r; };
struct image {
    uint64_t width, height;
    struct pixel* data;
};

struct image rotate( struct image const source );
void image_print(struct image const im);

enum read_status  {
    READ_OK,
    READ_NO_SUCH_FILE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER,
    READ_CANNOT_OPEN_FILE,
    READ_UNEXPECTED_END_OF_FILE
    /* коды других ошибок  */
};
enum  write_status  {
    WRITE_OK = 0,
    WRITE_ERROR
    /* коды других ошибок  */
};

typedef enum read_status file_reader (FILE*, struct image*);
typedef enum write_status file_writer (FILE*, struct image*);

enum read_status from_file( const char* name, struct image const* im, file_reader reader);
enum write_status to_file( const char* name, struct image const* im, file_writer writer );


#endif //IMAGE_ROTATION_APP_H
