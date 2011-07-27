/*
 * GameEveneReceiver.cpp
 *
 *  Created on: Jul 25, 2011
 *      Author: yejiabin
 */

#include "GameEventReceiver.h"
#include "Config.h"
#include "GameObject.h"

GameEventReceiver::GameEventReceiver() :
		hitStatus(0), lastHit(0), changed(false), status(IG_UPDATE) {
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
	}
	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
		switch (event.MouseInput.Event) {
		case EMIE_LMOUSE_PRESSED_DOWN:
			hitStatus = _handleMouse(event.MouseInput.X, event.MouseInput.Y);
			printf("mouse at %d,%d .\n", event.MouseInput.X,
					event.MouseInput.Y);
			changed = (hitStatus != lastHit);
			lastHit = hitStatus;
			mousePressed = true;
			break;
		case EMIE_LMOUSE_LEFT_UP:
			printf("up");
			mousePressed = false;
			hitStatus = _handleMouseUp(event.MouseInput.X, event.MouseInput.Y);
			break;
		default:
			changed = false;
			mousePressed = false;
			hitStatus = 0;
			break;
		}

	} else {
		hitStatus = 0;
	}
	return false;
}

u32 GameEventReceiver::_handleMouse(s32 mouseX, s32 mouseY) {
	switch (status) {
	case IG_UPDATE:
		return _handleUpdate(mouseX, mouseY);
		break;
	case IG_PAUSE:
		return _handlePause(mouseX, mouseY, HOVER_STATE);
		break;
	default:
		break;
	}
	return 0;
}

GameEventReceiver::~GameEventReceiver() {
	// TODO Auto-generated destructor stub
}

u32 GameEventReceiver::getHitStatus() const {
	return hitStatus;
}

void GameEventReceiver::setHitStatus(u32 hitStatus) {
	this->hitStatus = hitStatus;
}

u32 GameEventReceiver::getStatus() const {
	return status;
}

void GameEventReceiver::setStatus(u32 status) {
	this->status = status;
}

u32 GameEventReceiver::_handleMouseUp(s32 mouseX, s32 mouseY) {
	if (status == IG_PAUSE) {
		return _handlePause(mouseX, mouseY, CLICK_STATE);
	}
	return 0;
}

u32 GameEventReceiver::_handleUpdate(s32 mouseX, s32 mouseY) {
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
	} else if (mouseX >= 225 && mouseX <= 415) {
		if (mouseY >= 410) {
			result |= MENU_HIT;
		}
	}
	return result;
}

u32 GameEventReceiver::_handlePause(s32 mouseX,s32 mouseY, u32 mask) {
	u32 result = 0;
	if (mouseX >= 200 && mouseX <= 440) {
		if (mouseY >= 200 && mouseY <= 250) {
			result = GP_CONTINUE;
		} else if (mouseY >= 250 && mouseY <= 300) {
			result = GP_MAIN_MENU;
		} else if (mouseY >= 300 && mouseY <= 350) {
			result = GP_RESTART;
		}
	}
	printf("In pause state, before mask %d ", result);
	result |= mask;
	printf("fter mask %d \n", result);
	return result;
}