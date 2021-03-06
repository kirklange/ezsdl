/*  EzGL/Control.cpp
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

#include "EzGL/Control.hpp"

#include "EzGL/Object.hpp"

#include <string>

namespace EzGL
{



void Control::init(Object &self, Object &main)
{
    // Initialize all inputes to (probably) false or 0
    for (nlohmann::json::iterator it = self.data["controls"].begin();
            it != self.data["controls"].end(); it++)
    {
        std::string key = it.key(), value = it.value();
        self.data["input"][key] = main.data["input"][value];
    }
}



void Control::update(Object &self, Object &main)
{
    // Fetch input inputes (same as init)
    for (nlohmann::json::iterator it = self.data["controls"].begin();
            it != self.data["controls"].end(); it++)
    {
        std::string key = it.key(), value = it.value();
        self.data["input"][key] = main.data["input"][value];
    }
}



}; /* namespace EzGL */
