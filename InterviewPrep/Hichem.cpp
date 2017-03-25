#include "stdafx.h"
#include "Hichem.h"


Hichem::Hichem()
{
}


Hichem::~Hichem()
{
}

//void ParseEvents() {
//	int count = 0;
//	int prevStage = 0;
//	int currentStage = 0;
//	char currentState = 'A';
//	double prevTime = 0.0;
//	double currentTime = 0.0;
//
//
//	while (line != end) {
//		currentTime = line.getTime();
//		currentStage = line.getValue();
//
//		//Transition to State B if time greater than 5
//		if (currentState == 'A' && currentStage == 2 && prevStage == 3) {
//
//			//5 min time has expired
//			if ((currentTime - prevTime) > 5.0) {
//				currentState = 'B';
//			}
//		}
//
//		if (currentState == 'A' && prevStage != 3) {
//			prevTime = currentTime;
//		}
//
//		//In stage b and reset
//		if (currentState == 'B' && currentStage == 1) {
//			currentState = 'A';
//		}
//
//		//Fault
//		if (currentState == 'B' && currentStage == 0) {
//			currentState = 'A';
//			count++;
//			currentStage = 0;
//		}
//		prevStage = currentStage;
//	}
//
//
//}
