#include "TestObject.h"

TestObject::TestObject() {}

TestObject::TestObject(const Eigen::Map<RowMajorMatrixD>& A,
                       const Eigen::Map<RowMajorMatrixD>& B,
                       const Eigen::Map<RowMajorMatrixD>& C,
                       const Eigen::Map<RowMajorMatrixD>& Q,
                       const Eigen::Map<RowMajorMatrixD>& R,
                       const Eigen::Map<RowMajorMatrixD>& P) {
  this->A = A;
  this->B = B;
  this->C = C;
  this->Q = Q;
  this->R = R;
  this->P = P;

  m = C.rows();
  n = A.rows();
  c = B.rows();

  this->x_hat = Eigen::VectorXd(n);
  this->I = RowMajorMatrixD(n, n);
  I.setIdentity();
}

TestObject::~TestObject() {}

void TestObject::predict(const Eigen::VectorXd& u) {
  x_hat = A * x_hat + B * u;
  P = A * P * A.transpose() + Q;
}

void TestObject::update(const Eigen::VectorXd& y) {
  K = P * C.transpose() * (C * P * C.transpose() + R).inverse();
  x_hat += K * (y - C * x_hat);
  P = (I - K * C) * P;
}
