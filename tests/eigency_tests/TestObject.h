#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include <Eigen/Core>

typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> RowMajorMatrixD;

class TestObject {
 public:
  RowMajorMatrixD A, B, C, Q, R, P, K, P0;
  int m, n, c;
  RowMajorMatrixD I;
  Eigen::VectorXd x_hat;

  TestObject();
  TestObject(const Eigen::Map<RowMajorMatrixD>& A,
             const Eigen::Map<RowMajorMatrixD>& B,
             const Eigen::Map<RowMajorMatrixD>& C,
             const Eigen::Map<RowMajorMatrixD>& Q,
             const Eigen::Map<RowMajorMatrixD>& R,
             const Eigen::Map<RowMajorMatrixD>& P);
  ~TestObject();

  void predict(const Eigen::VectorXd& u);
  void update(const Eigen::VectorXd& y);
};

#endif  // TESTOBJECT_H
