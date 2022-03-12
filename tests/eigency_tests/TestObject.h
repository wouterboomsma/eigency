#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include <Eigen/Core>

class TestObject {
 public:
  Eigen::VectorXd data;

  TestObject();
  ~TestObject();
};

#endif  // TESTOBJECT_H
