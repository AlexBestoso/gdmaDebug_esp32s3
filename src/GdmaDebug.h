#define DBG_PERF_GDMA 0x3f000
#define DBG_PERF_GDMA_BASE 0x60000000 + DBG_PERF_GDMA
#define DBG_PERF_GDMA_READ(reg) (*(volatile uint32_t *)(DBG_PERF_GDMA_BASE+reg))
#define DBG_PERF_GDMA_WRITE(reg, val) ((*(volatile uint32_t *)(DBG_PERF_GDMA_BASE+reg)) = (val))

#include "./GdmaDebug.structs.h"

class GdmaDebug{
	private:
		void regWrite(uint32_t reg, uint32_t val, int offset);
		uint32_t regRead(uint32_t reg, int offset);

		// Helps isoltate fields within the 32 bit registers.
		bool regGet(uint32_t val, int pos);
		int regGet(uint32_t val, int x, int y);

		// Helps convert register structs into single register values.
		uint32_t regSet(uint32_t reg, bool val, int pos);
		uint32_t regSet(uint32_t reg, int val, int x, int y);
	public:
	
		int channel;
		/* 
		 * Configuration Registers
		 * */
		struct gdma_in_conf0_ch_reg in_conf0;
		struct gdma_in_conf1_ch_reg in_conf1; 
		struct gdma_in_pop_ch_reg in_pop;
		struct gdma_in_link_ch_reg in_link;
		struct gdma_out_conf0_ch_reg out_conf0;
		struct gdma_out_conf1_ch_reg out_conf1;
		struct gdma_out_push_ch_reg out_push;
		struct gdma_out_link_ch_reg out_link;
		struct gdma_pd_conf_reg pd_conf;
		struct gdma_misc_conf_reg misc_conf;
		/*
		 * Interrupt Registers
		 * */
		struct gdma_in_int_raw_ch_reg in_int_raw;
		struct gdma_in_int_st_ch_reg in_int_st;
		struct gdma_in_int_ena_ch_reg in_int_ena;
		struct gdma_in_int_clr_ch_reg in_int_clr;
		struct gdma_out_int_raw_ch_reg out_int_raw;
		struct gdma_out_int_st_ch_reg out_int_st;
		struct gdma_out_int_ena_ch_reg out_int_ena;
		struct gdma_out_int_clr_ch_reg out_int_clr;
		struct gdma_extmem_reject_int_raw_reg extmem_reject_int;
		struct gdma_extmem_reject_int_st_reg extmem_reject_int_st;
		struct gdma_extmem_reject_int_ena_reg extmem_reject_int_ena;
		struct gdma_extmem_reject_int_clr_reg extmem_reject_int_clr;
		/*
		 * Status Registers
		 * */
		struct gdma_infifo_status_chn_reg infifo_status;
		struct gdma_in_state_chn_reg in_state;
		struct gdma_in_suc_eof_des_addr_chn_reg in_suc_eof_des_addr;
		struct gdma_in_err_eof_des_addr_chn_reg in_err_eof_des_addr;
		struct gdma_in_dscr_chn_reg in_dscr;
		struct gdma_in_dscr_bf0_chn_reg in_dscr_bf0;
		struct gdma_in_dscr_bf1_chn_reg in_dscr_bf1;
		struct gdma_outfifo_status_chn_reg outfifo_status;
		struct gdma_out_state_chn_reg out_state;
		struct gdma_out_eof_des_addr_chn_reg out_eof_des_addr;
		struct gdma_out_eof_bfr_des_addr_chn_reg out_eof_bfr_des_addr;
		struct gdma_out_dscr_chn_reg out_dscr;
		struct gdma_out_dscr_bf0_chn_reg out_dscr_bf0;
		struct gdma_out_dscr_bf1_chn_reg out_dscr_bf1;
		/*
		 * Priority Registers
		 * */
		struct gdma_in_pri_chn_reg in_pri;
		struct gdma_out_pri_chn_reg out_pri;
		/*
		 * Peripheral Selection Registers
		 * */
		struct gdma_in_peri_sel_chn_reg in_peri_sel;
		struct gdma_out_peri_sel_chn_reg out_peri_sel;
		/*
		 * Permission Status Registers
		 * */
		struct gdma_extmem_reject_addr_reg extmem_reject_addr;
		struct gdma_extmem_reject_st_reg extmem_reject_st;
		/*
		 * Version Register
		 * */
		struct gdma_date_reg date;

		GdmaDebug(void);
		~GdmaDebug();
	
		void init(void);
		void refresh(void);

		/* 
		 * Struct initalization functions
		 * */
			
                // Configuration Registers
		void initConfigRegs(void);
       		void init_in_conf0(void);
		void init_in_conf1(void); 
		void init_in_pop(void);
		void init_in_link(void);
		void init_out_conf0(void);
		void init_out_conf1(void);
		void init_out_push(void);
		void init_out_link(void);
		void init_pd_conf(void);
		void init_misc_conf(void);

		
		// Interrupt Registers
		void initInterruptRegs(void);
		void init_in_int_raw(void);
		void init_in_int_st(void);
		void init_in_int_ena(void);
		void init_in_int_clr(void);
		void init_out_int_raw(void);
		void init_out_int_st(void);
		void init_out_int_ena(void);
		void init_out_int_clr(void);
		void init_extmem_reject_int(void);
		void init_extmem_reject_int_st(void);
		void init_extmem_reject_int_ena(void);
		void init_extmem_reject_int_clr(void);

