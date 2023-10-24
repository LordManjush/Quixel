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
            bool PrintInstruction = false;
            void Print(std::vector<Message> messages) {
                Message message;
                message.text = "Test";
                messages.push_back(message);
            }
        };
        struct Action {

            std::string name = "Empty";
            int TypeOfActionID = -1;
            const char* ActionTypes[4] = { "Start", "If", "End", "Update" };
            const char* LogicTypes[2] = { "Print", "Move"};
            int TypeOfLogicID = -1;
            bool OnStart = false;
            Logic logic;
        };
    }
}
