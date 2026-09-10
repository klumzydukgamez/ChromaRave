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

static const Uint8 asset_overlay_png[] = {
#embed "CR_overlay.png"
};
const Uint8* const CR_asset_overlay_png = asset_overlay_png;
const size_t CR_asset_overlany_png_size = sizeof(asset_overlay_png);

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

static const Uint8 asset_level_png[] = {
#embed "CR_level.png"
};
const Uint8* const CR_asset_level_png = asset_level_png;
const size_t CR_asset_level_png_size = sizeof(asset_level_png);

static const Uint8 asset_tile_1_png[] = {
#embed "CR_tile_1.png"
};
const Uint8* const CR_asset_tile_1_png = asset_tile_1_png;
const size_t CR_asset_tile_1_png_size = sizeof(asset_tile_1_png);
static const Uint8 asset_tile_2_png[] = {
#embed "CR_tile_2.png"
};
const Uint8* const CR_asset_tile_2_png = asset_tile_2_png;
const size_t CR_asset_tile_2_png_size = sizeof(asset_tile_2_png);
static const Uint8 asset_tile_3_png[] = {
#embed "CR_tile_3.png"
};
const Uint8* const CR_asset_tile_3_png = asset_tile_3_png;
const size_t CR_asset_tile_3_png_size = sizeof(asset_tile_3_png);
static const Uint8 asset_tile_4_png[] = {
#embed "CR_tile_4.png"
};
const Uint8* const CR_asset_tile_4_png = asset_tile_4_png;
const size_t CR_asset_tile_4_png_size = sizeof(asset_tile_4_png);
static const Uint8 asset_tile_5_png[] = {
#embed "CR_tile_5.png"
};
const Uint8* const CR_asset_tile_5_png = asset_tile_5_png;
const size_t CR_asset_tile_5_png_size = sizeof(asset_tile_5_png);
static const Uint8 asset_tile_6_png[] = {
#embed "CR_tile_6.png"
};
const Uint8* const CR_asset_tile_6_png = asset_tile_6_png;
const size_t CR_asset_tile_6_png_size = sizeof(asset_tile_6_png);
static const Uint8 asset_tile_7_png[] = {
#embed "CR_tile_7.png"
};
const Uint8* const CR_asset_tile_7_png = asset_tile_7_png;
const size_t CR_asset_tile_7_png_size = sizeof(asset_tile_7_png);
static const Uint8 asset_tile_8_png[] = {
#embed "CR_tile_8.png"
};
const Uint8* const CR_asset_tile_8_png = asset_tile_8_png;
const size_t CR_asset_tile_8_png_size = sizeof(asset_tile_8_png);
static const Uint8 asset_tile_9_png[] = {
#embed "CR_tile_9.png"
};
const Uint8* const CR_asset_tile_9_png = asset_tile_9_png;
const size_t CR_asset_tile_9_png_size = sizeof(asset_tile_9_png);
static const Uint8 asset_tile_10_png[] = {
#embed "CR_tile_10.png"
};
const Uint8* const CR_asset_tile_10_png = asset_tile_10_png;
const size_t CR_asset_tile_10_png_size = sizeof(asset_tile_10_png);
static const Uint8 asset_tile_11_png[] = {
#embed "CR_tile_11.png"
};
const Uint8* const CR_asset_tile_11_png = asset_tile_11_png;
const size_t CR_asset_tile_11_png_size = sizeof(asset_tile_11_png);
static const Uint8 asset_tile_12_png[] = {
#embed "CR_tile_12.png"
};
const Uint8* const CR_asset_tile_12_png = asset_tile_12_png;
const size_t CR_asset_tile_12_png_size = sizeof(asset_tile_12_png);
static const Uint8 asset_tile_13_png[] = {
#embed "CR_tile_13.png"
};
const Uint8* const CR_asset_tile_13_png = asset_tile_13_png;
const size_t CR_asset_tile_13_png_size = sizeof(asset_tile_13_png);
static const Uint8 asset_tile_14_png[] = {
#embed "CR_tile_14.png"
};
const Uint8* const CR_asset_tile_14_png = asset_tile_14_png;
const size_t CR_asset_tile_14_png_size = sizeof(asset_tile_14_png);
static const Uint8 asset_tile_15_png[] = {
#embed "CR_tile_15.png"
};
const Uint8* const CR_asset_tile_15_png = asset_tile_15_png;
const size_t CR_asset_tile_15_png_size = sizeof(asset_tile_15_png);
static const Uint8 asset_tile_16_png[] = {
#embed "CR_tile_16.png"
};
const Uint8* const CR_asset_tile_16_png = asset_tile_16_png;
const size_t CR_asset_tile_16_png_size = sizeof(asset_tile_16_png);
static const Uint8 asset_tile_17_png[] = {
#embed "CR_tile_17.png"
};
const Uint8* const CR_asset_tile_17_png = asset_tile_17_png;
const size_t CR_asset_tile_17_png_size = sizeof(asset_tile_17_png);
static const Uint8 asset_tile_18_png[] = {
#embed "CR_tile_18.png"
};
const Uint8* const CR_asset_tile_18_png = asset_tile_18_png;
const size_t CR_asset_tile_18_png_size = sizeof(asset_tile_18_png);
static const Uint8 asset_tile_19_png[] = {
#embed "CR_tile_19.png"
};
const Uint8* const CR_asset_tile_19_png = asset_tile_19_png;
const size_t CR_asset_tile_19_png_size = sizeof(asset_tile_19_png);
static const Uint8 asset_tile_20_png[] = {
#embed "CR_tile_20.png"
};
const Uint8* const CR_asset_tile_20_png = asset_tile_20_png;
const size_t CR_asset_tile_20_png_size = sizeof(asset_tile_20_png);
static const Uint8 asset_tile_21_png[] = {
#embed "CR_tile_21.png"
};
const Uint8* const CR_asset_tile_21_png = asset_tile_21_png;
const size_t CR_asset_tile_21_png_size = sizeof(asset_tile_21_png);
static const Uint8 asset_tile_22_png[] = {
#embed "CR_tile_22.png"
};
const Uint8* const CR_asset_tile_22_png = asset_tile_22_png;
const size_t CR_asset_tile_22_png_size = sizeof(asset_tile_22_png);
static const Uint8 asset_tile_23_png[] = {
#embed "CR_tile_23.png"
};
const Uint8* const CR_asset_tile_23_png = asset_tile_23_png;
const size_t CR_asset_tile_23_png_size = sizeof(asset_tile_23_png);
static const Uint8 asset_tile_24_png[] = {
#embed "CR_tile_24.png"
};
const Uint8* const CR_asset_tile_24_png = asset_tile_24_png;
const size_t CR_asset_tile_24_png_size = sizeof(asset_tile_24_png);
static const Uint8 asset_tile_25_png[] = {
#embed "CR_tile_25.png"
};
const Uint8* const CR_asset_tile_25_png = asset_tile_25_png;
const size_t CR_asset_tile_25_png_size = sizeof(asset_tile_25_png);
static const Uint8 asset_tile_26_png[] = {
#embed "CR_tile_26.png"
};
const Uint8* const CR_asset_tile_26_png = asset_tile_26_png;
const size_t CR_asset_tile_26_png_size = sizeof(asset_tile_26_png);
static const Uint8 asset_tile_27_png[] = {
#embed "CR_tile_27.png"
};
const Uint8* const CR_asset_tile_27_png = asset_tile_27_png;
const size_t CR_asset_tile_27_png_size = sizeof(asset_tile_27_png);
static const Uint8 asset_tile_28_png[] = {
#embed "CR_tile_28.png"
};
const Uint8* const CR_asset_tile_28_png = asset_tile_28_png;
const size_t CR_asset_tile_28_png_size = sizeof(asset_tile_28_png);
static const Uint8 asset_tile_29_png[] = {
#embed "CR_tile_29.png"
};
const Uint8* const CR_asset_tile_29_png = asset_tile_29_png;
const size_t CR_asset_tile_29_png_size = sizeof(asset_tile_29_png);
static const Uint8 asset_tile_30_png[] = {
#embed "CR_tile_30.png"
};
const Uint8* const CR_asset_tile_30_png = asset_tile_30_png;
const size_t CR_asset_tile_30_png_size = sizeof(asset_tile_30_png);
static const Uint8 asset_tile_31_png[] = {
#embed "CR_tile_31.png"
};
const Uint8* const CR_asset_tile_31_png = asset_tile_31_png;
const size_t CR_asset_tile_31_png_size = sizeof(asset_tile_31_png);
static const Uint8 asset_tile_32_png[] = {
#embed "CR_tile_32.png"
};
const Uint8* const CR_asset_tile_32_png = asset_tile_32_png;
const size_t CR_asset_tile_32_png_size = sizeof(asset_tile_32_png);
static const Uint8 asset_tile_33_png[] = {
#embed "CR_tile_33.png"
};
const Uint8* const CR_asset_tile_33_png = asset_tile_33_png;
const size_t CR_asset_tile_33_png_size = sizeof(asset_tile_33_png);
static const Uint8 asset_tile_34_png[] = {
#embed "CR_tile_34.png"
};
const Uint8* const CR_asset_tile_34_png = asset_tile_34_png;
const size_t CR_asset_tile_34_png_size = sizeof(asset_tile_34_png);
static const Uint8 asset_tile_35_png[] = {
#embed "CR_tile_35.png"
};
const Uint8* const CR_asset_tile_35_png = asset_tile_35_png;
const size_t CR_asset_tile_35_png_size = sizeof(asset_tile_35_png);
static const Uint8 asset_tile_36_png[] = {
#embed "CR_tile_36.png"
};
const Uint8* const CR_asset_tile_36_png = asset_tile_36_png;
const size_t CR_asset_tile_36_png_size = sizeof(asset_tile_36_png);
static const Uint8 asset_tile_37_png[] = {
#embed "CR_tile_37.png"
};
const Uint8* const CR_asset_tile_37_png = asset_tile_37_png;
const size_t CR_asset_tile_37_png_size = sizeof(asset_tile_37_png);
static const Uint8 asset_tile_38_png[] = {
#embed "CR_tile_38.png"
};
const Uint8* const CR_asset_tile_38_png = asset_tile_38_png;
const size_t CR_asset_tile_38_png_size = sizeof(asset_tile_38_png);
static const Uint8 asset_tile_39_png[] = {
#embed "CR_tile_39.png"
};
const Uint8* const CR_asset_tile_39_png = asset_tile_39_png;
const size_t CR_asset_tile_39_png_size = sizeof(asset_tile_39_png);
static const Uint8 asset_tile_40_png[] = {
#embed "CR_tile_40.png"
};
const Uint8* const CR_asset_tile_40_png = asset_tile_40_png;
const size_t CR_asset_tile_40_png_size = sizeof(asset_tile_40_png);
static const Uint8 asset_tile_41_png[] = {
#embed "CR_tile_41.png"
};
const Uint8* const CR_asset_tile_41_png = asset_tile_41_png;
const size_t CR_asset_tile_41_png_size = sizeof(asset_tile_41_png);
static const Uint8 asset_tile_42_png[] = {
#embed "CR_tile_42.png"
};
const Uint8* const CR_asset_tile_42_png = asset_tile_42_png;
const size_t CR_asset_tile_42_png_size = sizeof(asset_tile_42_png);
static const Uint8 asset_tile_43_png[] = {
#embed "CR_tile_43.png"
};
const Uint8* const CR_asset_tile_43_png = asset_tile_43_png;
const size_t CR_asset_tile_43_png_size = sizeof(asset_tile_43_png);
static const Uint8 asset_tile_44_png[] = {
#embed "CR_tile_44.png"
};
const Uint8* const CR_asset_tile_44_png = asset_tile_44_png;
const size_t CR_asset_tile_44_png_size = sizeof(asset_tile_44_png);
static const Uint8 asset_tile_45_png[] = {
#embed "CR_tile_45.png"
};
const Uint8* const CR_asset_tile_45_png = asset_tile_45_png;
const size_t CR_asset_tile_45_png_size = sizeof(asset_tile_45_png);
static const Uint8 asset_tile_46_png[] = {
#embed "CR_tile_46.png"
};
const Uint8* const CR_asset_tile_46_png = asset_tile_46_png;
const size_t CR_asset_tile_46_png_size = sizeof(asset_tile_46_png);
static const Uint8 asset_tile_47_png[] = {
#embed "CR_tile_47.png"
};
const Uint8* const CR_asset_tile_47_png = asset_tile_47_png;
const size_t CR_asset_tile_47_png_size = sizeof(asset_tile_47_png);
static const Uint8 asset_tile_48_png[] = {
#embed "CR_tile_48.png"
};
const Uint8* const CR_asset_tile_48_png = asset_tile_48_png;
const size_t CR_asset_tile_48_png_size = sizeof(asset_tile_48_png);
static const Uint8 asset_tile_49_png[] = {
#embed "CR_tile_49.png"
};
const Uint8* const CR_asset_tile_49_png = asset_tile_49_png;
const size_t CR_asset_tile_49_png_size = sizeof(asset_tile_49_png);
static const Uint8 asset_tile_50_png[] = {
#embed "CR_tile_50.png"
};
const Uint8* const CR_asset_tile_50_png = asset_tile_50_png;
const size_t CR_asset_tile_50_png_size = sizeof(asset_tile_50_png);
static const Uint8 asset_tile_51_png[] = {
#embed "CR_tile_51.png"
};
const Uint8* const CR_asset_tile_51_png = asset_tile_51_png;
const size_t CR_asset_tile_51_png_size = sizeof(asset_tile_51_png);
static const Uint8 asset_tile_52_png[] = {
#embed "CR_tile_52.png"
};
const Uint8* const CR_asset_tile_52_png = asset_tile_52_png;
const size_t CR_asset_tile_52_png_size = sizeof(asset_tile_52_png);
static const Uint8 asset_tile_53_png[] = {
#embed "CR_tile_53.png"
};
const Uint8* const CR_asset_tile_53_png = asset_tile_53_png;
const size_t CR_asset_tile_53_png_size = sizeof(asset_tile_53_png);
static const Uint8 asset_tile_54_png[] = {
#embed "CR_tile_54.png"
};
const Uint8* const CR_asset_tile_54_png = asset_tile_54_png;
const size_t CR_asset_tile_54_png_size = sizeof(asset_tile_54_png);
static const Uint8 asset_tile_55_png[] = {
#embed "CR_tile_55.png"
};
const Uint8* const CR_asset_tile_55_png = asset_tile_55_png;
const size_t CR_asset_tile_55_png_size = sizeof(asset_tile_55_png);
static const Uint8 asset_tile_56_png[] = {
#embed "CR_tile_56.png"
};
const Uint8* const CR_asset_tile_56_png = asset_tile_56_png;
const size_t CR_asset_tile_56_png_size = sizeof(asset_tile_56_png);
static const Uint8 asset_tile_57_png[] = {
#embed "CR_tile_57.png"
};
const Uint8* const CR_asset_tile_57_png = asset_tile_57_png;
const size_t CR_asset_tile_57_png_size = sizeof(asset_tile_57_png);
static const Uint8 asset_tile_58_png[] = {
#embed "CR_tile_58.png"
};
const Uint8* const CR_asset_tile_58_png = asset_tile_58_png;
const size_t CR_asset_tile_58_png_size = sizeof(asset_tile_58_png);
static const Uint8 asset_tile_59_png[] = {
#embed "CR_tile_59.png"
};
const Uint8* const CR_asset_tile_59_png = asset_tile_59_png;
const size_t CR_asset_tile_59_png_size = sizeof(asset_tile_59_png);
static const Uint8 asset_tile_60_png[] = {
#embed "CR_tile_60.png"
};
const Uint8* const CR_asset_tile_60_png = asset_tile_60_png;
const size_t CR_asset_tile_60_png_size = sizeof(asset_tile_60_png);
static const Uint8 asset_tile_61_png[] = {
#embed "CR_tile_61.png"
};
const Uint8* const CR_asset_tile_61_png = asset_tile_61_png;
const size_t CR_asset_tile_61_png_size = sizeof(asset_tile_61_png);
static const Uint8 asset_tile_62_png[] = {
#embed "CR_tile_62.png"
};
const Uint8* const CR_asset_tile_62_png = asset_tile_62_png;
const size_t CR_asset_tile_62_png_size = sizeof(asset_tile_62_png);
static const Uint8 asset_tile_63_png[] = {
#embed "CR_tile_63.png"
};
const Uint8* const CR_asset_tile_63_png = asset_tile_63_png;
const size_t CR_asset_tile_63_png_size = sizeof(asset_tile_63_png);
static const Uint8 asset_tile_64_png[] = {
#embed "CR_tile_64.png"
};
const Uint8* const CR_asset_tile_64_png = asset_tile_64_png;
const size_t CR_asset_tile_64_png_size = sizeof(asset_tile_64_png);
static const Uint8 asset_tile_65_png[] = {
#embed "CR_tile_65.png"
};
const Uint8* const CR_asset_tile_65_png = asset_tile_65_png;
const size_t CR_asset_tile_65_png_size = sizeof(asset_tile_65_png);
static const Uint8 asset_tile_66_png[] = {
#embed "CR_tile_66.png"
};
const Uint8* const CR_asset_tile_66_png = asset_tile_66_png;
const size_t CR_asset_tile_66_png_size = sizeof(asset_tile_66_png);
static const Uint8 asset_tile_67_png[] = {
#embed "CR_tile_67.png"
};
const Uint8* const CR_asset_tile_67_png = asset_tile_67_png;
const size_t CR_asset_tile_67_png_size = sizeof(asset_tile_67_png);
static const Uint8 asset_tile_68_png[] = {
#embed "CR_tile_68.png"
};
const Uint8* const CR_asset_tile_68_png = asset_tile_68_png;
const size_t CR_asset_tile_68_png_size = sizeof(asset_tile_68_png);
static const Uint8 asset_tile_69_png[] = {
#embed "CR_tile_69.png"
};
const Uint8* const CR_asset_tile_69_png = asset_tile_69_png;
const size_t CR_asset_tile_69_png_size = sizeof(asset_tile_69_png);
static const Uint8 asset_tile_70_png[] = {
#embed "CR_tile_70.png"
};
const Uint8* const CR_asset_tile_70_png = asset_tile_70_png;
const size_t CR_asset_tile_70_png_size = sizeof(asset_tile_70_png);
static const Uint8 asset_tile_71_png[] = {
#embed "CR_tile_71.png"
};
const Uint8* const CR_asset_tile_71_png = asset_tile_71_png;
const size_t CR_asset_tile_71_png_size = sizeof(asset_tile_71_png);
static const Uint8 asset_tile_72_png[] = {
#embed "CR_tile_72.png"
};
const Uint8* const CR_asset_tile_72_png = asset_tile_72_png;
const size_t CR_asset_tile_72_png_size = sizeof(asset_tile_72_png);
static const Uint8 asset_tile_73_png[] = {
#embed "CR_tile_73.png"
};
const Uint8* const CR_asset_tile_73_png = asset_tile_73_png;
const size_t CR_asset_tile_73_png_size = sizeof(asset_tile_73_png);
static const Uint8 asset_tile_74_png[] = {
#embed "CR_tile_74.png"
};
const Uint8* const CR_asset_tile_74_png = asset_tile_74_png;
const size_t CR_asset_tile_74_png_size = sizeof(asset_tile_74_png);
static const Uint8 asset_tile_75_png[] = {
#embed "CR_tile_75.png"
};
const Uint8* const CR_asset_tile_75_png = asset_tile_75_png;
const size_t CR_asset_tile_75_png_size = sizeof(asset_tile_75_png);
static const Uint8 asset_tile_76_png[] = {
#embed "CR_tile_76.png"
};
const Uint8* const CR_asset_tile_76_png = asset_tile_76_png;
const size_t CR_asset_tile_76_png_size = sizeof(asset_tile_76_png);
static const Uint8 asset_tile_77_png[] = {
#embed "CR_tile_77.png"
};
const Uint8* const CR_asset_tile_77_png = asset_tile_77_png;
const size_t CR_asset_tile_77_png_size = sizeof(asset_tile_77_png);
static const Uint8 asset_tile_78_png[] = {
#embed "CR_tile_78.png"
};
const Uint8* const CR_asset_tile_78_png = asset_tile_78_png;
const size_t CR_asset_tile_78_png_size = sizeof(asset_tile_78_png);
static const Uint8 asset_tile_79_png[] = {
#embed "CR_tile_79.png"
};
const Uint8* const CR_asset_tile_79_png = asset_tile_79_png;
const size_t CR_asset_tile_79_png_size = sizeof(asset_tile_79_png);
static const Uint8 asset_tile_80_png[] = {
#embed "CR_tile_80.png"
};
const Uint8* const CR_asset_tile_80_png = asset_tile_80_png;
const size_t CR_asset_tile_80_png_size = sizeof(asset_tile_80_png);
static const Uint8 asset_tile_81_png[] = {
#embed "CR_tile_81.png"
};
const Uint8* const CR_asset_tile_81_png = asset_tile_81_png;
const size_t CR_asset_tile_81_png_size = sizeof(asset_tile_81_png);
static const Uint8 asset_tile_82_png[] = {
#embed "CR_tile_82.png"
};
const Uint8* const CR_asset_tile_82_png = asset_tile_82_png;
const size_t CR_asset_tile_82_png_size = sizeof(asset_tile_82_png);
static const Uint8 asset_tile_83_png[] = {
#embed "CR_tile_83.png"
};
const Uint8* const CR_asset_tile_83_png = asset_tile_83_png;
const size_t CR_asset_tile_83_png_size = sizeof(asset_tile_83_png);
static const Uint8 asset_tile_84_png[] = {
#embed "CR_tile_84.png"
};
const Uint8* const CR_asset_tile_84_png = asset_tile_84_png;
const size_t CR_asset_tile_84_png_size = sizeof(asset_tile_84_png);
static const Uint8 asset_tile_85_png[] = {
#embed "CR_tile_85.png"
};
const Uint8* const CR_asset_tile_85_png = asset_tile_85_png;
const size_t CR_asset_tile_85_png_size = sizeof(asset_tile_85_png);
static const Uint8 asset_tile_86_png[] = {
#embed "CR_tile_86.png"
};
const Uint8* const CR_asset_tile_86_png = asset_tile_86_png;
const size_t CR_asset_tile_86_png_size = sizeof(asset_tile_86_png);
static const Uint8 asset_tile_87_png[] = {
#embed "CR_tile_87.png"
};
const Uint8* const CR_asset_tile_87_png = asset_tile_87_png;
const size_t CR_asset_tile_87_png_size = sizeof(asset_tile_87_png);
static const Uint8 asset_tile_88_png[] = {
#embed "CR_tile_88.png"
};
const Uint8* const CR_asset_tile_88_png = asset_tile_88_png;
const size_t CR_asset_tile_88_png_size = sizeof(asset_tile_88_png);
static const Uint8 asset_tile_89_png[] = {
#embed "CR_tile_89.png"
};
const Uint8* const CR_asset_tile_89_png = asset_tile_89_png;
const size_t CR_asset_tile_89_png_size = sizeof(asset_tile_89_png);
static const Uint8 asset_tile_90_png[] = {
#embed "CR_tile_90.png"
};
const Uint8* const CR_asset_tile_90_png = asset_tile_90_png;
const size_t CR_asset_tile_90_png_size = sizeof(asset_tile_90_png);
static const Uint8 asset_tile_91_png[] = {
#embed "CR_tile_91.png"
};
const Uint8* const CR_asset_tile_91_png = asset_tile_91_png;
const size_t CR_asset_tile_91_png_size = sizeof(asset_tile_91_png);
static const Uint8 asset_tile_92_png[] = {
#embed "CR_tile_92.png"
};
const Uint8* const CR_asset_tile_92_png = asset_tile_92_png;
const size_t CR_asset_tile_92_png_size = sizeof(asset_tile_92_png);
static const Uint8 asset_tile_93_png[] = {
#embed "CR_tile_93.png"
};
const Uint8* const CR_asset_tile_93_png = asset_tile_93_png;
const size_t CR_asset_tile_93_png_size = sizeof(asset_tile_93_png);
static const Uint8 asset_tile_94_png[] = {
#embed "CR_tile_94.png"
};
const Uint8* const CR_asset_tile_94_png = asset_tile_94_png;
const size_t CR_asset_tile_94_png_size = sizeof(asset_tile_94_png);
static const Uint8 asset_tile_95_png[] = {
#embed "CR_tile_95.png"
};
const Uint8* const CR_asset_tile_95_png = asset_tile_95_png;
const size_t CR_asset_tile_95_png_size = sizeof(asset_tile_95_png);
static const Uint8 asset_tile_96_png[] = {
#embed "CR_tile_96.png"
};
const Uint8* const CR_asset_tile_96_png = asset_tile_96_png;
const size_t CR_asset_tile_96_png_size = sizeof(asset_tile_96_png);
static const Uint8 asset_tile_97_png[] = {
#embed "CR_tile_97.png"
};
const Uint8* const CR_asset_tile_97_png = asset_tile_97_png;
const size_t CR_asset_tile_97_png_size = sizeof(asset_tile_97_png);
static const Uint8 asset_tile_98_png[] = {
#embed "CR_tile_98.png"
};
const Uint8* const CR_asset_tile_98_png = asset_tile_98_png;
const size_t CR_asset_tile_98_png_size = sizeof(asset_tile_98_png);
static const Uint8 asset_tile_99_png[] = {
#embed "CR_tile_99.png"
};
const Uint8* const CR_asset_tile_99_png = asset_tile_99_png;
const size_t CR_asset_tile_99_png_size = sizeof(asset_tile_99_png);
static const Uint8 asset_tile_100_png[] = {
#embed "CR_tile_100.png"
};
const Uint8* const CR_asset_tile_100_png = asset_tile_100_png;
const size_t CR_asset_tile_100_png_size = sizeof(asset_tile_100_png);
static const Uint8 asset_tile_101_png[] = {
#embed "CR_tile_101.png"
};
const Uint8* const CR_asset_tile_101_png = asset_tile_101_png;
const size_t CR_asset_tile_101_png_size = sizeof(asset_tile_101_png);
static const Uint8 asset_tile_102_png[] = {
#embed "CR_tile_102.png"
};
const Uint8* const CR_asset_tile_102_png = asset_tile_102_png;
const size_t CR_asset_tile_102_png_size = sizeof(asset_tile_102_png);
static const Uint8 asset_tile_103_png[] = {
#embed "CR_tile_103.png"
};
const Uint8* const CR_asset_tile_103_png = asset_tile_103_png;
const size_t CR_asset_tile_103_png_size = sizeof(asset_tile_103_png);
static const Uint8 asset_tile_104_png[] = {
#embed "CR_tile_104.png"
};
const Uint8* const CR_asset_tile_104_png = asset_tile_104_png;
const size_t CR_asset_tile_104_png_size = sizeof(asset_tile_104_png);
static const Uint8 asset_tile_105_png[] = {
#embed "CR_tile_105.png"
};
const Uint8* const CR_asset_tile_105_png = asset_tile_105_png;
const size_t CR_asset_tile_105_png_size = sizeof(asset_tile_105_png);
static const Uint8 asset_tile_106_png[] = {
#embed "CR_tile_106.png"
};
const Uint8* const CR_asset_tile_106_png = asset_tile_106_png;
const size_t CR_asset_tile_106_png_size = sizeof(asset_tile_106_png);
static const Uint8 asset_tile_107_png[] = {
#embed "CR_tile_107.png"
};
const Uint8* const CR_asset_tile_107_png = asset_tile_107_png;
const size_t CR_asset_tile_107_png_size = sizeof(asset_tile_107_png);
static const Uint8 asset_tile_108_png[] = {
#embed "CR_tile_108.png"
};
const Uint8* const CR_asset_tile_108_png = asset_tile_108_png;
const size_t CR_asset_tile_108_png_size = sizeof(asset_tile_108_png);
static const Uint8 asset_tile_109_png[] = {
#embed "CR_tile_109.png"
};
const Uint8* const CR_asset_tile_109_png = asset_tile_109_png;
const size_t CR_asset_tile_109_png_size = sizeof(asset_tile_109_png);
static const Uint8 asset_tile_110_png[] = {
#embed "CR_tile_110.png"
};
const Uint8* const CR_asset_tile_110_png = asset_tile_110_png;
const size_t CR_asset_tile_110_png_size = sizeof(asset_tile_110_png);
static const Uint8 asset_tile_111_png[] = {
#embed "CR_tile_111.png"
};
const Uint8* const CR_asset_tile_111_png = asset_tile_111_png;
const size_t CR_asset_tile_111_png_size = sizeof(asset_tile_111_png);
static const Uint8 asset_tile_112_png[] = {
#embed "CR_tile_112.png"
};
const Uint8* const CR_asset_tile_112_png = asset_tile_112_png;
const size_t CR_asset_tile_112_png_size = sizeof(asset_tile_112_png);
static const Uint8 asset_tile_113_png[] = {
#embed "CR_tile_113.png"
};
const Uint8* const CR_asset_tile_113_png = asset_tile_113_png;
const size_t CR_asset_tile_113_png_size = sizeof(asset_tile_113_png);
static const Uint8 asset_tile_114_png[] = {
#embed "CR_tile_114.png"
};
const Uint8* const CR_asset_tile_114_png = asset_tile_114_png;
const size_t CR_asset_tile_114_png_size = sizeof(asset_tile_114_png);
static const Uint8 asset_tile_115_png[] = {
#embed "CR_tile_115.png"
};
const Uint8* const CR_asset_tile_115_png = asset_tile_115_png;
const size_t CR_asset_tile_115_png_size = sizeof(asset_tile_115_png);
static const Uint8 asset_tile_116_png[] = {
#embed "CR_tile_116.png"
};
const Uint8* const CR_asset_tile_116_png = asset_tile_116_png;
const size_t CR_asset_tile_116_png_size = sizeof(asset_tile_116_png);
static const Uint8 asset_tile_117_png[] = {
#embed "CR_tile_117.png"
};
const Uint8* const CR_asset_tile_117_png = asset_tile_117_png;
const size_t CR_asset_tile_117_png_size = sizeof(asset_tile_117_png);
static const Uint8 asset_tile_118_png[] = {
#embed "CR_tile_118.png"
};
const Uint8* const CR_asset_tile_118_png = asset_tile_118_png;
const size_t CR_asset_tile_118_png_size = sizeof(asset_tile_118_png);
static const Uint8 asset_tile_119_png[] = {
#embed "CR_tile_119.png"
};
const Uint8* const CR_asset_tile_119_png = asset_tile_119_png;
const size_t CR_asset_tile_119_png_size = sizeof(asset_tile_119_png);
static const Uint8 asset_tile_120_png[] = {
#embed "CR_tile_120.png"
};
const Uint8* const CR_asset_tile_120_png = asset_tile_120_png;
const size_t CR_asset_tile_120_png_size = sizeof(asset_tile_120_png);
static const Uint8 asset_tile_121_png[] = {
#embed "CR_tile_121.png"
};
const Uint8* const CR_asset_tile_121_png = asset_tile_121_png;
const size_t CR_asset_tile_121_png_size = sizeof(asset_tile_121_png);
static const Uint8 asset_tile_122_png[] = {
#embed "CR_tile_122.png"
};
const Uint8* const CR_asset_tile_122_png = asset_tile_122_png;
const size_t CR_asset_tile_122_png_size = sizeof(asset_tile_122_png);
static const Uint8 asset_tile_123_png[] = {
#embed "CR_tile_123.png"
};
const Uint8* const CR_asset_tile_123_png = asset_tile_123_png;
const size_t CR_asset_tile_123_png_size = sizeof(asset_tile_123_png);
static const Uint8 asset_tile_124_png[] = {
#embed "CR_tile_124.png"
};
const Uint8* const CR_asset_tile_124_png = asset_tile_124_png;
const size_t CR_asset_tile_124_png_size = sizeof(asset_tile_124_png);
static const Uint8 asset_tile_125_png[] = {
#embed "CR_tile_125.png"
};
const Uint8* const CR_asset_tile_125_png = asset_tile_125_png;
const size_t CR_asset_tile_125_png_size = sizeof(asset_tile_125_png);
static const Uint8 asset_tile_126_png[] = {
#embed "CR_tile_126.png"
};
const Uint8* const CR_asset_tile_126_png = asset_tile_126_png;
const size_t CR_asset_tile_126_png_size = sizeof(asset_tile_126_png);

static const Uint8 asset_player_god_mode_png[] = {
#embed "CR_player_god_mode.png"
};
const Uint8* const CR_asset_player_god_mode_png = asset_player_god_mode_png;
const size_t CR_asset_player_god_mode_png_size = sizeof(asset_player_god_mode_png);
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
static const Uint8 asset_player_jump_png[] = {
#embed "CR_player_jump.png"
};
const Uint8* const CR_asset_player_jump_png = asset_player_jump_png;
const size_t CR_asset_player_jump_png_size = sizeof(asset_player_jump_png);
