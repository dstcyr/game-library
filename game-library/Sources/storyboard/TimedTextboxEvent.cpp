//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "storyboard/TimedTextboxEvent.h"
#include "gui/UITextbox.h"

TimedTextboxEvent::TimedTextboxEvent(Storyboard* screen, bool block, float x, float y) :
    IStoryboardEvent(block),
    m_Screen(screen)
{
    m_Finished = false;

    Game& tGame = Game::Get();
    m_Textbox = UITextbox::Create("Take Him!", x, y);
    tGame.PushUINode(m_Textbox);
}

void TimedTextboxEvent::Update(float deltaTime)
{
    m_Elapsed += deltaTime;
    if (m_Elapsed >= 3.0F)
    {
        // TODO(DaSt): not safe, there could be more node
        Game::Get().PopUINode();
        m_Finished = true;
    }
}
