#pragma once

struct Rotator {
	float Pitch, Yaw, Roll;
};

class MathUtils
{
public:
	static void makeRotationMatrixFromX(float x, float y, float z, float matrix[3][3]);
	static Rotator matrixToRotator(const float matrix[3][3]);
};

