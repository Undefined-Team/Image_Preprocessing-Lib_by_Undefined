#include "ud_image_preprocessing.h"

static float    ud_imgp_shift(float *channel, float *val, int pos, int len, int shift, size_t iterations)
{
    float tmp = *val;
    int new_pos = pos - shift < 0 ? len + (pos - shift) : pos - shift;
    if (iterations)
        *val = ud_imgp_shift(channel, new_pos < pos ? val - shift : &channel[new_pos], new_pos, len, shift, iterations - 1);
    return tmp;
}

ud_tensor       *ud_imgp_width_shift(ud_tensor *image, int shift)
{
    size_t  channel_len = image->shape_m[0];
    size_t  nb_rows = image->shape[1];
    size_t  row_len = image->shape[2];
    shift = (shift > 0) ? shift % row_len : -(shift % row_len);
    size_t  iterations = row_len / shift;
    float   tmp[3];

    float   *r_red = &image->val[0];
    float   *r_green = &image->val[channel_len];
    float   *r_blue = &image->val[2 * channel_len];

    if (row_len % 2)
        for (ud_ut_count i = 0; i < nb_rows; ++i, r_red += row_len, r_green += row_len, r_blue += row_len)
        {
            tmp[0] = *r_red;
            tmp[1] = *r_green;
            tmp[2] = *r_blue;
            for (ud_ut_count j = 0; j < (size_t)shift; ++j)
            {
                ud_imgp_shift(r_red, r_red + j, j, row_len, shift, iterations);
                ud_imgp_shift(r_green, r_green + j, j, row_len, shift, iterations);
                ud_imgp_shift(r_blue, r_blue + j, j, row_len, shift, iterations);
            }
            *(r_red + shift) = tmp[0];
            *(r_green + shift) = tmp[1];
            *(r_blue + shift) = tmp[2];
        }
    else
        for (ud_ut_count i = 0; i < nb_rows; ++i, r_red += row_len, r_green += row_len, r_blue += row_len)
            for (ud_ut_count j = 0; j < (size_t)shift; ++j)
            {
                ud_imgp_shift(r_red, r_red + j, j, row_len, shift, iterations);
                ud_imgp_shift(r_green, r_green + j, j, row_len, shift, iterations);
                ud_imgp_shift(r_blue, r_blue + j, j, row_len, shift, iterations);
            }
    return image;
}