#ifndef SONG_LIST_SCREEN_H
#define SONG_LIST_SCREEN_H

#include "irrlicht.h"
#ifdef WIN32
#pragma comment(lib,"irrlicht.lib")
#pragma comment(lib, "irrKlang.lib")
#endif

#ifdef USE_IRR
#include "irrKlang.h"
#endif
#include "SongCollection.h"
#include "Song.h"
#include "Config.h"

class SongListScreen : public IEventReceiver, public IState
{
public:
	SongListScreen(IrrlichtDevice *pDevice, StateMachine *pStateMachine,
			SongCollection *songs);
	virtual ~SongListScreen();
	virtual u32 update( void );
	virtual void activate( IState* pPrevious );
	virtual void deactivate( IState* pNext );
	virtual bool OnEvent( const SEvent& event );
	void drawScene();
private:
	//ISoundEngine *m_pSndEngine;//sound engine for menu
	char* backPath;//background path
	ITexture* back;
	SongCollection* songcollection;
	struct SMouseState {
		bool isMouseUp;
		core::position2di mouseDownPos;
		core::position2di mouseCurPos;
		SMouseState() : isMouseUp(false), mouseDownPos(0, 0), mouseCurPos(0, 0){}
	} MouseState;
	bool m_bSelect;
	int res;
	Song selectedsong;

};

#endif

