/*
 * GameEveneReceiver.h
 *
 *  Created on: Jul 25, 2011
 *      Author: yejiabin
 */

#ifndef GAMEEVENERECEIVER_H_
#define GAMEEVENERECEIVER_H_

<<<<<<< HEAD
#include "irrlicht.h"
#ifdef WIN32
#pragma comment(lib,"irrlicht.lib")
#endif

using namespace irr;

#define HOVER_STATE 0x100
#define CLICK_STATE 0x200

typedef enum{
	IG_MOUSE_DOWN,
	IG_MOUSE_UP,
	IG_MOUSE_OTHER
} IG_MOUSE_STATE;

=======
#include <irrlicht.h>

using namespace irr;

>>>>>>> yjb
class GameEventReceiver: public irr::IEventReceiver {
public:
	GameEventReceiver();
	virtual bool OnEvent(const SEvent& event);
	virtual ~GameEventReceiver();
<<<<<<< HEAD
    u32 getHitStatus() const;
    void setHitStatus(u32 hitStatus);
    u32 getStatus() const;
    void setStatus(u32 status);
    u8 getMouseState() const;
    void setMouseState(u8 mouseState);
private:
	u32 _handleMouse(s32 mouseX, s32 mouseY);
	u32 _handleMouseUp(s32 mouseX, s32 mouseY);
	u32 _handleUpdate(s32 mouseX, s32 mouseY);
	u32 _handleUpdateUp(s32 mouseX, s32 mouseY);
	u32 _handlePause(s32 mouseX, s32 mouseY, u32 mask);
	u32 hitStatus;
	u8 mouseState;
	u32 status;
=======
    u8 getHitStatus() const;
    void setHitStatus(u8 hitStatus);
    bool getChange() const { return changed; }
    bool getMousePressed() const { return mousePressed; }
private:
	u8 _handleMouse(s32 mouseX, s32 mouseY);
	u8 hitStatus;
	u8 lastHit;
	bool changed;
	bool mousePressed;
>>>>>>> yjb
};

#endif /* GAMEEVENERECEIVER_H_ */
