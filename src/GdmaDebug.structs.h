/* 
 * Configuration Registers
 * */
// configuration register 0 of rx channel 0  r/w
struct gdma_in_conf0_ch_reg{
	int offset = 192;
	uint16_t base = 0x0000;
	uint32_t reset = 0;
	uint32_t val = 0;
	
	bool gdma_mem_trans_en_ch = false;
	int gdma_mem_trans_en_ch_pos = 4;

	bool gdma_in_data_burst_en_ch = false;
	int gdma_in_data_burst_en_ch_pos = 3;
	
	bool gdma_indscr_burst_en_ch = false;
	int gdma_indscr_burst_en_ch_pos = 2;
	
	bool gdma_in_loop_test_ch = false;
	int gdma_in_loop_test_ch_pos = 1;
	
	bool gdma_in_rst_ch = false;
	int gdma_in_rst_ch_pos = 0;
};
// configuration register 1 of rx channel 0  r/w
struct gdma_in_conf1_ch_reg{
	int offset = 192;
	uint16_t base = 0x0004;
	uint32_t reset = 0xc;
	uint32_t val = 0;

	uint32_t gdma_in_ext_mem_bk_size_ch = 0;
	  int gdma_in_ext_mem_bk_size_ch_x = 13;
	  int gdma_in_ext_mem_bk_size_ch_y = 14;
	
	bool gdma_in_check_owner_ch = false;
	int gdma_in_check_owner_ch_pos = 12;

	uint32_t gdma_dma_infifo_full_thrs_ch = 0xc;
	int gdma_dma_infifo_full_thrs_ch_x = 0;
	int gdma_dma_infifo_full_thrs_ch_y = 11;

};
// pop control register of rx channel 0  varies
struct gdma_in_pop_ch_reg{
	int offset = 192;
	uint16_t base = 0x001c;
	uint32_t reset = 0x800;
	uint32_t val = 0;
	
	bool gdma_infifo_pop_ch = false;
	int gdma_infifo_pop_ch_pos = 12;
	
	uint32_t gdma_infifo_rdata_ch = 0x800;
	uint32_t gdma_infifo_rdata_ch_x = 0;
	uint32_t gdma_infifo_rdata_ch_y = 11;
};
// link descriptor configuration and control register of rx channel 0   varies
struct gdma_in_link_ch_reg{
	int offset = 192;
	uint16_t base = 0x0020;
	uint32_t reset = 0x1100000;
	uint32_t val = 0;
	
	bool gdma_inlink_park_ch = true;
	int gdma_inlink_park_ch_pos = 24;

	bool gdma_inlink_restart_ch = false;
	int gdma_inlink_restart_ch_pos = 23;

	bool gdma_inlink_start_ch = false;
	int gdma_inlink_start_ch_pos = 22;

	bool gdma_inlink_stop_ch = false;
	int gdma_inlink_stop_ch_pos = 21;

	bool gdma_inlink_auto_ret_ch = true;
	int gdma_inlink_auto_ret_ch_pos = 20;

	uint32_t gdma_inlink_addr_ch = 0x000;
	int gdma_inlink_addr_ch_x = 0;
	int gdma_inlink_addr_ch_y = 19;
};
// configuration register 0 of tx channel 0  r/w
struct gdma_out_conf0_ch_reg{
	int offset = 192;
	uint16_t base = 0x0060;
	uint32_t reset = 0x8;
	uint32_t val = 0;

	bool gdma_out_data_burst_en_ch = 0;
	int gdma_out_data_burst_en_ch_pos = 5;
	
	bool gdma_outdscr_burst_en_ch = 0;
	int gdma_outdscr_burst_en_ch_pos = 4;
	
	bool gdma_out_eof_mode_ch = 1;
	int gdma_out_eof_mode_ch_pos = 3;
	
	bool gdma_out_auto_wrback_ch = 0;
	int gdma_out_auto_wrback_ch_pos = 2;
	
	bool gdma_out_loop_test_ch = 0;
	int gdma_out_loop_test_ch_pos = 1;
	
