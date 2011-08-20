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
		hitStatus(0), mouseState(IG_MOUSE_OTHER), status(IG_UPDATE) {
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
			mouseState = IG_MOUSE_DOWN;
			break;
		case EMIE_LMOUSE_LEFT_UP:
			printf("up");
			hitStatus = _handleMouseUp(event.MouseInput.X, event.MouseInput.Y);
			mouseState = IG_MOUSE_UP;
			break;
		default:
			//hitStatus = 0;
			mouseState = IG_MOUSE_OTHER;
			break;
		}

	} else {
		//hitStatus = 0;
	}
	// printf ("event received: %d", hitStatus);
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
//	printf("Hit status is %d n\n", hitStatus);
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
	} else if (status == IG_UPDATE) {
		return _handleUpdateUp(mouseX, mouseY);
	}
	return 0;
}

u32 GameEventReceiver::_handleUpdateUp(s32 mouseX, s32 mouseY) {
	printf ("handle up\n");
	if (mouseX >= GAME_MENU_CONFIG[MENU].position.X
			&& mouseX <= GAME_MENU_CONFIG[MENU].position.X
							+ GAME_MENU_CONFIG[MENU].size.getWidth()) {
		if (mouseY >= GAME_MENU_CONFIG[MENU].position.Y) {
			return MENU_HIT;
		}
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
	}
	return result;
}

u32 GameEventReceiver::_handlePause(s32 mouseX, s32 mouseY, u32 mask) {
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

u8 GameEventReceiver::getMouseState() const {
	return mouseState;
}

void GameEventReceiver::setMouseState(u8 mouseState) {
	this->mouseState = mouseState;
}

