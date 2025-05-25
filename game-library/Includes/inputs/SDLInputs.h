//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef INPUTS_SDLINPUTS_H
#define INPUTS_SDLINPUTS_H

class SdlInputs final : public IInputs
{
public:
    bool IsKeyDown(EKey key) override;
    bool IsKeyPressed(EKey key) override;
    bool IsButtonDown(int button) override;
    void GetMousePosition(int* x, int* y) override;

protected:
    void Update() override;

private:
    void UpdateKeyboardState();

    std::vector<unsigned char> m_KeyStates;
    std::unordered_map<int, bool> m_KeyPressed;
    std::array<bool, 4> m_MouseStates = { false };
    int m_MouseX = 0;
    int m_MouseY = 0;
};

#endif
