#pragma once
class Vector3d {
public:
	float X, Y, Z;

	inline Vector3d(void) {}
	inline Vector3d(const float x, const float y, const float z)
	{
		X = x; Y = y; Z = z;
	}

	inline Vector3d operator + (const Vector3d& A) const
	{
		return Vector3d(X + A.X, Y + A.Y, Z + A.Z);
	}

	inline Vector3d operator + (const float A) const
	{
		return Vector3d(X + A, Y + A, Z + A);
	}

	inline float Dot(const Vector3d& A) const
	{
		return A.X*X + A.Y*Y + A.Z*Z;
	}
};