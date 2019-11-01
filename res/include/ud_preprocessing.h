#ifndef UD_PREPROCESSING_H
# define UD_PREPROCESSING_H

// Lib
#include <ud_tensor.h>
#include <ud_csv_array.h>

// Macro
# define    ud_prep_image(_var_name, ...) \
    ud_image_transform  _var_name = {__VA_ARGS__};

// for grayscales
# define CIE709(red, green, blue)       (0.299 * (red) + 0.587 * (green) + 0.114 * (blue))
# define CIE601(red, green, blue)       (0.2125 * (red) + 0.7154 * (green) + 0.0721 * (blue))

// Structures
typedef struct  uds_image_transform {
    ud_bool     featurewise_center;
    ud_bool     samplewise_center;
    ud_bool     vertical_flip;
    ud_bool     horizontal_flip;
    ud_bool     grayscale;
    float       rotation_range;
    float       rescale;
    float       width_shift_range;
    float       height_shift_range;
}               ud_image_transform;

// Prototypes
ud_tensor       *ud_prep_grayscale(ud_tensor *image);
ud_tensor       *ud_prep_vertical_flip(ud_tensor *image);
ud_tensor       *ud_prep_horizontal_flip(ud_tensor *image);
ud_tensor       *ud_prep_diagonal_flip(ud_tensor *image);
ud_tensor       *ud_prep_samplewise_center(ud_tensor *image);
ud_tensor       *ud_prep_image_transform(ud_tensor *image, ud_image_transform params);
ud_tensor       *ud_prep_rescale(ud_tensor *image, float factor);

#endif
