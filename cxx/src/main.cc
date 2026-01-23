#include "core.hh"

extern "C" __declspec(dllexport) bool
SKSEPlugin_Load(const SKSE::LoadInterface *a_interface) {
  SKSE::Init(a_interface);

  if (auto msg = SKSE::GetMessagingInterface(); msg != nullptr) {
    msg->RegisterListener([](SKSE::MessagingInterface::Message *a_msg) {
      switch (a_msg->type) {
      case SKSE::MessagingInterface::kPostLoadGame:
        skse_plugin_core::init();
        break;

      default:
        break;
      }
    });
  }

  return true;
}
