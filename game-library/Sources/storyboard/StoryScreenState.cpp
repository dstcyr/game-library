//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "storyboard/StoryScreenState.h"

StoryState* StoryScreenState::Create(Storyboard* screen, const std::string& id, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    StoryState* state = new StoryScreenState(screen, id, r, g, b, a);
    state->Enter();
    return state;
}

StoryScreenState::StoryScreenState(Storyboard* screen, const std::string& id, uint8_t r, uint8_t g, uint8_t b, uint8_t a) :
    StoryState(screen, id, r, g, b, a)
{
}

void StoryScreenState::Enter()
{
    IGraphics& tGraphics = Game::Get().Graphics();

    int screenW = 0;
    int screenH = 0;
    tGraphics.GetScreenSize(&screenW, &screenH);

    m_ScreenWidth = static_cast<float>(screenW);
    m_ScreenHeight = static_cast<float>(screenH);
}

void StoryScreenState::Exit()
{
}

void StoryScreenState::Update(float dt)
{
}

bool StoryScreenState::ProcessInput(float dt)
{
    return true;
}

void StoryScreenState::Draw()
{
    IGraphics& tGraphics = Game::Get().Graphics();

    tGraphics.EnableCamera(false);
    tGraphics.FillRect(0.0F, 0.0F, m_ScreenWidth, m_ScreenHeight, m_Red, m_Green, m_Blue, m_Alpha);
    tGraphics.EnableCamera(true);
}

void StoryScreenState::SetAlpha(uint8_t alpha)
{
    m_Alpha = alpha;
}
