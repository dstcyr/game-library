//  
//     _ ____  ____   ____   ____            _        
//    (_)  _ \|  _ \ / ___| |  _ \ _ __ ___ | |_ ___  
//    | | |_) | |_) | |  _  | |_) | '__/ _ \| __/ _ \ 
//    | |  _ <|  __/| |_| | |  __/| | | (_) | || (_) |
//   _/ |_| \_\_|    \____| |_|   |_|  \___/ \__\___/ 
//  |__/                                              
//  
//  jRPG Prototype
//  Copyright(C) 2024-2025 David St-Cyr
//  
//  The information in this file is confidential and solely for the attention
//  and use of the author. You are hereby notified that any dissemination,
//  distribution or copy of this content is prohibited without the prior
//  written consent of the author.
//
//  David St-Cyr
//  st-cyrdavid@hotmail.com

#include "Config.h"
#include "screens/Storyboard.h"
#include "storyboard/WaitEvent.h"
#include "storyboard/StoryScreenState.h"
#include "storyboard/FadeInEvent.h"
#include "storyboard/FadeOutEvent.h"
#include "storyboard/CaptionState.h"
#include "Game.h"
#include "storyboard/ExploreState.h"
#include "scenes/Character.h"
#include "storyboard/TimedTextboxEvent.h"
#include "storyboard/WaitStateEvent.h"
#include "storyboard/StoryState.h"

