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

#ifndef SCREENS_COMBATSCREEN_H
#define SCREENS_COMBATSCREEN_H
//#define DEBUG_COMBAT

#include "screens/ScreenState.h"
#include "gui/UIPanel.h"
#include "gui/UIHorizontalBox.h"
#include "gui/UIVerticalBox.h"
#include "gui/UISeparator.h"
#include "stats/IParty.h"
#include "gui/UIText.h"
#include "combat/CombatEventQueue.h"
#include "maths/Vec2.h"

class Character;
class UIProgressText;
class CombatActor;
class ICombatState;
class IEffect;

class CombatScreen : public ScreenState
{
public:
    void Enter() override;
    void Update(float deltaTime) override;
    bool ProcessInput(float deltaTime) override;
    void Draw() override;
    void Exit() override;
    void Destroy() override;
    void Push(ICombatState* combatState);
    static void CloseCombat();

    void SelectCharacter(CombatActor* selection);
    void HideSelection();

    CombatActor* GetRandomPartyMember();
    CombatActor* GetRandomEnemyMember();

    bool IsActorInParty(CombatActor* actor) const;
    void GetEnemyTarget(std::vector<CombatActor*>& targets);
    void GetPlayerTarget(std::vector<CombatActor*>& targets);
    void GetParty(std::vector<CombatActor*>& party);
    CombatEventQueue* GetEventQueue() { return &m_EventQueue; }
    void AddEffect(IEffect* effect);

    void UpdateUI();

    bool IsGameOver();
    bool PartyWins();
    bool EnemyWins();

    void PlayVictoryFanfare();
    void PlayDefeatSong();

    void ShowNotification(const std::string& message);

private:
    void InitializeUI();
    void ClearUI();
    void InitializeBattleStations();
    void CreateCombatCharacters();
    void AddTurns();

    size_t m_BgId = 0;

    bool m_ShowTip = false;
    bool m_ShowNotice = false;
    bool m_ShowSelectionMarker = false;

    UIPanel m_NamePanel;
    UIPanel m_InfoPanel;
    UIPanel m_NoticePanel;
    UIText m_NoticeText;
    UIPanel m_TipPanel;
    UIText m_TipText;
    UIHorizontalBox m_BottomBox;
    UIVerticalBox m_NamesBox;
    UIVerticalBox m_HpInfoBox;
    UIVerticalBox m_MpInfoBox;
    UIHorizontalBox m_InfoHorizontal;
    UISeparator m_Separator;

    TArray<UIText> m_PartyNameTexts;
    TArray<UIProgressText> m_PartyProgressBars;
    TArray<CombatActor> m_PartyActors;
    TArray<CombatActor> m_EnemyActors;
    TArray<ICombatState> m_CombatStateStack;
    TArray<IEffect> m_EffectStack;
    std::vector<Vec2<float>> m_PartyBattleStations;
    std::vector<Vec2<float>> m_EnemyBattleStations;

    CombatEventQueue m_EventQueue;
    SpriteSheet m_Icons;

    std::pair<float, float> m_SelectionLocation;

    size_t m_Theme = 0;
    size_t m_VictoryTheme = 0;
    size_t m_DefeatTheme = 0;
    int m_AudioChannel = 0;

#if defined(DEBUG_COMBAT)
    size_t m_DebugFont = 0;
#endif
};

#endif
