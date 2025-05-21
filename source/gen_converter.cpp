/*
void set_origin_pid_iv(struct gen3_mon* dst, struct gen3_mon_data_unenc* data_dst, u16 species, u16 wanted_ivs, u8 wanted_nature, u8 ot_gender, u8 is_egg, u8 no_restrictions) {
    struct game_data_t* trainer_data = get_own_game_data();
    struct gen3_mon_misc* misc = &data_dst->misc;
    u8 trainer_game_version = id_to_version(&trainer_data->game_identifier);
    u8 trainer_gender = trainer_data->trainer_gender;
    
    // Normalize nature
    wanted_nature = get_nature(wanted_nature);
    
    // Handle eggs separately
    u32 ot_id = dst->ot_id;
    if(is_egg)
        ot_id = trainer_data->trainer_id;
    
    // Prepare the TSV
    u16 tsv = (ot_id & 0xFFFF) ^ (ot_id >> 16);

    u8 chosen_version = get_default_conversion_game();
    if(!no_restrictions) {
        chosen_version = trainer_game_version;
        ot_gender = trainer_gender;
    }

    u8 encounter_type = get_encounter_type_gen3(species);
    u8 is_shiny = is_shiny_gen2_unfiltered(wanted_ivs);
    // To debug shiny Unown stuff more than normally possible
    //is_shiny = 1;
    u32 ivs = 0;
    u8 ability = 0;
    u8 is_ability_set = 0;
    u32 valid_balls = 0;
    const u8* searchable_table = egg_locations_bin;
    u8 find_in_table = 0;
    
    // Get PID and IVs
    switch(encounter_type) {
        case STATIC_ENCOUNTER:
            valid_balls = VALID_POKEBALL_NO_EGG;
            if(get_event_info_replacement() && (species == CELEBI_SPECIES)) {
                valid_balls = VALID_POKEBALL_CELEBI;
                chosen_version = R_VERSION_ID;
                generate_generic_genderless_shadow_info_xd(wanted_nature, 0, wanted_ivs, tsv, &dst->pid, &ivs, &ability);
                is_ability_set = 1;
                ot_gender = 1;
            }
            else if(!is_shiny) {
                // Prefer Colosseum/XD encounter, if possible
                if(get_conversion_colo_xd() && is_static_in_xd(species) && are_colo_valid_tid_sid(ot_id & 0xFFFF, ot_id >> 0x10) && ((ot_gender == 0) || (!get_prioritize_ot_gender()))) {
                    chosen_version = COLOSSEUM_CODE;
                    generate_generic_genderless_shadow_info_xd(wanted_nature, has_prev_check_tsv_in_xd(species), wanted_ivs, tsv, &dst->pid, &ivs, &ability);
                    misc->ribbons |= COLO_RIBBON_VALUE;
                    is_ability_set = 1;
                    ot_gender = 0;
                    data_dst->learnable_moves = (const struct learnset_data_mon_moves*)get_learnset_for_species((const u16*)learnset_static_xd_bin, species);
                }
                else
                    generate_static_info(wanted_nature, wanted_ivs, tsv, &dst->pid, &ivs);
            }
            else
                generate_static_shiny_info(wanted_nature, tsv, &dst->pid, &ivs);
            searchable_table = encounters_static_bin;
            find_in_table = 1;
            break;
        case ROAMER_ENCOUNTER:
            valid_balls = VALID_POKEBALL_NO_EGG;
            // Prefer Colosseum/XD encounter, if possible
            if(get_conversion_colo_xd() && are_colo_valid_tid_sid(ot_id & 0xFFFF, ot_id >> 0x10) && ((ot_gender == 0) || (!get_prioritize_ot_gender()))) {
                chosen_version = COLOSSEUM_CODE;
                if(!is_shiny)
                    generate_generic_genderless_shadow_info_colo(wanted_nature, wanted_ivs, tsv, &dst->pid, &ivs, &ability);
                else
                    generate_generic_genderless_shadow_shiny_info_colo(wanted_nature, tsv, &dst->pid, &ivs, &ability);
                misc->ribbons |= COLO_RIBBON_VALUE;
                is_ability_set = 1;
                ot_gender = 0;
            }
            else {
                if(!is_shiny)
                    generate_static_info(wanted_nature, wanted_ivs, tsv, &dst->pid, &ivs);
                else
                    generate_static_shiny_info(wanted_nature, tsv, &dst->pid, &ivs);
                // Roamers only get the first byte of their IVs
                ivs &= 0xFF;
            }
            searchable_table = encounters_roamers_bin;
            find_in_table = 1;
            break;
        case UNOWN_ENCOUNTER:
            valid_balls = VALID_POKEBALL_NO_EGG;
            if(!is_shiny)
                generate_unown_info(wanted_nature, wanted_ivs, tsv, &dst->pid, &ivs);
            else
                generate_unown_shiny_info(wanted_nature, wanted_ivs, tsv, &dst->pid, &ivs);
            searchable_table = encounters_unown_bin;
            find_in_table = 1;
            break;
        default:
            valid_balls = VALID_POKEBALL_EGG;
            if(!is_shiny)
                generate_egg_info(species, wanted_nature, wanted_ivs, tsv, 2, &dst->pid, &ivs);
            else
                generate_egg_shiny_info(species, wanted_nature, wanted_ivs, tsv, 2, &dst->pid, &ivs);
            break;
    }
    
    // Set met location and origins info
    u8 met_location = egg_locations_bin[chosen_version];
    if(!is_egg)
        met_location = get_egg_met_location();
    u8 met_level = 0;
    u8 obedience = 0;
    
    if(find_in_table) {
        u16 mon_index = get_mon_index(species, dst->pid, 0, 0);
        const struct mon_general_met_data_gen3* possible_met_data = (const struct mon_general_met_data_gen3*)search_table_for_index(searchable_table, mon_index);
        if(possible_met_data != NULL) {
            u8 num_elems = possible_met_data->num_entries;
            u8 chosen_entry = 0;
            for(int i = 0; i < num_elems; i++)
                if((possible_met_data->met_data_entries[i].origin_game) == chosen_version)
                    chosen_entry = i;
            chosen_version = possible_met_data->met_data_entries[chosen_entry].origin_game;
            obedience = possible_met_data->met_data_entries[chosen_entry].obedience;
            met_location = possible_met_data->met_data_entries[chosen_entry].location;
            met_level = possible_met_data->met_data_entries[chosen_entry].level;
        }
    }

*/