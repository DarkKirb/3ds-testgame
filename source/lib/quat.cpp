#include <math.hpp>

namespace Math {

Quat::Quat(float i, float j, float k, float r) {
    q = Quat_New(i,j,k,r);
}
Quat::Quat(C3D_FQuat q) {
    this->q = q;
}
Quat::Quat(const Quat &q) {
    this->q = q.q;
}


}
