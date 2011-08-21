/*
 * GameOverState.cpp
 *
 *  Created on: Aug 21, 2011
 *      Author: yejiabin
 */

#include "GameOverState.h"

GameOverState::GameOverState(IrrlichtDevice *pDevice,
		StateMachine *pStateMachine) :
		IState(pDevice, pStateMachine),back(0),currentInfo(0) {

}

u32 GameOverState::update() {

	return 0;
}

void GameOverState::activate(IState* pPrevious) {
	m_pStateMachine->setDrawScene(true);
	m_pDevice->setEventReceiver(this);
	_init();
}

void GameOverState::deactivate(IState* pNext) {
	m_pDevice->getSceneManager()->clear();
	m_pGuienv->clear();
}

bool GameOverState::OnEvent(const SEvent& event) {
	return false;
}

GameOverState::~GameOverState() {
}

void GameOverState::_init() {
	printf("gover\n");
	m_pGuienv->addImage(m_pDriver->getTexture("asset/images/back.png"), core::position2d<s32>(0, 0),
			-1, 0);
	u32 screenWidth = m_pDevice->getVideoDriver()->getScreenSize().Width;
	u32 screenHeight = m_pDevice->getVideoDriver()->getScreenSize().Height;

	if (currentInfo) {
		char* digitFileName = (char*)malloc(6);
		for (int i=0; i<10; i++) {
			sprintf(digitFileName,"%d.png",i);
			digit[i] = m_pDriver->getTexture(digitFileName);
		}
		free(digitFileName);
		m_pGuienv->addImage(m_pDriver->getTexture("asset/images/perfect.png"),
				core::position2d<s32>(100, 100));
		m_pGuienv->addImage(m_pDriver->getTexture("asset/images/wellDone.png"),
						core::position2d<s32>(100, 150));
		m_pGuienv->addImage(m_pDriver->getTexture("asset/images/good.png"),
						core::position2d<s32>(100, 200));
		m_pGuienv->addImage(m_pDriver->getTexture("asset/images/bad.png"),
								core::position2d<s32>(100, 250));
		m_pGuienv->addImage(m_pDriver->getTexture("asset/images/missed.png"),
										core::position2d<s32>(100, 300));
		m_pGuienv->addImage(m_pDriver->getTexture("asset/images/combo.png"),
												core::position2d<s32>(100, 350));
	} else {
		// This should never happen
	}
}
