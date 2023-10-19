#pragma once
#include <imnodes.h>
#include <vector>

namespace Quixel {
    namespace BluePrints
    {
        struct OutPut {
            int id;
            float In;
        };
        struct BaseNode {
            int id;
            float Out;
            float In;
        };
        struct Link
        {
            int id;
            int start_attr, end_attr;
        };
        struct BluePrintEditor {
            std::vector<BaseNode>     nodes;
            std::vector<Link>     links;
            int LastID;
            void Start();
        };
    }
}
