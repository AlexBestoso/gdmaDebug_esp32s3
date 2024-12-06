#include <Arduino.h>
#include <cstdint>
#include "./GdmaDebug.h"

/* (D/C)tors */
GdmaDebug::GdmaDebug(void){
	this->channel = 0;
}

GdmaDebug::~GdmaDebug(){

}
/* Private */
void GdmaDebug::regWrite(uint32_t reg, uint32_t val, int offset){
	reg = reg + (this->channel*offset);
	Serial.printf("Writing 0x%X to the address 0x%X\n", val, reg+DBG_PERF_GDMA_BASE);
	DBG_PERF_GDMA_WRITE(reg, val);
}
uint32_t GdmaDebug::regRead(uint32_t reg, int offset){
	reg = reg + (this->channel*offset);
	return DBG_PERF_GDMA_READ(reg);
}

// Helps isoltate fields within the 32 bit registers.
bool GdmaDebug::regGet(uint32_t val, int pos){
	int grabber = 1 << pos;
	int result = (val & grabber) >> pos;
	return result == 1 ? true : false;
}
int GdmaDebug::regGet(uint32_t val, int x, int y){
	int retSize = (y-x)+1;
	int grabber = 0;
	for(int i=0; i<retSize;i++)
		grabber = (grabber <<1)+1;
	int result = (val & (grabber << x)) >> x;
	return result;
}

// Helps convert register structs into single register values
uint32_t GdmaDebug::regSet(uint32_t reg, bool val, int pos){
	int v = val ? 1 : 0;
	reg &= ~(1<<pos);
	reg += (v<<pos);
	return reg;
}

