/*  ezsdl_window.c
 *
 *  <!---------
 *  Copyright (c) 2018 Kirk Lange
 *  
 *  This software is provided 'as-is', without any express or implied
 *  warranty.  In no event will the authors be held liable for any damages
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
 *  ---------->
 */

#include "EzSDL/ezsdl_window.h"
#include "EzUtil/ezutil_observer.h"
#include "EzUtil/ezutil_log.h"

#include <SDL2/SDL_image.h>



/* Anonymous window event handler function. */
void ezsdl_window_event(ezsdl_window *self);



ezsdl_window* ezsdl_window_new()
{
    ezsdl_window *self = (ezsdl_window*) malloc(sizeof(ezsdl_window));
    uint8_t error = 0;

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    SDL_GetDesktopDisplayMode(0, &self->displayMode);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    
    self->window = SDL_CreateWindow( "EzSDL",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            640, 480,
            SDL_WINDOW_SHOWN );

    self->renderer = SDL_CreateRenderer( self->window,
            -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    SDL_SetRenderDrawColor(self->renderer, 0x00, 0x00, 0xFF, 0xFF);

    self->event = (SDL_Event*) malloc(sizeof(SDL_Event));
    self->eventObsHead = (ezutil_observer*) malloc(sizeof(ezutil_observer));
    self->eventObsHead->prev = 0;
    self->eventObsHead->next = 0;
    self->eventObsHead->notify = &ezsdl_window_event;
    self->isRunning = 1;
    self->isPaused = 0;


    if (error)
    {
        ezutil_log(FATAL, __func__, "Failed to create ezsdl_window instance.");
        free(self);
        self = 0;
    }
    else
    {
        ezutil_log(DEBUG, __func__, "Successfully created new ezsdl_window "
                "instance.");
    }

    return self;
}



uint8_t ezsdl_window_del(ezsdl_window **self)
{
    if (*self)
    {
        SDL_DestroyRenderer((*self)->renderer);
        SDL_DestroyWindow((*self)->window);
        IMG_Quit();
        SDL_Quit();

        free((*self)->event);
        ezutil_observer_removeAll((*self)->eventObsHead);
        free(*self);
        *self = 0;

        return 1;
    }
    else
    {
        ezutil_log(VITAL, __func__, "Skipped deletion of ezsdl_window "
                "instance. Cannot free a null pointer.");
        return 0;
    }

}



uint8_t ezsdl_window_pollEvent(ezsdl_window *self)
{
    if (self)
    {
        while (SDL_PollEvent(self->event))
        {
            ezutil_observer_notifyAll(self->eventObsHead, self);
        }

        return 1;
    }
    else
    {
        ezutil_log(MAJOR, __func__, "Skipped event polling. Reference to "
                "self is null.");
        return 0;
    }
}



uint8_t ezsdl_window_clear(ezsdl_window *self)
{
    /* TODO: add error checking */

    /* TODO: For now it's obnoxious and bright blue so that it's obvious
     * when the bare background is exposed. Replace later with black. */
    SDL_SetRenderDrawColor(self->renderer, 0x00, 0x00, 0xFF, 0xFF);
    SDL_RenderClear(self->renderer);
}



uint8_t ezsdl_window_render(ezsdl_window *self)
{
    /* TODO: add error checking */

    SDL_RenderPresent(self->renderer);
}



void ezsdl_window_event(ezsdl_window *self)
{
    /* TODO: add error checking */

    SDL_Event e = *(self->event);

    /* Internal event handling */
    switch (e.type)
    {
        case SDL_QUIT:
            self->isRunning = 0;
            break;

        case SDL_KEYDOWN:
            switch (e.key.keysym.scancode)
            {
                case SDL_SCANCODE_ESCAPE:
                    self->isRunning = 0;
                    break;

                default:
                    break;
            }
            break;

        case SDL_KEYUP:
            break;

        case SDL_WINDOWEVENT:
            switch (e.window.event)
            {
                /* Pause app if lost keyboard focus (like tab out) */
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                    self->isPaused = 0;
                    break;
                case SDL_WINDOWEVENT_FOCUS_LOST:
                    self->isPaused = 1;
                    break;
            }
            break;

        default:
            break;
    }
}
