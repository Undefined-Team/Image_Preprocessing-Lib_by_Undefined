#include "ud_preprocessing_image.h"

ud_tensor   *ud_prep_vertical_flip(ud_tensor *image)
{
    size_t len = image->shape[2];
    size_t incr = len * (image->shape[1] - 1);
    size_t decr = 2 * len;

    float *red = (float *)image->val;
    float *r_red = red + incr;

    float *green = r_red + len;
    float *r_green = green + incr;

    float *blue = r_green + len;
    float *r_blue = blue + incr;

    for (; red < r_red; r_red -= decr, r_green -= decr, r_blue -= decr)
        for (ud_ut_count i = 0; i < len; ++i, ++r_red, ++r_green, ++r_blue, ++red, ++green, ++blue)
        {
            float tmp[3] = {*r_red, *r_green, *r_blue};
            *r_red = *red;
            *r_green = *green;
            *r_blue = *blue;
            *red = tmp[0];
            *green = tmp[1];
            *blue = tmp[2];
        }
    return image;
}