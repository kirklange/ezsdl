/*  EzSDL/WindowLogicComponent.hpp
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

#ifndef EZSDL_WINDOWLOGICCOMPONENT_HPP
#define EZSDL_WINDOWLOGICCOMPONENT_HPP

/** @file       EzSDL/WindowLogicComponent.hpp
 *  @brief      Lorem ipsum
 *  @details    Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 */

#include "EzSDL/LogicComponent.hpp"



namespace EzSDL
{

typename Component::Key const WindowLogicComponentID = 2;

/** @brief      Lorem ipsum
 *  @details    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do
 *              eiusmod tempor incididunt ut labore et dolore magna aliqua.
 */
class WindowLogicComponent : public LogicComponent<WindowLogicComponent>
{
public:
    WindowLogicComponent() = default;
    virtual ~WindowLogicComponent() = default;

    void initImpl(Object &object, Window const &window);
    void updateImpl(Object &object, double const &delta);

protected:

private:
    WindowLogicComponent(WindowLogicComponent const &other);
    WindowLogicComponent& operator=(WindowLogicComponent const &other);

    // TODO: const these first two if init at ctor?
    bool enableVSync;
    double deltaCeil;
    unsigned long lastFrame;
};


}; /* namespace EzSDL */



#endif /* EZSDL_WINDOWLOGICCOMPONENT_HPP */