void Storyboard::Enter()
{
    IAudio& tAudio = Game::Get().Audio();
    tAudio.StopAllSounds();

    IGraphics& tGraphics = Game::Get().Graphics();
    m_DefaultFont = tGraphics.LoadFont("fonts/junction.ttf", 24);

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "adding a blackscreen");
            storyboard->m_StoryStack.PushBack(StoryScreenState::Create(storyboard, "blackscreen", 0, 0, 0, 255));
            return new WaitEvent(0.0F);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "loading sontos house map");
            storyboard->m_StoryStack.PushFront(ExploreState::Create(storyboard, "room", "maps/sontosHouse.tmx"));
            return new WaitEvent(1.0F);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "adding sleeper to the map");

            size_t newID = Utils::GenerateID("StoryHero");
            auto* heroCharacter = new Character(newID, "StoryHero");
            heroCharacter->Load("characters/sleeper.xml");
            heroCharacter->SetSize(32.0F, 48.0F);
            heroCharacter->SetAnimationFrame("left");

            storyboard->m_Characters.PushBack(heroCharacter);

            Tilemap* map = storyboard->GetMap("maps/sontosHouse");
            heroCharacter->SetParentMap(map);

            int lX = 24;
            int lY = 12;
            heroCharacter->SetLocalLocation(lX, lY);

            float wX = 0.0F;
            float wY = 0.0F;
            map->GetTransform().GetTileFoot(lX, lY, &wX, &wY, 32, 48);
            heroCharacter->SetWorldLocation(wX, wY);

            map->AddToObjectLayer(heroCharacter);

            return new WaitEvent(0.0F);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "play rain audio");

            IAudio& tAudio = Game::Get().Audio();
            size_t id = tAudio.LoadAudio("sounds/rain.wav");
            int channel = tAudio.PlayAudio(id, -1);
            tAudio.SetVolume(id, 100);
            storyboard->AddSound("rain", channel);
            return new WaitEvent(0.0F);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "waiting for 1 seconds");
            return new WaitEvent(1.0F);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "fade out title");

            std::string id = "place";
            auto* caption = new CaptionState(storyboard, id, "title", "Village of Sontos");
            storyboard->m_StoryStack.PushBack(caption);
            caption->Enter();

            return new FadeOutEvent(storyboard, id, true);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "fade out subtitle");

            std::string id = "time";
            auto* caption = new CaptionState(storyboard, id, "subtitle", "MIDNIGHT");
            storyboard->m_StoryStack.PushBack(caption);
            caption->Enter();

            return new FadeOutEvent(storyboard, id, true);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "waiting for 2 seconds");

            return new WaitEvent(2.0F);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "fade in title");

            std::string id = "place";
            return new FadeInEvent(storyboard, id, false);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "fade in subtitle");

            std::string id = "time";
            return new FadeInEvent(storyboard, id, true);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "remove title");

            storyboard->RemoveState("place");
            return new WaitEvent(0.0F);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "remove subtitle");

            storyboard->RemoveState("time");
            return new WaitEvent(0.0F);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "add guard to the map");

            size_t newID = Utils::GenerateID("StoryGuard");
            auto* guardCharacter = new Character(newID, "StoryGuard");
            guardCharacter->Load("characters/guard.xml");
            guardCharacter->SetSize(32.0F, 48.0F);
            guardCharacter->SetAnimationFrame("up");

            storyboard->m_Characters.PushBack(guardCharacter);

            Tilemap* map = storyboard->GetMap("maps/sontosHouse");
            guardCharacter->SetParentMap(map);

            int lX = 29;
            int lY = 16;
            guardCharacter->SetLocalLocation(lX, lY);

            float wX = 0.0F;
            float wY = 0.0F;
            map->GetTransform().GetTileFoot(lX, lY, &wX, &wY, 32, 48);
            guardCharacter->SetWorldLocation(wX, wY);

            map->AddToObjectLayer(guardCharacter);

            return new WaitEvent(0.0F);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "guard start moving to destination");

            int index = storyboard->m_Characters.Find([](const Character* entity)
                {
                    return entity->GetName() == "StoryGuard";
                }
            );

            Character* guardCharacter = storyboard->m_Characters.At(index);
            Blackboard* bb = guardCharacter->GetBlackboard();
            bb->reachX = 25;
            bb->reachY = 12;

            guardCharacter->SetController("reach");
            return new WaitEvent(0.0F);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "fade in blackscreen");

            std::string id = "blackscreen";
            return new FadeInEvent(storyboard, id, true);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            int index = storyboard->m_Characters.Find([](const Character* entity) { return entity->GetName() == "StoryGuard"; });
            Character* guard = storyboard->m_Characters.At(index);

            float guardX = 0.0F;
            float guardY = 0.0F;
            guard->GetWorldLocation(&guardX, &guardY);
            return new TimedTextboxEvent(storyboard, true, guardX - 30.0F, guardY - 120.0F);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "waiting for 2 seconds");

            return new WaitEvent(2.0F);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "fade out blackscreen");

            std::string id = "blackscreen";
            return new FadeOutEvent(storyboard, id, true);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "removing room map");

            storyboard->RemoveState("room");

            IWorld& tWorld = Game::Get().World();
            Camera* camera = tWorld.GetCamera();
            camera->Restore();

            return new WaitEvent(0.0F);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "stop rain audio");

            IAudio& tAudio = Game::Get().Audio();
            storyboard->StopSound("rain");
            return new WaitEvent(0.0F);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "loading jail map");
            storyboard->m_StoryStack.PushFront(ExploreState::Create(storyboard, "jail", "maps/jail.tmx"));
            return new WaitEvent(0.0F);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "fade out title");

            std::string id = "prison";
            auto* caption = new CaptionState(storyboard, id, "title", "In prison");
            storyboard->m_StoryStack.PushBack(caption);
            caption->Enter();

            return new FadeOutEvent(storyboard, id, true);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "fade out subtitle");

            std::string id = "morning";
            auto* caption = new CaptionState(storyboard, id, "subtitle", "NEXT MORNING");
            storyboard->m_StoryStack.PushBack(caption);
            caption->Enter();

            return new FadeOutEvent(storyboard, id, true);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "waiting for 2 seconds");

            return new WaitEvent(2.0F);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "fade in title");

            std::string id = "prison";
            return new FadeInEvent(storyboard, id, false);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "fade in subtitle");

            std::string id = "morning";
            return new FadeInEvent(storyboard, id, true);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "remove title");

            storyboard->RemoveState("prison");
            return new WaitEvent(0.0F);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "remove subtitle");

            storyboard->RemoveState("morning");
            return new WaitEvent(0.0F);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "fade in blackscreen");

            std::string id = "blackscreen";
            return new FadeInEvent(storyboard, id, true);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "wait 2 seconds");

            return new WaitEvent(5.0F);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "fade out blackscreen");

            std::string id = "blackscreen";
            return new FadeOutEvent(storyboard, id, true);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "removing jail map");

            storyboard->RemoveState("jail");

            IWorld& tWorld = Game::Get().World();
            Camera* camera = tWorld.GetCamera();
            camera->Restore();

            return new WaitEvent(0.0F);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "wait 1 seconds");

            return new WaitEvent(1.0F);
        });

    m_StoryEvents.emplace_back([](Storyboard* storyboard)
        {
            BX_LOG(ELogLevel::Log, "fade in blackscreen");

            std::string id = "blackscreen";
            return new FadeInEvent(storyboard, id, true);
        });
}

