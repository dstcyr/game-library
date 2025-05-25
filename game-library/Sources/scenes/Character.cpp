//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "scenes/Character.h"
#include "properties/MapPropertyCollection.h"
#include "controllers/Controller.h"
#include "save/BufferedFile.h"
#include "maps/Tilemap.h"

Entity* Character::Create(const MapPropertyCollection& definition, Tilemap* map)
{
    const std::string name = definition.GetObjectName();
    const std::string mapName = map->GetName();
    const int idOnTheMap = definition.GetIDOnTheMap();
    size_t instID = Utils::GenerateID(mapName + name, idOnTheMap);

    auto* newCharacter = new Character(instID, name);
    newCharacter->SetParentMap(map);

    std::string filename = definition.GetString("File");
    newCharacter->Load(filename);

    float wX = 0.0F;
    float wY = 0.0F;
    int lX = 0;
    int lY = 0;
    definition.GetLocalLocation(&lX, &lY);

    Blackboard* tBB = newCharacter->GetBlackboard();
    tBB->targetX = definition.GetInt("TargetX");
    tBB->targetY = definition.GetInt("TargetY");
    tBB->startX = lX;
    tBB->startY = lY;

    IWorld& tWorld = Game::Get().World();
    newCharacter->SetLocalLocation(lX, lY);
    map->GetTransform().GetTileFoot(lX, lY, &wX, &wY, 32, 48);
    newCharacter->SetWorldLocation(wX, wY);
    newCharacter->SetSize(32, 48);

    std::string frame = definition.GetString("Frame", "down");
    newCharacter->SetAnimationFrame(frame);
    return newCharacter;
}

Character::Character(size_t instId, const std::string& name) :
    Entity(instId, name)
{
}

bool Character::Load(const std::string& filename)
{
    IResources& tResource = Game::Get().Resources();

    m_Controller.Initialize(this);

    tinyxml2::XMLDocument tDoc;
    std::vector<char> xmlFile = tResource.LoadData(filename);
    if (xmlFile.empty())
    {
        BX_LOG(ELogLevel::Error, filename + " is empty or not found");
        return false;
    }

    std::string xmlText(xmlFile.begin(), xmlFile.end());
    if (tDoc.Parse(xmlText.c_str()) == tinyxml2::XML_SUCCESS)
    {
        tinyxml2::XMLNode* characterNode = tDoc.FirstChild();
        tinyxml2::XMLNode* definitionNode = characterNode->FirstChild();

        while (definitionNode != nullptr)
        {
            std::string nodeValue = definitionNode->Value();

            if (nodeValue == "clips")
            {
                LoadClips(definitionNode);
            }
            else if (nodeValue == "controllers")
            {
                LoadControllers(definitionNode);
            }

            definitionNode = definitionNode->NextSibling();
        }

        return true;
    }

    BX_LOG(ELogLevel::Error, tDoc.ErrorStr());
    return false;
}

bool Character::ProcessInput(float dt)
{
    return m_Controller.ProcessInput(dt);
}

void Character::Update(float dt)
{
    m_AnimatedSprite.Update(dt);
    m_Controller.Update(dt);

    for (auto it = m_Children.Begin(); it != m_Children.End(); it++)
    {
        (*it)->Update(dt);
    }
}

void Character::Draw()
{
    m_AnimatedSprite.Draw(m_Bounds.x, m_Bounds.y, 0.0F);

    for (auto it = m_Children.Begin(); it != m_Children.End(); it++)
    {
        (*it)->Draw(m_Bounds.x, m_Bounds.y);
    }

#if defined(DEBUG_BATTLE_POSITIONS)
    IGraphics& tGraphics = Game::Get().Graphics();
    tGraphics.DrawRect(m_Bounds.x, m_Bounds.y, m_Bounds.width, m_Bounds.height, 255, 0, 0, 255);
    tGraphics.DrawLine(m_Bounds.x - 500.0F, m_Bounds.y + m_Bounds.height / 2.0F, m_Bounds.x + 500.0F, m_Bounds.y + m_Bounds.height / 2.0F, 255, 0, 0, 255);
#endif
}

void Character::Draw(float x, float y)
{
    m_AnimatedSprite.Draw(m_Bounds.x + x, m_Bounds.y + y, 0.0F);
}

void Character::Interact()
{
    BX_LOG(ELogLevel::Log, "Interacting with character \"" + GetName() + "\"");
    m_ParentMap->DestroyEntity(this);
}

void Character::Save(BufferedFile* saveFile)
{
    saveFile->WriteUInt64(m_InstanceId);
    saveFile->WriteInt32(m_MapX);
    saveFile->WriteInt32(m_MapY);

    std::string clipName = m_AnimatedSprite.GetCurrentClipName();
    saveFile->WriteString(clipName);
}