		// Status Registers
		void initStatusRegs(void);
		void init_infifo_status(void);
		void init_in_state(void);
		void init_in_suc_eof_des_addr(void);
		void init_in_err_eof_des_addr(void);
		void init_in_dscr(void);
		void init_in_dscr_bf0(void);
		void init_in_dscr_bf1(void);
		void init_outfifo_status(void);
		void init_out_state(void);
		void init_out_eof_des_addr(void);
		void init_out_eof_bfr_des_addr(void);
		void init_out_dscr(void);
		void init_out_dscr_bf0(void);
		void init_out_dscr_bf1(void);

		// Priority Registers
		void initPriorityRegs(void);
		void init_in_pri(void);
		void init_out_pri(void);

		// Peripheral Selection Registers
		void initPeriphSelRegs(void);
		void init_in_peri_sel(void);
		void init_out_peri_sel(void);

		// Permission Status Registers
		void initPermissionStatRegs(void);
		void init_extmem_reject_addr(void);
		void init_extmem_reject_st(void);
		
		// Version Register
		void init_date(void);

		/*
		 * Print Functions 
		 * */
		void print(bool onlyCoreValues);

		// Configuration Registers
		void printConfigRegs(bool onlyCoreValues);
       		void print_in_conf0(bool onlyCoreValues);
		void print_in_conf1(bool onlyCoreValues); 
		void print_in_pop(bool onlyCoreValues);
		void print_in_link(bool onlyCoreValues);
		void print_out_conf0(bool onlyCoreValues);
		void print_out_conf1(bool onlyCoreValues);
		void print_out_push(bool onlyCoreValues);
		void print_out_link(bool onlyCoreValues);
		void print_pd_conf(bool onlyCoreValues);
		void print_misc_conf(bool onlyCoreValues);

		
		// Interrupt Registers
		void printInterruptRegs(bool onlyCoreValues);
		void print_in_int_raw(bool onlyCoreValues);
		void print_in_int_st(bool onlyCoreValues);
		void print_in_int_ena(bool onlyCoreValues);
		void print_in_int_clr(bool onlyCoreValues);
		void print_out_int_raw(bool onlyCoreValues);
		void print_out_int_st(bool onlyCoreValues);
		void print_out_int_ena(bool onlyCoreValues);
		void print_out_int_clr(bool onlyCoreValues);
		void print_extmem_reject_int(bool onlyCoreValues);
		void print_extmem_reject_int_st(bool onlyCoreValues);
		void print_extmem_reject_int_ena(bool onlyCoreValues);
		void print_extmem_reject_int_clr(bool onlyCoreValues);

		// Status Registers
		void printStatusRegs(bool onlyCoreValues);
		void print_infifo_status(bool onlyCoreValues);
		void print_in_state(bool onlyCoreValues);
		void print_in_suc_eof_des_addr(bool onlyCoreValues);
		void print_in_err_eof_des_addr(bool onlyCoreValues);
		void print_in_dscr(bool onlyCoreValues);
		void print_in_dscr_bf0(bool onlyCoreValues);
		void print_in_dscr_bf1(bool onlyCoreValues);
		void print_outfifo_status(bool onlyCoreValues);
		void print_out_state(bool onlyCoreValues);
		void print_out_eof_des_addr(bool onlyCoreValues);
		void print_out_eof_bfr_des_addr(bool onlyCoreValues);
		void print_out_dscr(bool onlyCoreValues);
		void print_out_dscr_bf0(bool onlyCoreValues);
		void print_out_dscr_bf1(bool onlyCoreValues);

		// Priority Registers
		void printPriorityRegs(bool onlyCoreValues);
		void print_in_pri(bool onlyCoreValues);
		void print_out_pri(bool onlyCoreValues);

		// Peripheral Selection Registers
		void printPeriphSelRegs(bool onlyCoreValues);
		void print_in_peri_sel(bool onlyCoreValues);
		void print_out_peri_sel(bool onlyCoreValues);

		// Permission Status Registers
		void printPermissionStatRegs(bool onlyCoreValues);
		void print_extmem_reject_addr(bool onlyCoreValues);
		void print_extmem_reject_st(bool onlyCoreValues);
		
		// Version Register
		void print_date(bool onlyCoreValues);

		/*
		 * Patch Functions 
		 * */
		void patch(bool writeMode);

		// Configuration Registers
		void patchConfigRegs(bool writeMode);
       		void patch_in_conf0(bool writeMode);
		void patch_in_conf1(bool writeMode); 
		void patch_in_pop(bool writeMode);
		void patch_in_link(bool writeMode);
		void patch_out_conf0(bool writeMode);
		void patch_out_conf1(bool writeMode);
		void patch_out_push(bool writeMode);
		void patch_out_link(bool writeMode);
		void patch_pd_conf(bool writeMode);
		void patch_misc_conf(bool writeMode);

		
		// Interrupt Registers
		void patchInterruptRegs(bool writeMode);
		void patch_in_int_raw(bool writeMode);
		void patch_in_int_ena(bool writeMode);
		void patch_in_int_clr(bool writeMode);
		void patch_out_int_raw(bool writeMode);
		void patch_out_int_ena(bool writeMode);
		void patch_out_int_clr(bool writeMode);
		void patch_extmem_reject_int(bool writeMode);
		void patch_extmem_reject_int_ena(bool writeMode);
		void patch_extmem_reject_int_clr(bool writeMode);

		// Priority Registers
		void patchPriorityRegs(bool writeMode);
		void patch_in_pri(bool writeMode);
		void patch_out_pri(bool writeMode);

		// Peripheral Selection Registers
		void patchPeriphSelRegs(bool writeMode);
		void patch_in_peri_sel(bool writeMode);
		void patch_out_peri_sel(bool writeMode);

		// Version Register
		void patch_date(bool writeMode);

};
