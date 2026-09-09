#include "CR_shared.h"

static const char asset_final_vert[] = {
#embed "CR_final.vert" suffix(, 0)
};
static const char asset_final_frag[] = {
#embed "CR_final.frag" suffix(, 0)
};
const char* const CR_asset_final_vert = asset_final_vert;
const char* const CR_asset_final_frag = asset_final_frag;

static const char asset_scene_vert[] = {
#embed "CR_scene.vert" suffix(, 0)
};
static const char asset_scene_frag[] = {
#embed "CR_scene.frag" suffix(, 0)
};
const char* const CR_asset_scene_vert = asset_scene_vert;
const char* const CR_asset_scene_frag = asset_scene_frag;

static const Uint8 asset_default_png[] = {
#embed "CR_default.png"
};
const Uint8* const CR_asset_default_png = asset_default_png;
const size_t CR_asset_default_png_size = sizeof(asset_default_png);

static const Uint8 asset_blank_png[] = {
#embed "CR_blank.png"
};
const Uint8* const CR_asset_blank_png = asset_blank_png;
const size_t CR_asset_blank_png_size = sizeof(asset_blank_png);

static const Uint8 asset_background_1_png[] = {
#embed "CR_background_1.png"
};
const Uint8* const CR_asset_background_1_png = asset_background_1_png;
const size_t CR_asset_background_1_png_size = sizeof(asset_background_1_png);
static const Uint8 asset_background_2_png[] = {
#embed "CR_background_2.png"
};
const Uint8* const CR_asset_background_2_png = asset_background_2_png;
const size_t CR_asset_background_2_png_size = sizeof(asset_background_2_png);
static const Uint8 asset_background_3_png[] = {
#embed "CR_background_3.png"
};
const Uint8* const CR_asset_background_3_png = asset_background_3_png;
const size_t CR_asset_background_3_png_size = sizeof(asset_background_3_png);
static const Uint8 asset_background_4_png[] = {
#embed "CR_background_4.png"
};
const Uint8* const CR_asset_background_4_png = asset_background_4_png;
const size_t CR_asset_background_4_png_size = sizeof(asset_background_4_png);
static const Uint8 asset_background_5_png[] = {
#embed "CR_background_5.png"
};
const Uint8* const CR_asset_background_5_png = asset_background_5_png;
const size_t CR_asset_background_5_png_size = sizeof(asset_background_5_png);

static const Uint8 asset_player_idle_png[] = {
#embed "CR_player_idle.png"
};
const Uint8* const CR_asset_player_idle_png = asset_player_idle_png;
const size_t CR_asset_player_idle_png_size = sizeof(asset_player_idle_png);

static const Uint8 asset_player_run_png[] = {
#embed "CR_player_run.png"
};
const Uint8* const CR_asset_player_run_png = asset_player_run_png;
const size_t CR_asset_player_run_png_size = sizeof(asset_player_run_png);
