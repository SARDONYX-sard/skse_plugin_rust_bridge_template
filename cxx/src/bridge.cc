// C++ to Rust bridge

#include "bridge.hh"

namespace bridge {
    void spdlog_trace(rust::Str msg) {
        spdlog::trace("{}", std::string_view(msg.data(), msg.size()));
    }

    void spdlog_debug(rust::Str msg) {
        spdlog::debug("{}", std::string_view(msg.data(), msg.size()));
    }

    void spdlog_info(rust::Str msg) {
        spdlog::info("{}", std::string_view(msg.data(), msg.size()));
    }

    void spdlog_warn(rust::Str msg) {
        spdlog::warn("{}", std::string_view(msg.data(), msg.size()));
    }

    void spdlog_error(rust::Str msg) {
        spdlog::error("{}", std::string_view(msg.data(), msg.size()));
    }

    rust::String get_calendar_time() {
        std::array<char, 64> buffer{};
        constexpr auto       BUFFER_SIZE = static_cast<rust::u32>(buffer.size());

        auto calendar = RE::Calendar::GetSingleton();
        calendar->GetTimeDateString(buffer.data(), BUFFER_SIZE, true);

        return rust::String{ buffer.data() };
    }

    void message_box(rust::Str msg) {
        RE::DebugMessageBox(std::string{ msg }.data());
    }
}  // namespace bridge
