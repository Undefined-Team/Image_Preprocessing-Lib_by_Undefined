#include "ud_preprocessing_image.h"

ud_tensor   *ud_prep_rescale(ud_tensor *image, float factor)
{
    printf("rescale\n");
    size_t  len = image->shape_m[0];
    float   *red = (float *)image->val;
    float   *green = red + len;
    float   *blue = green + len;
    for (ud_ut_count i = 0; i < len; ++i, ++red, ++green, ++blue)
    {
        *red *= factor;
        *green *= factor;
        *blue *= factor;
    }
    return image;
}