	bool gdma_out_rst_ch = 0;
	int gdma_out_rst_ch_pos = 0;
};
// configuration register 1 of tx channel 0  r/w
struct gdma_out_conf1_ch_reg{
	int offset = 192;
	uint16_t base = 0x0064;
	uint32_t reset = 0;
	uint32_t val = 0;

	uint32_t gdma_out_ext_mem_bk_size_ch = 0;
	int gdma_out_ext_mem_bk_size_ch_x = 13;
	int gdma_out_ext_mem_bk_size_ch_y = 14;

	bool gdma_out_check_owner_ch = false;
	int gdma_out_check_owner_ch_pos = 12;
};
// push control register of rx channel 0  varies
struct gdma_out_push_ch_reg{
	int offset = 192;
	uint16_t base = 0x007c;
	uint32_t reset = 0;
	uint32_t val = 0;

	bool gdma_outfifo_push_ch = false;
	int gdma_outfifo_push_ch_pos = 9;
	
	uint32_t gdma_outfifo_wdata_ch = 0x0;
	int gdma_outfifo_wdata_ch_x = 0;
	int gdma_outfifo_wdata_ch_y = 8;
};
// link descriptor configuration and control register of tx channel 0   varies
struct gdma_out_link_ch_reg{
	int offset = 192;
	uint16_t base = 0x0080;
	uint32_t reset = 0;
	uint32_t val = 0;
	
	bool gdma_outlink_park_ch = true;
	int gdma_outlink_park_ch_pos = 23;
	
	bool gdma_outlink_restart_ch = false;
	int gdma_outlink_restart_ch_pos = 22;

	bool gdma_outlink_start_ch = false;
	int gdma_outlink_start_ch_pos = 21;

	bool gdma_outlink_stop_ch = false;
	int gdma_outlink_stop_ch_pos = 20;

	uint32_t gdma_outlink_addr_ch = 0x000;
	int gdma_outlink_addr_ch_x = 0;
	int gdma_outlink_addr_ch_y = 19;
};
// reserved  r/w
struct gdma_pd_conf_reg{
	int offset = 0;
	uint16_t base = 0x03c4;
	uint32_t reset = 0;
	uint32_t val = 0;
	
	bool gdma_dma_ram_clk_fo = false;
	int gdma_dma_ram_clk_fo_pos = 6;

	bool gdma_dma_ram_force_pu = true;
	int gdma_dma_ram_force_pu_pos = 5;

	bool gdma_dma_ram_force_pd = false;
	int gdma_dma_ram_force_pd_pos = 4;
};
// miscellaneous register  r/w
struct gdma_misc_conf_reg{
	int offset = 0;
	uint16_t base = 0x03c8;
	uint32_t reset = 0;
	uint32_t val = 0;

	bool gdma_clk_en = false;
	int gdma_clk_en_pos = 4;

	bool gdma_arb_pri_dis = false;
	int gdma_arb_pri_dis_pos = 2;

	bool gdma_ahbm_rst_exter = false;
	int gdma_ahbm_rst_exter_pos = 1;

	bool gdma_ahbm_rst_inter = false;
	int gdma_ahbm_rst_inter_pos = 0;
};

/*
 * Interrupt Registers
 * */
// raw status interrupt of rx channel 0 r/wtc/ss
struct gdma_in_int_raw_ch_reg{
 	int offset = 192;
	uint16_t base = 0x0008;
	uint32_t reset = 0;
	uint32_t val = 0;
	bool gdma_infifo_full_wm_ch0_int_raw = false;
	int  gdma_infifo_full_wm_ch0_int_raw_pos = 5;

	bool gdma_in_dscr_empty_ch0_int_raw = false;
	int  gdma_in_dscr_empty_ch0_int_raw_pos = 4;

	bool gdma_in_dscr_err_ch0_int_raw = false;
	int  gdma_in_dscr_err_ch0_int_raw_pos = 3;

	bool gdma_in_err_eof_ch0_int_raw = false;
	int  gdma_in_err_eof_ch0_int_raw_pos = 2;

