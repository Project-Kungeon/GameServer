#include "pch.h"
#include "MathUtils.h"

const float PI = std::acos(-1.0f);

void MathUtils::makeRotationMatrixFromX(float x, float y, float z, float matrix[3][3])
{
    // Normalize the input vector
    float length = std::sqrt(x * x + y * y + z * z);
    if (length > 0) {
        x /= length;
        y /= length;
        z /= length;
    }

    // Find a vector perpendicular to x-axis
    float ax, ay, az;
    if (std::abs(x) < std::abs(y) && std::abs(x) < std::abs(z)) {
        ax = 0; ay = -z; az = y;
    }
    else if (std::abs(y) < std::abs(z)) {
        ax = -z; ay = 0; az = x;
    }
    else {
        ax = -y; ay = x; az = 0;
    }

    // Normalize the perpendicular vector
    length = std::sqrt(ax * ax + ay * ay + az * az);
    ax /= length;
    ay /= length;
    az /= length;

    // Compute z-axis as cross product of x and y
    float zx = y * az - z * ay;
    float zy = z * ax - x * az;
    float zz = x * ay - y * ax;

    // Construct the rotation matrix
    matrix[0][0] = x;  matrix[0][1] = y;  matrix[0][2] = z;
    matrix[1][0] = ax; matrix[1][1] = ay; matrix[1][2] = az;
    matrix[2][0] = zx; matrix[2][1] = zy; matrix[2][2] = zz;
}

Rotator MathUtils::matrixToRotator(const float matrix[3][3])
{
    Rotator rotator;

    // Pitch (X rotation)
    rotator.Pitch = std::asin(-matrix[0][2]) * (180.0f / PI);

    // Yaw (Z rotation)
    rotator.Yaw = std::atan2(matrix[0][1], matrix[0][0]) * (180.0f / PI);

    // Roll (Y rotation)
    rotator.Roll = std::atan2(matrix[1][2], matrix[2][2]) * (180.0f / PI);

    return rotator;
}

Vector3 MathUtils::getMoveTargetLocation(float deltaTime, ObjectPtr object, ObjectPtr target)
{
    //Location ObjectLoc = object->GetLocation();
    //Location TargetLoc = target->GetLocation();

    //Vector3 position(ObjectLoc.x, ObjectLoc.y, ObjectLoc.z);
    //Vector3 targetPosition(TargetLoc.x, TargetLoc.y, TargetLoc.z);
    //Vector3 direction = (targetPosition - position).Normalized();

    //// 목표 방향으로 가속
    //velocity = velocity + direction * acceleration * deltaTime;

    //// 최대 속도 제한
    //if (velocity.Length() > maxSpeed) {
    //    velocity = velocity.Normalized() * maxSpeed;
    //}

    //// 새 위치 계산
    //position = position + velocity * deltaTime;

    //elapsedTime += deltaTime;
    return Vector3();
}
