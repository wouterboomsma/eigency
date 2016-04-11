#ifndef TEST1_H
#define TEST1_H

#include "Eigen/Dense"

void function_w_vec_arg(Eigen::Map<Eigen::VectorXd> &vec);

void function_w_vec_arg_no_map1(Eigen::VectorXd vec);

void function_w_vec_arg_no_map2(const Eigen::VectorXd &vec);

void function_w_mat_arg(Eigen::Map<Eigen::MatrixXd> &mat);

void function_w_fullspec_arg(Eigen::Map<Eigen::Array<double, Eigen::Dynamic, 1> > &vec);

Eigen::VectorXd function_w_vec_retval();

Eigen::Matrix3d function_w_mat_retval();

Eigen::Matrix<double, 2, 4> function_w_mat_retval_full_spec();

class MyClass {
public:
    MyClass():
        matrix(Eigen::Matrix3d::Constant(4.)) {
    }
    Eigen::Matrix3d &get_matrix() {
        return this->matrix;
    }
private:
    Eigen::Matrix3d matrix;
};

#endif
