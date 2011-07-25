/***********************************************************************
 * Module: CCredits.h
 * Author:  liwenhaosuper
 * Modified: 2011Äê07ÔÂ23ÈÕ 21:30:51
 * Purpose: Declaration of the class CCredits
 * Comment: This is the state of credits,I just do it for funny. 
 ***********************************************************************/

#ifndef _C_CREDITS
#define _C_CREDITS

#include "irrlicht.h"
#ifdef WIN32
#pragma comment(lib,"irrlicht.lib")
#endif
#include "IState.h"

class CCredits : public IState, public IEventReceiver {
  private:
    class CCreditsAnimator : public ISceneNodeAnimator {
      private:
        u32 m_iLastAnim,
            m_iPauseStart;
        f32 m_fRotY;
        bool m_bLessZero;
        list<ITexture *> m_lTextures;
        list<ITexture *>::Iterator m_lIt;
        ISceneNode *pLight;

      public:
        CCreditsAnimator(IVideoDriver *pDriver, ISceneManager *pSmgr);
        virtual ~CCreditsAnimator();
        virtual void animateNode(ISceneNode *pNode, u32 iTime);
        virtual ISceneNodeAnimator *createClone(ISceneNode *node, ISceneManager *newManager=0);
        virtual ESCENE_NODE_ANIMATOR_TYPE getType() const;
        virtual bool isEventReceiverEnabled() const;
        virtual bool OnEvent(const SEvent &event);
    };

    ITimer *m_pTimer;
    u32 m_iRet;
    ISoundEngine *m_pSndEngine;
	u32 m_iPreState; //use to record the preview state

  public:
    CCredits(IrrlichtDevice *pDevice, StateMachine *pStateMachine);
    virtual void activate(IState *pPrevious);
    virtual void deactivate(IState *pNext);
    virtual u32 update();

    virtual bool OnEvent (const SEvent &event);
};

#endif


