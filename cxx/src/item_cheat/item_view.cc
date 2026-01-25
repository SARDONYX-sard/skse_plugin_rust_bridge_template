#include <SKSEMenuFramework.h>

#include "RE/F/FormTypes.h"
#include "item_cheat/item_model.hh"
#include "item_cheat/item_view.hh"

#include "ui.hh"

namespace item_cheat::view {

    namespace {
        static std::atomic_int64_t selectedPlugin = -1;
        static int                 addCount = 1;
        static float               tableHeight = 400.0f;

        static std::string filterPlugin;
        static std::string filterFormType;
        static std::string filterFormList;
    }

    void Render() {
        using namespace item_cheat::model;

        if (GetPlugins().empty()) {
            if (ImGuiMCP::Button("Load Plugins")) {
                BuildPluginList();
            }
            return;
        }

        // --- Plugin search + dropdown ---
        ImGuiMCP::TextUnformatted("Plugin: ");
        ImGuiMCP::SameLine();
        static std::array<char, 100> pluginBuffer{};
        std::strncpy(pluginBuffer.data(), filterPlugin.c_str(), pluginBuffer.size());
        if (ImGuiMCP::InputText("##pluginSearch", pluginBuffer.data(), pluginBuffer.size())) {
            filterPlugin = pluginBuffer.data();
        }

        ImGuiMCP::SameLine();

        const char* pluginPreview = selectedPlugin >= 0 ? GetPlugins()[selectedPlugin].name.c_str() : "<Select>";
        if (ImGuiMCP::BeginCombo("##pluginDropdown", pluginPreview)) {
            const auto& plugins = GetPlugins();

            for (const auto& [i, plugin] : std::views::enumerate(plugins)) {
                if (!filterPlugin.empty() && plugin.name.find(filterPlugin) == std::string::npos) {
                    continue;
                }

                if (ImGuiMCP::Selectable(plugin.name.c_str(), selectedPlugin == i)) {
                    selectedPlugin = i;
                    BuildItemList(plugin.file);
                }
            }
            ImGuiMCP::EndCombo();
        }

        // --- FormType search + dropdown ---
        ImGuiMCP::Text("Type: ");
        ImGuiMCP::SameLine();
        static std::array<char, 50> formTypeBuffer{};
        std::strncpy(formTypeBuffer.data(), filterFormType.c_str(), formTypeBuffer.size());
        if (ImGuiMCP::InputText("##formTypeSearch", formTypeBuffer.data(), formTypeBuffer.size())) {
            filterFormType = formTypeBuffer.data();
        }

        ImGuiMCP::SameLine();

        const char* formTypePreview = ToFormTypeName(view::selectedFormType);
        if (ImGuiMCP::BeginCombo("##formTypeDropdown", formTypePreview)) {
            for (auto& [type, label] : kFormTypeList) {
                if (!filterFormType.empty() && std::string(label).find(filterFormType) == std::string::npos) {
                    continue;
                }

                if (ImGuiMCP::Selectable(label, view::selectedFormType == type)) {
                    view::selectedFormType = type;
                }
            }
            ImGuiMCP::EndCombo();
        }

        // --- Form List Search ---
        ImGuiMCP::Text("Form List: ");
        ImGuiMCP::SameLine();
        static std::array<char, 256> formListBuffer{};
        std::strncpy(formListBuffer.data(), filterFormList.c_str(), formListBuffer.size());
        if (ImGuiMCP::InputText("##formListSearch", formListBuffer.data(), formListBuffer.size())) {
            filterFormList = formListBuffer.data();
        }

        // -- Get all button
        ImGuiMCP::SameLine();
        if (ImGuiMCP::Button("Get all")) {
            auto player =
                RE::PlayerCharacter::GetSingleton()
                    ->As<RE::TESObjectREFR>();
            for (auto& item : GetItems()) {
                bool matches = true;
                if (view::selectedFormType != RE::FormType::None && view::selectedFormType != item.formType) {
                    matches = false;
                }
                if (!filterFormList.empty() && item.name.find(filterFormList) == std::string::npos) {
                    matches = false;
                }

                if (matches) {
                    player->AddObjectToContainer(item.object, nullptr, 1, nullptr);
                }
            }
        }

        // --- Table ---
        ImGuiMCP::BeginChild("TableScrollRegion", ImGuiMCP::ImVec2{ 0, tableHeight }, true);
        if (ImGuiMCP::BeginTable("items", 2, ui::Example3::flags)) {
            ImGuiMCP::TableSetupColumn("Name");
            ImGuiMCP::TableSetupColumn("Type");
            ImGuiMCP::TableHeadersRow();

            for (auto& item : GetItems()) {
                bool matches = true;

                if (selectedFormType != RE::FormType::None && selectedFormType != item.formType) {
                    matches = false;
                }
                if (!filterFormList.empty() && item.name.find(filterFormList) == std::string::npos) {
                    matches = false;
                }

                if (!matches) {
                    continue;
                }

                ImGuiMCP::TableNextRow();
                ImGuiMCP::TableSetColumnIndex(0);

                if (ImGuiMCP::Selectable(
                        item.name.c_str(),
                        GetSelectedItem() == item.object,
                        ImGuiMCP::ImGuiSelectableFlags_SpanAllColumns)) {
                    SelectItem(item.object);
                }

                ImGuiMCP::TableSetColumnIndex(1);
                ImGuiMCP::TextUnformatted(ToFormTypeName(item.formType));
            }

            ImGuiMCP::EndTable();
        }
        ImGuiMCP::EndChild();

        // --- Add / Amount ---
        if (GetSelectedItem()) {
            ImGuiMCP::Separator();

            if (ImGuiMCP::Button("Add")) {
                AddSelectedItem(addCount);
            }
            ImGuiMCP::SameLine();
            ImGuiMCP::SliderInt("Amount", &addCount, 1, 999999);
        }
    }

}  // namespace item_cheat::view
