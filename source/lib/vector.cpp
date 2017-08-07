#include <math.hpp>
#include <cmath>

namespace Math {

Vec4::Vec4(float x, float y, float z, float w): x(x), y(y), z(z), w(w) {}
Vec4::Vec4(const Vec4 &v): x(v.x), y(v.y), z(v.z), w(v.w) {}
Vec4::~Vec4() {}
auto Vec4::operator=(const Vec4 v) -> Vec4 &{
    x=v.x;
    y=v.y;
    z=v.z;
    w=v.w;
    return *this;
}

auto Vec4::operator+(const Vec4 v) const -> Vec4 {
    return Vec4(x+v.x, y+v.y, z+v.z, w+v.w);
}
auto Vec4::operator+=(const Vec4 v) -> Vec4 & {
    *this = *this + v;
    return *this;
}

auto Vec4::operator-(const Vec4 v) const -> Vec4 {
    return Vec4(x-v.x, y-v.y, z-v.z, w-v.w);
}
auto Vec4::operator-=(const Vec4 v) -> Vec4 & {
    *this = *this - v;
    return *this;
}
auto Vec4::operator-() const -> Vec4 {
    return Vec4(-x, -y, -z, -w);
}

auto Vec4::operator*(float s) const -> Vec4 {
    return Vec4(x*s, y*s, z*s, w*s);
}
auto Vec4::operator*=(float s) -> Vec4 & {
    *this = *this * s;
    return *this;
}
auto Vec4::operator*(const Vec4 v) const -> float {
    return x*v.x + y*v.y + z*v.z + w*v.w;
}

auto Vec4::perspDiv() const -> Vec4 {
    return Vec4(x/w, y/w, z/w, 1.0f);
}
auto Vec4::magnitude() const -> float {
    return sqrt((*this) * (*this));
}
auto Vec4::normalize() const -> Vec4 {
    auto m = magnitude();
    return Vec4(x/m, y/m, z/m, w/m);
}

Vec4::operator C3D_FVec() const {
    return FVec4_New(x,y,z,w);
}
Vec4::operator Vec3() const {
    auto a = perspDiv();
    return Vec3(a.x, a.y, a.z);
}

Vec3::Vec3(float x, float y, float z): Vec4(x,y,z,0.0f) {}
Vec3::Vec3(const Vec3 &v): Vec4(v) {}
Vec3::~Vec3() {}

auto Vec3::operator*(const Vec4 v) const -> float {
    return x*v.x + y*v.y + z*v.z;
}

auto Vec3::operator%(const Vec3 v) const -> Vec3 {
    return Vec3(y*v.z, z*v.x, x*v.y);
}
auto Vec3::operator%=(const Vec3 v) -> Vec3 & {
    *this = *this % v;
    return *this;
}

auto Vec3::distance(const Vec3 v) const -> float {
    return Vec3(*this - v).magnitude();
}
auto Vec3::normalize() const -> Vec4 {
    auto m = magnitude();

    return Vec4(x/m, y/m, z/m, 1.0f/m);
}
}
