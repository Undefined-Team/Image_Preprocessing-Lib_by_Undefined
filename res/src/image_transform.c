#include "ud_image_preprocessing.h"

ud_tensor   *ud_imgp_image_transform(ud_tensor *image, ud_image_transform params)
{
    if (params.samplewise_center)
        ud_imgp_samplewise_center(image);
    if (params.vertical_flip)
    {
        if (params.horizontal_flip)
            ud_imgp_diagonal_flip(image);
        else
            ud_imgp_vertical_flip(image);
    }
    else if (params.horizontal_flip)
        ud_imgp_horizontal_flip(image);
    if (params.grayscale)
        ud_imgp_grayscale(image);
    if (params.rescale > 0.f)
        ud_imgp_rescale(image, params.rescale);
    return image;
}