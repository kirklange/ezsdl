/*  EzSDL/WindowRenderComponent.cpp
 *
 *  Copyright (c) 2018 Kirk Lange <github.com/kirklange>
 *
 *  This software is provided 'as-is', without any express or implied
 *  warranty. In no event will the authors be held liable for any damages
 *  arising from the use of this software.
 *
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute it
 *  freely, subject to the following restrictions:
 *
 *  1. The origin of this software must not be misrepresented; you must not
 *     claim that you wrote the original software. If you use this software
 *     in a product, an acknowledgment in the product documentation would be
 *     appreciated but is not required.
 *  2. Altered source versions must be plainly marked as such, and must not be
 *     misrepresented as being the original software.
 *  3. This notice may not be removed or altered from any source distribution.
 */

#include "EzSDL/WindowRenderComponent.hpp"

#include "EzSDL/Object.hpp"

#include <SDL2/SDL_render.h>

namespace EzSDL
{



void WindowRenderComponent::initImpl(Object &object, Window const &window)
{
}



void WindowRenderComponent::updateImpl(Object &object, SDL_Renderer *renderer)
{
    SDL_RenderPresent(renderer);

    // For some reason need to disable this when doing Emscripten
#ifndef __EMSCRIPTEN__
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);
#endif
}



}; /* namespace EzSDL */
