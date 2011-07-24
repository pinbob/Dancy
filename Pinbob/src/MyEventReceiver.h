/*
 * MouseEventReceiver.h
 *
 *  Created on: Jul 17, 2011
 *      Author: yejiabin
 */

/*
2011-07-20: add key event recognition .by liwenhaosuper
*/

#ifndef MOUSEEVENTRECEIVER_H_
#define MOUSEEVENTRECEIVER_H_

#include <irrlicht.h>

using namespace irr;

class MyEventReceiver: public IEventReceiver {
public:
	// We'll create a struct to record info on the mouse state
	struct SMouseState {
		core::position2di Position;
		bool LeftButtonDown;
		SMouseState() :
				LeftButtonDown(false) {
		}
	} MouseState;

	// This is the one method that we have to implement
	virtual bool OnEvent(const SEvent& event) {
		// Remember the mouse state
		if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
			switch (event.MouseInput.Event) {
			case EMIE_LMOUSE_PRESSED_DOWN:
				MouseState.LeftButtonDown = true;
				break;

			case EMIE_LMOUSE_LEFT_UP:
				MouseState.LeftButtonDown = false;
				break;

			case EMIE_MOUSE_MOVED:
				MouseState.Position.X = event.MouseInput.X;
				MouseState.Position.Y = event.MouseInput.Y;
				break;

			default:
				// We won't use the wheel
				break;
			}
		}

		// Remember whether each key is down or up
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

		return false;
	}


	const SMouseState & getMouseState(void) const {
		return MouseState;
	}

	/**
	 * change last hit status
	 */
	void setLastHitStatus(bool newStatus) {
		lastHitStayed = newStatus;
	}
	bool getLastHitStatus() const {
		return lastHitStayed;
	}

	MyEventReceiver():lastHitStayed(false) {
		for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}

private:
	bool lastHitStayed;
	// We use this array to store the current state of each key
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

#endif /* MOUSEEVENTRECEIVER_H_ */
