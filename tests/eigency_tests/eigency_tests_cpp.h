#ifndef TEST1_H
#define TEST1_H

#include "Eigen/Dense"

void function_w_vec_arg(const Eigen::Map<Eigen::VectorXd> &vec);

void function_w_mat_arg(const Eigen::Map<Eigen::MatrixXd> &mat);

void set_first_zero_inplace(Eigen::Map<Eigen::VectorXd> &vec);

void function_w_1darray_arg(Eigen::Map<Eigen::Array<double, Eigen::Dynamic, 1> > &vec);

Eigen::VectorXd function_w_vec_retval();

Eigen::Matrix3d function_w_mat_retval();

#endif
