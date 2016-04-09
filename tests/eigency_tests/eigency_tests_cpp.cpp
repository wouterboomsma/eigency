#include "eigency_tests_cpp.h"
#include <iostream>

void function_w_vec_arg(const Eigen::Map<Eigen::VectorXd> &vec) {
    // std::cout << vec << "\n";
}

void function_w_mat_arg(const Eigen::Map<Eigen::MatrixXd> &mat) {
    // std::cout << mat << "\n";
}

void set_first_zero_inplace(Eigen::Map<Eigen::VectorXd> &vec) {
    vec[0] = 0.;
}

void function_w_1darray_arg(Eigen::Map<Eigen::Array<double, Eigen::Dynamic, 1> > &vec) {
    // std::cout << vec << "\n";
}

Eigen::VectorXd function_w_vec_retval() {
    return Eigen::VectorXd::Zero(4);
}

Eigen::Matrix3d function_w_mat_retval() {
    return Eigen::Matrix3d::Constant(2.);
}

