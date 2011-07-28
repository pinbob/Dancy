/*
 * MouseEventReceiver.h
 *
 *  Created on: Jul 17, 2011
 *      Author: yejiabin
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
	}


private:
	bool lastHitStayed;
};

#endif /* MOUSEEVENTRECEIVER_H_ */
