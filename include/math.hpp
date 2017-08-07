#pragma once
#include <citro3d.h>
namespace Math {
    constexpr float pi = 3.141592653589793;
    constexpr float tau = 2*pi;
    constexpr float rev_to_rad(const float revolutions) {
        return revolutions * tau;
    }
    constexpr float deg_to_rad(const float deg) {
        return deg*tau/360.0f;
    }
    constexpr float aspect_ratio_top=400.0f / 240.0f;
    constexpr float aspect_ratio_bottom=320.0f / 240.0f;

    struct Vec3;
    struct Vec4 {
        float w;
        float z;
        float y;
        float x;

        Vec4(float x, float y, float z, float w);
        Vec4(const Vec4 &);
        ~Vec4();
        auto operator=(const Vec4) -> Vec4&;

        auto operator+(const Vec4) const -> Vec4;
        auto operator+=(const Vec4) -> Vec4 &;

        auto operator-(const Vec4) const -> Vec4;
        auto operator-=(const Vec4) -> Vec4 &;
        auto operator-() const -> Vec4;

        auto operator*(float) const -> Vec4;
        auto operator*=(float) -> Vec4 &;
        virtual auto operator*(const Vec4) const -> float;

        auto perspDiv() const -> Vec4;
        virtual auto normalize() const -> Vec4;
        auto magnitude() const -> float;
        operator C3D_FVec() const;
        operator Vec3() const;
    };

    struct Vec3: public Vec4 {
        Vec3(float x, float y, float z);
        Vec3(const Vec3 &);
        ~Vec3();

        virtual auto operator*(const Vec4) const -> float;
        auto operator%(const Vec3) const -> Vec3;
        auto operator%=(const Vec3) -> Vec3 &;

        auto distance(const Vec3) const -> float;

        virtual auto normalize() const -> Vec4;
    };

    struct Quat {
        C3D_FQuat q;
        Quat(float i, float j, float k, float rk);
        Quat(C3D_FQuat);
        Quat(const Quat &);
        ~Quat();
        auto operator=(const Quat) -> Quat &;

        auto operator+(const Quat) const -> Quat;
        auto operator+=(const Quat) -> Quat &;
        auto operator-(const Quat) const -> Quat;
        auto operator-=(const Quat) -> Quat &;

    };
}
