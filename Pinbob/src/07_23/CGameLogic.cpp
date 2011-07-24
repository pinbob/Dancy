

#include "CGameLogic.h"


CGameLogic::CGameLogic()
{
	m_iState=eGameStateInitGame;
	m_iCountDown=3;
	m_iTime = 0;
	m_iStartTime = 0;
}

CGameLogic::~CGameLogic()
{

}

void CGameLogic::setDevice( IrrlichtDevice *pDevice )
{
	m_pDevice=pDevice;
}

void CGameLogic::setGame( GameObject *pGame )
{
	m_pGame = pGame;
	m_pGame->SetGameLogic(this);
}

void CGameLogic::update()
{
	switch (m_iState)
	{
	case eGameStateInitGame:
		printf("init game\n");
		m_iState = eGameStateReady1;
		break;
	case eGameStateReady1:
		//TODO:draw the elements here
		printf("ready 1\n");
		m_iTime=m_pTimer->getTime();
		m_iState=eGameStateReady2;
		m_pGame->toggleCountdown(0);
		break;
	case eGameStateReady2:
		//3 seconds
		printf("ready2\n");
		if (m_pTimer->getTime()-m_iTime>3000) m_iState=eGameStateCountdown1;
		break;
	case eGameStateCountdown1:
		printf("count down 1\n");
		m_iTime=m_pTimer->getTime();
		m_iState=eGameStateCountdown2;
		m_pGame->toggleCountdown(1+(3-m_iCountDown));
		break;
	case eGameStateCountdown2:
		printf("count down2!\n");
		if (m_pTimer->getTime()-m_iTime>1000) {
			m_iCountDown--;
			if (m_iCountDown) m_iState=eGameStateCountdown1; else m_iState=eGameStateGo;
		}
		break;
	case eGameStateGo:
		printf("GO!\n");
		m_iStartTime=m_pTimer->getTime();
		m_pGame->toggleCountdown(4);
		//add more elements here

		m_iState=eGameStatePlay;
		break;
	case eGameStatePlay:
		//I don't know what to add
		printf("play!\n");
		break;
	case eGameStateStarting:
		//during playing
		printf("playing!\n");
		break;
	case eGameStateFinished:
		printf("finished!\n");
		
		break;
	case eGameStateGameOver1:
		printf("game over!\n");
		break;
	case eGameStateGameOver2:
		printf("show available options!\n");
		break;
	default:
		break;
	}
}

void CGameLogic::init()
{

}

void CGameLogic::setGameState( u32 iState )
{
	m_iState =(eGameLogicState) iState;
}

void CGameLogic::setTimer( ITimer *pTimer )
{
	m_pTimer = pTimer;
}

irr::u32 CGameLogic::getGameState()
{
	return (u32)m_iState;
}