	bool gdma_in_suc_eof_ch0_int_raw = false;
	int  gdma_in_suc_eof_ch0_int_raw_pos = 1;

	bool gdma_in_done_ch0_int_raw = false;
	int  gdma_in_done_ch0_int_raw_pos = 0;

}; 
// masked interrupt of rx channel 0 ro
struct gdma_in_int_st_ch_reg{
 	int offset = 192;
	uint16_t base = 0x000c;
	uint32_t reset = 0;
	uint32_t val = 0;

	bool gdma_infifo_full_wm_ch0_int_st = false;
	int  gdma_infifo_full_wm_ch0_int_st_pos = 5;

	bool gdma_in_dscr_empty_ch0_int_st = false;
	int  gdma_in_dscr_empty_ch0_int_st_pos = 4;

	bool gdma_in_dscr_err_ch0_int_st = false;
	int  gdma_in_dscr_err_ch0_int_st_pos = 3;

	bool gdma_in_err_eof_ch0_int_st = false;
	int  gdma_in_err_eof_ch0_int_st_pos = 2;

	bool gdma_in_suc_eof_ch0_int_st = false;
	int  gdma_in_suc_eof_ch0_int_st_pos = 1;

	bool gdma_in_done_ch0_int_st = false;
	int  gdma_in_done_ch0_int_st_pos = 0;

}; 
// interrupt enable bits of rx channel 0 r/w
struct gdma_in_int_ena_ch_reg{
 	int offset = 192;
	uint16_t base = 0x0010;
	uint32_t reset = 0;
	uint32_t val = 0;
	bool gdma_infifo_full_wm_ch0_int_ena = false;
	int  gdma_infifo_full_wm_ch0_int_ena_pos = 5;

	bool gdma_in_dscr_empty_ch0_int_ena = false;
	int  gdma_in_dscr_empty_ch0_int_ena_pos = 4;

	bool gdma_in_dscr_err_ch0_int_ena = false;
	int  gdma_in_dscr_err_ch0_int_ena_pos = 3;

	bool gdma_in_err_eof_ch0_int_ena = false;
	int  gdma_in_err_eof_ch0_int_ena_pos = 2;

	bool gdma_in_suc_eof_ch0_int_ena = false;
	int  gdma_in_suc_eof_ch0_int_ena_pos = 1;

	bool gdma_in_done_ch0_int_ena = false;
	int  gdma_in_done_ch0_int_ena_pos = 0;
}; 
// interrupt clear bits of rx channel 0 wt
struct gdma_in_int_clr_ch_reg{
 	int offset = 192;
	uint16_t base = 0x0014;
	uint32_t reset = 0;
	uint32_t val = 0;
	bool gdma_dma_infifo_full_wm_ch0_int_clr = false;
	int  gdma_dma_infifo_full_wm_ch0_int_clr_pos = 5;

	bool gdma_in_dscr_empty_ch0_int_clr = false;
	int  gdma_in_dscr_empty_ch0_int_clr_pos = 4;

	bool gdma_in_dscr_err_ch0_int_clr = false;
	int  gdma_in_dscr_err_ch0_int_clr_pos = 3;

	bool gdma_in_err_eof_ch0_int_clr = false;
	int  gdma_in_err_eof_ch0_int_clr_pos = 2;

	bool gdma_in_suc_eof_ch0_int_clr = false;
	int  gdma_in_suc_eof_ch0_int_clr_pos = 1;

	bool gdma_in_done_ch0_int_clr = false;
	int  gdma_in_done_ch0_int_clr_pos = 0;
}; 
// raw status interrupt of tx channel 0 r/wtc/ss
struct gdma_out_int_raw_ch_reg{
 	int offset = 192;
	uint16_t base = 0x0068;
	uint32_t reset = 0;
	uint32_t val = 0;

	bool gdma_out_total_eof_ch0_int_raw = false;
	int  gdma_out_total_eof_ch0_int_raw_pos = 3;

