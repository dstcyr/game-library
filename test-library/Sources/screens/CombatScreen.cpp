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
#include "screens/CombatScreen.h"
#include "gui/UIText.h"
#include "screens/UIProgressText.h"
#include "scenes/Character.h"
#include "combat/CETurn.h"
#include "gui/UIProgress.h"
#include "combat/CombatActor.h"
#include "combat/ICombatState.h"
#include "combat/IEffect.h"
#include "combat/VictoryState.h"
#include "../../Includes/stats/Party.h"
#include "../../Includes/combat/CombatManager.h"

void CombatScreen::Enter()
{
    m_Icons.Load("textures/inventory_icons.png");
    m_Icons.AddFrame("downarrow", 36, 36, 36, 36);
    m_SelectionLocation = { 0.0F, 0.0F };

    IAudio& tAudio = Game::Get().Audio();
    m_VictoryTheme = tAudio.LoadAudio("sounds/20.ogg");
    tAudio.SetVolume(m_VictoryTheme, 50);

    m_DefeatTheme = tAudio.LoadAudio("sounds/21.ogg");
    tAudio.SetVolume(m_DefeatTheme, 50);

    m_Theme = tAudio.LoadAudio("sounds/19.ogg");
    tAudio.SetVolume(m_Theme, 50);

    tAudio.PlayMusic(m_Theme);

    InitializeUI();
    InitializeBattleStations();
    CreateCombatCharacters();

    int stationIndex = 0;
    for (auto it = m_PartyActors.Begin(); it != m_PartyActors.End(); it++)
    {
        Vec2<float> battleStation = m_PartyBattleStations[stationIndex];
        stationIndex++;

        (*it)->character->SetWorldLocation(battleStation.x, battleStation.y);
    }

    stationIndex = 0;
    for (auto it = m_EnemyActors.Begin(); it != m_EnemyActors.End(); it++)
    {
        Vec2<float> battleStation = m_EnemyBattleStations[stationIndex];
        stationIndex++;

        (*it)->character->SetWorldLocation(battleStation.x, battleStation.y);
    }

#if defined(DEBUG_COMBAT)
    IGraphics& tGraphics = Game::Get().Graphics();
    m_DebugFont = tGraphics.LoadFont("fonts/charriot.ttf", 22);
#endif

    m_ShowTip = false;
    m_ShowNotice = false;
}

void CombatScreen::Update(float deltaTime)
{
    for (auto it = m_PartyActors.Begin(); it != m_PartyActors.End(); it++)
    {
        (*it)->character->Update(deltaTime);
    }

    for (auto it = m_EnemyActors.Begin(); it != m_EnemyActors.End(); it++)
    {
        (*it)->character->Update(deltaTime);
    }

    if (!m_EffectStack.IsEmpty())
    {
        auto it = m_EffectStack.Begin();
        while (it != m_EffectStack.End())
        {
            (*it)->Update(deltaTime);

            if ((*it)->IsFinished())
            {
                it = m_EffectStack.Remove(it);
            }
            else
            {
                ++it;
            }
        }
    }

    if (!m_CombatStateStack.IsEmpty())
    {
        ICombatState* head = m_CombatStateStack.First();
        head->Update(deltaTime);
        if (head->IsFinished())
        {
            m_CombatStateStack.PopFront();
            delete head;
        }
    }
    else if (m_EventQueue.IsEmpty())
    {
        AddTurns();
    }
    else
    {
        m_EventQueue.Update(deltaTime);
    }
}

bool CombatScreen::ProcessInput(float deltaTime)
{
    if (!m_CombatStateStack.IsEmpty())
    {
        ICombatState* top = m_CombatStateStack.Last();
        if (!top->ProcessInput(deltaTime))
        {
            return false;
        }
    }

#if defined(DEBUG_COMBAT)
    IInputs& tInput = Game::Get().Inputs();
    if (tInput.IsKeyPressed(EKey::EKEY_ESCAPE))
    {
        CloseCombat();
    }
#endif

    return true;
}

