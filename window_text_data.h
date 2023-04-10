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
extern const UINT8 win_txt_rob_caught[];
extern const UINT8 win_txt_rob_success[];
extern const UINT8 win_txt_rank_boy_scout[];
extern const UINT8 win_txt_rank_juvenile_delinquent[];
extern const UINT8 win_txt_rank_demi_god[];
extern const UINT8 win_txt_rank_seed_of_evil[];
extern const UINT8 win_txt_rank_exceptional[];
extern const UINT8 win_txt_rank_utter_failure[];
extern const UINT8 win_txt_rank_multimillionaire[];
extern const UINT8 win_txt_rank_selfless_millionaire[];
extern const UINT8 win_txt_rank_genuine_hellraiser[];
extern const UINT8 win_txt_rank_extraordinary[];
extern const UINT8 win_txt_rank_millionaire[];
extern const UINT8 win_txt_rank_undeniably_wicked[];
extern const UINT8 win_txt_rank_mediocre[];
extern const UINT8 win_txt_rank_white_collar_criminal[];
extern const UINT8 win_txt_rank_girl_scout[];
extern const UINT8 win_txt_rank_extraordinarily_evil[];
extern const UINT8 win_txt_rank_philanthropist[];
extern const UINT8 win_txt_rank_mr_dog[];
extern const UINT8 win_txt_rank_god[];
extern const UINT8 win_txt_rank_billionaire_god[];
extern const UINT8 win_txt_rank_novice[];
extern const UINT8 win_txt_rank_drug_lord[];
extern const UINT8 win_txt_rank_loser[];
extern const UINT8 win_txt_rank_genius[];
extern const UINT8 win_txt_rank_apostle[];
extern const UINT8 win_txt_rank_hopeless[];
extern const UINT8 win_txt_rank_saint[];
extern const UINT8 win_txt_rank_extraordinarily_good[];
extern const UINT8 win_txt_rank_petty_criminal[];
extern const UINT8 win_txt_rank_car_jacker[];
extern const UINT8 win_txt_rank_mr_natas[];
extern const UINT8 win_txt_rank_incompetent[];
extern const UINT8 win_txt_rank_wuss[];
extern const UINT8 win_txt_rank_good_samaritan[];
extern const UINT8 win_txt_general_unimplemented[];
extern const UINT8 win_txt_appstore_tv[];
extern const UINT8 win_txt_appstore_pc[];
extern const UINT8 win_txt_appstore_df[];
extern const UINT8 win_txt_appstore_tm[];
extern const UINT8 win_txt_appstore_bed[];
extern const UINT8 win_txt_nli_vp[];
extern const UINT8 win_txt_nli_exec[];
extern const UINT8 win_txt_nli_ceo[];
extern const UINT8 win_txt_nli_sales[];
extern const UINT8 win_txt_nli_jan[];
extern const UINT8 win_txt_nli_mail[];
extern const UINT8 win_txt_nli_no_int[];
extern const UINT8 win_txt_end_died[];
extern const UINT8 win_txt_end_time[];
extern const UINT8 win_txt_dealer_int[];
extern const UINT8 win_txt_hobo_int[];
extern const UINT8 win_txt_hobo_give_1[];
extern const UINT8 win_txt_hobo_give_2[];
extern const UINT8 win_txt_hobo_give_3[];
extern const UINT8 win_txt_hobo_booze_1[];
extern const UINT8 win_txt_hobo_booze_3[];
extern const UINT8 win_txt_hobo_booze_2[];
extern const UINT8 win_txt_bar_int[];
extern const UINT8 win_txt_restaurant_int[];
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
extern const UINT8 win_txt_barfight_win2[];
extern const UINT8 win_txt_barfight_win[];
extern const UINT8 win_txt_barfight_noattckpnts[];
