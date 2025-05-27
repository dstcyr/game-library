//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef GRAPHICS_IGRAPHICS_H
#define GRAPHICS_IGRAPHICS_H

#include "maths/Rect.h"

class IGraphics
{
public:
    virtual ~IGraphics() = default;
    virtual bool Initialize(const std::string& title, int w, int h) = 0;
    virtual void GetScreenSize(int* width, int* height) = 0;
    virtual void Shutdown() = 0;
    virtual void Clear() = 0;
    virtual void DrawImage(size_t id, const Rect<int>& src, const Rect<float>& dst, float angle, bool flipH, bool flipV, uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;
    virtual void DrawImage(size_t id, const Rect<int>& src, const Rect<float>& dst, uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;
    virtual void DrawImage(size_t id, const Rect<float>& dst, uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;
    virtual void DrawImage(size_t id, float x, float y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;
    virtual void DrawImage(size_t id, uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;
    virtual void DrawLine(float x1, float y1, float x2, float y2, uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;
    virtual void DrawRect(float x, float y, float w, float h, uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;
    virtual void FillRect(float x, float y, float w, float h, uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;
    virtual void DrawCross(float x, float y, float size, uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;
    virtual void GetImageSize(size_t id, int* width, int* height) = 0;
    virtual void GetTextSize(const std::string& text, size_t fontId, int* width, int* height) = 0;
    virtual void DrawString(const std::string& text, size_t fontId, float x, float y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;
    virtual void DrawString(const std::string& text, size_t fontId, float x, float y, int warp, uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;
    virtual void Present() = 0;
    virtual void SetCameraLocation(float x, float y) = 0;
    virtual void GetCameraLocation(float* x, float* y) = 0;
    virtual void EnableCamera(bool enable) = 0;
    virtual void ClearCache() = 0;

    virtual size_t LoadTexture(const std::string& filename) = 0;
    virtual size_t LoadFont(const std::string& filename, int fontSize) = 0;
};

#endif
