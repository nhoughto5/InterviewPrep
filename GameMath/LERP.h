#pragma once

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
