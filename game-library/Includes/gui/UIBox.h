//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef GUI_UIBOX_H
#define GUI_UIBOX_H

#include "UINode.h"

class UIBox : public UINode
{
public:
    void AddChild(UINode* node);
    int Count() const { return static_cast<int>(m_Children.size()); }
    void Clear() override;

    auto Begin() { return m_Children.begin(); }
    auto End() { return m_Children.end(); }

protected:
    std::vector<UINode*> m_Children;
};

#endif
