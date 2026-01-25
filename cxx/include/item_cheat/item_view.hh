#pragma once

#include "RE/F/FormTypes.h"
#include <SKSEMenuFramework.h>

namespace item_cheat::view {
    inline static RE::FormType selectedFormType = RE::FormType::None;

    static constexpr std::pair<RE::FormType, const char*> kFormTypeList[] = {
        { RE::FormType::None, "All" },
        { RE::FormType::Weapon, "Weapon" },
        { RE::FormType::Armor, "Armor" },
        { RE::FormType::Ammo, "Ammo" },
        { RE::FormType::Ingredient, "Ingredient" },
        { RE::FormType::AlchemyItem, "Alchemy" },
        { RE::FormType::Book, "Book" },
        { RE::FormType::Scroll, "Scroll" },
        { RE::FormType::KeyMaster, "Key" },
        { RE::FormType::Misc, "Misc" },

        { RE::FormType::Outfit, "Outfit" },
        { RE::FormType::Note, "Note" },
        { RE::FormType::SoulGem, "SoulGem" },
        { RE::FormType::NPC, "NPC" },
    };

    constexpr const char* ToFormTypeName(RE::FormType type) {
        for (auto& [t, name] : kFormTypeList) {
            if (t == type) {
                return name;
            }
        }
        return "Unknown";
    }

    void Render();

}