uint32_t GdmaDebug::regSet(uint32_t reg, int val, int x, int y){
	int s = y - x;
	int g = 0;
	for(int i=0; i<s; i++)
		g = (g << 1) + 1;
	val &= g;
	reg &= ~(1<<x);
	reg += (val << x);
	return reg;
}

	/*
	 * Struct Initalization Functions 
	*/
	void GdmaDebug::init(void){
		this->initConfigRegs();
		this->initInterruptRegs();
		this->initStatusRegs();
		this->initPriorityRegs();
		this->initPeriphSelRegs();
		this->initPermissionStatRegs();
		this->init_date();
	}
	void GdmaDebug::refresh(void){
		this->init();
	}

	// Configuration Registers
	void GdmaDebug::initConfigRegs(void){
		this->init_in_conf0();
		this->init_in_conf1(); 
		this->init_in_pop();
		this->init_in_link();
		this->init_out_conf0();
		this->init_out_conf1();
		this->init_out_push();
		this->init_out_link();
		this->init_pd_conf();
		this->init_misc_conf();
	}

	void GdmaDebug::init_in_conf0(void){
		int offset = this->in_conf0.offset;
		uint16_t base = this->in_conf0.base;
		this->in_conf0.val = this->regRead(base, offset);
		this->in_conf0.gdma_mem_trans_en_ch = this->regGet(
			this->in_conf0.val,
			this->in_conf0.gdma_mem_trans_en_ch_pos
		);
		this->in_conf0.gdma_in_data_burst_en_ch = this->regGet(
			this->in_conf0.val,
			this->in_conf0.gdma_in_data_burst_en_ch_pos
		);
		this->in_conf0.gdma_indscr_burst_en_ch = this->regGet(
			this->in_conf0.val,
			this->in_conf0.gdma_indscr_burst_en_ch_pos
		);
		this->in_conf0.gdma_in_loop_test_ch = this->regGet(
			this->in_conf0.val,
			this->in_conf0.gdma_in_loop_test_ch_pos
		);
		this->in_conf0.gdma_in_rst_ch = this->regGet(
			this->in_conf0.val,
			this->in_conf0.gdma_in_rst_ch_pos
		);
	}
	void GdmaDebug::init_in_conf1(void){
		int offset = this->in_conf1.offset;
		uint16_t base = this->in_conf1.base;
		this->in_conf1.val = this->regRead(base, offset);
		this->in_conf1.gdma_in_ext_mem_bk_size_ch = this->regGet(
			this->in_conf1.val,
			this->in_conf1.gdma_in_ext_mem_bk_size_ch_x,
			this->in_conf1.gdma_in_ext_mem_bk_size_ch_y
		);
		this->in_conf1.gdma_in_check_owner_ch = this->regGet(
			this->in_conf1.val,
			this->in_conf1.gdma_in_check_owner_ch_pos
		);
		this->in_conf1.gdma_dma_infifo_full_thrs_ch = this->regGet(
			this->in_conf1.val,
			this->in_conf1.gdma_dma_infifo_full_thrs_ch_x,
			this->in_conf1.gdma_dma_infifo_full_thrs_ch_y
		);
	}
	void GdmaDebug::init_in_pop(void){
		int offset = this->in_pop.offset;
		uint16_t base = this->in_pop.base;
		this->in_pop.val = this->regRead(base, offset);
		this->in_pop.gdma_infifo_pop_ch = this->regGet(
			this->in_pop.val,
			this->in_pop.gdma_infifo_pop_ch_pos
		);
	}
	void GdmaDebug::init_in_link(void){
		int offset = this->in_link.offset;
		uint16_t base = this->in_link.base;
		this->in_link.val = this->regRead(base, offset);
		this->in_link.gdma_inlink_park_ch = this->regGet(
			this->in_link.val,
			this->in_link.gdma_inlink_park_ch_pos
		);
		this->in_link.gdma_inlink_restart_ch = this->regGet(
			this->in_link.val,
			this->in_link.gdma_inlink_restart_ch_pos
		);
		this->in_link.gdma_inlink_start_ch = this->regGet(
			this->in_link.val,
			this->in_link.gdma_inlink_start_ch_pos
		);
		this->in_link.gdma_inlink_stop_ch = this->regGet(
			this->in_link.val,
			this->in_link.gdma_inlink_stop_ch_pos
		);
		this->in_link.gdma_inlink_auto_ret_ch = this->regGet(
			this->in_link.val,
			this->in_link.gdma_inlink_auto_ret_ch_pos
		);
		this->in_link.gdma_inlink_addr_ch = this->regGet(
			this->in_link.val,
			this->in_link.gdma_inlink_addr_ch_x,
			this->in_link.gdma_inlink_addr_ch_y
		);
	}
	void GdmaDebug::init_out_conf0(void){
		int offset = this->out_conf0.offset;
		uint16_t base = this->out_conf0.base;
		this->out_conf0.val = this->regRead(base, offset);
		this->out_conf0.gdma_out_data_burst_en_ch = this->regGet(
			this->out_conf0.val,
			this->out_conf0.gdma_out_data_burst_en_ch_pos
		);
		this->out_conf0.gdma_outdscr_burst_en_ch = this->regGet(
			this->out_conf0.val,
			this->out_conf0.gdma_outdscr_burst_en_ch_pos
		);
		this->out_conf0.gdma_out_eof_mode_ch = this->regGet(
			this->out_conf0.val,
			this->out_conf0.gdma_out_eof_mode_ch_pos
		);
		this->out_conf0.gdma_out_auto_wrback_ch = this->regGet(
			this->out_conf0.val,
			this->out_conf0.gdma_out_auto_wrback_ch_pos
		);
		this->out_conf0.gdma_out_loop_test_ch = this->regGet(
			this->out_conf0.val,
			this->out_conf0.gdma_out_loop_test_ch_pos
		);
		this->out_conf0.gdma_out_rst_ch = this->regGet(
			this->out_conf0.val,
			this->out_conf0.gdma_out_rst_ch_pos
		);
	}
	void GdmaDebug::init_out_conf1(void){
		int offset = this->out_conf1.offset;
		uint16_t base = this->out_conf1.base;
		this->out_conf1.val = this->regRead(base, offset);
		this->out_conf1.gdma_out_ext_mem_bk_size_ch = this->regGet(
			this->out_conf1.val,
			this->out_conf1.gdma_out_ext_mem_bk_size_ch_x,
			this->out_conf1.gdma_out_ext_mem_bk_size_ch_y
		);
		this->out_conf1.gdma_out_check_owner_ch = this->regGet(
			this->out_conf1.val,
			this->out_conf1.gdma_out_check_owner_ch_pos
		);
	}
	void GdmaDebug::init_out_push(void){
		int offset = this->out_push.offset;
		uint16_t base = this->out_push.base;
		this->out_push.val = this->regRead(base, offset);
		this->out_push.gdma_outfifo_push_ch = this->regGet(
			this->out_push.val,
			this->out_push.gdma_outfifo_push_ch_pos
		);
		this->out_push.gdma_outfifo_wdata_ch = this->regGet(
			this->out_push.val,
			this->out_push.gdma_outfifo_wdata_ch_x,
			this->out_push.gdma_outfifo_wdata_ch_y
		);
	}
	void GdmaDebug::init_out_link(void){
		int offset = this->out_link.offset;
		uint16_t base = this->out_link.base;
		this->out_link.val = this->regRead(base, offset);
		this->out_link.gdma_outlink_park_ch = this->regGet(
			this->out_link.val,
			this->out_link.gdma_outlink_park_ch_pos
		);
		this->out_link.gdma_outlink_restart_ch = this->regGet(
			this->out_link.val,
			this->out_link.gdma_outlink_restart_ch_pos
		);
		this->out_link.gdma_outlink_start_ch = this->regGet(
			this->out_link.val,
			this->out_link.gdma_outlink_start_ch_pos
		);
		this->out_link.gdma_outlink_stop_ch = this->regGet(
			this->out_link.val,
			this->out_link.gdma_outlink_stop_ch_pos
		);
		this->out_link.gdma_outlink_addr_ch = this->regGet(
			this->out_link.val,
			this->out_link.gdma_outlink_addr_ch_x,
			this->out_link.gdma_outlink_addr_ch_y
		);
	}
	void GdmaDebug::init_pd_conf(void){
		int offset = this->pd_conf.offset;
		uint16_t base = this->pd_conf.base;
		this->pd_conf.val = this->regRead(base, offset);
		this->pd_conf.gdma_dma_ram_clk_fo = this->regGet(
			this->pd_conf.val,
			this->pd_conf.gdma_dma_ram_clk_fo_pos
		);
		this->pd_conf.gdma_dma_ram_force_pu = this->regGet(
			this->pd_conf.val,
			this->pd_conf.gdma_dma_ram_force_pu_pos
		);
		this->pd_conf.gdma_dma_ram_force_pd = this->regGet(
			this->pd_conf.val,
			this->pd_conf.gdma_dma_ram_force_pd_pos
		);
	}
	void GdmaDebug::init_misc_conf(void){
		int offset = this->misc_conf.offset;
		uint16_t base = this->misc_conf.base;
		this->misc_conf.val = this->regRead(base, offset);
		this->misc_conf.gdma_clk_en = this->regGet(
			this->misc_conf.val,
			this->misc_conf.gdma_clk_en_pos
		);
		this->misc_conf.gdma_arb_pri_dis = this->regGet(
			this->misc_conf.val,
			this->misc_conf.gdma_arb_pri_dis_pos
		);
		this->misc_conf.gdma_ahbm_rst_exter = this->regGet(
			this->misc_conf.val,
			this->misc_conf.gdma_ahbm_rst_exter_pos
		);
		this->misc_conf.gdma_ahbm_rst_inter = this->regGet(
			this->misc_conf.val,
			this->misc_conf.gdma_ahbm_rst_inter_pos
		);
	}
	// Interrupt Registers
	void GdmaDebug::initInterruptRegs(void){
		this->init_in_int_raw();
		this->init_in_int_st();
		this->init_in_int_ena();
		this->init_in_int_clr();
		this->init_out_int_raw();
		this->init_out_int_st();
		this->init_out_int_ena();
		this->init_out_int_clr();
		this->init_extmem_reject_int();
		this->init_extmem_reject_int_st();
		this->init_extmem_reject_int_ena();
		this->init_extmem_reject_int_clr();
	}

	void GdmaDebug::init_in_int_raw(void){
		int offset = this->in_int_raw.offset;
		uint16_t base = this->in_int_raw.base;
		this->in_int_raw.val = this->regRead(base, offset);
		this->in_int_raw.gdma_infifo_full_wm_ch0_int_raw = this->regGet(
			this->in_int_raw.val,
			this->in_int_raw. gdma_infifo_full_wm_ch0_int_raw_pos
		);
		this->in_int_raw.gdma_in_dscr_empty_ch0_int_raw = this->regGet(
			this->in_int_raw.val,
			this->in_int_raw. gdma_in_dscr_empty_ch0_int_raw_pos
		);
		this->in_int_raw.gdma_in_dscr_err_ch0_int_raw = this->regGet(
			this->in_int_raw.val,
			this->in_int_raw. gdma_in_dscr_err_ch0_int_raw_pos
		);
		this->in_int_raw.gdma_in_err_eof_ch0_int_raw = this->regGet(
			this->in_int_raw.val,
			this->in_int_raw. gdma_in_err_eof_ch0_int_raw_pos
		);
		this->in_int_raw.gdma_in_suc_eof_ch0_int_raw = this->regGet(
			this->in_int_raw.val,
			this->in_int_raw. gdma_in_suc_eof_ch0_int_raw_pos
		);
		this->in_int_raw.gdma_in_done_ch0_int_raw = this->regGet(
			this->in_int_raw.val,
			this->in_int_raw. gdma_in_done_ch0_int_raw_pos
		);
	}
	void GdmaDebug::init_in_int_st(void){
		int offset = this->in_int_st.offset;
		uint16_t base = this->in_int_st.base;
		this->in_int_st.val = this->regRead(base, offset);
		this->in_int_st.gdma_infifo_full_wm_ch0_int_st = this->regGet(
			this->in_int_st.val,
			this->in_int_st. gdma_infifo_full_wm_ch0_int_st_pos
		);
		this->in_int_st.gdma_in_dscr_empty_ch0_int_st = this->regGet(
			this->in_int_st.val,
			this->in_int_st. gdma_in_dscr_empty_ch0_int_st_pos
		);
		this->in_int_st.gdma_in_dscr_err_ch0_int_st = this->regGet(
			this->in_int_st.val,
			this->in_int_st. gdma_in_dscr_err_ch0_int_st_pos
		);
		this->in_int_st.gdma_in_err_eof_ch0_int_st = this->regGet(
			this->in_int_st.val,
			this->in_int_st. gdma_in_err_eof_ch0_int_st_pos
		);
		this->in_int_st.gdma_in_suc_eof_ch0_int_st = this->regGet(
			this->in_int_st.val,
			this->in_int_st. gdma_in_suc_eof_ch0_int_st_pos
		);
		this->in_int_st.gdma_in_done_ch0_int_st = this->regGet(
			this->in_int_st.val,
			this->in_int_st. gdma_in_done_ch0_int_st_pos
		);
	}
	void GdmaDebug::init_in_int_ena(void){
		int offset = this->in_int_ena.offset;
		uint16_t base = this->in_int_ena.base;
		this->in_int_ena.val = this->regRead(base, offset);
		this->in_int_ena.gdma_infifo_full_wm_ch0_int_ena = this->regGet(
			this->in_int_ena.val,
			this->in_int_ena. gdma_infifo_full_wm_ch0_int_ena_pos
		);
		this->in_int_ena.gdma_in_dscr_empty_ch0_int_ena = this->regGet(
			this->in_int_ena.val,
			this->in_int_ena. gdma_in_dscr_empty_ch0_int_ena_pos
		);
		this->in_int_ena.gdma_in_dscr_err_ch0_int_ena = this->regGet(
			this->in_int_ena.val,
			this->in_int_ena. gdma_in_dscr_err_ch0_int_ena_pos
		);
		this->in_int_ena.gdma_in_err_eof_ch0_int_ena = this->regGet(
			this->in_int_ena.val,
			this->in_int_ena. gdma_in_err_eof_ch0_int_ena_pos
		);
		this->in_int_ena.gdma_in_suc_eof_ch0_int_ena = this->regGet(
			this->in_int_ena.val,
			this->in_int_ena. gdma_in_suc_eof_ch0_int_ena_pos
		);
		this->in_int_ena.gdma_in_done_ch0_int_ena = this->regGet(
			this->in_int_ena.val,
			this->in_int_ena. gdma_in_done_ch0_int_ena_pos
		);
	}
	void GdmaDebug::init_in_int_clr(void){
		int offset = this->in_int_clr.offset;
		uint16_t base = this->in_int_clr.base;
		this->in_int_clr.val = this->regRead(base, offset);
		this->in_int_clr.gdma_dma_infifo_full_wm_ch0_int_clr = this->regGet(
			this->in_int_clr.val,
			this->in_int_clr. gdma_dma_infifo_full_wm_ch0_int_clr_pos
		);
		this->in_int_clr.gdma_in_dscr_empty_ch0_int_clr = this->regGet(
			this->in_int_clr.val,
			this->in_int_clr. gdma_in_dscr_empty_ch0_int_clr_pos
		);
		this->in_int_clr.gdma_in_dscr_err_ch0_int_clr = this->regGet(
			this->in_int_clr.val,
			this->in_int_clr. gdma_in_dscr_err_ch0_int_clr_pos
		);
		this->in_int_clr.gdma_in_err_eof_ch0_int_clr = this->regGet(
			this->in_int_clr.val,
			this->in_int_clr. gdma_in_err_eof_ch0_int_clr_pos
		);
		this->in_int_clr.gdma_in_suc_eof_ch0_int_clr = this->regGet(
			this->in_int_clr.val,
			this->in_int_clr. gdma_in_suc_eof_ch0_int_clr_pos
		);
		this->in_int_clr.gdma_in_done_ch0_int_clr = this->regGet(
			this->in_int_clr.val,
			this->in_int_clr. gdma_in_done_ch0_int_clr_pos
		);
	}
	void GdmaDebug::init_out_int_raw(void){
		int offset = this->out_int_raw.offset;
		uint16_t base = this->out_int_raw.base;
		this->out_int_raw.val = this->regRead(base, offset);
		this->out_int_raw.gdma_out_total_eof_ch0_int_raw = this->regGet(
			this->out_int_raw.val,
			this->out_int_raw. gdma_out_total_eof_ch0_int_raw_pos
		);
		this->out_int_raw.gdma_out_dscr_err_ch0_int_raw = this->regGet(
			this->out_int_raw.val,
			this->out_int_raw. gdma_out_dscr_err_ch0_int_raw_pos
		);
		this->out_int_raw.gdma_out_eof_ch0_int_raw = this->regGet(
			this->out_int_raw.val,
			this->out_int_raw. gdma_out_eof_ch0_int_raw_pos
		);
		this->out_int_raw.gdma_out_done_ch0_int_raw = this->regGet(
			this->out_int_raw.val,
			this->out_int_raw. gdma_out_done_ch0_int_raw_pos
		);
	}
	void GdmaDebug::init_out_int_st(void){
		int offset = this->out_int_st.offset;
		uint16_t base = this->out_int_st.base;
		this->out_int_st.val = this->regRead(base, offset);
		this->out_int_st.gdma_out_total_eof_ch0_int_st = this->regGet(
			this->out_int_st.val,
			this->out_int_st. gdma_out_total_eof_ch0_int_st_pos
		);
		this->out_int_st.gdma_out_dscr_err_ch0_int_st = this->regGet(
			this->out_int_st.val,
			this->out_int_st. gdma_out_dscr_err_ch0_int_st_pos
		);
		this->out_int_st.gdma_out_eof_ch0_int_st = this->regGet(
			this->out_int_st.val,
			this->out_int_st. gdma_out_eof_ch0_int_st_pos
		);
		this->out_int_st.gdma_out_done_ch0_int_st = this->regGet(
			this->out_int_st.val,
			this->out_int_st. gdma_out_done_ch0_int_st_pos
		);
	}
	void GdmaDebug::init_out_int_ena(void){
		int offset = this->out_int_ena.offset;
		uint16_t base = this->out_int_ena.base;
		this->out_int_ena.val = this->regRead(base, offset);
		this->out_int_ena.gdma_out_total_eof_ch0_int_ena = this->regGet(
			this->out_int_ena.val,
			this->out_int_ena. gdma_out_total_eof_ch0_int_ena_pos
		);
		this->out_int_ena.gdma_out_dscr_err_ch0_int_ena = this->regGet(
			this->out_int_ena.val,
			this->out_int_ena. gdma_out_dscr_err_ch0_int_ena_pos
		);
		this->out_int_ena.gdma_out_eof_ch0_int_ena = this->regGet(
			this->out_int_ena.val,
			this->out_int_ena. gdma_out_eof_ch0_int_ena_pos
		);
		this->out_int_ena.gdma_out_done_ch0_int_ena = this->regGet(
			this->out_int_ena.val,
			this->out_int_ena. gdma_out_done_ch0_int_ena_pos
		);
	}
	void GdmaDebug::init_out_int_clr(void){
		int offset = this->out_int_clr.offset;
		uint16_t base = this->out_int_clr.base;
		this->out_int_clr.val = this->regRead(base, offset);
		this->out_int_clr.gdma_out_total_eof_ch0_int_clr = this->regGet(
			this->out_int_clr.val,
			this->out_int_clr. gdma_out_total_eof_ch0_int_clr_pos
		);
		this->out_int_clr.gdma_out_dscr_err_ch0_int_clr = this->regGet(
			this->out_int_clr.val,
			this->out_int_clr. gdma_out_dscr_err_ch0_int_clr_pos
		);
		this->out_int_clr.gdma_out_eof_ch0_int_clr = this->regGet(
			this->out_int_clr.val,
			this->out_int_clr. gdma_out_eof_ch0_int_clr_pos
		);
		this->out_int_clr.gdma_out_done_ch0_int_clr = this->regGet(
			this->out_int_clr.val,
			this->out_int_clr. gdma_out_done_ch0_int_clr_pos
		);
	}
	void GdmaDebug::init_extmem_reject_int(void){
		int offset = this->extmem_reject_int.offset;
		uint16_t base = this->extmem_reject_int.base;
		this->extmem_reject_int.val = this->regRead(base, offset);
		this->extmem_reject_int.gdma_extmem_reject_int_raw = this->regGet(
			this->extmem_reject_int.val,
			this->extmem_reject_int. gdma_extmem_reject_int_raw_pos
		);
	}
	void GdmaDebug::init_extmem_reject_int_st(void){
		int offset = this->extmem_reject_int_st.offset;
		uint16_t base = this->extmem_reject_int_st.base;
		this->extmem_reject_int_st.val = this->regRead(base, offset);
		this->extmem_reject_int_st.gdma_extmem_reject_int_st = this->regGet(
			this->extmem_reject_int_st.val,
			this->extmem_reject_int_st.gdma_extmem_reject_int_st_pos
		);
	}
	void GdmaDebug::init_extmem_reject_int_ena(void){
		int offset = this->extmem_reject_int_ena.offset;
		uint16_t base = this->extmem_reject_int_ena.base;
		this->extmem_reject_int_ena.val = this->regRead(base, offset);
		this->extmem_reject_int_ena.gdma_extmem_reject_int_ena = this->regGet(
			this->extmem_reject_int_ena.val,
			this->extmem_reject_int_ena.gdma_extmem_reject_int_ena_pos
		);
	}
	void GdmaDebug::init_extmem_reject_int_clr(void){
		int offset = this->extmem_reject_int_clr.offset;
		uint16_t base = this->extmem_reject_int_clr.base;
		this->extmem_reject_int_clr.val = this->regRead(base, offset);
		this->extmem_reject_int_clr.gdma_extmem_reject_int_clr = this->regGet(
			this->extmem_reject_int_clr.val,
			this->extmem_reject_int_clr.gdma_extmem_reject_int_clr_pos
		);
	}

	// Status Registers
	void GdmaDebug::initStatusRegs(void){
		this->init_infifo_status();
		this->init_in_state();
		this->init_in_suc_eof_des_addr();
		this->init_in_err_eof_des_addr();
		this->init_in_dscr();
		this->init_in_dscr_bf0();
		this->init_in_dscr_bf1();
		this->init_outfifo_status();
		this->init_out_state();
		this->init_out_eof_des_addr();
		this->init_out_eof_bfr_des_addr();
		this->init_out_dscr();
		this->init_out_dscr_bf0();
		this->init_out_dscr_bf1();
	}

	void GdmaDebug::init_infifo_status(void){
		int offset = this->infifo_status.offset;
		uint16_t base = this->infifo_status.base;
		this->infifo_status.val = this->regRead(base, offset);
		this->infifo_status.gdma_infifo_cnt_l3_ch0 = this->regGet(
			this->infifo_status.val,
			this->infifo_status.gdma_infifo_cnt_l3_ch0_x,
			this->infifo_status.gdma_infifo_cnt_l3_ch0_y
		);
		this->infifo_status.gdma_infifo_cnt_l2_ch0 = this->regGet(
			this->infifo_status.val,
			this->infifo_status.gdma_infifo_cnt_l2_ch0_x,
			this->infifo_status.gdma_infifo_cnt_l2_ch0_y
		);
		this->infifo_status.gdma_infifo_cnt_l1_ch0 = this->regGet(
			this->infifo_status.val,
			this->infifo_status.gdma_infifo_cnt_l1_ch0_x,
			this->infifo_status.gdma_infifo_cnt_l1_ch0_y
		);
		this->infifo_status.gdma_infifo_empty_l3_ch0 = this->regGet(
			this->infifo_status.val,
			this->infifo_status.gdma_infifo_empty_l3_ch0_pos
		);
		this->infifo_status.gdma_infifo_full_l3_ch0 = this->regGet(
			this->infifo_status.val,
			this->infifo_status.gdma_infifo_full_l3_ch0_pos
		);
		this->infifo_status.gdma_infifo_empty_l2_ch0 = this->regGet(
			this->infifo_status.val,
			this->infifo_status.gdma_infifo_empty_l2_ch0_pos
		);
		this->infifo_status.gdma_infifo_full_l2_ch0 = this->regGet(
			this->infifo_status.val,
			this->infifo_status.gdma_infifo_full_l2_ch0_pos
		);
		this->infifo_status.gdma_infifo_empty_l1_ch0 = this->regGet(
			this->infifo_status.val,
			this->infifo_status.gdma_infifo_empty_l1_ch0_pos
		);
		this->infifo_status.gdma_infifo_full_l1_ch0 = this->regGet(
			this->infifo_status.val,
			this->infifo_status.gdma_infifo_full_l1_ch0_pos
		);
	}
	void GdmaDebug::init_in_state(void){
		int offset = this->in_state.offset;
		uint16_t base = this->in_state.base;
		this->in_state.val = this->regRead(base, offset);
		this->in_state.gdma_inlink_dscr_addr_ch0 = this->regGet(
			this->in_state.val,
			this->in_state.gdma_inlink_dscr_addr_ch0_x,
			this->in_state.gdma_inlink_dscr_addr_ch0_y
		);
	}
	void GdmaDebug::init_in_suc_eof_des_addr(void){
		int offset = this->in_suc_eof_des_addr.offset;
		uint16_t base = this->in_suc_eof_des_addr.base;
		this->in_suc_eof_des_addr.val = this->regRead(base, offset);
		this->in_suc_eof_des_addr.gdma_in_suc_eof_des_addr_ch0 = this->regGet(
			this->in_suc_eof_des_addr.val,
			this->in_suc_eof_des_addr.gdma_in_suc_eof_des_addr_ch0_x,
			this->in_suc_eof_des_addr.gdma_in_suc_eof_des_addr_ch0_y
		);
	}
	void GdmaDebug::init_in_err_eof_des_addr(void){
		int offset = this->in_err_eof_des_addr.offset;
		uint16_t base = this->in_err_eof_des_addr.base;
		this->in_err_eof_des_addr.val = this->regRead(base, offset);
		this->in_err_eof_des_addr.gdma_in_err_eof_des_addr_ch0 = this->regGet(
			this->in_err_eof_des_addr.val,
			this->in_err_eof_des_addr.gdma_in_err_eof_des_addr_ch0_x,
			this->in_err_eof_des_addr.gdma_in_err_eof_des_addr_ch0_y
		);
	}
	void GdmaDebug::init_in_dscr(void){
		int offset = this->in_dscr.offset;
		uint16_t base = this->in_dscr.base;
		this->in_dscr.val = this->regRead(base, offset);
		this->in_dscr.gdma_inlink_dscr_ch0 = this->regGet(
			this->in_dscr.val,
			this->in_dscr.gdma_inlink_dscr_ch0_x,
			this->in_dscr.gdma_inlink_dscr_ch0_y
		);
	}
	void GdmaDebug::init_in_dscr_bf0(void){
		int offset = this->in_dscr_bf0.offset;
		uint16_t base = this->in_dscr_bf0.base;
		this->in_dscr_bf0.val = this->regRead(base, offset);
		this->in_dscr_bf0.gdma_inlink_dscr_bf0_ch0 = this->regGet(
			this->in_dscr_bf0.val,
			this->in_dscr_bf0.gdma_inlink_dscr_bf0_ch0_x,
			this->in_dscr_bf0.gdma_inlink_dscr_bf0_ch0_y
		);
	}
	void GdmaDebug::init_in_dscr_bf1(void){
		int offset = this->in_dscr_bf1.offset;
		uint16_t base = this->in_dscr_bf1.base;
		this->in_dscr_bf1.val = this->regRead(base, offset);
		this->in_dscr_bf1.gdma_inlink_dscr_bf1_ch0 = this->regGet(
			this->in_dscr_bf1.val,
			this->in_dscr_bf1.gdma_inlink_dscr_bf1_ch0_x,
			this->in_dscr_bf1.gdma_inlink_dscr_bf1_ch0_y
		);
	}
	void GdmaDebug::init_outfifo_status(void){
		int offset = this->outfifo_status.offset;
		uint16_t base = this->outfifo_status.base;
		this->outfifo_status.val = this->regRead(base, offset);
		this->outfifo_status.gdma_out_remain_under_4b_l3_ch0 = this->regGet(
			this->outfifo_status.val,
			this->outfifo_status.gdma_out_remain_under_4b_l3_ch0_pos
		);
		this->outfifo_status.gdma_out_remain_under_3b_l3_ch0 = this->regGet(
			this->outfifo_status.val,
			this->outfifo_status.gdma_out_remain_under_3b_l3_ch0_pos
		);
		this->outfifo_status.gdma_out_remain_under_2b_l3_ch0 = this->regGet(
			this->outfifo_status.val,
			this->outfifo_status.gdma_out_remain_under_2b_l3_ch0_pos
		);
		this->outfifo_status.gdma_out_remain_under_1b_l3_ch0 = this->regGet(
			this->outfifo_status.val,
			this->outfifo_status.gdma_out_remain_under_1b_l3_ch0_pos
		);
		this->outfifo_status.gdma_outfifo_cnt_l3_ch0 = this->regGet(
			this->outfifo_status.val,
			this->outfifo_status.gdma_outfifo_cnt_l3_ch0_x,
			this->outfifo_status.gdma_outfifo_cnt_l3_ch0_y
		);
		this->outfifo_status.gdma_outfifo_cnt_l2_ch0 = this->regGet(
			this->outfifo_status.val,
			this->outfifo_status.gdma_outfifo_cnt_l2_ch0_x,
			this->outfifo_status.gdma_outfifo_cnt_l2_ch0_y
		);
		this->outfifo_status.gdma_outfifo_cnt_l1_ch0 = this->regGet(
			this->outfifo_status.val,
			this->outfifo_status.gdma_outfifo_cnt_l1_ch0_x,
			this->outfifo_status.gdma_outfifo_cnt_l1_ch0_y
		);
		this->outfifo_status.gdma_outfifo_empty_l3_ch0 = this->regGet(
			this->outfifo_status.val,
			this->outfifo_status.gdma_outfifo_empty_l3_ch0_pos
		);
		this->outfifo_status.gdma_outfifo_full_l3_ch0 = this->regGet(
			this->outfifo_status.val,
			this->outfifo_status.gdma_outfifo_full_l3_ch0_pos
		);
		this->outfifo_status.gdma_outfifo_empty_l2_ch0 = this->regGet(
			this->outfifo_status.val,
			this->outfifo_status.gdma_outfifo_empty_l2_ch0_pos
		);
		this->outfifo_status.gdma_outfifo_full_l2_ch0 = this->regGet(
			this->outfifo_status.val,
			this->outfifo_status.gdma_outfifo_full_l2_ch0_pos
		);
		this->outfifo_status.gdma_outfifo_empty_l1_ch0 = this->regGet(
			this->outfifo_status.val,
			this->outfifo_status.gdma_outfifo_empty_l1_ch0_pos
		);
		this->outfifo_status.gdma_outfifo_full_l1_ch0 = this->regGet(
			this->outfifo_status.val,
			this->outfifo_status.gdma_outfifo_full_l1_ch0_pos
		);
	}
	void GdmaDebug::init_out_state(void){
		int offset = this->out_state.offset;
		uint16_t base = this->out_state.base;
		this->out_state.val = this->regRead(base, offset);
		this->out_state.gdma_out_state_ch0 = this->regGet(
			this->out_state.val,
			this->out_state.gdma_out_state_ch0_x,
			this->out_state.gdma_out_state_ch0_y
		);
		this->out_state.gdma_out_dscr_state_ch0 = this->regGet(
			this->out_state.val,
			this->out_state.gdma_out_dscr_state_ch0_x,
			this->out_state.gdma_out_dscr_state_ch0_y
		);
		this->out_state.gdma_outlink_dscr_addr_ch0 = this->regGet(
			this->out_state.val,
			this->out_state.gdma_outlink_dscr_addr_ch0_x,
			this->out_state.gdma_outlink_dscr_addr_ch0_y
		);
	}
	void GdmaDebug::init_out_eof_des_addr(void){
		int offset = this->out_eof_des_addr.offset;
		uint16_t base = this->out_eof_des_addr.base;
		this->out_eof_des_addr.val = this->regRead(base, offset);
		this->out_eof_des_addr.gdma_out_eof_des_addr_ch0 = this->regGet(
			this->out_eof_des_addr.val,
			this->out_eof_des_addr.gdma_out_eof_des_addr_ch0_x,
			this->out_eof_des_addr.gdma_out_eof_des_addr_ch0_y
		);
	}
	void GdmaDebug::init_out_eof_bfr_des_addr(void){
		int offset = this->out_eof_bfr_des_addr.offset;
		uint16_t base = this->out_eof_bfr_des_addr.base;
		this->out_eof_bfr_des_addr.val = this->regRead(base, offset);
		this->out_eof_bfr_des_addr.gdma_out_eof_bfr_des_addr_ch0 = this->regGet(
			this->out_eof_bfr_des_addr.val,
			this->out_eof_bfr_des_addr.gdma_out_eof_bfr_des_addr_ch0_x,
			this->out_eof_bfr_des_addr.gdma_out_eof_bfr_des_addr_ch0_y
		);
	}
	void GdmaDebug::init_out_dscr(void){
		int offset = this->out_dscr.offset;
		uint16_t base = this->out_dscr.base;
		this->out_dscr.val = this->regRead(base, offset);
		this->out_dscr.gdma_outlink_dscr_ch0 = this->regGet(
			this->out_dscr.val,
			this->out_dscr.gdma_outlink_dscr_ch0_x,
			this->out_dscr.gdma_outlink_dscr_ch0_y
		);
	}
	void GdmaDebug::init_out_dscr_bf0(void){
		int offset = this->out_dscr_bf0.offset;
		uint16_t base = this->out_dscr_bf0.base;
		this->out_dscr_bf0.val = this->regRead(base, offset);
		this->out_dscr_bf0.gdma_outlink_dscr_bf0_ch0 = this->regGet(
			this->out_dscr_bf0.val,
			this->out_dscr_bf0.gdma_outlink_dscr_bf0_ch0_x,
			this->out_dscr_bf0.gdma_outlink_dscr_bf0_ch0_y
		);
	}
	void GdmaDebug::init_out_dscr_bf1(void){
		int offset = this->out_dscr_bf1.offset;
		uint16_t base = this->out_dscr_bf1.base;
		this->out_dscr_bf1.val = this->regRead(base, offset);
		this->out_dscr_bf1.gdma_outlink_dscr_bf1_ch0 = this->regGet(
			this->out_dscr_bf1.val,
			this->out_dscr_bf1.gdma_outlink_dscr_bf1_ch0_x,
			this->out_dscr_bf1.gdma_outlink_dscr_bf1_ch0_y
		);
	}

	// Priority Registers
	void GdmaDebug::initPriorityRegs(void){
		this->init_in_pri();
		this->init_out_pri();
	}

	void GdmaDebug::init_in_pri(void){
		int offset = this->in_pri.offset;
		uint16_t base = this->in_pri.base;
		this->in_pri.val = this->regRead(base, offset);
		this->in_pri.gdma_rx_pri_ch0 = this->regGet(
			this->in_pri.val,
			this->in_pri.gdma_rx_pri_ch0_x,
			this->in_pri.gdma_rx_pri_ch0_y
		);
	}
	void GdmaDebug::init_out_pri(void){
		int offset = this->out_pri.offset;
		uint16_t base = this->out_pri.base;
		this->out_pri.val = this->regRead(base, offset);
		this->out_pri.gdma_tx_pri_ch0 = this->regGet(
			this->out_pri.val,
			this->out_pri.gdma_tx_pri_ch0_x,
			this->out_pri.gdma_tx_pri_ch0_y
		);
	}

	// Peripheral Selection Registers
	void GdmaDebug::initPeriphSelRegs(void){
		this->init_in_peri_sel();
		this->init_out_peri_sel();
	}

	void GdmaDebug::init_in_peri_sel(void){
		int offset = this->in_peri_sel.offset;
		uint16_t base = this->in_peri_sel.base;
		this->in_peri_sel.val = this->regRead(base, offset);
		this->in_peri_sel.gdma_peri_in_sel_ch0 = this->regGet(
			this->in_peri_sel.val,
			this->in_peri_sel.gdma_peri_in_sel_ch0_x,
			this->in_peri_sel.gdma_peri_in_sel_ch0_y
		);
	}
	void GdmaDebug::init_out_peri_sel(void){
		int offset = this->out_peri_sel.offset;
		uint16_t base = this->out_peri_sel.base;
		this->out_peri_sel.val = this->regRead(base, offset);
		this->out_peri_sel.gdma_peri_out_sel_ch0 = this->regGet(
			this->out_peri_sel.val,
			this->out_peri_sel.gdma_peri_out_sel_ch0_x,
			this->out_peri_sel.gdma_peri_out_sel_ch0_y
		);
	}

	// Permission Status Registers
	void GdmaDebug::initPermissionStatRegs(void){
		this->init_extmem_reject_addr();
		this->init_extmem_reject_st();
	}

	void GdmaDebug::init_extmem_reject_addr(void){
		int offset = this->extmem_reject_addr.offset;
		uint16_t base = this->extmem_reject_addr.base;
		this->extmem_reject_addr.val = this->regRead(base, offset);
		this->extmem_reject_addr.gdma_extmem_reject_addr = this->regGet(
			this->extmem_reject_addr.val,
			this->extmem_reject_addr.gdma_extmem_reject_addr_x,
			this->extmem_reject_addr.gdma_extmem_reject_addr_y
		);
	}
	void GdmaDebug::init_extmem_reject_st(void){
		int offset = this->extmem_reject_st.offset;
		uint16_t base = this->extmem_reject_st.base;
		this->extmem_reject_st.val = this->regRead(base, offset);
		this->extmem_reject_st.gdma_extmem_reject_peri_num = this->regGet(
			this->extmem_reject_st.val,
			this->extmem_reject_st.gdma_extmem_reject_peri_num_x,
			this->extmem_reject_st.gdma_extmem_reject_peri_num_y
		);
		this->extmem_reject_st.gdma_extmem_reject_channel_num = this->regGet(
			this->extmem_reject_st.val,
			this->extmem_reject_st.gdma_extmem_reject_channel_num_x,
			this->extmem_reject_st.gdma_extmem_reject_channel_num_y
		);
		this->extmem_reject_st.gdma_extmem_reject_atrr = this->regGet(
			this->extmem_reject_st.val,
			this->extmem_reject_st.gdma_extmem_reject_atrr_x,
			this->extmem_reject_st.gdma_extmem_reject_atrr_y
		);
	}

	void GdmaDebug::init_date(void){
		int offset = this->date.offset;
		uint16_t base = this->date.base;
		this->date.val = this->regRead(base, offset);
		this->date.gdma_date = this->regGet(
			this->date.val,
			this->date.gdma_date_x,
			this->date.gdma_date_y
		);
	}

	/*
	 * Debug print functions
	 * */
	void GdmaDebug::print(bool onlyCoreValues){
		this->printConfigRegs(onlyCoreValues);
		this->printInterruptRegs(onlyCoreValues);
		this->printStatusRegs(onlyCoreValues);
		this->printPriorityRegs(onlyCoreValues);
		this->printPeriphSelRegs(onlyCoreValues);
		this->printPermissionStatRegs(onlyCoreValues);
		this->print_date(onlyCoreValues);
	}

	// Configuration Registers
	void GdmaDebug::printConfigRegs(bool onlyCoreValues){
		this->print_in_conf0(onlyCoreValues);
		this->print_in_conf1(onlyCoreValues); 
		this->print_in_pop(onlyCoreValues);
		this->print_in_link(onlyCoreValues);
		this->print_out_conf0(onlyCoreValues);
		this->print_out_conf1(onlyCoreValues);
		this->print_out_push(onlyCoreValues);
		this->print_out_link(onlyCoreValues);
		this->print_pd_conf(onlyCoreValues);
		this->print_misc_conf(onlyCoreValues);
	}

	void GdmaDebug::print_in_conf0(bool onlyCoreValues){
		Serial.printf("=== in_conf0 values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->in_conf0.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->in_conf0.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->in_conf0.offset);
			Serial.printf("\tgdma_mem_trans_en_ch : 0x%x\n", this->in_conf0.gdma_mem_trans_en_ch);
			Serial.printf("\tgdma_in_data_burst_en_ch : 0x%x\n", this->in_conf0.gdma_in_data_burst_en_ch);
			Serial.printf("\tgdma_indscr_burst_en_ch : 0x%x\n", this->in_conf0.gdma_indscr_burst_en_ch);
			Serial.printf("\tgdma_in_loop_test_ch : 0x%x\n", this->in_conf0.gdma_in_loop_test_ch);
			Serial.printf("\tgdma_in_rst_ch : 0x%x\n", this->in_conf0.gdma_in_rst_ch);
		}
	}
	void GdmaDebug::print_in_conf1(bool onlyCoreValues){
		Serial.printf("=== in_conf1 values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->in_conf1.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->in_conf1.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->in_conf1.offset);
			Serial.printf("\tgdma_in_ext_mem_bk_size_ch : 0x%x\n", this->in_conf1.gdma_in_ext_mem_bk_size_ch);
			Serial.printf("\tgdma_in_check_owner_ch : 0x%x\n", this->in_conf1.gdma_in_check_owner_ch);
			Serial.printf("\tgdma_dma_infifo_full_thrs_ch : 0x%x\n", this->in_conf1.gdma_dma_infifo_full_thrs_ch);
		}
	}
	void GdmaDebug::print_in_pop(bool onlyCoreValues){
		Serial.printf("=== in_pop values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->in_pop.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->in_pop.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->in_pop.offset);
			Serial.printf("\tgdma_infifo_pop_ch : 0x%x\n", this->in_pop.gdma_infifo_pop_ch);
		}
	}
	void GdmaDebug::print_in_link(bool onlyCoreValues){
		Serial.printf("=== in_link values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->in_link.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->in_link.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->in_link.offset);
			Serial.printf("\tgdma_inlink_park_ch : 0x%x\n", this->in_link.gdma_inlink_park_ch);
			Serial.printf("\tgdma_inlink_restart_ch : 0x%x\n", this->in_link.gdma_inlink_restart_ch);
			Serial.printf("\tgdma_inlink_start_ch : 0x%x\n", this->in_link.gdma_inlink_start_ch);
			Serial.printf("\tgdma_inlink_stop_ch : 0x%x\n", this->in_link.gdma_inlink_stop_ch);
			Serial.printf("\tgdma_inlink_auto_ret_ch : 0x%x\n", this->in_link.gdma_inlink_auto_ret_ch);
			Serial.printf("\tgdma_inlink_addr_ch : 0x%x\n", this->in_link.gdma_inlink_addr_ch);
		}
	}
	void GdmaDebug::print_out_conf0(bool onlyCoreValues){
		Serial.printf("=== out_conf0 values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->out_conf0.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->out_conf0.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->out_conf0.offset);
			Serial.printf("\tgdma_out_data_burst_en_ch : 0x%x\n", this->out_conf0.gdma_out_data_burst_en_ch);
			Serial.printf("\tgdma_outdscr_burst_en_ch : 0x%x\n", this->out_conf0.gdma_outdscr_burst_en_ch);
			Serial.printf("\tgdma_out_eof_mode_ch : 0x%x\n", this->out_conf0.gdma_out_eof_mode_ch);
			Serial.printf("\tgdma_out_auto_wrback_ch : 0x%x\n", this->out_conf0.gdma_out_auto_wrback_ch);
			Serial.printf("\tgdma_out_loop_test_ch : 0x%x\n", this->out_conf0.gdma_out_loop_test_ch);
			Serial.printf("\tgdma_out_rst_ch : 0x%x\n", this->out_conf0.gdma_out_rst_ch);
		}
	}
	void GdmaDebug::print_out_conf1(bool onlyCoreValues){
		Serial.printf("=== out_conf1 values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->out_conf1.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->out_conf1.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->out_conf1.offset);
			Serial.printf("\tgdma_out_ext_mem_bk_size_ch : 0x%x\n", this->out_conf1.gdma_out_ext_mem_bk_size_ch);
			Serial.printf("\tgdma_out_check_owner_ch : 0x%x\n", this->out_conf1.gdma_out_check_owner_ch);
		}
	}
	void GdmaDebug::print_out_push(bool onlyCoreValues){
		Serial.printf("=== out_push values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->out_push.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->out_push.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->out_push.offset);
			Serial.printf("\tgdma_outfifo_push_ch : 0x%x\n", this->out_push.gdma_outfifo_push_ch);
			Serial.printf("\tgdma_outfifo_wdata_ch : 0x%x\n", this->out_push.gdma_outfifo_wdata_ch);
		}
	}
	void GdmaDebug::print_out_link(bool onlyCoreValues){
		Serial.printf("=== out_link values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->out_link.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->out_link.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->out_link.offset);
			Serial.printf("\tgdma_outlink_park_ch : 0x%x\n", this->out_link.gdma_outlink_park_ch);
			Serial.printf("\tgdma_outlink_restart_ch : 0x%x\n", this->out_link.gdma_outlink_restart_ch);
			Serial.printf("\tgdma_outlink_start_ch : 0x%x\n", this->out_link.gdma_outlink_start_ch);
			Serial.printf("\tgdma_outlink_stop_ch : 0x%x\n", this->out_link.gdma_outlink_stop_ch);
			Serial.printf("\tgdma_outlink_addr_ch : 0x%x\n", this->out_link.gdma_outlink_addr_ch);
		}
	}
	void GdmaDebug::print_pd_conf(bool onlyCoreValues){
		Serial.printf("=== pd_conf values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->pd_conf.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->pd_conf.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->pd_conf.offset);
			Serial.printf("\tgdma_dma_ram_clk_fo : 0x%x\n", this->pd_conf.gdma_dma_ram_clk_fo);
			Serial.printf("\tgdma_dma_ram_force_pu : 0x%x\n", this->pd_conf.gdma_dma_ram_force_pu);
			Serial.printf("\tgdma_dma_ram_force_pd : 0x%x\n", this->pd_conf.gdma_dma_ram_force_pd);
		}
	}
	void GdmaDebug::print_misc_conf(bool onlyCoreValues){
		Serial.printf("=== misc_conf values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->misc_conf.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->misc_conf.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->misc_conf.offset);
			Serial.printf("\tgdma_clk_en : 0x%x\n", this->misc_conf.gdma_clk_en);
			Serial.printf("\tgdma_arb_pri_dis : 0x%x\n", this->misc_conf.gdma_arb_pri_dis);
			Serial.printf("\tgdma_ahbm_rst_exter : 0x%x\n", this->misc_conf.gdma_ahbm_rst_exter);
			Serial.printf("\tgdma_ahbm_rst_inter : 0x%x\n", this->misc_conf.gdma_ahbm_rst_inter);
		}
	}

	// Interrupt Registers
	void GdmaDebug::printInterruptRegs(bool onlyCoreValues){
		this->print_in_int_raw(onlyCoreValues);
		this->print_in_int_st(onlyCoreValues);
		this->print_in_int_ena(onlyCoreValues);
		this->print_in_int_clr(onlyCoreValues);
		this->print_out_int_raw(onlyCoreValues);
		this->print_out_int_st(onlyCoreValues);
		this->print_out_int_ena(onlyCoreValues);
		this->print_out_int_clr(onlyCoreValues);
		this->print_extmem_reject_int(onlyCoreValues);
		this->print_extmem_reject_int_st(onlyCoreValues);
		this->print_extmem_reject_int_ena(onlyCoreValues);
		this->print_extmem_reject_int_clr(onlyCoreValues);
	}

	void GdmaDebug::print_in_int_raw(bool onlyCoreValues){
		Serial.printf("=== in_int_raw values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->in_int_raw.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->in_int_raw.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->in_int_raw.offset);
			Serial.printf("\tgdma_infifo_full_wm_ch0_int_raw : 0x%x\n", this->in_int_raw.gdma_infifo_full_wm_ch0_int_raw);
			Serial.printf("\tgdma_in_dscr_empty_ch0_int_raw : 0x%x\n", this->in_int_raw.gdma_in_dscr_empty_ch0_int_raw);
			Serial.printf("\tgdma_in_dscr_err_ch0_int_raw : 0x%x\n", this->in_int_raw.gdma_in_dscr_err_ch0_int_raw);
			Serial.printf("\tgdma_in_err_eof_ch0_int_raw : 0x%x\n", this->in_int_raw.gdma_in_err_eof_ch0_int_raw);
			Serial.printf("\tgdma_in_suc_eof_ch0_int_raw : 0x%x\n", this->in_int_raw.gdma_in_suc_eof_ch0_int_raw);
			Serial.printf("\tgdma_in_done_ch0_int_raw : 0x%x\n", this->in_int_raw.gdma_in_done_ch0_int_raw);
		}
	}
	void GdmaDebug::print_in_int_st(bool onlyCoreValues){
		Serial.printf("=== in_int_st values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->in_int_st.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->in_int_st.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->in_int_st.offset);
			Serial.printf("\tgdma_infifo_full_wm_ch0_int_st : 0x%x\n", this->in_int_st.gdma_infifo_full_wm_ch0_int_st);
			Serial.printf("\tgdma_in_dscr_empty_ch0_int_st : 0x%x\n", this->in_int_st.gdma_in_dscr_empty_ch0_int_st);
			Serial.printf("\tgdma_in_dscr_err_ch0_int_st : 0x%x\n", this->in_int_st.gdma_in_dscr_err_ch0_int_st);
			Serial.printf("\tgdma_in_err_eof_ch0_int_st : 0x%x\n", this->in_int_st.gdma_in_err_eof_ch0_int_st);
			Serial.printf("\tgdma_in_suc_eof_ch0_int_st : 0x%x\n", this->in_int_st.gdma_in_suc_eof_ch0_int_st);
			Serial.printf("\tgdma_in_done_ch0_int_st : 0x%x\n", this->in_int_st.gdma_in_done_ch0_int_st);
		}
	}
	void GdmaDebug::print_in_int_ena(bool onlyCoreValues){
		Serial.printf("=== in_int_ena values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->in_int_ena.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->in_int_ena.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->in_int_ena.offset);
			Serial.printf("\tgdma_infifo_full_wm_ch0_int_ena : 0x%x\n", this->in_int_ena.gdma_infifo_full_wm_ch0_int_ena);
			Serial.printf("\tgdma_in_dscr_empty_ch0_int_ena : 0x%x\n", this->in_int_ena.gdma_in_dscr_empty_ch0_int_ena);
			Serial.printf("\tgdma_in_dscr_err_ch0_int_ena : 0x%x\n", this->in_int_ena.gdma_in_dscr_err_ch0_int_ena);
			Serial.printf("\tgdma_in_err_eof_ch0_int_ena : 0x%x\n", this->in_int_ena.gdma_in_err_eof_ch0_int_ena);
			Serial.printf("\tgdma_in_suc_eof_ch0_int_ena : 0x%x\n", this->in_int_ena.gdma_in_suc_eof_ch0_int_ena);
			Serial.printf("\tgdma_in_done_ch0_int_ena : 0x%x\n", this->in_int_ena.gdma_in_done_ch0_int_ena);
		}
	}
	void GdmaDebug::print_in_int_clr(bool onlyCoreValues){
		Serial.printf("=== in_int_clr values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->in_int_clr.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->in_int_clr.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->in_int_clr.offset);
			Serial.printf("\tgdma_dma_infifo_full_wm_ch0_int_clr : 0x%x\n", this->in_int_clr.gdma_dma_infifo_full_wm_ch0_int_clr);
			Serial.printf("\tgdma_in_dscr_empty_ch0_int_clr : 0x%x\n", this->in_int_clr.gdma_in_dscr_empty_ch0_int_clr);
			Serial.printf("\tgdma_in_dscr_err_ch0_int_clr : 0x%x\n", this->in_int_clr.gdma_in_dscr_err_ch0_int_clr);
			Serial.printf("\tgdma_in_err_eof_ch0_int_clr : 0x%x\n", this->in_int_clr.gdma_in_err_eof_ch0_int_clr);
			Serial.printf("\tgdma_in_suc_eof_ch0_int_clr : 0x%x\n", this->in_int_clr.gdma_in_suc_eof_ch0_int_clr);
			Serial.printf("\tgdma_in_done_ch0_int_clr : 0x%x\n", this->in_int_clr.gdma_in_done_ch0_int_clr);
		}
	}
	void GdmaDebug::print_out_int_raw(bool onlyCoreValues){
		Serial.printf("=== out_int_raw values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->out_int_raw.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->out_int_raw.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->out_int_raw.offset);
			Serial.printf("\tgdma_out_total_eof_ch0_int_raw : 0x%x\n", this->out_int_raw.gdma_out_total_eof_ch0_int_raw);
			Serial.printf("\tgdma_out_dscr_err_ch0_int_raw : 0x%x\n", this->out_int_raw.gdma_out_dscr_err_ch0_int_raw);
			Serial.printf("\tgdma_out_eof_ch0_int_raw : 0x%x\n", this->out_int_raw.gdma_out_eof_ch0_int_raw);
			Serial.printf("\tgdma_out_done_ch0_int_raw : 0x%x\n", this->out_int_raw.gdma_out_done_ch0_int_raw);
		}
	}
	void GdmaDebug::print_out_int_st(bool onlyCoreValues){
		Serial.printf("=== out_int_st values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->out_int_st.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->out_int_st.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->out_int_st.offset);
			Serial.printf("\tgdma_out_total_eof_ch0_int_st : 0x%x\n", this->out_int_st.gdma_out_total_eof_ch0_int_st);
			Serial.printf("\tgdma_out_dscr_err_ch0_int_st : 0x%x\n", this->out_int_st.gdma_out_dscr_err_ch0_int_st);
			Serial.printf("\tgdma_out_eof_ch0_int_st : 0x%x\n", this->out_int_st.gdma_out_eof_ch0_int_st);
			Serial.printf("\tgdma_out_done_ch0_int_st : 0x%x\n", this->out_int_st.gdma_out_done_ch0_int_st);
		}
	}
	void GdmaDebug::print_out_int_ena(bool onlyCoreValues){
		Serial.printf("=== out_int_ena values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->out_int_ena.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->out_int_ena.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->out_int_ena.offset);
			Serial.printf("\tgdma_out_total_eof_ch0_int_ena : 0x%x\n", this->out_int_ena.gdma_out_total_eof_ch0_int_ena);
			Serial.printf("\tgdma_out_dscr_err_ch0_int_ena : 0x%x\n", this->out_int_ena.gdma_out_dscr_err_ch0_int_ena);
			Serial.printf("\tgdma_out_eof_ch0_int_ena : 0x%x\n", this->out_int_ena.gdma_out_eof_ch0_int_ena);
			Serial.printf("\tgdma_out_done_ch0_int_ena : 0x%x\n", this->out_int_ena.gdma_out_done_ch0_int_ena);
		}
	}
	void GdmaDebug::print_out_int_clr(bool onlyCoreValues){
		Serial.printf("=== out_int_clr values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->out_int_clr.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->out_int_clr.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->out_int_clr.offset);
			Serial.printf("\tgdma_out_total_eof_ch0_int_clr : 0x%x\n", this->out_int_clr.gdma_out_total_eof_ch0_int_clr);
			Serial.printf("\tgdma_out_dscr_err_ch0_int_clr : 0x%x\n", this->out_int_clr.gdma_out_dscr_err_ch0_int_clr);
			Serial.printf("\tgdma_out_eof_ch0_int_clr : 0x%x\n", this->out_int_clr.gdma_out_eof_ch0_int_clr);
			Serial.printf("\tgdma_out_done_ch0_int_clr : 0x%x\n", this->out_int_clr.gdma_out_done_ch0_int_clr);
		}
	}
	void GdmaDebug::print_extmem_reject_int(bool onlyCoreValues){
		Serial.printf("=== extmem_reject_int values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->extmem_reject_int.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->extmem_reject_int.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->extmem_reject_int.offset);
			Serial.printf("\tgdma_extmem_reject_int_raw : 0x%x\n", this->extmem_reject_int.gdma_extmem_reject_int_raw);
		}
	}
	void GdmaDebug::print_extmem_reject_int_st(bool onlyCoreValues){
		Serial.printf("=== extmem_reject_int_st values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->extmem_reject_int_st.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->extmem_reject_int_st.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->extmem_reject_int_st.offset);
			Serial.printf("\tgdma_extmem_reject_int_st : 0x%x\n", this->extmem_reject_int_st.gdma_extmem_reject_int_st);
		}
	}
	void GdmaDebug::print_extmem_reject_int_ena(bool onlyCoreValues){
		Serial.printf("=== extmem_reject_int_ena values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->extmem_reject_int_ena.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->extmem_reject_int_ena.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->extmem_reject_int_ena.offset);
			Serial.printf("\tgdma_extmem_reject_int_ena : 0x%x\n", this->extmem_reject_int_ena.gdma_extmem_reject_int_ena);
		}
	}
	void GdmaDebug::print_extmem_reject_int_clr(bool onlyCoreValues){
		Serial.printf("=== extmem_reject_int_clr values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->extmem_reject_int_clr.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->extmem_reject_int_clr.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->extmem_reject_int_clr.offset);
			Serial.printf("\tgdma_extmem_reject_int_clr : 0x%x\n", this->extmem_reject_int_clr.gdma_extmem_reject_int_clr);
		}
	}


	// Status Registers
	void GdmaDebug::printStatusRegs(bool onlyCoreValues){
		this->print_infifo_status(onlyCoreValues);
		this->print_in_state(onlyCoreValues);
		this->print_in_suc_eof_des_addr(onlyCoreValues);
		this->print_in_err_eof_des_addr(onlyCoreValues);
		this->print_in_dscr(onlyCoreValues);
		this->print_in_dscr_bf0(onlyCoreValues);
		this->print_in_dscr_bf1(onlyCoreValues);
		this->print_outfifo_status(onlyCoreValues);
		this->print_out_state(onlyCoreValues);
		this->print_out_eof_des_addr(onlyCoreValues);
		this->print_out_eof_bfr_des_addr(onlyCoreValues);
		this->print_out_dscr(onlyCoreValues);
		this->print_out_dscr_bf0(onlyCoreValues);
		this->print_out_dscr_bf1(onlyCoreValues);
	}

	void GdmaDebug::print_infifo_status(bool onlyCoreValues){
		Serial.printf("=== infifo_status values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->infifo_status.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->infifo_status.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->infifo_status.offset);
			Serial.printf("\tgdma_infifo_cnt_l3_ch0 : 0x%x\n", this->infifo_status.gdma_infifo_cnt_l3_ch0);
			Serial.printf("\tgdma_infifo_cnt_l2_ch0 : 0x%x\n", this->infifo_status.gdma_infifo_cnt_l2_ch0);
			Serial.printf("\tgdma_infifo_cnt_l1_ch0 : 0x%x\n", this->infifo_status.gdma_infifo_cnt_l1_ch0);
			Serial.printf("\tgdma_infifo_empty_l3_ch0 : 0x%x\n", this->infifo_status.gdma_infifo_empty_l3_ch0);
			Serial.printf("\tgdma_infifo_full_l3_ch0 : 0x%x\n", this->infifo_status.gdma_infifo_full_l3_ch0);
			Serial.printf("\tgdma_infifo_empty_l2_ch0 : 0x%x\n", this->infifo_status.gdma_infifo_empty_l2_ch0);
			Serial.printf("\tgdma_infifo_full_l2_ch0 : 0x%x\n", this->infifo_status.gdma_infifo_full_l2_ch0);
			Serial.printf("\tgdma_infifo_empty_l1_ch0 : 0x%x\n", this->infifo_status.gdma_infifo_empty_l1_ch0);
			Serial.printf("\tgdma_infifo_full_l1_ch0 : 0x%x\n", this->infifo_status.gdma_infifo_full_l1_ch0);
		}
	}
	void GdmaDebug::print_in_state(bool onlyCoreValues){
		Serial.printf("=== in_state values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->in_state.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->in_state.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->in_state.offset);
			Serial.printf("\tgdma_inlink_dscr_addr_ch0 : 0x%x\n", this->in_state.gdma_inlink_dscr_addr_ch0);
		}
	}
	void GdmaDebug::print_in_suc_eof_des_addr(bool onlyCoreValues){
		Serial.printf("=== in_suc_eof_des_addr values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->in_suc_eof_des_addr.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->in_suc_eof_des_addr.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->in_suc_eof_des_addr.offset);
			Serial.printf("\tgdma_in_suc_eof_des_addr_ch0 : 0x%x\n", this->in_suc_eof_des_addr.gdma_in_suc_eof_des_addr_ch0);
		}
	}
	void GdmaDebug::print_in_err_eof_des_addr(bool onlyCoreValues){
		Serial.printf("=== in_err_eof_des_addr values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->in_err_eof_des_addr.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->in_err_eof_des_addr.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->in_err_eof_des_addr.offset);
			Serial.printf("\tgdma_in_err_eof_des_addr_ch0 : 0x%x\n", this->in_err_eof_des_addr.gdma_in_err_eof_des_addr_ch0);
		}
	}
	void GdmaDebug::print_in_dscr(bool onlyCoreValues){
		Serial.printf("=== in_dscr values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->in_dscr.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->in_dscr.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->in_dscr.offset);
			Serial.printf("\tgdma_inlink_dscr_ch0 : 0x%x\n", this->in_dscr.gdma_inlink_dscr_ch0);
		}
	}
	void GdmaDebug::print_in_dscr_bf0(bool onlyCoreValues){
		Serial.printf("=== in_dscr_bf0 values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->in_dscr_bf0.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->in_dscr_bf0.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->in_dscr_bf0.offset);
			Serial.printf("\tgdma_inlink_dscr_bf0_ch0 : 0x%x\n", this->in_dscr_bf0.gdma_inlink_dscr_bf0_ch0);
		}
	}
	void GdmaDebug::print_in_dscr_bf1(bool onlyCoreValues){
		Serial.printf("=== in_dscr_bf1 values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->in_dscr_bf1.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->in_dscr_bf1.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->in_dscr_bf1.offset);
			Serial.printf("\tgdma_inlink_dscr_bf1_ch0 : 0x%x\n", this->in_dscr_bf1.gdma_inlink_dscr_bf1_ch0);
		}
	}
	void GdmaDebug::print_outfifo_status(bool onlyCoreValues){
		Serial.printf("=== outfifo_status values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->outfifo_status.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->outfifo_status.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->outfifo_status.offset);
			Serial.printf("\tgdma_out_remain_under_4b_l3_ch0 : 0x%x\n", this->outfifo_status.gdma_out_remain_under_4b_l3_ch0);
			Serial.printf("\tgdma_out_remain_under_3b_l3_ch0 : 0x%x\n", this->outfifo_status.gdma_out_remain_under_3b_l3_ch0);
			Serial.printf("\tgdma_out_remain_under_2b_l3_ch0 : 0x%x\n", this->outfifo_status.gdma_out_remain_under_2b_l3_ch0);
			Serial.printf("\tgdma_out_remain_under_1b_l3_ch0 : 0x%x\n", this->outfifo_status.gdma_out_remain_under_1b_l3_ch0);
			Serial.printf("\tgdma_outfifo_cnt_l3_ch0 : 0x%x\n", this->outfifo_status.gdma_outfifo_cnt_l3_ch0);
			Serial.printf("\tgdma_outfifo_cnt_l2_ch0 : 0x%x\n", this->outfifo_status.gdma_outfifo_cnt_l2_ch0);
			Serial.printf("\tgdma_outfifo_cnt_l1_ch0 : 0x%x\n", this->outfifo_status.gdma_outfifo_cnt_l1_ch0);
			Serial.printf("\tgdma_outfifo_empty_l3_ch0 : 0x%x\n", this->outfifo_status.gdma_outfifo_empty_l3_ch0);
			Serial.printf("\tgdma_outfifo_full_l3_ch0 : 0x%x\n", this->outfifo_status.gdma_outfifo_full_l3_ch0);
			Serial.printf("\tgdma_outfifo_empty_l2_ch0 : 0x%x\n", this->outfifo_status.gdma_outfifo_empty_l2_ch0);
			Serial.printf("\tgdma_outfifo_full_l2_ch0 : 0x%x\n", this->outfifo_status.gdma_outfifo_full_l2_ch0);
			Serial.printf("\tgdma_outfifo_empty_l1_ch0 : 0x%x\n", this->outfifo_status.gdma_outfifo_empty_l1_ch0);
			Serial.printf("\tgdma_outfifo_full_l1_ch0 : 0x%x\n", this->outfifo_status.gdma_outfifo_full_l1_ch0);
		}
	}
	void GdmaDebug::print_out_state(bool onlyCoreValues){
		Serial.printf("=== out_state values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->out_state.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->out_state.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->out_state.offset);
			Serial.printf("\tgdma_out_state_ch0 : 0x%x\n", this->out_state.gdma_out_state_ch0);
			Serial.printf("\tgdma_out_dscr_state_ch0 : 0x%x\n", this->out_state.gdma_out_dscr_state_ch0);
			Serial.printf("\tgdma_outlink_dscr_addr_ch0 : 0x%x\n", this->out_state.gdma_outlink_dscr_addr_ch0);
		}
	}
	void GdmaDebug::print_out_eof_des_addr(bool onlyCoreValues){
		Serial.printf("=== out_eof_des_addr values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->out_eof_des_addr.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->out_eof_des_addr.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->out_eof_des_addr.offset);
			Serial.printf("\tgdma_out_eof_des_addr_ch0 : 0x%x\n", this->out_eof_des_addr.gdma_out_eof_des_addr_ch0);
		}
	}
	void GdmaDebug::print_out_eof_bfr_des_addr(bool onlyCoreValues){
		Serial.printf("=== out_eof_bfr_des_addr values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->out_eof_bfr_des_addr.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->out_eof_bfr_des_addr.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->out_eof_bfr_des_addr.offset);
			Serial.printf("\tgdma_out_eof_bfr_des_addr_ch0 : 0x%x\n", this->out_eof_bfr_des_addr.gdma_out_eof_bfr_des_addr_ch0);
		}
	}
	void GdmaDebug::print_out_dscr(bool onlyCoreValues){
		Serial.printf("=== out_dscr values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->out_dscr.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->out_dscr.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->out_dscr.offset);
			Serial.printf("\tgdma_outlink_dscr_ch0 : 0x%x\n", this->out_dscr.gdma_outlink_dscr_ch0);
		}
	}
	void GdmaDebug::print_out_dscr_bf0(bool onlyCoreValues){
		Serial.printf("=== out_dscr_bf0 values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->out_dscr_bf0.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->out_dscr_bf0.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->out_dscr_bf0.offset);
			Serial.printf("\tgdma_outlink_dscr_bf0_ch0 : 0x%x\n", this->out_dscr_bf0.gdma_outlink_dscr_bf0_ch0);
		}
	}
	void GdmaDebug::print_out_dscr_bf1(bool onlyCoreValues){
		Serial.printf("=== out_dscr_bf1 values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->out_dscr_bf1.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->out_dscr_bf1.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->out_dscr_bf1.offset);
			Serial.printf("\tgdma_outlink_dscr_bf1_ch0 : 0x%x\n", this->out_dscr_bf1.gdma_outlink_dscr_bf1_ch0);
		}
	}

	// Priority Registers
	void GdmaDebug::printPriorityRegs(bool onlyCoreValues){
		this->print_in_pri(onlyCoreValues);
		this->print_out_pri(onlyCoreValues);
	}
	void GdmaDebug::print_in_pri(bool onlyCoreValues){
		Serial.printf("=== in_pri values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->in_pri.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->in_pri.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->in_pri.offset);
			Serial.printf("\tgdma_rx_pri_ch0 : 0x%x\n", this->in_pri.gdma_rx_pri_ch0);
		}
	}
	void GdmaDebug::print_out_pri(bool onlyCoreValues){
		Serial.printf("=== out_pri values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->out_pri.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->out_pri.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->out_pri.offset);
			Serial.printf("\tgdma_tx_pri_ch0 : 0x%x\n", this->out_pri.gdma_tx_pri_ch0);
		}
	}

	// Peripheral Selection Registers
	void GdmaDebug::printPeriphSelRegs(bool onlyCoreValues){
		this->print_in_peri_sel(onlyCoreValues);
		this->print_out_peri_sel(onlyCoreValues);
	}
	void GdmaDebug::print_in_peri_sel(bool onlyCoreValues){
		Serial.printf("=== in_peri_sel values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->in_peri_sel.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->in_peri_sel.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->in_peri_sel.offset);
			Serial.printf("\tgdma_peri_in_sel_ch0 : 0x%x\n", this->in_peri_sel.gdma_peri_in_sel_ch0);
		}
	}
	void GdmaDebug::print_out_peri_sel(bool onlyCoreValues){
		Serial.printf("=== out_peri_sel values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->out_peri_sel.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->out_peri_sel.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->out_peri_sel.offset);
			Serial.printf("\tgdma_peri_out_sel_ch0 : 0x%x\n", this->out_peri_sel.gdma_peri_out_sel_ch0);
		}
	}

	// Permission Status Registers
	void GdmaDebug::printPermissionStatRegs(bool onlyCoreValues){
		this->print_extmem_reject_addr(onlyCoreValues);
		this->print_extmem_reject_st(onlyCoreValues);
	}

	void GdmaDebug::print_extmem_reject_addr(bool onlyCoreValues){
		Serial.printf("=== extmem_reject_addr values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->extmem_reject_addr.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->extmem_reject_addr.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->extmem_reject_addr.offset);
			Serial.printf("\tgdma_extmem_reject_addr : 0x%x\n", this->extmem_reject_addr.gdma_extmem_reject_addr);
		}
	}
	void GdmaDebug::print_extmem_reject_st(bool onlyCoreValues){
		Serial.printf("=== extmem_reject_st values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->extmem_reject_st.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->extmem_reject_st.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->extmem_reject_st.offset);
			Serial.printf("\tgdma_extmem_reject_peri_num : 0x%x\n", this->extmem_reject_st.gdma_extmem_reject_peri_num);
			Serial.printf("\tgdma_extmem_reject_channel_num : 0x%x\n", this->extmem_reject_st.gdma_extmem_reject_channel_num);
			Serial.printf("\tgdma_extmem_reject_atrr : 0x%x\n", this->extmem_reject_st.gdma_extmem_reject_atrr);
		}
	}

	// Date Register
	void GdmaDebug::print_date(bool onlyCoreValues){
		Serial.printf("=== date values ===\n");
		Serial.printf("\tRegister Value : 0x%x\n", this->date.val);
		if(!onlyCoreValues){
			Serial.printf("\tReset Value : 0x%x\n", this->date.reset);
			Serial.printf("\tOffset Value : 0x%x\n", this->date.offset);
			Serial.printf("\tgdma_date : 0x%x\n", this->date.gdma_date);
		}
	}


	/*
	 * Patch functions
	 * */
	void GdmaDebug::patch(bool writeMode){
		this->patchConfigRegs(writeMode);
		this->patchInterruptRegs(writeMode);
		this->patchPriorityRegs(writeMode);
		this->patchPeriphSelRegs(writeMode);
		this->patch_date(writeMode);

	}
	void GdmaDebug::patchConfigRegs(bool writeMode){
		this->patch_in_conf0(writeMode);
		this->patch_in_conf1(writeMode); 
		this->patch_in_pop(writeMode);
		this->patch_in_link(writeMode);
		this->patch_out_conf0(writeMode);
		this->patch_out_conf1(writeMode);
		this->patch_out_push(writeMode);
		this->patch_out_link(writeMode);
		this->patch_pd_conf(writeMode);
		this->patch_misc_conf(writeMode);
	}
	void GdmaDebug::patch_in_conf0(bool writeMode){
		uint32_t r = this->in_conf0.val;
		r = this->regSet(r, this->in_conf0.gdma_mem_trans_en_ch, this->in_conf0.gdma_mem_trans_en_ch_pos);
	r = this->regSet(r, this->in_conf0.gdma_in_data_burst_en_ch, this->in_conf0.gdma_in_data_burst_en_ch_pos);
	r = this->regSet(r, this->in_conf0.gdma_indscr_burst_en_ch, this->in_conf0.gdma_indscr_burst_en_ch_pos);
	r = this->regSet(r, this->in_conf0.gdma_in_loop_test_ch, this->in_conf0.gdma_in_loop_test_ch_pos);
	r = this->regSet(r, this->in_conf0.gdma_in_rst_ch, this->in_conf0.gdma_in_rst_ch_pos);
	if(writeMode){
		this->regWrite(this->in_conf0.base, r, this->in_conf0.offset);
		this->init_in_conf0();
	}else{
		this->in_conf0.val = r;
	}
}
void GdmaDebug::patch_in_conf1(bool writeMode){
	uint32_t r = this->in_conf1.val;
	r = this->regSet(r, this->in_conf1.gdma_in_ext_mem_bk_size_ch, this->in_conf1.gdma_in_ext_mem_bk_size_ch_x, this->in_conf1.gdma_in_ext_mem_bk_size_ch_y);
	r = this->regSet(r, this->in_conf1.gdma_in_check_owner_ch, this->in_conf1.gdma_in_check_owner_ch_pos);
	r = this->regSet(r, this->in_conf1.gdma_dma_infifo_full_thrs_ch, this->in_conf1.gdma_dma_infifo_full_thrs_ch_x, this->in_conf1.gdma_dma_infifo_full_thrs_ch_y);
	if(writeMode){
		this->regWrite(this->in_conf1.base, r, this->in_conf1.offset);
		this->init_in_conf1();
	}else{
		this->in_conf1.val = r;
	}
}
void GdmaDebug::patch_in_pop(bool writeMode){
	uint32_t r = this->in_pop.val;
	r = this->regSet(r, this->in_pop.gdma_infifo_pop_ch, this->in_pop.gdma_infifo_pop_ch_pos);
	r = this->regSet(r, this->in_pop.gdma_infifo_rdata_ch, this->in_pop.gdma_infifo_rdata_ch_x, this->in_pop.gdma_infifo_rdata_ch_y);
	if(writeMode){
		this->regWrite(this->in_pop.base, r, this->in_pop.offset);
		this->init_in_pop();
	}else{
		this->in_pop.val = r;
	}
}
void GdmaDebug::patch_in_link(bool writeMode){
	uint32_t r = this->in_link.val;
	r = this->regSet(r, this->in_link.gdma_inlink_park_ch, this->in_link.gdma_inlink_park_ch_pos);
	r = this->regSet(r, this->in_link.gdma_inlink_restart_ch, this->in_link.gdma_inlink_restart_ch_pos);
	r = this->regSet(r, this->in_link.gdma_inlink_start_ch, this->in_link.gdma_inlink_start_ch_pos);
	r = this->regSet(r, this->in_link.gdma_inlink_stop_ch, this->in_link.gdma_inlink_stop_ch_pos);
	r = this->regSet(r, this->in_link.gdma_inlink_auto_ret_ch, this->in_link.gdma_inlink_auto_ret_ch_pos);
	r = this->regSet(r, this->in_link.gdma_inlink_addr_ch, this->in_link.gdma_inlink_addr_ch_x, this->in_link.gdma_inlink_addr_ch_y);
	if(writeMode){
		this->regWrite(this->in_link.base, r, this->in_link.offset);
		this->init_in_link();
	}else{
		this->in_link.val = r;
	}
}
void GdmaDebug::patch_out_conf0(bool writeMode){
	uint32_t r = this->out_conf0.val;
	r = this->regSet(r, this->out_conf0.gdma_out_data_burst_en_ch, this->out_conf0.gdma_out_data_burst_en_ch_pos);
	r = this->regSet(r, this->out_conf0.gdma_outdscr_burst_en_ch, this->out_conf0.gdma_outdscr_burst_en_ch_pos);
	r = this->regSet(r, this->out_conf0.gdma_out_eof_mode_ch, this->out_conf0.gdma_out_eof_mode_ch_pos);
	r = this->regSet(r, this->out_conf0.gdma_out_auto_wrback_ch, this->out_conf0.gdma_out_auto_wrback_ch_pos);
	r = this->regSet(r, this->out_conf0.gdma_out_loop_test_ch, this->out_conf0.gdma_out_loop_test_ch_pos);
	r = this->regSet(r, this->out_conf0.gdma_out_rst_ch, this->out_conf0.gdma_out_rst_ch_pos);
	if(writeMode){
		this->regWrite(this->out_conf0.base, r, this->out_conf0.offset);
		this->init_out_conf0();
	}else{
		this->out_conf0.val = r;
	}
}
void GdmaDebug::patch_out_conf1(bool writeMode){
	uint32_t r = this->out_conf1.val;
	r = this->regSet(r, this->out_conf1.gdma_out_ext_mem_bk_size_ch, this->out_conf1.gdma_out_ext_mem_bk_size_ch_x, this->out_conf1.gdma_out_ext_mem_bk_size_ch_y);
	r = this->regSet(r, this->out_conf1.gdma_out_check_owner_ch, this->out_conf1.gdma_out_check_owner_ch_pos);
	if(writeMode){
		this->regWrite(this->out_conf1.base, r, this->out_conf1.offset);
		this->init_out_conf1();
	}else{
		this->out_conf1.val = r;
	}
}
void GdmaDebug::patch_out_push(bool writeMode){
	uint32_t r = this->out_push.val;
	r = this->regSet(r, this->out_push.gdma_outfifo_push_ch, this->out_push.gdma_outfifo_push_ch_pos);
	r = this->regSet(r, this->out_push.gdma_outfifo_wdata_ch, this->out_push.gdma_outfifo_wdata_ch_x, this->out_push.gdma_outfifo_wdata_ch_y);
	if(writeMode){
		this->regWrite(this->out_push.base, r, this->out_push.offset);
		this->init_out_push();
	}else{
		this->out_push.val = r;
	}
}
void GdmaDebug::patch_out_link(bool writeMode){
	uint32_t r = this->out_link.val;
	r = this->regSet(r, this->out_link.gdma_outlink_park_ch, this->out_link.gdma_outlink_park_ch_pos);
	r = this->regSet(r, this->out_link.gdma_outlink_restart_ch, this->out_link.gdma_outlink_restart_ch_pos);
	r = this->regSet(r, this->out_link.gdma_outlink_start_ch, this->out_link.gdma_outlink_start_ch_pos);
	r = this->regSet(r, this->out_link.gdma_outlink_stop_ch, this->out_link.gdma_outlink_stop_ch_pos);
	r = this->regSet(r, this->out_link.gdma_outlink_addr_ch, this->out_link.gdma_outlink_addr_ch_x, this->out_link.gdma_outlink_addr_ch_y);
	if(writeMode){
		this->regWrite(this->out_link.base, r, this->out_link.offset);
		this->init_out_link();
	}else{
		this->out_link.val = r;
	}
}
void GdmaDebug::patch_pd_conf(bool writeMode){
	uint32_t r = this->pd_conf.val;
	r = this->regSet(r, this->pd_conf.gdma_dma_ram_clk_fo, this->pd_conf.gdma_dma_ram_clk_fo_pos);
	r = this->regSet(r, this->pd_conf.gdma_dma_ram_force_pu, this->pd_conf.gdma_dma_ram_force_pu_pos);
	r = this->regSet(r, this->pd_conf.gdma_dma_ram_force_pd, this->pd_conf.gdma_dma_ram_force_pd_pos);
	if(writeMode){
		this->regWrite(this->pd_conf.base, r, this->pd_conf.offset);
		this->init_pd_conf();
	}else{
		this->pd_conf.val = r;
	}
}
void GdmaDebug::patch_misc_conf(bool writeMode){
	uint32_t r = this->misc_conf.val;
	r = this->regSet(r, this->misc_conf.gdma_clk_en, this->misc_conf.gdma_clk_en_pos);
	r = this->regSet(r, this->misc_conf.gdma_arb_pri_dis, this->misc_conf.gdma_arb_pri_dis_pos);
	r = this->regSet(r, this->misc_conf.gdma_ahbm_rst_exter, this->misc_conf.gdma_ahbm_rst_exter_pos);
	r = this->regSet(r, this->misc_conf.gdma_ahbm_rst_inter, this->misc_conf.gdma_ahbm_rst_inter_pos);
	if(writeMode){
		this->regWrite(this->misc_conf.base, r, this->misc_conf.offset);
		this->init_misc_conf();
	}else{
		this->misc_conf.val = r;
	}
}