void Character::Load(BufferedFile* saveFile)
{
    size_t id = 0;
    saveFile->ReadUInt64(&id);

    if (id != m_InstanceId)
    {
        BX_LOG(ELogLevel::Warning, "Trying to load a character but the id are incorrect");
        return;
    }

    int mapX = 0;
    int mapY = 0;
    saveFile->ReadInt32(&mapX);
    saveFile->ReadInt32(&mapY);

    std::string clipName;
    saveFile->ReadString(clipName);
    if (!clipName.empty())
    {
        m_AnimatedSprite.SetFrame(clipName);
    }

    IWorld& tWorld = Game::Get().World();
    SetLocalLocation(mapX, mapY);

    float worldX = 0.0F;
    float worldY = 0.0F;
    m_ParentMap->GetTransform().GetTileFoot(mapX, mapY, &worldX, &worldY, 32, 48);
    SetWorldLocation(worldX, worldY);
}

EDirection Character::GetDirection() const
{
    const std::string& clipName = m_AnimatedSprite.GetCurrentClipName();
    if (clipName == "up") { return EDirection::e_Up; }
    if (clipName == "left") { return EDirection::e_Left; }
    if (clipName == "right") { return EDirection::e_Right; }

    return EDirection::e_Down;
}

void Character::Clear()
{
    m_Controller.Clear();
}

void Character::PlayAnimation(const std::string& clipName, bool bLoop, bool bHoldLast)
{
    m_AnimatedSprite.Play(clipName, bLoop, bHoldLast);
}

void Character::PlayAnimationOnce(const std::string& clipName, const std::function<void()>& callback)
{
    m_AnimatedSprite.PlayOnce(clipName, callback);
}

void Character::StopAnimation()
{
    m_AnimatedSprite.Stop();
}

std::string Character::GetCurrentClipName()
{
    return m_AnimatedSprite.GetCurrentClipName();
}

void Character::SetAnimationFrame(const std::string& clipName)
{
    m_AnimatedSprite.SetFrame(clipName);
}

bool Character::IsLooping() const
{
    return m_AnimatedSprite.IsLooping();
}

void Character::PauseControls()
{
    m_Controller.Pause();
    m_AnimatedSprite.Stop();
}

void Character::ResumeControls()
{
    m_Controller.Resume(m_DefaultControllerState);
}

void Character::SetController(const std::string& controllerName)
{
    m_Controller.Set(controllerName);
}

void Character::SetColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
    m_AnimatedSprite.SetColor(red, green, blue, alpha);
}

void Character::SetState(const std::string& stateName)
{
    m_Controller.Set(stateName);
}

void Character::LoadClips(tinyxml2::XMLNode* node)
{
    tinyxml2::XMLNode* clipNode = node->FirstChild();
    tinyxml2::XMLElement* definitionElement = node->ToElement();
    const int rowSize = definitionElement->IntAttribute("rowsize");
    const int frameWidth = definitionElement->IntAttribute("framewidth");
    const int frameHeight = definitionElement->IntAttribute("frameheight");
    const char* defaultFrame = definitionElement->Attribute("default");
    const char* image = definitionElement->Attribute("image");

    m_AnimatedSprite.Load(image);
    m_AnimatedSprite.Init(rowSize, frameWidth, frameHeight);

    while (clipNode != nullptr)
    {
        tinyxml2::XMLElement* clipElement = clipNode->ToElement();
        const char* name = clipElement->Attribute("name");
        const int start = clipElement->IntAttribute("start");
        const int count = clipElement->IntAttribute("count");
        const float delay = clipElement->FloatAttribute("delay");
        m_AnimatedSprite.AddClip(name, start, count, delay);

        clipNode = clipNode->NextSibling();
    }

    if (defaultFrame != nullptr)
    {
        m_AnimatedSprite.SetFrame(defaultFrame);
    }
}

void Character::LoadControllers(tinyxml2::XMLNode* definitionNode)
{
    tinyxml2::XMLNode* controllerNode = definitionNode->FirstChild();
    tinyxml2::XMLElement* definitionElement = definitionNode->ToElement();
    const char* firstState = definitionElement->Attribute("default");
    m_DefaultControllerState = firstState != nullptr ? firstState : "";

    IWorld& tWorld = Game::Get().World();
    while (controllerNode != nullptr)
    {
        tinyxml2::XMLElement* controllerElement = controllerNode->ToElement();
        const char* controllerName = controllerElement->Attribute("name");
        const char* nextValue = controllerElement->Attribute("next");

        if (controllerName != nullptr)
        {
            std::string nextState = (nextValue != nullptr) ? nextValue : "";
            ControllerState* newController = tWorld.CreateController(controllerName, nextState);
            if (newController != nullptr)
            {
                m_Controller.Add(controllerName, newController);
            }
        }

        controllerNode = controllerNode->NextSibling();
    }

    if (!m_DefaultControllerState.empty())
    {
        m_Controller.Set(m_DefaultControllerState);
    }
}

