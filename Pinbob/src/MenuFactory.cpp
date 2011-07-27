#include "MenuFactory.h"
#include "IState.h"
        
MenuHandler* MenuFactory::createMenuHandler(IrrlichtDevice *pDevice, 
         StateMachine *pStateMachine, IState::StateType stateType){
    switch(stateType){
        case IState::INIT_STATE:
            
            break;
            
        case IState::MAIN_MENU_STATE:{
            char* imgPath[] = {"asset/images/main_menu/0", "asset/images/main_menu/1",
			"asset/images/main_menu/2", "asset/images/main_menu/3",
			"asset/images/main_menu/4"};
            MenuHandler* menuHandler = new MenuHandler(
                    pDevice, pStateMachine, "asset/images/back.png",
                    240, 80, "asset/images/main_menu/title.png",
                    5, 240, 50, imgPath, 0);
            return menuHandler;
            break;
        }
        
        case IState::MODE_STATE:{
            char* imgPath[] = {"asset/images/mode_menu/0", "asset/images/mode_menu/back"};
            MenuHandler* menuHandler = new MenuHandler(
                    pDevice, pStateMachine, "asset/images/back.png",
                    240, 80, "asset/images/mode_menu/title.png",
                    2, 240, 50, imgPath, 0);
            return menuHandler;
            break;
        }
        
        case IState::SONG_STATE:{
            char* imgPath[] = {"asset/images/song_menu/0", "asset/images/song_menu/1",
                                "asset/images/mode_menu/back"};
            MenuHandler* menuHandler = new MenuHandler(
                    pDevice, pStateMachine, "asset/images/back.png",
                    240, 80, "asset/images/song_menu/title.png",
                    3, 240, 50, imgPath, 0);
            return menuHandler;
            break;
        }
        
        default:
            return NULL;
            break;
    }
}