	bool gdma_out_dscr_err_ch0_int_raw = false;
	int  gdma_out_dscr_err_ch0_int_raw_pos = 2;

	bool gdma_out_eof_ch0_int_raw = false;
	int  gdma_out_eof_ch0_int_raw_pos = 1;

	bool gdma_out_done_ch0_int_raw = false;
	int  gdma_out_done_ch0_int_raw_pos = 0;
}; 
// masked interrupt of tx channel 0 ro
struct gdma_out_int_st_ch_reg{
 	int offset = 192;
	uint16_t base = 0x006c;
	uint32_t reset = 0;
	uint32_t val = 0;
	
	bool gdma_out_total_eof_ch0_int_st = false;
	int  gdma_out_total_eof_ch0_int_st_pos = 3;

	bool gdma_out_dscr_err_ch0_int_st = false;
	int  gdma_out_dscr_err_ch0_int_st_pos = 2;

	bool gdma_out_eof_ch0_int_st = false;
	int  gdma_out_eof_ch0_int_st_pos = 1;

	bool gdma_out_done_ch0_int_st = false;
	int  gdma_out_done_ch0_int_st_pos = 0;
}; 
// interrupt enable bits of tx channel 0 r/w
struct gdma_out_int_ena_ch_reg{
 	int offset = 192;
	uint16_t base = 0x0070;
	uint32_t reset = 0;
	uint32_t val = 0;

	bool gdma_out_total_eof_ch0_int_ena = false;
	int  gdma_out_total_eof_ch0_int_ena_pos = 3;

	bool gdma_out_dscr_err_ch0_int_ena = false;
	int  gdma_out_dscr_err_ch0_int_ena_pos = 2;

	bool gdma_out_eof_ch0_int_ena = false;
	int  gdma_out_eof_ch0_int_ena_pos = 1;

	bool gdma_out_done_ch0_int_ena = false;
	int  gdma_out_done_ch0_int_ena_pos = 0;
}; 
// interrupt clear bits of tx channel 0 wt
struct gdma_out_int_clr_ch_reg{
 	int offset = 192;
	uint16_t base = 0x0074;
	uint32_t reset = 0;
	uint32_t val = 0;

	bool gdma_out_total_eof_ch0_int_clr = false;
	int  gdma_out_total_eof_ch0_int_clr_pos = 3;

	bool gdma_out_dscr_err_ch0_int_clr = false;
	int  gdma_out_dscr_err_ch0_int_clr_pos = 2;

	bool gdma_out_eof_ch0_int_clr = false;
	int  gdma_out_eof_ch0_int_clr_pos = 1;

	bool gdma_out_done_ch0_int_clr = false;
	int  gdma_out_done_ch0_int_clr_pos = 0;
}; 
// raw interrupt status of external ram permission r/wtc/ss
struct gdma_extmem_reject_int_raw_reg{
 	int offset = 192;
	uint16_t base = 0x03fc;
	uint32_t reset = 0;
	uint32_t val = 0;

	bool gdma_extmem_reject_int_raw = false;
	int  gdma_extmem_reject_int_raw_pos = 0;
}; 
// masked interrupt status of external ram permission ro
struct gdma_extmem_reject_int_st_reg{
 	int offset = 192;
	uint16_t base = 0x0400;
	uint32_t reset = 0;
	uint32_t val = 0;

	bool gdma_extmem_reject_int_st = false;
	int gdma_extmem_reject_int_st_pos = 0;
}; 
// interrupt enable bits of external ram permission r/w
struct gdma_extmem_reject_int_ena_reg{
 	int offset = 192;
	uint16_t base = 0x0404;
	uint32_t reset = 0;
	uint32_t val = 0;

	bool gdma_extmem_reject_int_ena = false;
	int gdma_extmem_reject_int_ena_pos = 0;
}; 
// interrupt clear bits of external ram permission wt
struct gdma_extmem_reject_int_clr_reg{
 	int offset = 192;
	uint16_t base = 0x0408;
	uint32_t reset = 0;
	uint32_t val = 0;

