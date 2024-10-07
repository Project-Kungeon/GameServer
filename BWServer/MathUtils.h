#pragma once

struct Rotator {
	float Pitch, Yaw, Roll;
};

struct Vector3 {
    float x, y, z;
    Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }
    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }
    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }
    float Length() const {
        return std::sqrt(x * x + y * y + z * z);
    }
    Vector3 Normalized() const {
        float len = Length();
        if (len > 0) {
            return Vector3(x / len, y / len, z / len);
        }
        return *this;
    }
};


class MathUtils
{
public:
	static void makeRotationMatrixFromX(float x, float y, float z, float matrix[3][3]);
	static Rotator matrixToRotator(const float matrix[3][3]);
    static Vector3 getMoveTargetLocation(float deltaTime, ObjectPtr object, ObjectPtr target);
};

