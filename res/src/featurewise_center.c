#include "ud_image_preprocessing.h"

static float    ud_imgp_substract_mean(ud_tensor **images, float *val, float mean, size_t channel_len, ud_imgp_channel channel, size_t dataset_len, size_t image_len, size_t n)
{
    if (!image_len)
    {
        if (!dataset_len) return (float)(mean / (float)n);
        ud_tensor *t_channel = *(++images);
        return ud_imgp_substract_mean(images, &t_channel->val[channel * channel_len], mean, channel_len, channel, dataset_len - 1, t_channel->shape_m[0], n);
    }
    float mean_ret = ud_imgp_substract_mean(images, val + 1, mean + *val, channel_len, channel, dataset_len, image_len - 1, n + 1);
    // int new_val = (int)(*val - mean_ret);
    float new_val = *val - mean_ret;
    *val = new_val;//(new_val > 0) ? new_val : 255 + new_val;
    return mean_ret;
}

ud_arr  *ud_imgp_featurewise_center(ud_arr *dataset)
{
    size_t      channel_len = ((ud_tensor **)dataset->val)[0]->shape_m[0];
    ud_tensor   *red = ((ud_tensor **)dataset->val)[0];
    ud_tensor   *green = ((ud_tensor **)dataset->val)[0];
    ud_tensor   *blue = ((ud_tensor **)dataset->val)[0];
    ud_imgp_substract_mean((ud_tensor **)dataset->val, red->val, 0, channel_len, UD_CH_RED, dataset->len - 2, channel_len, 0);
    ud_imgp_substract_mean((ud_tensor **)dataset->val, &green->val[channel_len], 0, channel_len, UD_CH_GREEN, dataset->len - 2, channel_len, 0);
    ud_imgp_substract_mean((ud_tensor **)dataset->val, &blue->val[2 * channel_len], 0, channel_len, UD_CH_BLUE, dataset->len - 2, channel_len, 0);
    return dataset;
}