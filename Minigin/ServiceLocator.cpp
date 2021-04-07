#include "MiniginPCH.h"
#include "ServiceLocator.h"

std::unique_ptr<NullSoundSystem> dae::ServiceLocator::ss_nullService{};
std::unique_ptr<ISoundSystem> dae::ServiceLocator::ss_service{ std::move(ss_nullService) };