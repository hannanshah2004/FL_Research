#ifndef NN_FC_H
#define NN_FC_H

#include <vector>

class FCLayer {
public:
    int input_size, output_size, batch_size, quant_zero_point;
    double quant_scale;
    double *bias;
    double **weights;
    double **output_error_softmax;
    double dropout_rate;  
    std::vector<std::vector<bool>> dropout_mask;  

    FCLayer();
    FCLayer(int input_sz, int output_sz, double scale, 
            int zero_point, int batch, bool default_weight, double dropout_rate = 0.5);
    void forward(double **input_float, double **output);
    void backward(double **output, int **ground_truth, 
                  double **input_error, double **input_float,
                  double learning_rate, double lambda); 
    void dequantize(int *input_data, double *input_float);
    void cleanup();
    ~FCLayer();
    void apply_dropout(double** input_float);
    void set_weights_bias(double **new_weights, double *new_bias);
    void prune_weights_hard(double prune_percentage);
};

void FL_round_simulation(double **input_f, int **input_i, int **ground_truth, int local_episodes, 
                        double learning_rate, FCLayer *model, double lambda, 
                        bool verbose, bool local, bool unquantize);

#endif
