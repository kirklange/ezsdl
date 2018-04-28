/*  pong_paddle.c
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

#define PADDLE_VELOCITY 10

#include "EzSDL/ezsdl_window.h"
#include "EzUtil/ezutil_observer.h"
#include "pong_paddle.h"

#include <stdio.h>




pong_paddle* pong_paddle_new(uint16_t keyUp, uint16_t keyDown,
        SDL_Color *color, ezsdl_window *window)
{
    pong_paddle *self = (pong_paddle*) malloc(sizeof(pong_paddle));
    self->x = self->y = self->dy = self->score = 0;
    self->w = window->displayMode->w * 0.01;
    self->h = window->displayMode->h * 0.1;
    self->keyUp = keyUp;
    self->keyDown = keyDown;
    self->color = color;
    self->window = window;

    ezutil_observer_add(window->headEvent, &pong_paddle_event, self);
    ezutil_observer_add(window->headUpdate, &pong_paddle_update, self);
    ezutil_observer_add(window->headDraw, &pong_paddle_draw, self);

    return self;
}



uint8_t pong_paddle_event(pong_paddle *self)
{
    if (self)
    {
        SDL_Event e = *(self->window->event);

        switch (e.type)
        {
            case SDL_KEYDOWN:
                if (e.key.keysym.scancode == self->keyUp)
                    self->dy = -PADDLE_VELOCITY;
                else if (e.key.keysym.scancode == self->keyDown)
                    self->dy = PADDLE_VELOCITY;
                break;
            case SDL_KEYUP:
                if (e.key.keysym.scancode == self->keyUp ||
                        e.key.keysym.scancode == self->keyDown)
                    self->dy = 0;
                break;
        }

        return 1;
    }
    else
    {
        /* TODO: error handling */
        return 0;
    }
}



uint8_t pong_paddle_update(pong_paddle *self)
{
    if (self)
    {
        self->y += self->dy;

        if (self->y < 0) self->y = 0;
        else if (self->y + self->h > self->window->displayMode->h)
            self->y = self->window->displayMode->h - self->h;

        snprintf(self->scoreStr, 8, "%i", self->score);
    }
    else
    {
        /* TODO: error handling */
        return 0;
    }
}



uint8_t pong_paddle_draw(pong_paddle *self)
{
    if (self)
    {
        ezsdl_window_drawRect(self->window, self->color, self->x, self->y,
                self->w, self->h);
        return 1;
    }
    else
    {
        /* TODO: error handling */
        return 0;
    }
}
