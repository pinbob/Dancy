/*
 * GameEveneReceiver.cpp
 *
 *  Created on: Jul 25, 2011
 *      Author: yejiabin
 */

#include "GameEventReceiver.h"
#include "Config.h"

GameEventReceiver::GameEventReceiver():hitStatus(0),lastHit(0),changed(false) {
	// TODO Auto-generated constructor stub

}

bool GameEventReceiver::OnEvent(const SEvent& event) {
	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		switch (event.KeyInput.Key) {
		case KEY_KEY_W:
			printf("w\n");
			break;
		case KEY_KEY_A:
			printf("a\n");
			break;
		case KEY_KEY_S:
			printf("s\n");
			break;
		case KEY_KEY_D:
			printf("d\n");
			break;
		default:
			break;
		}
	} else if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
		switch (event.MouseInput.Event) {
		case EMIE_LMOUSE_PRESSED_DOWN:
			hitStatus = _handleMouse(event.MouseInput.X, event.MouseInput.Y);
			changed = hitStatus == lastHit;
			printf("mouse at %d,%d .\n", event.MouseInput.X,
					event.MouseInput.Y);
			break;
		case EMIE_LMOUSE_LEFT_UP:
			hitStatus = 0;
			break;
		case EMIE_MOUSE_MOVED:
			break;
		default:
			break;
		}
		changed = hitStatus != lastHit;
		lastHit = hitStatus;
	}
	return false;
}

u8 GameEventReceiver::_handleMouse(s32 mouseX, s32 mouseY) {
	u8 result = 0;
	if (mouseX <= 130) {
		if (mouseY >= 130 && mouseY < 240) {
			result |= UP_LEFT_HIT;
		} else if (mouseY >= 240 && mouseY <= 350) {
			result |= DOWN_LEFT_HIT;
		}
	} else if (mouseX >= 510) {
		if (mouseY >= 130 && mouseY < 240) {
			result |= UP_RIGHT_HIT;
		} else if (mouseY >= 240 && mouseY <= 350) {
			result |= DOWN_RIGHT_HIT;
		}
	}
	printf("result is %d", result);
	return result;

}

GameEventReceiver::~GameEventReceiver() {
	// TODO Auto-generated destructor stub
}

u8 GameEventReceiver::getHitStatus() const
{
    return hitStatus;
}

void GameEventReceiver::setHitStatus(u8 hitStatus)
{
    this->hitStatus = hitStatus;
}