void CombatScreen::Draw()
{
    IGraphics& tGraphics = Game::Get().Graphics();
    tGraphics.EnableCamera(false);

    int screenW = 0;
    int screenH = 0;
    tGraphics.GetScreenSize(&screenW, &screenH);

    Rect<float> dst = { 0.0F, 0.0F, static_cast<float>(screenW), static_cast<float>(screenH) - 180.0F };
    tGraphics.DrawImage(m_BgId, dst, 255, 255, 255, 255);

    m_BottomBox.Draw(0.0F, screenH - 200.0F);

    for (auto it = m_PartyActors.Begin(); it != m_PartyActors.End(); it++)
    {
        (*it)->character->Draw();
    }

    for (auto it = m_EnemyActors.Begin(); it != m_EnemyActors.End(); it++)
    {
        (*it)->character->Draw();
    }

    if (m_ShowSelectionMarker)
    {
        m_Icons.Draw("downarrow", m_SelectionLocation.first, m_SelectionLocation.second);
    }

    if (!m_CombatStateStack.IsEmpty())
    {
        ICombatState* top = m_CombatStateStack.Last();
        top->Draw();
    }

    if (!m_EffectStack.IsEmpty())
    {
        for (auto it = m_EffectStack.Begin(); it != m_EffectStack.End(); it++)
        {
            (*it)->Draw();
        }
    }

    if (m_ShowNotice)
    {
        float noticeWidth = m_NoticePanel.GetWidth();
        m_NoticePanel.Draw((static_cast<float>(screenW) / 2.0F) - (noticeWidth / 2.0F), 50.0F);
    }

    if (m_ShowTip)
    {
        m_TipPanel.Draw(0.0F, 810.0F);
    }

    tGraphics.EnableCamera(true);

#if defined(DEBUG_COMBAT)
    IGraphics& tDebugGraphics = Game::Get().Graphics();
    tDebugGraphics.EnableCamera(false);
    float startY = 70.0F;
    int cnt = 1;

    for (auto it = m_PartyActors.begin(); it != m_PartyActors.end(); it++)
    {
        Character* character = (*it)->character;
        FCharacterDefinition* definition = (*it)->definition;

        std::string entry = "[" + std::to_string(cnt) + "] " + character->GetName();
        entry += " -> " + std::to_string(character->GetInstanceID());
        entry += " " + character->GetBounds().ToString();
        entry += " " + definition->ToString();

        tDebugGraphics.DrawString(entry, m_DebugFont, 10.0F, startY, 255, 255, 0, 255);
        startY += 30.0F;
        cnt++;
    }

    for (auto it = m_EnemyActors.begin(); it != m_EnemyActors.end(); it++)
    {
        Character* character = (*it)->character;
        FCharacterDefinition* definition = (*it)->definition;

        std::string entry = "[" + std::to_string(cnt) + "] " + character->GetName();
        entry += " -> " + std::to_string(character->GetInstanceID());
        entry += " " + character->GetBounds().ToString();
        entry += " " + definition->ToString();

        tDebugGraphics.DrawString(entry, m_DebugFont, 10.0F, startY, 255, 0, 0, 255);
        startY += 30.0F;
        cnt++;
    }

    if (m_EventQueue.IsEmpty())
    {
        tDebugGraphics.DrawString("Event Queue is empty", m_DebugFont, 10.0F, startY, 255, 0, 255, 255);
        startY += 30.0F;
    }
    else
    {
        tDebugGraphics.DrawString("Event Queue: ", m_DebugFont, 10.0F, startY, 255, 0, 255, 255);
        startY += 30.0F;

        ICombatEvent* currentEvent = m_EventQueue.GetCurrent();
        if (currentEvent != nullptr)
        {
            std::string entry = "Current Event: [" + std::to_string(currentEvent->GetCountDown()) + "][" + currentEvent->GetName() + "]";
            tDebugGraphics.DrawString(entry, m_DebugFont, 10.0F, startY, 255, 0, 255, 255);
        }
        else
        {
            tDebugGraphics.DrawString("Current Event: null", m_DebugFont, 10.0F, startY, 255, 0, 255, 255);
        }

        startY += 30.0F;

        int cntEvent = 1;
        for (auto it = m_EventQueue.Begin(); it != m_EventQueue.End(); it++)
        {
            ICombatEvent* ce = (*it);
            std::string entry = "[" + std::to_string(cntEvent) + "] Event: [" + std::to_string(ce->GetCountDown()) + "][" + ce->GetName() + "]";
            cntEvent++;

            tDebugGraphics.DrawString(entry, m_DebugFont, 40.0F, startY, 255, 0, 255, 255);
            startY += 30.0F;
        }
    }

    tDebugGraphics.EnableCamera(true);
#endif

}

