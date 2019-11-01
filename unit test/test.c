#include <ud_preprocessing_image.h>

void ex_image_use(void)
{
    /*ud_data_mnist(x_train, y_train, x_test, y_test); // load mnist image dataset as (x_train, y_train), (x_test, y_test)
    y_train = ud_prep_ohe(y_train, 2); // one hot encode with 2 classes (for ex: dogs and cats)
    y_test = ud_prep_ohe(y_test, 2);

    ud_prep_image(datagen,
        .featurewise_center = true,
        .rotation_range = 20,
        .width_shift_range = 0.2); // create data generator from image transformations

    ud_pdc_model(model, "network.csv"); // load network model from csv

    size_t generations = 10;
    size_t batch_size = 16;
    size_t inputs_len = x_train->len;
    float best_accuracy = -1;
    int best_generation = -1;
    for (size_t gen = 0; gen < generations; ++gen)
    {
        for (size_t i = 0; i < inputs_len; ++i)
        {
            ud_tensor *results = NULL;
            ud_tensor *test_results = NULL;
            ud_prep_transform(datagen, x_batch, y_batch, x_train, y_train);

            for (size_t j = 0; j < batch_size && i < inputs_len; ++i, ++j)
            {
                ud_tensor *actual_result = ud_pdc_predict(model, x_batch[i]);
                results = ud_tens_concat(results, actual_result);

                ud_tensor *test_actual_result = ud_pdc_predict(model, x_test[i]);
                test_results = ud_tens_concat(test_results, test_actual_result);
            }
            
            ud_tensor *error = ud_pdc_error(results, y_train[i - batch_size : i]);
            ud_tens_free(results);
            ud_pdc_backprop(model, error);

            float accuracy = ud_pdc_accuracy(results, y_test[i - batch_size : i]);
            ud_tens_free(test_results);
            if (accuracy > best_accuracy)
            {
                best_accuracy = accuracy;
                best_generation = gen;
            }
        }
    }*/
}

int main(void)
{
    ud_tensor *image = ud_tens_init_rand(ud_arr_set(size_t, 3, 10, 10), 0, 255);
    ud_tensor *image_cpy = ud_tens_cpy(image);
    ud_prep_image(datagen,
        .featurewise_center = true,
        .horizontal_flip = true,
        .samplewise_center = true,
        .rescale = 1.0 / 255.0,
        .rotation_range = 20,
        .width_shift_range = 0.2);
    ud_prep_image_transform(image, datagen);
    ud_prep_samplewise_center(image_cpy);
    ud_prep_horizontal_flip(image_cpy);
    ud_tens_print(image);
    ud_ut_test(!ud_mem_cmp(image->val, image_cpy->val, image->len));
}