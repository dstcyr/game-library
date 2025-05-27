//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "graphics/SDLGraphics.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

bool SDLGraphics::Initialize(const std::string& title, int w, int h)
{
    std::string sdlVersion = std::to_string(SDL_MAJOR_VERSION) + "." + std::to_string(SDL_MINOR_VERSION) + "." + std::to_string(SDL_PATCHLEVEL);
    BX_LOG(ELogLevel::Log, "SDL " + sdlVersion);

    sdlVersion = std::to_string(SDL_IMAGE_MAJOR_VERSION) + "." + std::to_string(SDL_IMAGE_MINOR_VERSION) + "." + std::to_string(SDL_IMAGE_PATCHLEVEL);
    BX_LOG(ELogLevel::Log, "SDL_image " + sdlVersion);

    sdlVersion = std::to_string(SDL_TTF_MAJOR_VERSION) + "." + std::to_string(SDL_TTF_MINOR_VERSION) + "." + std::to_string(SDL_TTF_PATCHLEVEL);
    BX_LOG(ELogLevel::Log, "SDL_ttf " + sdlVersion);

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO) < 0)
    {
        return false;
    }

    // Fullscreen:
    // SDL_DisplayMode currentDisplayMode;
    // SDL_GetCurrentDisplayMode(0, &currentDisplayMode);
    // int windowWidth = currentDisplayMode.w;
    // int windowHeight = currentDisplayMode.h;
    int windowWidth = w;
    int windowHeight = h;

    m_Window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_UTILITY
        // SDL_WINDOW_FULLSCREEN_DESKTOP
    );

    if (m_Window == nullptr)
    {
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
    if (m_Renderer == nullptr)
    {
        return false;
    }

    m_Width = 1024;
    m_Height = 962;
    SDL_RenderSetLogicalSize(m_Renderer, m_Width, m_Height);

    if (TTF_Init() == -1)
    {
        return false;
    }

    SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);

    m_Viewport.Set(0.0F, 0.0F, static_cast<float>(m_Width), static_cast<float>(m_Height));
    m_SavedViewport.Set(0.0F, 0.0F, static_cast<float>(m_Width), static_cast<float>(m_Height));

#if !defined(_DEBUG)
    SDL_ShowCursor(SDL_DISABLE);
#endif

    return true;
}

void SDLGraphics::GetScreenSize(int* width, int* height)
{
    *width = m_Width;
    *height = m_Height;
}

void SDLGraphics::Shutdown()
{
    ClearCache();

    TTF_Quit();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

void SDLGraphics::Clear()
{
    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_Renderer);
}

void SDLGraphics::DrawLine(float x1, float y1, float x2, float y2, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    const int tX1 = static_cast<int>(x1 - m_Viewport.x);
    const int tY1 = static_cast<int>(y1 - m_Viewport.y);
    const int tX2 = static_cast<int>(x2 - m_Viewport.x);
    const int tY2 = static_cast<int>(y2 - m_Viewport.y);

    SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
    SDL_RenderDrawLine(m_Renderer, tX1, tY1, tX2, tY2);
}

void SDLGraphics::DrawRect(float x, float y, float w, float h, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    SDL_Rect rect = {
        static_cast<int>(x - m_Viewport.x),
        static_cast<int>(y - m_Viewport.y),
        static_cast<int>(w),
        static_cast<int>(h)
    };

    SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
    SDL_RenderDrawRect(m_Renderer, &rect);
}

void SDLGraphics::FillRect(float x, float y, float w, float h, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    SDL_Rect rect = {
        static_cast<int>(x - m_Viewport.x),
        static_cast<int>(y - m_Viewport.y),
        static_cast<int>(w),
        static_cast<int>(h)
    };

    SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
    SDL_RenderFillRect(m_Renderer, &rect);
}

void SDLGraphics::DrawCross(float x, float y, float size, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    float halfSize = size * 0.5F;
    DrawLine(x - halfSize, y, x + halfSize, y, r, g, b, a);
    DrawLine(x, y - halfSize, x, y + halfSize, r, g, b, a);
}

void SDLGraphics::DrawImage(size_t id, const Rect<int>& src, const Rect<float>& dst, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    if (id == 0)
    {
        return;
    }

    SDL_Rect srcRect = {
        static_cast<int>(src.x),
        static_cast<int>(src.y),
        static_cast<int>(src.width),
        static_cast<int>(src.height)
    };

    SDL_Rect dstRect = {
        static_cast<int>(dst.x - m_Viewport.x),
        static_cast<int>(dst.y - m_Viewport.y),
        static_cast<int>(dst.width),
        static_cast<int>(dst.height)
    };

    SDL_SetTextureColorMod(m_TextureCache[id], r, g, b);
    SDL_SetTextureAlphaMod(m_TextureCache[id], a);
    SDL_SetTextureBlendMode(m_TextureCache[id], SDL_BlendMode::SDL_BLENDMODE_BLEND);
    SDL_RenderCopyEx(m_Renderer, m_TextureCache[id], &srcRect, &dstRect, 0.0, nullptr, SDL_FLIP_NONE);
}

