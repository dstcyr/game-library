//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef GRAPHICS_SDLGRAPHICS_H
#define GRAPHICS_SDLGRAPHICS_H

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

struct FFont
{
    void* font = nullptr;
    std::vector<char> buffer;
};

class SDLGraphics : public IGraphics
{
public:
    bool Initialize() override;
    void GetScreenSize(int* width, int* height) override;
    void Shutdown() override;
    void Clear() override;
    void DrawImage(size_t id, const Rect<int>& src, const Rect<float>& dst, float angle, bool flipH, bool flipV, uint8_t r, uint8_t g, uint8_t b, uint8_t a) override;
    void DrawImage(size_t id, const Rect<int>& src, const Rect<float>& dst, uint8_t r, uint8_t g, uint8_t b, uint8_t a) override;
    void DrawImage(size_t id, const Rect<float>& dst, uint8_t r, uint8_t g, uint8_t b, uint8_t a) override;
    void DrawImage(size_t id, float x, float y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) override;
    void DrawImage(size_t id, uint8_t r, uint8_t g, uint8_t b, uint8_t a) override;
    void DrawLine(float x1, float y1, float x2, float y2, uint8_t r, uint8_t g, uint8_t b, uint8_t a) override;
    void DrawRect(float x, float y, float w, float h, uint8_t r, uint8_t g, uint8_t b, uint8_t a) override;
    void FillRect(float x, float y, float w, float h, uint8_t r, uint8_t g, uint8_t b, uint8_t a) override;
    void DrawCross(float x, float y, float size, uint8_t r, uint8_t g, uint8_t b, uint8_t a) override;
    void GetImageSize(size_t id, int* width, int* height) override;
    void GetTextSize(const std::string& text, size_t fontId, int* width, int* height) override;
    void DrawString(const std::string& text, size_t fontId, float x, float y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) override;
    void DrawString(const std::string& text, size_t fontId, float x, float y, int warp, uint8_t r, uint8_t g, uint8_t b, uint8_t a) override;
    void Present() override;
    void SetCameraLocation(float x, float y) override;
    void GetCameraLocation(float* x, float* y) override;
    void EnableCamera(bool enable) override;
    void ClearCache() override;

    size_t LoadTexture(const std::string& filename) override;
    size_t LoadFont(const std::string& filename, int fontSize) override;

private:
    SDL_Window* m_Window = nullptr;
    SDL_Renderer* m_Renderer = nullptr;
    int m_Width = 0;
    int m_Height = 0;
    std::map<size_t, SDL_Texture*> m_TextureCache;
    std::map<size_t, FFont*> m_FontCache;
    SDL_Texture* m_TextBuffer = nullptr;
    Rect<float> m_Viewport{ 0.0F, 0.0F, 0.0F, 0.0F };
    Rect<float> m_SavedViewport{ 0.0F, 0.0F, 0.0F, 0.0F };
};

#endif
