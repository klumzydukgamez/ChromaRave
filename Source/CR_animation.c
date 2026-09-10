#include "CR_shared.h"

const int CR_PLAYER_ANIM_LENGTHS[CR_EPlayerAnim_COUNT] = {
	[CR_EPlayerAnim_GOD_MODE] = 0,
	[CR_EPlayerAnim_IDLE] = 4,
	[CR_EPlayerAnim_RUN] = 6,
	[CR_EPlayerAnim_JUMP] = 8
};
const Uint64 CR_PLAYER_ANIM_TIMES[CR_EPlayerAnim_COUNT] = {
	[CR_EPlayerAnim_GOD_MODE] = 0,
	[CR_EPlayerAnim_IDLE] = 150,
	[CR_EPlayerAnim_RUN] = 150,
	[CR_EPlayerAnim_JUMP] = 100
};