void GdmaDebug::patchInterruptRegs(bool writeMode){
	this->patch_in_int_raw(writeMode);
	this->patch_in_int_ena(writeMode);
	this->patch_in_int_clr(writeMode);
	this->patch_out_int_raw(writeMode);
	this->patch_out_int_ena(writeMode);
	this->patch_out_int_clr(writeMode);
	this->patch_extmem_reject_int(writeMode);
	this->patch_extmem_reject_int_ena(writeMode);
	this->patch_extmem_reject_int_clr(writeMode);
}
void GdmaDebug::patch_in_int_raw(bool writeMode){
	uint32_t r = this->in_int_raw.val;
	r = this->regSet(r, this->in_int_raw.gdma_infifo_full_wm_ch0_int_raw, this->in_int_raw. gdma_infifo_full_wm_ch0_int_raw_pos);
	r = this->regSet(r, this->in_int_raw.gdma_in_dscr_empty_ch0_int_raw, this->in_int_raw. gdma_in_dscr_empty_ch0_int_raw_pos);
	r = this->regSet(r, this->in_int_raw.gdma_in_dscr_err_ch0_int_raw, this->in_int_raw. gdma_in_dscr_err_ch0_int_raw_pos);
	r = this->regSet(r, this->in_int_raw.gdma_in_err_eof_ch0_int_raw, this->in_int_raw. gdma_in_err_eof_ch0_int_raw_pos);
	r = this->regSet(r, this->in_int_raw.gdma_in_suc_eof_ch0_int_raw, this->in_int_raw. gdma_in_suc_eof_ch0_int_raw_pos);
	r = this->regSet(r, this->in_int_raw.gdma_in_done_ch0_int_raw, this->in_int_raw. gdma_in_done_ch0_int_raw_pos);
	if(writeMode){
		this->regWrite(this->in_int_raw.base, r, this->in_int_raw.offset);
		this->init_in_int_raw();
	}else{
		this->in_int_raw.val = r;
	}
}
void GdmaDebug::patch_in_int_ena(bool writeMode){
	uint32_t r = this->in_int_ena.val;
	r = this->regSet(r, this->in_int_ena.gdma_infifo_full_wm_ch0_int_ena, this->in_int_ena. gdma_infifo_full_wm_ch0_int_ena_pos);
	r = this->regSet(r, this->in_int_ena.gdma_in_dscr_empty_ch0_int_ena, this->in_int_ena. gdma_in_dscr_empty_ch0_int_ena_pos);
	r = this->regSet(r, this->in_int_ena.gdma_in_dscr_err_ch0_int_ena, this->in_int_ena. gdma_in_dscr_err_ch0_int_ena_pos);
	r = this->regSet(r, this->in_int_ena.gdma_in_err_eof_ch0_int_ena, this->in_int_ena. gdma_in_err_eof_ch0_int_ena_pos);
	r = this->regSet(r, this->in_int_ena.gdma_in_suc_eof_ch0_int_ena, this->in_int_ena. gdma_in_suc_eof_ch0_int_ena_pos);
	r = this->regSet(r, this->in_int_ena.gdma_in_done_ch0_int_ena, this->in_int_ena. gdma_in_done_ch0_int_ena_pos);
	if(writeMode){
		this->regWrite(this->in_int_ena.base, r, this->in_int_ena.offset);
		this->init_in_int_ena();
	}else{
		this->in_int_ena.val = r;
	}
}
void GdmaDebug::patch_in_int_clr(bool writeMode){
	uint32_t r = this->in_int_clr.val;
	r = this->regSet(r, this->in_int_clr.gdma_dma_infifo_full_wm_ch0_int_clr, this->in_int_clr. gdma_dma_infifo_full_wm_ch0_int_clr_pos);
	r = this->regSet(r, this->in_int_clr.gdma_in_dscr_empty_ch0_int_clr, this->in_int_clr. gdma_in_dscr_empty_ch0_int_clr_pos);
	r = this->regSet(r, this->in_int_clr.gdma_in_dscr_err_ch0_int_clr, this->in_int_clr. gdma_in_dscr_err_ch0_int_clr_pos);
	r = this->regSet(r, this->in_int_clr.gdma_in_err_eof_ch0_int_clr, this->in_int_clr. gdma_in_err_eof_ch0_int_clr_pos);
	r = this->regSet(r, this->in_int_clr.gdma_in_suc_eof_ch0_int_clr, this->in_int_clr. gdma_in_suc_eof_ch0_int_clr_pos);
	r = this->regSet(r, this->in_int_clr.gdma_in_done_ch0_int_clr, this->in_int_clr. gdma_in_done_ch0_int_clr_pos);
	if(writeMode){
		this->regWrite(this->in_int_clr.base, r, this->in_int_clr.offset);
		this->init_in_int_clr();
	}else{
		this->in_int_clr.val = r;
	}
}
void GdmaDebug::patch_out_int_raw(bool writeMode){
	uint32_t r = this->out_int_raw.val;
	r = this->regSet(r, this->out_int_raw.gdma_out_total_eof_ch0_int_raw, this->out_int_raw. gdma_out_total_eof_ch0_int_raw_pos);
	r = this->regSet(r, this->out_int_raw.gdma_out_dscr_err_ch0_int_raw, this->out_int_raw. gdma_out_dscr_err_ch0_int_raw_pos);
	r = this->regSet(r, this->out_int_raw.gdma_out_eof_ch0_int_raw, this->out_int_raw. gdma_out_eof_ch0_int_raw_pos);
	r = this->regSet(r, this->out_int_raw.gdma_out_done_ch0_int_raw, this->out_int_raw. gdma_out_done_ch0_int_raw_pos);
	if(writeMode){
		this->regWrite(this->out_int_raw.base, r, this->out_int_raw.offset);
		this->init_out_int_raw();
	}else{
		this->out_int_raw.val = r;
	}
}
void GdmaDebug::patch_out_int_ena(bool writeMode){
	uint32_t r = this->out_int_ena.val;
	r = this->regSet(r, this->out_int_ena.gdma_out_total_eof_ch0_int_ena, this->out_int_ena. gdma_out_total_eof_ch0_int_ena_pos);
	r = this->regSet(r, this->out_int_ena.gdma_out_dscr_err_ch0_int_ena, this->out_int_ena. gdma_out_dscr_err_ch0_int_ena_pos);
	r = this->regSet(r, this->out_int_ena.gdma_out_eof_ch0_int_ena, this->out_int_ena. gdma_out_eof_ch0_int_ena_pos);
	r = this->regSet(r, this->out_int_ena.gdma_out_done_ch0_int_ena, this->out_int_ena. gdma_out_done_ch0_int_ena_pos);
	if(writeMode){
		this->regWrite(this->out_int_ena.base, r, this->out_int_ena.offset);
		this->init_out_int_ena();
	}else{
		this->out_int_ena.val = r;
	}
}
void GdmaDebug::patch_out_int_clr(bool writeMode){
	uint32_t r = this->out_int_clr.val;
	r = this->regSet(r, this->out_int_clr.gdma_out_total_eof_ch0_int_clr, this->out_int_clr. gdma_out_total_eof_ch0_int_clr_pos);
	r = this->regSet(r, this->out_int_clr.gdma_out_dscr_err_ch0_int_clr, this->out_int_clr. gdma_out_dscr_err_ch0_int_clr_pos);
	r = this->regSet(r, this->out_int_clr.gdma_out_eof_ch0_int_clr, this->out_int_clr. gdma_out_eof_ch0_int_clr_pos);
	r = this->regSet(r, this->out_int_clr.gdma_out_done_ch0_int_clr, this->out_int_clr. gdma_out_done_ch0_int_clr_pos);
	if(writeMode){
		this->regWrite(this->out_int_clr.base, r, this->out_int_clr.offset);
		this->init_out_int_clr();
	}else{
		this->out_int_clr.val = r;
	}
}
void GdmaDebug::patch_extmem_reject_int(bool writeMode){
	uint32_t r = this->extmem_reject_int.val;
	r = this->regSet(r, this->extmem_reject_int.gdma_extmem_reject_int_raw, this->extmem_reject_int. gdma_extmem_reject_int_raw_pos);
	if(writeMode){
		this->regWrite(this->extmem_reject_int.base, r, this->extmem_reject_int.offset);
		this->init_extmem_reject_int();
	}else{
		this->extmem_reject_int.val = r;
	}
}
void GdmaDebug::patch_extmem_reject_int_ena(bool writeMode){
	uint32_t r = this->extmem_reject_int_ena.val;
	r = this->regSet(r, this->extmem_reject_int_ena.gdma_extmem_reject_int_ena, this->extmem_reject_int_ena.gdma_extmem_reject_int_ena_pos);
	if(writeMode){
		this->regWrite(this->extmem_reject_int_ena.base, r, this->extmem_reject_int_ena.offset);
		this->init_extmem_reject_int_ena();
	}else{
		this->extmem_reject_int_ena.val = r;
	}
}
void GdmaDebug::patch_extmem_reject_int_clr(bool writeMode){
	uint32_t r = this->extmem_reject_int_clr.val;
	r = this->regSet(r, this->extmem_reject_int_clr.gdma_extmem_reject_int_clr, this->extmem_reject_int_clr.gdma_extmem_reject_int_clr_pos);
	if(writeMode){
		this->regWrite(this->extmem_reject_int_clr.base, r, this->extmem_reject_int_clr.offset);
		this->init_extmem_reject_int_clr();
	}else{
		this->extmem_reject_int_clr.val = r;
	}
}

