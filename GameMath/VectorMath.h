#pragma once
/*
Pitch: Look up and down (nod)
Yaw: Look left and right (shake head: no)
Roll: Tilt head (ask dog a question)

(P, Y, R) Convert to (X, Y, X)
*/

Vector3d convertToXYZ(float Pitch, float Yaw, float Roll) {
	Vector3d vect;
	vect.X = cos(Yaw) * cos(Pitch);
	vect.Y = sin(Pitch);
	vect.Z = sin(Yaw) * cos(Pitch);
}


/*
Cross Product

Returns a vector which is perpindicular to all input vectors

Player's up Vector U.
Player's forward vector F.
Player's right vector R.
*/

Vector3d CrossProduct(Vector3d A, Vector3d B) {
	Vector3d R;
	R.X = A.Y * B.Z - A.Z * B.Y;
	R.Y = A.Z * B.X - A.X * B.Z;
	R.Z = A.X * B.Y - A.Y * B.X;
	return R;
}

/*
https://youtu.be/qJq7I2DLGzI?list=PLW3Zl3wyJwWOpdhYedlD-yCB7WQoHf-My
*/
float Approach(float goal, float current, float dt) {
	float difference = goal - current;

	if (difference < dt) {
		return current + dt;
	}
	if (difference < -dt) {
		return current - dt;
	}

	return goal;
}
