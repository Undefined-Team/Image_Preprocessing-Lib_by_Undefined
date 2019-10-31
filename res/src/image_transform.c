#include "ud_preprocessing.h"

ud_tensor   *ud_prep_image_transform(ud_tensor *image, ud_image_transform params)
{
    if (params.samplewise_center)
        ud_prep_samplewise_center(image);
    if (params.vertical_flip)
    {
        if (params.horizontal_flip)
            ud_prep_diagonal_flip(image);
        else
            ud_prep_vertical_flip(image);
    }
    else if (params.horizontal_flip)
        ud_prep_horizontal_flip(image);
    if (params.grayscale)
        ud_prep_grayscale(image);
    return image;
}