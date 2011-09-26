#include "MenuFactory.h"
#include "IState.h"
#include "Config.h"
        
MenuHandler* MenuFactory::createMenuHandler(IrrlichtDevice *pDevice, 
         StateMachine *pStateMachine, IState::StateType stateType){
    switch(stateType){            
        case IState::MAIN_MENU_STATE:{
            char* imgPath[] = {"asset/images/main_menu/0", //"asset/images/main_menu/1",(it's option menu)
            		"asset/images/main_menu/5", // help
            		"asset/images/main_menu/3",
			//"asset/images/main_menu/2", (it's highscore)
			"asset/images/main_menu/4"};
            MenuHandler* menuHandler = new MenuHandler(
                    pDevice, pStateMachine, "asset/images/back.png",
                    240, 80, "asset/images/main_menu/title.png",
                    4, 240, 50, imgPath, 0);
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
        
        case IState::HELP_STATE: {
        	char* imgPath[] = {"asset/images/credits_menu/back"};
        	MenuHandler* menuHandler = new MenuHandler(
        	                    pDevice, pStateMachine, "asset/images/back.png",
        	                    SCREEN_WIDTH*.8, SCREEN_HEIGHT*.8, "asset/images/help.png",
        	                    1, 240, 50, imgPath, 0);
        	return menuHandler;
        	break;
        }

//        case IState::SONG_STATE:{
//            char* imgPath[] = {"asset/images/song_menu/0", "asset/images/song_menu/1",
//                                "asset/images/mode_menu/back"};
//            MenuHandler* menuHandler = new MenuHandler(
//                    pDevice, pStateMachine, "asset/images/back.png",
//                    240, 80, "asset/images/song_menu/title.png",
//                    3, 240, 50, imgPath, 0);
//            return menuHandler;
//            break;
//        }
        
        case IState::CREDITS_STATE:{
            char* imgPath[] = {"asset/images/credits_menu/back"};
            MenuHandler* menuHandler = new MenuHandler(
                    pDevice, pStateMachine, "asset/images/back.png",
                    500, 152, "asset/images/credits_menu/credit.png",
                    1, 240, 50, imgPath, 0);
            return menuHandler;
            break;
        }
        
        default:
            return NULL;
            break;
    }
    return NULL;
}
