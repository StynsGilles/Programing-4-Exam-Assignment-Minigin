#include "MiniginPCH.h"
#include "ServiceLocator.h"

std::unique_ptr<ISoundSystem> ServiceLocator::ss_service{};