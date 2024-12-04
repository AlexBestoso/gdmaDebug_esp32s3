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
void GdmaDebug::regWrite(uint32_t reg, uint32_t val){
	reg = reg + (this->channel*192);
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
