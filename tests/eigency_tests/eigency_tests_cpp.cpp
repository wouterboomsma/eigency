#include "eigency_tests_cpp.h"
#include <iostream>

long function_w_vec_arg(Eigen::Map<Eigen::VectorXd> &vec) {
    vec[0] = 0.;
    return vec.size();
}

long function_w_1darr_arg(Eigen::Map<Eigen::ArrayXi> &arr) {
    arr[0] = 0.;
    return arr.size();
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

void function_w_complex_mat_arg(Eigen::Map<Eigen::MatrixXcd> &mat) {
    mat(0,0) = 0.+0.j;
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

Eigen::Map<Eigen::ArrayXXd> &function_filter1(Eigen::Map<Eigen::ArrayXXd> &mat) {
    return mat;
}

Eigen::Map<Eigen::Array<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > &function_filter2(Eigen::Map<Eigen::Array<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > &mat) {
    return mat;
}

Eigen::Map<Eigen::ArrayXXd, Eigen::Unaligned, Eigen::Stride<1, Eigen::Dynamic> > &function_filter3(Eigen::Map<Eigen::ArrayXXd, Eigen::Unaligned, Eigen::Stride<1, Eigen::Dynamic> > &mat) {
    return mat;
}

Eigen::ArrayXXd function_type_double(Eigen::Map<Eigen::ArrayXXd> &mat) {
    Eigen::ArrayXXd output = mat;
    return output;
}

Eigen::ArrayXXf function_type_float(Eigen::Map<Eigen::ArrayXXf> &mat) {
    Eigen::ArrayXXf output = mat;
    return output;
}

Eigen::Array<long, Eigen::Dynamic, Eigen::Dynamic> function_type_long(Eigen::Map<Eigen::Array<long, Eigen::Dynamic, Eigen::Dynamic> > &mat) {
    Eigen::Array<long, Eigen::Dynamic, Eigen::Dynamic> output = mat;
    return output;
}

Eigen::ArrayXXi function_type_int(Eigen::Map<Eigen::ArrayXXi> &mat) {
    Eigen::ArrayXXi output = mat;
    return output;
}

Eigen::Array<short, Eigen::Dynamic, Eigen::Dynamic> function_type_short(Eigen::Map<Eigen::Array<short, Eigen::Dynamic, Eigen::Dynamic> > &mat) {
    Eigen::Array<short, Eigen::Dynamic, Eigen::Dynamic> output = mat;
    return output;
}

Eigen::Array<char, Eigen::Dynamic, Eigen::Dynamic> function_type_char(Eigen::Map<Eigen::Array<char, Eigen::Dynamic, Eigen::Dynamic> > &mat) {
    Eigen::Array<char, Eigen::Dynamic, Eigen::Dynamic> output = mat;
    return output;
}

Eigen::ArrayXXcd function_type_complex_double(Eigen::Map<Eigen::ArrayXXcd> &mat) {
    Eigen::ArrayXXcd output = mat;
    return output;
}

Eigen::ArrayXXcf function_type_complex_float(Eigen::Map<Eigen::ArrayXXcf> &mat) {
    Eigen::ArrayXXcf output = mat;
    return output;
}

