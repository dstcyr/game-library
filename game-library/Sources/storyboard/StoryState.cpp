//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "storyboard/StoryState.h"

StoryState::StoryState(Storyboard* screen, const std::string& id, uint8_t r, uint8_t g, uint8_t b, uint8_t a) :
    m_Screen(screen),
    m_Red(r),
    m_Green(g),
    m_Blue(b),
    m_Alpha(a),
    m_Id(id),
    m_IsReady(false)
{
}

void StoryState::Enter()
{
}

void StoryState::Exit()
{
}

void StoryState::Update(float dt)
{
}

bool StoryState::ProcessInput(float dt)
{
    return false;
}

void StoryState::Draw()
{
}

void StoryState::SetAlpha(uint8_t alpha)
{
    m_Alpha = alpha;
}
