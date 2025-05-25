//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef GUI_UICHOICE_H
#define GUI_UICHOICE_H

#include "UINode.h"
#include "UIPanel.h"
#include "UIText.h"
#include "UIImage.h"
#include "UIVerticalBox.h"
#include "UISeparator.h"
#include <vector>
#include <string>
#include <functional>
#include "data/Stack.h"
#include "maths/Vec2.h"

class UIChoice : public UINode
{
public:
    static void Create(const std::string& text, const std::vector<std::string>& dataSource, float posX, float posY, const std::function<void(int)>& callback);

    bool ProcessInput(float deltaTime) override;
    void Draw() override;
    void Draw(float posX, float posY) override;
    float GetWidth() const override;
    float GetHeight() const override;
    void Clear() override;

private:
    void AddOptionLocation(float posX, float posY);

    UIPanel m_Panel;
    UIImage m_CursorImage;
    UIText m_Text;
    UIVerticalBox m_OptionBox;
    UISeparator m_Separator;
    float m_PosX = 0.0F;
    float m_PosY = 0.0F;
    std::vector<Vec2<float>> m_OptionLocations;
    int m_SelectedOption = 0;
    TArray<UINode> m_Pointers;

    std::function<void(int)> m_ChoiceCallback;
};

#endif
