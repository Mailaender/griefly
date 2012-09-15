#include "Screen.h"

#include <assert.h>

#include <SDL.h>
#include <SDL_opengl.h>

Screen::Screen(unsigned int x, unsigned int y, bool fullscreen)
{
    fail_ = true;
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return;

    auto flag = SDL_FULLSCREEN;
    if(!fullscreen)
        flag = 0;
    screen_ = SDL_SetVideoMode(x, y, 32, SDL_OPENGL | flag);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, x, y, 0, -1, 1); // TODO: check
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
  
    glClearColor(0, 0, 0, 0);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

#ifdef WIN32
    typedef BOOL (WINAPI *PFNWGLSWAPINTERVALEXTPROC)(int);
    PFNWGLSWAPINTERVALEXTPROC wglSwapInterval = nullptr;

    wglSwapInterval = reinterpret_cast<PFNWGLSWAPINTERVALEXTPROC>(wglGetProcAddress("wglSwapIntervalEXT"));
    if (wglSwapInterval) 
        wglSwapInterval(1);
#endif

    fail_ = false;
}

void Screen::Swap()
{
    SDL_GL_SwapBuffers();
}

void Screen::Draw(const ApproxGLImage* sprite, int x_ul, int y_ul, int x_dr, int y_dr)
{
    if (sprite == nullptr)
        return;

    glColor4f(1, 1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, sprite->GetText());
    if (glGetError())
        SYSTEM_STREAM << glGetError() << std::endl; 

    float text_x = sprite->GetX();
    float text_y = sprite->GetY();

    glBegin(GL_QUADS);
        glTexCoord2f(0.0,       0.0);     glVertex2f(static_cast<float>(x_ul), static_cast<float>(y_ul));
        glTexCoord2f(0.0,    text_y);     glVertex2f(static_cast<float>(x_ul), static_cast<float>(y_dr));
        glTexCoord2f(text_x, text_y);     glVertex2f(static_cast<float>(x_dr), static_cast<float>(y_dr));
        glTexCoord2f(text_x,    0.0);     glVertex2f(static_cast<float>(x_dr), static_cast<float>(y_ul));
    glEnd();
    if (glGetError())
        SYSTEM_STREAM << glGetError() << std::endl; 
}

void Screen::Draw(const GLSprite* sprite_in, int x, int y, int imageW, int imageH)
{
    if (sprite_in == nullptr)
        return;
    const GLSprite& sprite = *sprite_in;

    glColor4f(1, 1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, sprite[imageH][imageW]);
    if (glGetError())
        SYSTEM_STREAM << glGetError() << std::endl; 

    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);     glVertex2f(static_cast<float>(x),              static_cast<float>(y));
        glTexCoord2f(0.0, 1.0);     glVertex2f(static_cast<float>(x),              static_cast<float>(y + sprite.H()));
        glTexCoord2f(1.0, 1.0);     glVertex2f(static_cast<float>(x + sprite.W()), static_cast<float>(y + sprite.H()));
        glTexCoord2f(1.0, 0.0);     glVertex2f(static_cast<float>(x + sprite.W()), static_cast<float>(y));
    glEnd();
    //glDisable(GL_TEXTURE_2D);
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_BLEND);
    if (glGetError())
        SYSTEM_STREAM << glGetError() << std::endl; 

}