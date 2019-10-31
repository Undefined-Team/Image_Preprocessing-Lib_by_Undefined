#include "ud_preprocessing.h"

ud_tensor   *ud_prep_grayscale(ud_tensor *image)
{
    float *red = (float *)image->val;
    float *green = ud_tens_get_pval(image, ud_ut_array(size_t, 1, 0, 0));
    float *blue = ud_tens_get_pval(image, ud_ut_array(size_t, 2, 0, 0));
    size_t len = image->shape_m[0];
    for (ud_ut_count i = 0; i < len; ++i, ++red, ++green, ++blue)
    {
        float gray = CIE709(*red, *green, *blue);
        *red = gray;
        *green = gray;
        *blue = gray;
    }
    return image;
}