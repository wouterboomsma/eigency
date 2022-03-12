#include "TestObject.h"

#include <Eigen/Core>

TestObject::TestObject() {
    this->data = Eigen::VectorXd(2);
}

TestObject::~TestObject() {}
