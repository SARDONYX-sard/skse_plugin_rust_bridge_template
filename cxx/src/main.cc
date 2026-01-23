#include "SKSE/Interfaces.h"
#include "core.hh"

namespace {
static void skse_listener(SKSE::MessagingInterface::Message *a_msg) {
  switch (a_msg->type) {
  // Fired after all plugins are loaded.
  case SKSE::MessagingInterface::kPostLoad:
  // Fired after all `PostLoad` events have completed.
  case SKSE::MessagingInterface::kPostPostLoad:
  // Fired before loading a game save.
  case SKSE::MessagingInterface::kPreLoadGame:
    return;

  // Fired after loading a game save.
  case SKSE::MessagingInterface::kPostLoadGame:
    skse_plugin_core::init();
    return;

  // Fired before saving a game.
  case SKSE::MessagingInterface::kSaveGame:
  // Fired before deleting a game save.
  case SKSE::MessagingInterface::kDeleteGame:
  // Fired when the input system is loaded.
  case SKSE::MessagingInterface::kInputLoaded:
  // Fired when starting a new game.
  case SKSE::MessagingInterface::kNewGame:
  // Fired after all game data has loaded.
  case SKSE::MessagingInterface::kDataLoaded:
  default:
    return;
  }
}
} // namespace

extern "C" __declspec(dllexport) bool
SKSEPlugin_Load(const SKSE::LoadInterface *a_interface) {
  SKSE::Init(a_interface);

  auto msg = SKSE::GetMessagingInterface();
  if (msg == nullptr) {
    return false;
  }

  msg->RegisterListener("SKSE", ::skse_listener);

  return true;
}