void Storyboard::Update(float deltaTime)
{


    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    for (auto it = m_Characters.Begin(); it != m_Characters.End(); it++)
    {
        (*it)->Update(deltaTime);
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////


    // m_SubStack.Update(deltaTime);
    for (auto it = m_StoryStack.Begin(); it != m_StoryStack.End(); it++)
    {
        (*it)->Update(deltaTime);
    }

    if (m_StoryEvents.empty() && m_Events.IsEmpty())
    {
        IWorld& tWorld = Game::Get().World();
        tWorld.PopState();
    }

    if (!m_Events.IsEmpty())
    {
        auto it = m_Events.Begin();
        while (it != m_Events.End())
        {
            IStoryboardEvent* storyEvt = *it;
            storyEvt->Update(deltaTime);

            if (storyEvt->IsFinished())
            {
                it = m_Events.Remove(it);
                delete storyEvt;
                continue;
            }

            if (storyEvt->IsBlocking())
            {
                return;
            }

            it++;
        }
    }

    auto it = m_StoryEvents.begin();
    while (it != m_StoryEvents.end())
    {
        IStoryboardEvent* nextEvent = (*it)(this);
        it = m_StoryEvents.erase(it);

        if (nextEvent != nullptr)
        {
            nextEvent->Update(deltaTime);

            if (nextEvent->IsFinished())
            {
                delete nextEvent;
                continue;
            }

            m_Events.PushBack(nextEvent);

            if (nextEvent->IsBlocking())
            {
                return;
            }
        }
    }
}

bool Storyboard::ProcessInput(float deltaTime)
{
    return true;
}

void Storyboard::Draw()
{
    // m_SubStack.Draw();
    for (auto it = m_StoryStack.Begin(); it != m_StoryStack.End(); it++)
    {
        (*it)->Draw();
    }
}

void Storyboard::Exit()
{
    // m_SubStack.Clear();
    while (!m_StoryStack.IsEmpty())
    {
        IState* state = m_StoryStack.PopBack();
        delete state;
    }

    IAudio& tAudio = Game::Get().Audio();
    tAudio.StopAllSounds();
}

StoryState* Storyboard::Find(const std::string& id)
{
    for (auto it = m_StoryStack.Begin(); it != m_StoryStack.End(); it++)
    {
        if ((*it)->GetID() == id)
        {
            return *it;
        }
    }

    return nullptr;
}

void Storyboard::RemoveState(const std::string& id)
{
    m_StoryStack.Remove([id](const StoryState* state)
        {
            if (state != nullptr)
            {
                return state->GetID() == id;
            }

            return false;
        });
}

void Storyboard::AddSound(const std::string& filename, int channel)
{
    if (m_AudioChannels.count(filename) == 0)
    {
        m_AudioChannels.emplace(filename, channel);
    }
}

void Storyboard::StopSound(const std::string& filename)
{
    if (m_AudioChannels.count(filename) > 0)
    {
        IAudio& tAutio = Game::Get().Audio();
        int channel = m_AudioChannels[filename];
        tAutio.StopSound(channel);
        m_AudioChannels.erase(filename);
    }
}

void Storyboard::AddMap(Tilemap* map)
{
    m_Maps.PushBack(map);
}

void Storyboard::RemoveMap(Tilemap* map)
{
    auto it = m_Maps.Begin();
    while (it != m_Maps.End())
    {
        if (*it == map)
        {
            it = m_Maps.Remove(it);
        }
        else
        {
            it++;
        }
    }
}

Tilemap* Storyboard::GetMap(const std::string& mapName)
{
    int index = m_Maps.Find([mapName](const Tilemap* map) { return map->GetName() == mapName; });
    if (index >= 0)
    {
        return m_Maps.At(index);
    }

    return nullptr;
}
