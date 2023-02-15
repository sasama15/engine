#include "SceneFactory.h"
#include "TitleScene.h"
#include "../StageSelect.h"
#include "../Operation.h"
#include "GamePlayScene.h"
#include "../GameClear.h"
#include "../GamePlayScene2.h"

BaseScene* SceneFactory::CreateScene(const std::string& sceneName)
{
    //éüÇÃÉVÅ[ÉìÇê∂ê¨
    BaseScene* newScene = nullptr;
    
    if (sceneName == "TITLE") {
        newScene = new TitleScene();
    }

    else if (sceneName == "STAGESELECT") {
        newScene = new StageSelect();
    }

    else if (sceneName == "OPERATION") {
        newScene = new Operation();
    }

    else if (sceneName == "GAMEPLAY") {
        newScene = new GamePlayScene();
    }

    else if (sceneName == "GAMEPLAY2") {
        newScene = new GamePlayScene2();
    }

    else if (sceneName == "GAMECLEAR") {
        newScene = new GameClear();
    }

    return newScene;
}
