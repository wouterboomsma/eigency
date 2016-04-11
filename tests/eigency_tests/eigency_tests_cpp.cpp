#include "eigency_tests_cpp.h"
#include <iostream>

void function_w_vec_arg(Eigen::Map<Eigen::VectorXd> &vec) {
    vec[0] = 0.;
}

void function_w_vec_arg_no_map1(Eigen::VectorXd vec) {
    // Change will not be passed back to Python since argument is not a reference, and not a map
    vec[0] = 0.;
}

void function_w_vec_arg_no_map2(const Eigen::VectorXd &vec) {
    // Cannot change vec in-place, since it is a const ref
    // vec[0] = 0.;     // will result in compile error
}

void function_w_mat_arg(Eigen::Map<Eigen::MatrixXd> &mat) {
    mat(0,0) = 0.;
}

void function_w_fullspec_arg(Eigen::Map<Eigen::Array<double, Eigen::Dynamic, 1> > &vec) {
    vec[0] = 0.;
}

Eigen::VectorXd function_w_vec_retval() {
    return Eigen::VectorXd::Constant(10, 4.);
}

Eigen::Matrix3d function_w_mat_retval() {
    return Eigen::Matrix3d::Constant(4.);
}

Eigen::Matrix<double, 2, 4> function_w_mat_retval_full_spec() {
    return Eigen::Matrix<double, 2, 4>::Constant(2.);
}

