#include "ud_image_preprocessing.h"

static size_t       ud_imgp_substract_mean(float *val, unsigned long mean, size_t len, size_t n)
{
    if (!len) return mean / n;
    size_t  mean_ret = ud_imgp_substract_mean(&val[1], mean + *val, --len, ++n);
    float   new_val = *val - mean_ret;
    *val = (new_val > 0) ? new_val : 255 + new_val;
    return mean_ret;
}

ud_tensor           *ud_imgp_samplewise_center(ud_tensor *image)
{
    size_t  color_len = image->shape_m[0];
    ud_imgp_substract_mean(&image->val[0], 0, color_len, 0);
    ud_imgp_substract_mean(&image->val[color_len], 0, color_len, 0);
    ud_imgp_substract_mean(&image->val[2 * color_len], 0, color_len, 0);
    ud_imgp_substract_mean(&image->val[0], 0, image->len, 0);
    return image;
}