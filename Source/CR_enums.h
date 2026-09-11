#if !defined __CR_ENUMS_H__
#define __CR_ENUMS_H__

typedef enum : int {
	CR_EEnemyType_BATON_WARDEN,
	CR_EEnemyType_COUNT
} CR_EEnemyType;

typedef enum : int {
	CR_EEnemyAnim_IDLE,
	CR_EEnemyAnim_WALK,
	CR_EEnemyAnim_COUNT
} CR_EEnemyAnim;

typedef enum : int {
	CR_EPlayerAnim_GOD_MODE,
	CR_EPlayerAnim_IDLE,
	CR_EPlayerAnim_RUN,
	CR_EPlayerAnim_JUMP,
	CR_EPlayerAnim_COUNT
} CR_EPlayerAnim;

#endif /* __CR_ENUMS_H__ */
