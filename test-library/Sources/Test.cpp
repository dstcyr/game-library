#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <vector>
#include <string>

#include "Game.h"
#include "packer/Packer.h"

#if defined(USE_VLD)
#include <vld.h>
#endif

#include "screens/tests/TestGameStates.h"
#include "screens/tests/TestPushStates.h"
#include "screens/tests/TestChangeStates.h"
#include "screens/tests/TestPrimitiveDraw.h"
#include "screens/tests/TestLogs.h"
#include "screens/tests/TestAnimation.h"
#include "screens/tests/TestFade.h"
#include "screens/tests/TestInterpolations.h"
#include "screens/tests/TestUI.h"
#include "screens/MainMenu.h"
#include "screens/GameMenu.h"
#include "screens/CombatScreen.h"
#include "screens/Storyboard.h"
#include "screens/CheatMenu.h"
#include "screens/GameLocationState.h"
#include "../Includes/Controllers/WaitController.h"
#include "../Includes/Controllers/MoveController.h"
#include "../Includes/Controllers/ReachController.h"
#include "../Includes/Controllers/IdleController.h"
#include "../Includes/Controllers/StrollController.h"
#include "../Includes/Controllers/StandController.h"
#include "../Includes/Controllers/CombatMoveController.h"
#include "../Includes/Controllers/CombatRunController.h"
#include "../Includes/Controllers/CombatStandbyController.h"
#include "../Includes/Controllers/CombatDieController.h"
#include "../Includes/Controllers/SleepController.h"
#include "../Includes/combat/CombatManager.h"
#include "../Includes/stats/Party.h"

void RegisterStates();
void RegisterControllers();

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    Game& tGame = Game::Get();
    if (tGame.Initialize())
    {
        RegisterStates();
        RegisterControllers();

        CombatManager::Get().Initialize();
        Party::Get().Initialize();

        if (IsDebuggerPresent() == TRUE)
        {
            std::vector<std::string> assets;
            pak::ListFiles("../assets", assets);

            if (!assets.empty())
            {
                pak::CreatePackFile(assets, "../test-library/game.pak");
            }

#if defined(DEBUG_PACKER)
            pak::ReadPackHeader("../test-library/game.pak");
#endif
        }

        tGame.Start();
    }

    return 0;
}

void RegisterStates()
{
    auto& world = Game::Get().World();
    world.ClearStates();
    world.RegisterState("TestGameStates", new TestGameStates());
    world.RegisterState("TestPushStates", new TestPushStates());
    world.RegisterState("TestChangeStates", new TestChangeStates());
    world.RegisterState("TestPrimitiveDraw", new TestPrimitiveDraw());
    world.RegisterState("TestLogs", new TestLogs());
    world.RegisterState("TestAnimation", new TestAnimation());
    world.RegisterState("TestFade", new TestFade());
    world.RegisterState("TestInterpolations", new TestInterpolations());
    world.RegisterState("TestUI", new TestUI());
    world.RegisterState("MainMenu", new MainMenu());
    world.RegisterState("GameMenu", new GameMenu());
    world.RegisterState("Combat", new CombatScreen());
    world.RegisterState("Story", new Storyboard());
    world.RegisterState("CheatMenu", new CheatMenu());
    world.RegisterState("TestCave", new GameLocationState({ "maps/cave.tmx", "sounds/14.ogg" }));
    world.RegisterState("Overland", new GameLocationState({ "maps/overland.tmx", "sounds/07.ogg" }));
    world.RegisterState("TestRoom", new GameLocationState({ "maps/smallRoom.tmx", "sounds/10.ogg" }));
    world.RegisterState("Town", new GameLocationState({ "maps/town.tmx", "sounds/10.ogg" }));
    world.RegisterState("Room_int_01", new GameLocationState({ "maps/room_int_01.tmx" }));

    // TODO (DaSt):
    // m_SaveBlacklist.emplace("MainMenu", m_StateDatabase["MainMenu"]);
    // m_SaveBlacklist.emplace("GameMenu", m_StateDatabase["GameMenu"]);
    // m_SaveBlacklist.emplace("CheatMenu", m_StateDatabase["CheatMenu"]);
    // m_SaveBlacklist.emplace("Combat", m_StateDatabase["Combat"]);
    // m_SaveBlacklist.emplace("Story", m_StateDatabase["Story"]);
}

void RegisterControllers()
{
    auto& world = Game::Get().World();

    world.RegisterControllerFactory("wait", &WaitController::Create);
    world.RegisterControllerFactory("move", &MoveController::Create);
    world.RegisterControllerFactory("reach", &ReachController::Create);
    world.RegisterControllerFactory("idle", &IdleController::Create);
    world.RegisterControllerFactory("stroll", &StrollController::Create);
    world.RegisterControllerFactory("stand", &StandController::Create);
    
    world.RegisterControllerFactory("combat_move", &CombatMoveController::Create);
    world.RegisterControllerFactory("combat_run", &CombatRunController::Create);
    world.RegisterControllerFactory("combat_standby", &CombatStandbyController::Create);
    world.RegisterControllerFactory("combat_die", &CombatDieController::Create);
    world.RegisterControllerFactory("sleep", &SleepController::Create);
}