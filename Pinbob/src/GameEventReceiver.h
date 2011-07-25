/*
 * GameEveneReceiver.h
 *
 *  Created on: Jul 25, 2011
 *      Author: yejiabin
 */

#ifndef GAMEEVENERECEIVER_H_
#define GAMEEVENERECEIVER_H_

#include <irrlicht.h>

using namespace irr;

class GameEventReceiver: public irr::IEventReceiver {
public:
	GameEventReceiver();
	virtual bool OnEvent(const SEvent& event);
	virtual ~GameEventReceiver();
    u8 getHitStatus() const;
    void setHitStatus(u8 hitStatus);
    bool getChange() const { return changed; }
private:
	u8 _handleMouse(s32 mouseX, s32 mouseY);
	u8 hitStatus;
	u8 lastHit;
	bool changed;
};

#endif /* GAMEEVENERECEIVER_H_ */