	bool gdma_extmem_reject_int_clr = false;
	int gdma_extmem_reject_int_clr_pos = 0;
}; 


/*
 * Status Registers
 * */
struct gdma_infifo_status_chn_reg{
	int offset = 192;
	uint16_t base = 0x0018;
	uint32_t reset = 0;
	uint32_t val = 0;

	uint32_t gdma_infifo_cnt_l3_ch0 = 0;
	int gdma_infifo_cnt_l3_ch0_x = 19;
	int gdma_infifo_cnt_l3_ch0_y = 23;

	uint32_t gdma_infifo_cnt_l2_ch0 = 0;
	int gdma_infifo_cnt_l2_ch0_x = 12;
	int gdma_infifo_cnt_l2_ch0_y = 18;

	uint32_t gdma_infifo_cnt_l1_ch0 = 0;
	int gdma_infifo_cnt_l1_ch0_x = 6;
	int gdma_infifo_cnt_l1_ch0_y = 11;

	bool gdma_infifo_empty_l3_ch0 = true;
	int gdma_infifo_empty_l3_ch0_pos = 5;

	bool gdma_infifo_full_l3_ch0 = true;
	int gdma_infifo_full_l3_ch0_pos = 4;

	bool gdma_infifo_empty_l2_ch0 = true;
	int gdma_infifo_empty_l2_ch0_pos = 3;

	bool gdma_infifo_full_l2_ch0 = true;
	int gdma_infifo_full_l2_ch0_pos = 2;

	bool gdma_infifo_empty_l1_ch0 = true;
	int gdma_infifo_empty_l1_ch0_pos = 1;

	bool gdma_infifo_full_l1_ch0 = true;
	int gdma_infifo_full_l1_ch0_pos = 0;
};

struct gdma_in_state_chn_reg{
	int offset = 192;
	uint16_t base = 0x0024;
	uint32_t reset = 0;
	uint32_t val = 0;

	uint32_t gdma_inlink_dscr_addr_ch0 = 0;
	int gdma_inlink_dscr_addr_ch0_x = 0;
	int gdma_inlink_dscr_addr_ch0_y = 17;
};

struct gdma_in_suc_eof_des_addr_chn_reg{
	int offset = 192;
	uint16_t base = 0x0028;
	uint32_t reset = 0;
	uint32_t val = 0;

	uint32_t gdma_in_suc_eof_des_addr_ch0 = 0x000000;
	int gdma_in_suc_eof_des_addr_ch0_x = 0;
	int gdma_in_suc_eof_des_addr_ch0_y = 31;
};

struct gdma_in_err_eof_des_addr_chn_reg{
	int offset = 192;
	uint16_t base = 0x002c;
	uint32_t reset = 0;
	uint32_t val = 0;

	uint32_t gdma_in_err_eof_des_addr_ch0 = 0x000000;
	int gdma_in_err_eof_des_addr_ch0_x = 0;
	int gdma_in_err_eof_des_addr_ch0_y = 31;
};

struct gdma_in_dscr_chn_reg{
	int offset = 192;
	uint16_t base = 0x0030;
	uint32_t reset = 0;
	uint32_t val = 0;

	uint32_t gdma_inlink_dscr_ch0 = 0;
	int gdma_inlink_dscr_ch0_x = 0;
	int gdma_inlink_dscr_ch0_y = 31;
};

struct gdma_in_dscr_bf0_chn_reg{
	int offset = 192;
	uint16_t base = 0x0034;
	uint32_t reset = 0;
	uint32_t val = 0;

	uint32_t gdma_inlink_dscr_bf0_ch0 = 0;
	int gdma_inlink_dscr_bf0_ch0_x = 0;
	int gdma_inlink_dscr_bf0_ch0_y = 31;
};

struct gdma_in_dscr_bf1_chn_reg{
	int offset = 192;
	uint16_t base = 0x0038;
	uint32_t reset = 0;
	uint32_t val = 0;

	uint32_t gdma_inlink_dscr_bf1_ch0 = 0;
	int gdma_inlink_dscr_bf1_ch0_x = 0;
	int gdma_inlink_dscr_bf1_ch0_y = 31;
};

