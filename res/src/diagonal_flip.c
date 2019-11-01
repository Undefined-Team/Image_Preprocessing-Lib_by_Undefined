#include "ud_preprocessing.h"

ud_tensor   *ud_prep_diagonal_flip(ud_tensor *image)
{
    float *rg_bound = ud_tens_get_pval(image, ud_ut_array(size_t, 1, 0, 0));
    float *gb_bound = ud_tens_get_pval(image, ud_ut_array(size_t, 2, 0, 0));

    float *red = (float *)image->val;
    float *r_red = rg_bound - 1;

    float *green = rg_bound;
    float *r_green = gb_bound - 1;

    float *blue = gb_bound;
    float *r_blue = ud_tens_get_pval(image, ud_ut_array(size_t, 2, image->shape[1] - 1, 0));
    
    for (; red < r_red; ++red, ++green, ++blue, --r_red, --r_green, --r_blue)
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