void CombatScreen::Exit()
{
    Destroy();
}

void CombatScreen::Destroy()
{
    IAudio& tAudio = Game::Get().Audio();
    tAudio.StopAllSounds();

    while (!m_CombatStateStack.IsEmpty())
    {
        ICombatState* state = m_CombatStateStack.PopBack();
        delete state;
    }

    m_ShowTip = false;
    m_ShowNotice = false;
    m_EffectStack.Clear();
    m_PartyNameTexts.Clear();
    m_PartyProgressBars.Clear();
    m_PartyBattleStations.clear();
    m_EnemyBattleStations.clear();
    m_EventQueue.Clear();
    ClearUI();

    while (!m_PartyActors.IsEmpty())
    {
        CombatActor* actor = m_PartyActors.PopBack();
        actor->character->Clear();
        delete actor->character;
        delete actor;
    }

    while (!m_EnemyActors.IsEmpty())
    {
        CombatActor* actor = m_EnemyActors.PopBack();
        actor->character->Clear();
        delete actor->character;
        delete actor->definition;
        delete actor;
    }
}

void CombatScreen::Push(ICombatState* combatState)
{
    m_CombatStateStack.PushBack(combatState);
}

void CombatScreen::CloseCombat()
{
    IWorld& tWorld = Game::Get().World();
    tWorld.PopState();
}

void CombatScreen::SelectCharacter(CombatActor* selection)
{
    int tIndex = -1;
    m_ShowSelectionMarker = false;

    for (auto it = m_PartyActors.Begin(); it != m_PartyActors.End(); it++)
    {
        tIndex++;
        m_PartyNameTexts.At(tIndex)->SetColor(255, 255, 255, 255);
        if (*it == selection)
        {
            float wx = 0.0F;
            float wy = 0.0F;
            (*it)->character->SetSelectPadding(35.0F);
            (*it)->character->GetSelectPosition(&wx, &wy, 36.0F, 36.0F);
            m_SelectionLocation = { wx, wy };
            m_PartyNameTexts.At(tIndex)->SetColor(255, 255, 0, 255);
            m_ShowSelectionMarker = true;
        }
    }
}

void CombatScreen::HideSelection()
{
    m_ShowSelectionMarker = false;
}

CombatActor* CombatScreen::GetRandomPartyMember()
{
    if (!m_PartyActors.IsEmpty())
    {
        TArray<CombatActor> availableActors = m_PartyActors.FindAll([](const CombatActor* actor)
            {
                return !actor->IsDead();
            }
        );

        return availableActors.Random();
    }

    return nullptr;
}

CombatActor* CombatScreen::GetRandomEnemyMember()
{
    if (!m_EnemyActors.IsEmpty())
    {
        TArray<CombatActor> availableActors = m_EnemyActors.FindAll([](const CombatActor* actor)
            {
                return !actor->IsDead();
            }
        );

        return availableActors.Random();
    }

    return nullptr;
}

bool CombatScreen::IsActorInParty(CombatActor* actor) const
{
    return m_PartyActors.Find([actor](const CombatActor* other)
        {
            return actor == other;
        }
    ) >= 0;
}

void CombatScreen::GetEnemyTarget(std::vector<CombatActor*>& targets)
{
    for (auto it = m_EnemyActors.Begin(); it != m_EnemyActors.End(); it++)
    {
        if (!(*it)->IsDead())
        {
            targets.push_back(*it);
        }
    }
}

void CombatScreen::GetPlayerTarget(std::vector<CombatActor*>& targets)
{
    for (auto it = m_PartyActors.Begin(); it != m_PartyActors.End(); it++)
    {
        if (!(*it)->IsDead())
        {
            targets.push_back(*it);
        }
    }
}

void CombatScreen::GetParty(std::vector<CombatActor*>& party)
{
    for (auto it = m_PartyActors.Begin(); it != m_PartyActors.End(); it++)
    {
        if (!(*it)->IsDead())
        {
            party.push_back(*it);
        }
    }
}

