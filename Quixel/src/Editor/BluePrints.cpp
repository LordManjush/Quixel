#include "Editor/BluePrints.h"
#include <imgui.h>
#include <string>
Quixel::BluePrints::OutPut node;
void Quixel::BluePrints::BluePrintEditor::Start()
{
	imnodes::BeginNodeEditor();
    node.id = -1;
    imnodes::BeginNode(node.id);
    imnodes::BeginNodeTitleBar();
    ImGui::TextUnformatted("Output");
    imnodes::EndNodeTitleBar();

    imnodes::BeginInputAttribute(node.id >> 1);
    ImGui::TextUnformatted("input");
    imnodes::EndInputAttribute();
    ImGui::Text(std::to_string(node.In).c_str());
    imnodes::EndNode();
    for (BaseNode& node : nodes)
    {
        imnodes::BeginNode(node.id);
        imnodes::BeginNodeTitleBar();
        ImGui::TextUnformatted("node");
        imnodes::EndNodeTitleBar();

        imnodes::BeginInputAttribute(node.id << 1);
        ImGui::TextUnformatted("input");
        imnodes::EndInputAttribute();

        imnodes::BeginOutputAttribute(node.id << 24);
        ImGui::TextUnformatted("output");
        imnodes::EndOutputAttribute();

        imnodes::EndNode();
    }
    for (const Link& link : links)
    {
        imnodes::Link(link.id, link.start_attr, link.end_attr);
    }
	imnodes::EndNodeEditor();
    {
        Link link;
        if (imnodes::IsLinkCreated(&link.start_attr, &link.end_attr))
        {
            link.id = ++LastID;
            links.push_back(link);
        }
    }

    {
        int link_id;
        Link link;
        if (imnodes::IsLinkCreated(&link.start_attr, &link.end_attr))
        {
            link.id = ++LastID;
           links.push_back(link);
        }
    }

    {
        int link_id;
        if (imnodes::IsLinkDestroyed(&link_id))
        {
            auto iter = std::find_if(
                links.begin(), links.end(), [link_id](const Link& link) -> bool {
                    return link.id == link_id;
                });
            assert(iter != links.end());
            links.erase(iter);
        }
    }
}