void SDLGraphics::DrawImage(size_t id, const Rect<float>& dst, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    if (id == 0)
    {
        return;
    }

    SDL_Rect dstRect = {
        static_cast<int>(dst.x - m_Viewport.x),
        static_cast<int>(dst.y - m_Viewport.y),
        static_cast<int>(dst.width),
        static_cast<int>(dst.height)
    };

    SDL_SetTextureColorMod(m_TextureCache[id], r, g, b);
    SDL_SetTextureAlphaMod(m_TextureCache[id], a);
    SDL_SetTextureBlendMode(m_TextureCache[id], SDL_BlendMode::SDL_BLENDMODE_BLEND);
    SDL_RenderCopy(m_Renderer, m_TextureCache[id], nullptr, &dstRect);
}

void SDLGraphics::DrawImage(size_t id, const Rect<int>& src, const Rect<float>& dst, float angle, bool flipH, bool flipV, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    if (id == 0)
    {
        return;
    }

    SDL_Rect srcRect = {
        static_cast<int>(src.x),
        static_cast<int>(src.y),
        static_cast<int>(src.width),
        static_cast<int>(src.height)
    };

    SDL_Rect dstRect = {
        static_cast<int>(dst.x - m_Viewport.x),
        static_cast<int>(dst.y - m_Viewport.y),
        static_cast<int>(dst.width),
        static_cast<int>(dst.height)
    };

    int flip = SDL_FLIP_NONE;
    if (flipH)
    {
        flip = SDL_FLIP_HORIZONTAL;
    }

    if (flipV)
    {
        flip |= SDL_FLIP_VERTICAL;
    }

    const auto renderFlip = static_cast<SDL_RendererFlip>(flip);
    SDL_SetTextureColorMod(m_TextureCache[id], r, g, b);
    SDL_SetTextureAlphaMod(m_TextureCache[id], a);
    SDL_SetTextureBlendMode(m_TextureCache[id], SDL_BlendMode::SDL_BLENDMODE_BLEND);
    SDL_RenderCopyEx(m_Renderer, m_TextureCache[id], &srcRect, &dstRect, angle, nullptr, renderFlip);
}

void SDLGraphics::DrawImage(size_t id, float x, float y, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    if (id == 0)
    {
        return;
    }

    SDL_Rect dstRect = {
        static_cast<int>(x - m_Viewport.x),
        static_cast<int>(y - m_Viewport.y),
        0, 0
    };

    GetImageSize(id, &dstRect.w, &dstRect.h);
    SDL_SetTextureColorMod(m_TextureCache[id], r, g, b);
    SDL_SetTextureAlphaMod(m_TextureCache[id], a);
    SDL_SetTextureBlendMode(m_TextureCache[id], SDL_BlendMode::SDL_BLENDMODE_BLEND);
    SDL_RenderCopy(m_Renderer, m_TextureCache[id], nullptr, &dstRect);
}

void SDLGraphics::DrawImage(size_t id, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    if (id == 0)
    {
        return;
    }

    if (m_TextureCache.count(id) > 0)
    {
        SDL_SetTextureColorMod(m_TextureCache[id], r, g, b);
        SDL_SetTextureAlphaMod(m_TextureCache[id], a);
        SDL_SetTextureBlendMode(m_TextureCache[id], SDL_BlendMode::SDL_BLENDMODE_BLEND);
        SDL_RenderCopy(m_Renderer, m_TextureCache[id], nullptr, nullptr);
    }
}

void SDLGraphics::GetImageSize(size_t id, int* width, int* height)
{
    if (id == 0)
    {
        *width = 0;
        *height = 0;
        return;
    }

    if (m_TextureCache.count(id) > 0)
    {
        SDL_QueryTexture(m_TextureCache[id], nullptr, nullptr, width, height);
    }
    else
    {
        *width = 0;
        *height = 0;
    }
}

void SDLGraphics::GetTextSize(const std::string& text, size_t fontId, int* width, int* height)
{
    if (fontId == 0)
    {
        return;
    }

    if (m_FontCache.count(fontId) > 0)
    {
        FFont* fontData = m_FontCache[fontId];
        auto* font = static_cast<TTF_Font*>(fontData->font);
        TTF_SizeText(font, text.c_str(), width, height);
    }
    else
    {
        *width = 0;
        *height = 0;
    }
}

void SDLGraphics::DrawString(const std::string& text, size_t fontId, float x, float y, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    if (text.empty())
    {
        return;
    }

    if (fontId <= 0)
    {
        return;
    }

    FFont* fontData = m_FontCache[fontId];
    auto* font = static_cast<TTF_Font*>(fontData->font);
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), { 255, 255, 255, 255 });
    SDL_Rect dstRect = {
        static_cast<int>(x - m_Viewport.x),
        static_cast<int>(y - m_Viewport.y),
        surface->w,
        surface->h
    };

    m_TextBuffer = SDL_CreateTextureFromSurface(m_Renderer, surface);

    SDL_SetTextureColorMod(m_TextBuffer, r, g, b);
    SDL_SetTextureAlphaMod(m_TextBuffer, a);
    SDL_SetTextureBlendMode(m_TextBuffer, SDL_BlendMode::SDL_BLENDMODE_BLEND);

    SDL_RenderCopy(m_Renderer, m_TextBuffer, nullptr, &dstRect);
    SDL_FreeSurface(surface);
}

