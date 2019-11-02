#include "ud_image_preprocessing.h"

void    *ud_imgp_apply_ctr(void *data, ud_arr_type *type, ud_image_transform params)
{
    if (type == ud_tens_type_tens())
    {
        ud_tensor *image = (ud_tensor *)data;
        if (params.samplewise_center || params.featurewise_center)
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
        if (params.width_shift_range > 0.f)
            ud_imgp_width_shift(image, params.rescale);
        return image;
    }
    else if (type == ud_arr_type_arr())
    {
        ud_arr *dataset = (ud_arr *)data;
        ud_tensor **images = (ud_tensor **)dataset->val;
        if (params.samplewise_center)
            ud_ptr_foreach(images, image, ud_imgp_samplewise_center(*image););
        if (params.featurewise_center)
            ud_imgp_featurewise_center(dataset);
        if (params.vertical_flip)
        {
            if (params.horizontal_flip)
                ud_ptr_foreach(images, image, ud_imgp_diagonal_flip(*image););
            else
                ud_ptr_foreach(images, image, ud_imgp_vertical_flip(*image););
        }
        else if (params.horizontal_flip)
            ud_ptr_foreach(images, image, ud_imgp_horizontal_flip(*image););
        if (params.grayscale)
            ud_ptr_foreach(images, image, ud_imgp_grayscale(*image););
        if (params.rescale > 0.f)
            ud_ptr_foreach(images, image, ud_imgp_rescale(*image, params.rescale););
        if (params.width_shift_range > 0.f)
            ud_ptr_foreach(images, image, ud_imgp_width_shift(*image, params.width_shift_range););
        return data;
    }
    return NULL;
}