struct gdma_outfifo_status_chn_reg{
	int offset = 192;
	uint16_t base = 0x0078;
	uint32_t reset = 0;
	uint32_t val = 0;

	bool gdma_out_remain_under_4b_l3_ch0 = true;
	int gdma_out_remain_under_4b_l3_ch0_pos = 26;

	bool gdma_out_remain_under_3b_l3_ch0 = true;
	int gdma_out_remain_under_3b_l3_ch0_pos = 25;

	bool gdma_out_remain_under_2b_l3_ch0 = true;
	int gdma_out_remain_under_2b_l3_ch0_pos = 24;

	bool gdma_out_remain_under_1b_l3_ch0 = true;
	int gdma_out_remain_under_1b_l3_ch0_pos = 23;

	uint32_t gdma_outfifo_cnt_l3_ch0 = 0;
	int gdma_outfifo_cnt_l3_ch0_x = 18;
	int gdma_outfifo_cnt_l3_ch0_y = 22;

	uint32_t gdma_outfifo_cnt_l2_ch0 = 0;
	int gdma_outfifo_cnt_l2_ch0_x = 11;
	int gdma_outfifo_cnt_l2_ch0_y = 17;

	uint32_t gdma_outfifo_cnt_l1_ch0 = 0;
	int gdma_outfifo_cnt_l1_ch0_x = 6;
	int gdma_outfifo_cnt_l1_ch0_y = 10;

	bool gdma_outfifo_empty_l3_ch0 = true;
	int gdma_outfifo_empty_l3_ch0_pos = 5;

	bool gdma_outfifo_full_l3_ch0 = true;
	int gdma_outfifo_full_l3_ch0_pos = 4;

	bool gdma_outfifo_empty_l2_ch0 = true;
	int gdma_outfifo_empty_l2_ch0_pos = 3;

	bool gdma_outfifo_full_l2_ch0 = true;
	int gdma_outfifo_full_l2_ch0_pos = 2;

	bool gdma_outfifo_empty_l1_ch0 = true;
	int gdma_outfifo_empty_l1_ch0_pos = 1;

	bool gdma_outfifo_full_l1_ch0 = true;
	int gdma_outfifo_full_l1_ch0_pos = 0;
};

struct gdma_out_state_chn_reg{
	int offset = 192;
	uint16_t base = 0x0084;
	uint32_t reset = 0;
	uint32_t val = 0;

	uint32_t gdma_out_state_ch0 = 0;
	int gdma_out_state_ch0_x = 20;
	int gdma_out_state_ch0_y = 22;

	uint32_t gdma_out_dscr_state_ch0 = 0;
	int gdma_out_dscr_state_ch0_x = 18;
	int gdma_out_dscr_state_ch0_y = 19;

	uint32_t gdma_outlink_dscr_addr_ch0 = 0;
	int gdma_outlink_dscr_addr_ch0_x = 0;
	int gdma_outlink_dscr_addr_ch0_y = 17;
};

struct gdma_out_eof_des_addr_chn_reg{
	int offset = 192;
	uint16_t base = 0x0088;
	uint32_t reset = 0;
	uint32_t val = 0;

	uint32_t gdma_out_eof_des_addr_ch0 = 0x000000;
	int gdma_out_eof_des_addr_ch0_x = 0;
	int gdma_out_eof_des_addr_ch0_y = 31;
};

struct gdma_out_eof_bfr_des_addr_chn_reg{
	int offset = 192;
	uint16_t base = 0x008c;
	uint32_t reset = 0;
	uint32_t val = 0;

	uint32_t gdma_out_eof_bfr_des_addr_ch0 = 0x000000;
	int gdma_out_eof_bfr_des_addr_ch0_x = 0;
	int gdma_out_eof_bfr_des_addr_ch0_y = 31;
};

struct gdma_out_dscr_chn_reg{
	int offset = 192;
	uint16_t base = 0x0090;
	uint32_t reset = 0;
	uint32_t val = 0;

