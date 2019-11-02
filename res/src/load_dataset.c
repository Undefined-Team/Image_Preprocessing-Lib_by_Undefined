#include "ud_image_preprocessing.h"

ud_tensor   *ud_img_read(char *name) // to remove when real function is done
{
    (void)name;
    return ud_tens_init_rand(ud_arr_set(size_t, 3, 11, 11), 0, 255);
}

ud_tensor   **ud_imgp_get_dataset(DIR *d, struct dirent *dir, ud_arr **dataset, size_t nb_images)
{
    if (dir && dir->d_type != DT_REG)
        return ud_imgp_get_dataset(d, readdir(d), dataset, nb_images);
    if (!dir)
    {
        *dataset = ud_arr_tinit(ud_tens_type_tens(), nb_images + 1);
        ud_arr *p_dataset = *dataset;
        ((ud_tensor **)p_dataset->val)[nb_images] = NULL;
        return &((ud_tensor **)p_dataset->val)[nb_images - 1];
    }
    ud_tensor **t_dataset_val = ud_imgp_get_dataset(d, readdir(d), dataset, nb_images + 1);
    *t_dataset_val = ud_img_read(dir->d_name);
    return t_dataset_val - 1;
}

ud_arr      *ud_imgp_load_dataset_from_dir(char *image_dir)
{
    DIR             *d;
    d = opendir(image_dir);
    if (!d) ud_ut_error("Can't open directory %s.", image_dir);
    
    ud_arr *dataset = NULL;
    ud_imgp_get_dataset(d, readdir(d), &dataset, 0);
    closedir(d);
    return dataset;
}