void GdmaDebug::patchPriorityRegs(bool writeMode){
	this->patch_in_pri(writeMode);
	this->patch_out_pri(writeMode);
}

void GdmaDebug::patch_in_pri(bool writeMode){
	uint32_t r = this->in_pri.val;
	r = this->regSet(r, this->in_pri.gdma_rx_pri_ch0, this->in_pri.gdma_rx_pri_ch0_x, this->in_pri.gdma_rx_pri_ch0_y);
	if(writeMode){
		this->regWrite(this->in_pri.base, r, this->in_pri.offset);
		this->init_in_pri();
	}else{
		this->in_pri.val = r;
	}
}
void GdmaDebug::patch_out_pri(bool writeMode){
	uint32_t r = this->out_pri.val;
	r = this->regSet(r, this->out_pri.gdma_tx_pri_ch0, this->out_pri.gdma_tx_pri_ch0_x, this->out_pri.gdma_tx_pri_ch0_y);
	if(writeMode){
		this->regWrite(this->out_pri.base, r, this->out_pri.offset);
		this->init_out_pri();
	}else{
		this->out_pri.val = r;
	}
}

void GdmaDebug::patchPeriphSelRegs(bool writeMode){
	this->patch_in_peri_sel(writeMode);
	this->patch_out_peri_sel(writeMode);
}

