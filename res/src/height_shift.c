#include "ud_image_preprocessing.h"

static float    ud_imgp_shift(float *channel, float *val, int pos, int len, int y_offset, int x_offset, int shift, size_t iterations)
{
    float tmp = *val;
    int new_pos = pos - shift < 0 ? len + (pos - shift) : pos - shift;
    if (iterations)
        *val = ud_imgp_shift(channel, new_pos < pos ? val - (shift * y_offset) : &channel[new_pos * y_offset + x_offset], new_pos, len, y_offset, x_offset, shift, iterations - 1);
    return tmp;
}

ud_tensor   *ud_imgp_height_shift(ud_tensor *image, size_t shift)
{
    size_t  channel_len = image->shape_m[0];
    size_t  nb_cols = image->shape[2];
    size_t  col_len = image->shape[1];
    shift = (shift > 0) ? shift % col_len : -(shift % col_len);
    size_t  iterations = col_len / shift;
    float   tmp[3];

    float   *r_red = &image->val[0];
    float   *r_green = &image->val[channel_len];
    float   *r_blue = &image->val[2 * channel_len];

    if (nb_cols % 2)
        for (ud_ut_count i = 0; i < nb_cols; ++i)
        {
            tmp[0] = *(r_red + i);
            tmp[1] = *(r_green + i);
            tmp[2] = *(r_blue + i);
            for (ud_ut_count j = 0; j < (size_t)shift; ++j)
            {
                ud_imgp_shift(r_red, r_red + (j * nb_cols) + i, j, col_len, nb_cols, i, shift, iterations);
                ud_imgp_shift(r_green, r_green + (j * nb_cols) + i, j, col_len, nb_cols, i, shift, iterations);
                ud_imgp_shift(r_blue, r_blue + (j * nb_cols) + i, j, col_len, nb_cols, i, shift, iterations);
            }
            *(r_red + (nb_cols * shift) + i) = tmp[0];
            *(r_green + (nb_cols * shift) + i) = tmp[1];
            *(r_blue + (nb_cols * shift) + i) = tmp[2];
        }
    else
        for (ud_ut_count i = 0; i < nb_cols; ++i)
            for (ud_ut_count j = 0; j < (size_t)shift; ++j)
            {
                ud_imgp_shift(r_red, r_red + (j * nb_cols) + i, j, col_len, nb_cols, i, shift, iterations);
                ud_imgp_shift(r_green, r_green + (j * nb_cols) + i, j, col_len, nb_cols, i, shift, iterations);
                ud_imgp_shift(r_blue, r_blue + (j * nb_cols) + i, j, col_len, nb_cols, i, shift, iterations);
            }
    return image;
}