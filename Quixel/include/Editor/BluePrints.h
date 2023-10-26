#pragma once
#include <vector>
#include <chrono>
#include <cmath>
#include <imgui.h>
#include "Console.h"

namespace Quixel
{
    namespace BluePrints 
    {
        struct Logic {
            
        };
        struct Action {

            std::string name = "Empty";
            int TypeOfActionID = -1;
            const char* ActionTypes[5] = { "Start", "KeyPressed", "KeyDown", "KeReleased", "Forever"};
            const char* LogicTypes[12] = { 
                "Print", 
                "Move X",
                "Move Y", 
                "Change Scale by X", 
                "Change Scale by Y", 
                "Rotate",
                "Set Color",
                "Set Scale X",
                "Set Scale Y",
                "Set Position X",
                "Set Position Y",
                "Set Rotation"
            };
            float CodeColor[3] = { (float)255 / 255, (float)255 / 255, (float)255 / 255 };
            float CodeOpacity = 255;
            std::string PrintCode = "Simple Message";
            int TypeOfLogicID = -1;
            float StepData = 0;
            void SetUpAllKeys();
            const char* KeyTypes[36] = { 
                "A",
                "B", 
                "C",
                "D", 
                "E", 
                "F", 
                "G",
                "H",
                "I",
                "J",
                "K",
                "L", 
                "M", 
                "N", 
                "O",
                "P",
                "Q",
                "R",
                "S",
                "T",
                "U",
                "V",
                "W",
                "X", 
                "Y",
                "Z", 
                "Space",
                "Left Shift",
                "Right Shift",
                "Right Control",
                "Left Control",
                "Tab",
                "Enter",
                "Caps Lock",
                "Escape",
                "BackSpace"
            };
            int KeyID = -1;
            ImGuiKey keyCode;
        };
    }
}
