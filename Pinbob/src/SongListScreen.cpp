
#include "GameObject.h"
#include "SongListScreen.h"

SongListScreen::SongListScreen(IrrlichtDevice *pDevice,
		StateMachine *pStateMachine, SongCollection* songs) :
		IState(pDevice, pStateMachine),songcollection(songs) {
	backPath = "asset/images/back.png";
	back = m_pDriver->getTexture(backPath);
	for (unsigned int i=0; i<songcollection->song_list().size(); i++) {
		printf("get song %s.\n", songcollection->GetSong(i).main_title().c_str());
	}
	res = 0;
}

irr::u32 SongListScreen::update(void) {
	if (!m_pDevice->getCursorControl()->isVisible())
		m_pDevice->getCursorControl()->setVisible(true);
	m_bSelect = false;
	if (res == START_GAME) {
		m_pStateMachine->m_pGameObj->setCurrentSong(&selectedsong);
//		m_pStateMachine->m_pGameObj->setCurrentSong(
//				selectedsong.main_title().c_str());
	}
	return res;
}

void SongListScreen::activate(IState* pPrevious) {
	m_pStateMachine->setDrawScene(true);
	m_pDevice->setEventReceiver(this);
	m_bSelect = false;
	res = 0;
	drawScene();
}

void SongListScreen::deactivate(IState* pNext) {
	m_pDevice->getSceneManager()->clear();
	m_pGuienv->clear();
}

bool SongListScreen::OnEvent(const SEvent& event) {
	// Remember the mouse state
	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
		switch (event.MouseInput.Event) {
		case EMIE_LMOUSE_PRESSED_DOWN:
			MouseState.mouseDownPos.X = event.MouseInput.X;
			MouseState.mouseDownPos.Y = event.MouseInput.Y;
			//when mouse down, set isMouseDown to be true
			MouseState.isMouseUp = false;
			MouseState.mouseCurPos.X = event.MouseInput.X;
			MouseState.mouseCurPos.Y = event.MouseInput.Y;
			m_bSelect = false;
			break;
		case EMIE_LMOUSE_LEFT_UP:
			//when mouse up, set isMouseDown to be false
			MouseState.isMouseUp = true;
			if (event.MouseInput.X
					< static_cast<s32>(3 * SCREEN_WIDTH / 10)
					&& event.MouseInput.Y
							< static_cast<s32>(2
									* SCREEN_HEIGHT / 10)) {
				printf("back\n");
				res = MODE_STATE;
			} else if (event.MouseInput.X
					> static_cast<s32>(7 * SCREEN_WIDTH / 10)
					&& event.MouseInput.Y
							< static_cast<s32>(2 * SCREEN_HEIGHT / 10)) {
				printf("continue\n");
				if (songcollection->song_list().size() == 0)
					break;
				res = START_GAME;
			}
			break;
		default:
			break;
		}
	}
	return false;
}

SongListScreen::~SongListScreen() {

}

void SongListScreen::drawScene() {
	//IGUISkin* skin = m_pGuienv->getSkin();
	//Font cannot load
	//IGUIFont* font = m_pGuienv->getFont("asset/images/font.png");
//	if (font)
//		skin->setFont(font);
//	skin->setFont(m_pGuienv->getBuiltInFont(), EGDF_TOOLTIP);
	m_pGuienv->addImage(back, core::position2d<s32>(0, 0), -1, 0);

	// get screen size method will misleading the program
	// so I must fix the screen size
	u32 screenWidth = SCREEN_WIDTH; //m_pDevice->getVideoDriver()->getScreenSize().Width;
	u32 screenHeight = SCREEN_HEIGHT; //m_pDevice->getVideoDriver()->getScreenSize().Height;
	m_pGuienv->addImage(
			m_pDriver->getTexture("asset/images/song_menu/back0.png"),
			position2d<s32>(0, 0));
	m_pGuienv->addImage(
			m_pDriver->getTexture("asset/images/main_menu/title.png"),
			position2d<s32>(screenWidth / 3, screenHeight / 20));
	m_pGuienv->addImage(
			m_pDriver->getTexture("asset/images/song_menu/continue.png"),
			position2d<s32>(65 * screenWidth / 100, 0));
	m_pGuienv->addStaticText(
			L"Selected a song:",
			rect<s32>(screenWidth / 4, 26 * screenHeight / 100,
					3 * screenWidth / 4, 32 * screenHeight / 100), true);

}
