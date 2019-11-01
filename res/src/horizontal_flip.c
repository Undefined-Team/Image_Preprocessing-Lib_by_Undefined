#include "ud_preprocessing_image.h"

ud_tensor   *ud_prep_horizontal_flip(ud_tensor *image)
{
    size_t len = image->shape[2];
    size_t incr = image->shape_m[0];
    size_t nb_rows = image->shape[1];

    float *r_red = (float *)image->val;
    float *r_green = r_red + incr;
    float *r_blue = r_green + incr;

    for (ud_ut_count i = 0; i < nb_rows; r_red += len, r_green += len, r_blue += len, ++i)
    {
        float *red = r_red;
        float *c_red = red + len - 1;

        float *green = r_green;
        float *c_green = green + len - 1;

        float *blue = r_blue;
        float *c_blue = blue + len - 1;

        for (; red < c_red; --c_red, --c_green, --c_blue, ++red, ++green, ++blue)
        {
            float tmp[3] = {*c_red, *c_green, *c_blue};
            *c_red = *red;
            *c_green = *green;
            *c_blue = *blue;
            *red = tmp[0];
            *green = tmp[1];
            *blue = tmp[2];
        }
    }
    return image;
}