void SDLGraphics::DrawString(const std::string& text, size_t fontId, float x, float y, int warp, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    if (text.empty())
    {
        return;
    }

    if (fontId == 0)
    {
        return;
    }

    FFont* fontData = m_FontCache[fontId];
    if (fontData != nullptr)
    {
        auto* font = static_cast<TTF_Font*>(fontData->font);
        SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), { 255, 255, 255, 255 }, warp);
        SDL_Rect dstRect = {
            static_cast<int>(x - m_Viewport.x),
            static_cast<int>(y - m_Viewport.y),
            surface->w,
            surface->h
        };

        m_TextBuffer = SDL_CreateTextureFromSurface(m_Renderer, surface);
        SDL_SetTextureColorMod(m_TextBuffer, r, g, b);
        SDL_SetTextureAlphaMod(m_TextBuffer, a);
        SDL_SetTextureBlendMode(m_TextBuffer, SDL_BlendMode::SDL_BLENDMODE_BLEND);
        SDL_RenderCopy(m_Renderer, m_TextBuffer, nullptr, &dstRect);
        SDL_FreeSurface(surface);
    }
}

void SDLGraphics::Present()
{
    SDL_RenderPresent(m_Renderer);
}

void SDLGraphics::SetCameraLocation(float x, float y)
{
    m_Viewport.x = x;
    m_Viewport.y = y;
    m_SavedViewport.Set(m_Viewport);
}

void SDLGraphics::GetCameraLocation(float* x, float* y)
{
    *x = m_Viewport.x;
    *y = m_Viewport.y;
}

void SDLGraphics::EnableCamera(bool enable)
{
    if (enable)
    {
        m_Viewport.Set(m_SavedViewport);
    }
    else
    {
        m_Viewport.Set(0.0F, 0.0F, 0.0F, 0.0F);
    }
}

void SDLGraphics::ClearCache()
{
    for (auto keyPair : m_TextureCache)
    {
        SDL_DestroyTexture(keyPair.second);
    }

    m_TextureCache.clear();

    for (auto keyPair : m_FontCache)
    {
        auto* font = static_cast<TTF_Font*>(keyPair.second->font);
        TTF_CloseFont(font);
        delete keyPair.second;
    }

    m_FontCache.clear();
}

size_t SDLGraphics::LoadTexture(const std::string& filename)
{
    const size_t textureID = std::hash<std::string>()(filename);
    if (m_TextureCache.count(textureID) > 0)
    {
        return textureID;
    }

    IResources& tResources = Game::Get().Resources();

    std::vector<char> rawData = tResources.LoadData(filename);
    if (!rawData.empty())
    {
        SDL_RWops* rWops = SDL_RWFromMem(const_cast<char*>(rawData.data()), static_cast<int>(rawData.size()));
        if (rWops == nullptr)
        {
            std::string sdlError = SDL_GetError();
            BX_LOG(ELogLevel::Error, "SDL_RWFromMem failed: " + sdlError);
            return 0;
        }

        SDL_Texture* texture = IMG_LoadTexture_RW(m_Renderer, rWops, 0);
        if (texture == nullptr)
        {
            std::string sdlError = IMG_GetError();
            BX_LOG(ELogLevel::Error, "IMG_LoadTexture_RW failed: " + sdlError);
            return 0;
        }

        m_TextureCache.emplace(textureID, texture);
        return textureID;
    }

    BX_LOG(ELogLevel::Error, "Cannot load: " + filename);
    return 0;
}

size_t SDLGraphics::LoadFont(const std::string& filename, int fontSize)
{
    const size_t fontID = std::hash<std::string>()(filename + std::to_string(fontSize));
    if (m_FontCache.count(fontID) > 0)
    {
        return fontID;
    }

    IResources& tResources = Game::Get().Resources();

    auto* newFont = new FFont();
    newFont->buffer = tResources.LoadData(filename);
    if (!newFont->buffer.empty())
    {
        SDL_RWops* rWops = SDL_RWFromMem(const_cast<char*>(newFont->buffer.data()), static_cast<int>(newFont->buffer.size()));
        if (rWops == nullptr)
        {
            std::string sdlError = SDL_GetError();
            BX_LOG(ELogLevel::Error, "SDL_RWFromMem failed: " + sdlError);
            return 0;
        }

        newFont->font = TTF_OpenFontIndexRW(rWops, 1, fontSize, 0);
        if (newFont->font == nullptr)
        {
            std::string sdlError = TTF_GetError();
            BX_LOG(ELogLevel::Error, "TTF_OpenFontRW failed: " + sdlError);
            return 0;
        }

        m_FontCache.emplace(fontID, newFont);
        return fontID;
    }

    return 0;
}
