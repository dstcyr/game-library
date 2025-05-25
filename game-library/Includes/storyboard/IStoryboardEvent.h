//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef STORYBOARD_ISTORYBOARDEVENT_H
#define STORYBOARD_ISTORYBOARDEVENT_H

class IStoryboardEvent
{
public:
    virtual ~IStoryboardEvent() = default;
    explicit IStoryboardEvent(bool block) : m_Blocking(block) {}

    virtual void Update(float deltaTime) = 0;
    virtual bool IsBlocking() { return m_Blocking; }
    virtual bool IsFinished() { return m_Finished; }

protected:
    bool m_Blocking = true;
    bool m_Finished = false;
};

#endif