void GdmaDebug::patch_in_peri_sel(bool writeMode){
	uint32_t r = this->in_peri_sel.val;
	r = this->regSet(r, this->in_peri_sel.gdma_peri_in_sel_ch0, this->in_peri_sel.gdma_peri_in_sel_ch0_x, this->in_peri_sel.gdma_peri_in_sel_ch0_y);
	if(writeMode){
		this->regWrite(this->in_peri_sel.base, r, this->in_peri_sel.offset);
		this->init_in_peri_sel();
	}else{
		this->in_peri_sel.val = r;
	}
}
void GdmaDebug::patch_out_peri_sel(bool writeMode){
	uint32_t r = this->out_peri_sel.val;
	r = this->regSet(r, this->out_peri_sel.gdma_peri_out_sel_ch0, this->out_peri_sel.gdma_peri_out_sel_ch0_x, this->out_peri_sel.gdma_peri_out_sel_ch0_y);
	if(writeMode){
		this->regWrite(this->out_peri_sel.base, r, this->out_peri_sel.offset);
		this->init_out_peri_sel();
	}else{
		this->out_peri_sel.val = r;
	}
}

void GdmaDebug::patch_date(bool writeMode){

	uint32_t r = this->date.val;
	r = this->regSet(r, this->date.gdma_date, this->date.gdma_date_x, this->date.gdma_date_y);
	if(writeMode){
		this->regWrite(this->date.base, r, this->date.offset);
		this->init_date();
	}else{
		this->date.val = r;
	}
}