void CombatScreen::AddEffect(IEffect* effect)
{
    // I didn't sort the effect by priority.
    // For now, I don't know when one effect might be more a priority then another.
    m_EffectStack.PushBack(effect);
}

void CombatScreen::UpdateUI()
{
    std::vector<FCharacterDefinition*> partyDefinition = Party::Get().GetPartyDefinition();
    int tIndex = 0;
    for (FCharacterDefinition* definition : partyDefinition)
    {
        auto hp = static_cast<int>(definition->attributes.GetHealth());
        auto maxHp = static_cast<int>(definition->attributes.GetMaxHealthAttribute().GetValue());
        m_PartyProgressBars.At(tIndex)->SetInfo(hp, maxHp);
        tIndex++;
    }
}

bool CombatScreen::IsGameOver()
{
    return PartyWins() || EnemyWins();
}

void CombatScreen::InitializeUI()
{
    IGraphics& tGraphics = Game::Get().Graphics();

    int screenW = 0;
    int screenH = 0;
    tGraphics.GetScreenSize(&screenW, &screenH);

    ICombat& tCombat = CombatManager::Get();
    m_BgId = tCombat.GetBackgroundImage();
    //tGraphics.LoadTexture("textures/arena_background.png");

    float border = 6.0F;
    std::string panelImage = "gui/simple_panel.png";

    m_NamePanel.Initialize(panelImage, 600.0F, 200.0F, border);
    m_InfoPanel.Initialize(panelImage, screenW - 600.0F, 200.0F, border);
    m_NamesBox.SetPadding(5.0F, 5.0F);

    auto* nameText = new UIText();
    nameText->Initialize("fonts/junction.ttf", 24, 970.0F, 40.0F);
    nameText->SetText("NAME");
    nameText->SetColor(255, 255, 255, 255);
    nameText->SetPadding(10.0F, 5.0F);
    m_NamesBox.AddChild(nameText);

    auto* hpText = new UIText();
    hpText->Initialize("fonts/junction.ttf", 24, 100.0F, 40.0F);
    hpText->SetText("HP");
    hpText->SetColor(255, 255, 255, 255);
    hpText->SetPadding(10.0F, 5.0F);
    m_HpInfoBox.AddChild(hpText);
    m_HpInfoBox.SetPadding(5.0F, 5.0F);

    auto* mpText = new UIText();
    mpText->Initialize("fonts/junction.ttf", 24, 100.0F, 40.0F);
    mpText->SetText("MP");
    mpText->SetColor(255, 255, 255, 255);
    mpText->SetPadding(10.0F, 5.0F);
    m_MpInfoBox.AddChild(mpText);
    m_MpInfoBox.SetPadding(5.0F, 5.0F);

    std::vector<FCharacterDefinition*> partyDefinition = Party::Get().GetPartyDefinition();
    for (FCharacterDefinition* definition : partyDefinition)
    {
        auto* newText = new UIText();
        newText->Initialize("fonts/junction.ttf", 24, 970.0F, 45.0F);
        newText->SetText(definition->name);
        newText->SetColor(255, 255, 255, 255);
        newText->SetPadding(25.0F, 5.0F);
        newText->SetAlign(EHAlignContent::LEFT, EVAlignContent::MIDDLE);
        m_NamesBox.AddChild(newText);
        m_PartyNameTexts.PushBack(newText);

        auto* hpInfo = new UIProgressText();
        hpInfo->Initialize();

        auto hp = static_cast<int>(definition->attributes.GetHealth());
        auto maxHp = static_cast<int>(definition->attributes.GetMaxHealthAttribute().GetValue());
        hpInfo->SetInfo(hp, maxHp);
        hpInfo->SetPadding(25.0F, 2.0F);
        m_HpInfoBox.AddChild(hpInfo);
        m_PartyProgressBars.PushBack(hpInfo);

        auto* mpInfo = new UIProgressText();
        mpInfo->Initialize();

        auto mp = static_cast<int>(definition->attributes.GetMagic());
        auto maxMp = static_cast<int>(definition->attributes.GetMaxMagicAttribute().GetValue());
        mpInfo->SetInfo(mp, maxMp);
        mpInfo->SetPadding(25.0F, 2.0F);
        m_MpInfoBox.AddChild(mpInfo);
    }

    m_Separator.Initialize(150.0F, 50.0F);
    m_InfoHorizontal.AddChild(&m_HpInfoBox);
    m_InfoHorizontal.AddChild(&m_Separator);
    m_InfoHorizontal.AddChild(&m_MpInfoBox);
    //    m_InfoHorizontal.SetPadding(0.0F, 0.0F);
    m_InfoPanel.SetChild(&m_InfoHorizontal);
    m_NamePanel.SetChild(&m_NamesBox);
    m_BottomBox.AddChild(&m_NamePanel);
    m_BottomBox.AddChild(&m_InfoPanel);

    m_NoticePanel.Initialize(panelImage, screenW - 600.0F, 100.0F, border);
    m_NoticeText.Initialize("fonts/junction.ttf", 24, screenW - 600.0F, 90.0F);
    m_NoticeText.SetText("Notice");
    m_NoticeText.SetColor(255, 255, 255, 255);
    m_NoticeText.SetAlign(EHAlignContent::CENTER, EVAlignContent::MIDDLE);
    m_NoticePanel.SetChild(&m_NoticeText);

    m_TipPanel.Initialize(panelImage, static_cast<float>(screenW), 60.0F, border);
    m_TipText.Initialize("fonts/junction.ttf", 24, static_cast<float>(screenW), 50.0F);
    m_TipText.SetText("Tip");
    m_TipText.SetColor(255, 255, 255, 255);
    m_TipText.SetAlign(EHAlignContent::CENTER, EVAlignContent::MIDDLE);
    m_TipPanel.SetChild(&m_TipText);
}

