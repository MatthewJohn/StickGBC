/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */



#include "gb.h"

#define WINDOW_TEXT_SKIP 46U
#define WINDOW_TEXT_END 47U

extern const UINT8 win_txt_shop_int[];
extern const UINT8 win_txt_pawn_int[];
extern const UINT8 win_txt_bus_statn_no_mon[];
extern const UINT8 win_txt_bus_statn_no_deal[];
extern const UINT8 win_txt_bus_statn_no_phone[];
extern const UINT8 win_txt_bus_statn_no_ammo[];
extern const UINT8 win_txt_bus_statn_bust[];
extern const UINT8 win_txt_bus_statn_coke_deal[];
extern const UINT8 win_txt_bus_statn_late[];
extern const UINT8 win_txt_bus_statn_bad[];
extern const UINT8 win_txt_bus_statn_no_gun_3[];
extern const UINT8 win_txt_bus_statn_no_gun_2[];
extern const UINT8 win_txt_bus_statn_no_gun_1[];
extern const UINT8 win_txt_bus_statn_rob_1[];
extern const UINT8 win_txt_bus_statn_rob_3[];
extern const UINT8 win_txt_bus_statn_rob_2[];
extern const UINT8 win_txt_bus_statn_beer_deal[];
extern const UINT8 win_txt_bus_statn_no_inv[];
extern const UINT8 win_txt_skater_give[];
extern const UINT8 win_txt_skater_int[];
extern const UINT8 win_txt_skater_thx_1[];
extern const UINT8 win_txt_skater_thx_2[];
extern const UINT8 win_txt_skater_thx_3[];
extern const UINT8 win_txt_skater_thx_4[];
extern const UINT8 win_txt_nli_vp[];
extern const UINT8 win_txt_nli_exec[];
extern const UINT8 win_txt_nli_ceo[];
extern const UINT8 win_txt_nli_sales[];
extern const UINT8 win_txt_nli_jan[];
extern const UINT8 win_txt_nli_mail[];
extern const UINT8 win_txt_nli_no_int[];
extern const UINT8 win_txt_dealer_int[];
extern const UINT8 win_txt_hobo_int[];
extern const UINT8 win_txt_hobo_give_1[];
extern const UINT8 win_txt_hobo_give_2[];
extern const UINT8 win_txt_hobo_give_3[];
extern const UINT8 win_txt_hobo_booze_1[];
extern const UINT8 win_txt_hobo_booze_3[];
extern const UINT8 win_txt_hobo_booze_2[];