	uint32_t gdma_outlink_dscr_ch0 = 0;
	int gdma_outlink_dscr_ch0_x = 0;
	int gdma_outlink_dscr_ch0_y = 31;
};

struct gdma_out_dscr_bf0_chn_reg{
	int offset = 192;
	uint16_t base = 0x0094;
	uint32_t reset = 0;
	uint32_t val = 0;

	uint32_t gdma_outlink_dscr_bf0_ch0 = 0;
	int gdma_outlink_dscr_bf0_ch0_x = 0;
	int gdma_outlink_dscr_bf0_ch0_y = 31;
};

struct gdma_out_dscr_bf1_chn_reg{
	int offset = 192;
	uint16_t base = 0x0098;
	uint32_t reset = 0;
	uint32_t val = 0;

	uint32_t gdma_outlink_dscr_bf1_ch0 = 0;
	int gdma_outlink_dscr_bf1_ch0_x = 0;
	int gdma_outlink_dscr_bf1_ch0_y = 31;
};

/*
 * Priority Registers
 * */
struct gdma_in_pri_chn_reg{
	int offset = 192;
	uint16_t base = 0x0044;
	uint32_t reset = 0;
	uint32_t val = 0;

	uint32_t gdma_rx_pri_ch0 = 0;
	int gdma_rx_pri_ch0_x = 0;
	int gdma_rx_pri_ch0_y = 3;
};
struct gdma_out_pri_chn_reg{
	int offset = 192;
	uint16_t base = 0x00a4;
	uint32_t reset = 0;
	uint32_t val = 0;

	uint32_t gdma_tx_pri_ch0 = 0;
	int gdma_tx_pri_ch0_x = 0;
	int gdma_tx_pri_ch0_y = 3;
};

/*
 * Peripheral Selection Registers
 * */
struct gdma_in_peri_sel_chn_reg{
	int offset = 192;
	uint16_t base = 0x0048;
	uint32_t reset = 0x3f;
	uint32_t val = 0;

	uint32_t gdma_peri_in_sel_ch0 = 0x3f;
	int gdma_peri_in_sel_ch0_x = 0;
	int gdma_peri_in_sel_ch0_y = 5;
};
struct gdma_out_peri_sel_chn_reg{
	int offset = 192;
	uint16_t base = 0x00a8;
	uint32_t reset = 0x3f;
	uint32_t val = 0;

	uint32_t gdma_peri_out_sel_ch0 = 0x3f;
	int gdma_peri_out_sel_ch0_x = 0;
	int gdma_peri_out_sel_ch0_y = 5;
};

/*
 * Permission Status Registers
 * */
struct gdma_extmem_reject_addr_reg{
	int offset = 0;
	uint16_t base = 0x03f4;
	uint32_t reset = 0;
	uint32_t val = 0;

	uint32_t gdma_extmem_reject_addr = 0;
	int gdma_extmem_reject_addr_x = 0;
	int gdma_extmem_reject_addr_y = 31;
};
struct gdma_extmem_reject_st_reg{
	int offset = 0;
	uint16_t base = 0x03f8;
	uint32_t reset = 0;
	uint32_t val = 0;

	uint32_t gdma_extmem_reject_peri_num = 0;
	int gdma_extmem_reject_peri_num_x = 6;
	int gdma_extmem_reject_peri_num_y = 11;

	uint32_t gdma_extmem_reject_channel_num = 0;
	int gdma_extmem_reject_channel_num_x = 2;
	int gdma_extmem_reject_channel_num_y = 5;

	uint32_t gdma_extmem_reject_atrr = 0;
	int gdma_extmem_reject_atrr_x = 0;
	int gdma_extmem_reject_atrr_y = 1;
};

/*
 * Version Register
 * */
struct gdma_date_reg{
	int offset = 0;
	uint16_t base = 0x040c;
	uint32_t reset = 0x2101180;
	uint32_t val = 0;

	uint32_t gdma_date = 0x2101180;
	int gdma_date_x = 0;
	int gdma_date_y = 31;
};