void CombatScreen::ClearUI()
{
    IGraphics& tGraphics = Game::Get().Graphics();

    for (auto it = m_NamesBox.Begin(); it != m_NamesBox.End(); it++)
    {
        delete* it;
    }
    m_NamesBox.Clear();

    for (auto it = m_HpInfoBox.Begin(); it != m_HpInfoBox.End(); it++)
    {
        delete* it;
    }
    m_HpInfoBox.Clear();

    for (auto it = m_MpInfoBox.Begin(); it != m_MpInfoBox.End(); it++)
    {
        delete* it;
    }
    m_MpInfoBox.Clear();

    m_InfoHorizontal.Clear();
    m_BottomBox.Clear();
}

void CombatScreen::InitializeBattleStations()
{
    float startX = 1200.0F;
    float startY = 550.0F;
    float separation = 80.0F;
    float offset = 15.0F;

    for (int i = 0; i < 3; i++)
    {
        float battleX = startX + (i * offset);
        float battleY = startY + (i * separation);
        m_PartyBattleStations.emplace_back(battleX, battleY);
    }

    startX = 600.0F;
    for (int i = 0; i < 3; i++)
    {
        float battleX = startX - (i * offset);
        float battleY = startY + (i * separation);
        m_EnemyBattleStations.emplace_back(battleX, battleY);
    }
}

void CombatScreen::CreateCombatCharacters()
{
    std::vector<FCharacterDefinition*> partyMemberDefs = Party::Get().GetPartyDefinition();

    m_PartyActors.Clear();
    for (FCharacterDefinition* definition : partyMemberDefs)
    {
        size_t newID = Utils::GenerateID(definition->name);
        auto* partyCharacter = new Character(newID, definition->name);
        partyCharacter->Load(definition->data);
        partyCharacter->SetSize(128.0F, 128.0F);

        auto* newActor = new CombatActor();
        newActor->character = partyCharacter;
        newActor->definition = definition;
        m_PartyActors.PushBack(newActor);
    }

    BX_CHECKS(m_EnemyActors.IsEmpty(), "Combat already have enemies loaded");

    std::string goblinName = "Goblin";
    size_t goblin1Id = Utils::GenerateID(goblinName, 1);
    auto* goblin1 = new Character(goblin1Id, "Goblin1");
    goblin1->Load("characters/combatGoblin.xml");
    goblin1->SetSize(128.0F, 128.0F);

    auto* goblin1Def = new FCharacterDefinition();
    goblin1Def->name = "Goblin1";
    goblin1Def->portrait = "";
    goblin1Def->data = "characters/combatGoblin.xml";
    goblin1Def->attributes = AttributeSet(20.0F, 5.0F, 10.0F, 4.0F, 10.0F);
    goblin1Def->locked = false;

    auto* goblinActor1 = new CombatActor();
    goblinActor1->character = goblin1;
    goblinActor1->definition = goblin1Def;
    m_EnemyActors.PushBack(goblinActor1);

    size_t goblin2Id = Utils::GenerateID(goblinName, 2);
    auto* goblin2 = new Character(goblin2Id, "Goblin2");
    goblin2->Load("characters/combatGoblin.xml");
    goblin2->SetSize(128.0F, 128.0F);

    auto* goblin2Def = new FCharacterDefinition();
    goblin2Def->name = "Goblin2";
    goblin2Def->portrait = "";
    goblin2Def->data = "characters/combatGoblin.xml";
    goblin2Def->attributes = AttributeSet(20.0F, 5.0F, 10.0F, 4.0F, 10.0F);
    goblin2Def->locked = false;

    auto* goblinActor2 = new CombatActor();
    goblinActor2->character = goblin2;
    goblinActor2->definition = goblin2Def;
    m_EnemyActors.PushBack(goblinActor2);

    size_t goblin3Id = Utils::GenerateID(goblinName, 3);
    auto* goblin3 = new Character(goblin3Id, "Goblin3");
    goblin3->Load("characters/combatGoblin.xml");
    goblin3->SetSize(128.0F, 128.0F);

    auto* goblin3Def = new FCharacterDefinition();
    goblin3Def->name = "Goblin3";
    goblin3Def->portrait = "";
    goblin3Def->data = "characters/combatGoblin.xml";
    goblin3Def->attributes = AttributeSet(20.0F, 5.0F, 10.0F, 4.0F, 10.0F);
    goblin3Def->locked = false;

    auto* goblinActor3 = new CombatActor();
    goblinActor3->character = goblin3;
    goblinActor3->definition = goblin3Def;
    m_EnemyActors.PushBack(goblinActor3);
}

void CombatScreen::AddTurns()
{
    if (PartyWins() || EnemyWins())
    {
        auto* victory = new VictoryState(this);
        victory->Enter();
        m_CombatStateStack.PushBack(victory);
        return;
    }

    for (auto it = m_PartyActors.Begin(); it != m_PartyActors.End(); it++)
    {
        if (!(*it)->IsDead())
        {
            ICombatEvent* turnEvent = new CETurn((*it), true, this);
            float tp = turnEvent->GetTimePoints(&m_EventQueue);
            m_EventQueue.Add(turnEvent, tp);
        }
    }

    for (auto it = m_EnemyActors.Begin(); it != m_EnemyActors.End(); it++)
    {
        if (!(*it)->IsDead())
        {
            ICombatEvent* turnEvent = new CETurn((*it), false, this);
            float tp = turnEvent->GetTimePoints(&m_EventQueue);
            m_EventQueue.Add(turnEvent, tp);
        }
    }
}

bool CombatScreen::PartyWins()
{
    for (auto it = m_EnemyActors.Begin(); it != m_EnemyActors.End(); it++)
    {
        if (!(*it)->IsDead())
        {
            return false;
        }
    }

    return true;
}

bool CombatScreen::EnemyWins()
{
    for (auto it = m_PartyActors.Begin(); it != m_PartyActors.End(); it++)
    {
        if (!(*it)->IsDead())
        {
            return false;
        }
    }

    return true;
}

void CombatScreen::PlayVictoryFanfare()
{
    IAudio& tAudio = Game::Get().Audio();
    tAudio.StopMusic();
    m_AudioChannel = tAudio.PlayAudio(m_VictoryTheme, -1);
}

void CombatScreen::PlayDefeatSong()
{
    IAudio& tAudio = Game::Get().Audio();
    tAudio.StopMusic();
    m_AudioChannel = tAudio.PlayAudio(m_DefeatTheme, -1);
}

void CombatScreen::ShowNotification(const std::string& message)
{
    m_NoticeText.SetText(message);
    m_ShowNotice = true;
}
