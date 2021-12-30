/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright 2021 Google, LLC
 *
 */

#ifndef GS101_USECASE_H_
#define GS101_USECASE_H_

struct max77759_usecase_data {
	int is_a1;

	int bst_on;		/* ext boost */
	int bst_sel;		/* 5V or 7.5V */
	int apbst_on;		/* AP boost ping */
	int ext_bst_ctl;	/* MW VENDOR_EXTBST_CTRL */
	int otg_enable;		/* enter/exit from OTG cases */

	int ls2_en;		/* OVP LS2, rtx case */
	int sw_en;		/* OVP SW Enable, rtx+otg case */

	int vin_is_valid;	/* MAX20339 STATUS1.vinvalid */
	int lsw1_is_open;	/* MAX20339 STATUS2.lsw1open */
	int lsw1_is_closed;	/* MAX20339 STATUS2.lsw1closed */
	int ls1_en;		/* MAX20339 close LSW1 directly */

	int wlc_en;		/* wlcrx/chgin coex */
	int wlc_vbus_en;	/* b/202526678 */
	int ext_bst_mode;	/* wlcrx+otg: b/175706836, TPS61372 P1.1+ */
	int cpout_en;		/* wlcrx+otg: CPOUT enabled/disabled */
	int cpout_ctl;		/* wlcrx+otg: CPOUT level 5.3V or DFLT */

	int cpout21_en;		/* wlctx: CPOUT 2:1 converter enable/disable */

	u8 otg_ilim;		/* TODO: TCPM to control this? */
	u8 otg_vbyp;		/* TODO: TCPM to control this? */
	u8 otg_orig;		/* restore value */
	u8 otg_value;		/* CHG_CNFG_11:VBYPSET for USB OTG Voltage */

	struct i2c_client *client;
	bool init_done;
	int use_case;

	bool dcin_is_dock;
};

enum gsu_usecases {
	GSU_RAW_MODE 		= -1,	/* raw mode, default, */

	GSU_MODE_STANDBY	= 0,	/* 8, PMIC mode 0 */
	GSU_MODE_USB_CHG	= 1,	/* 1-1 wired mode 0x4, mode 0x5 */
	GSU_MODE_USB_DC 	= 2,	/* 1-2 wired mode 0x0 */
	GSU_MODE_USB_CHG_WLC_TX = 3,	/* 2-1, 1041, */
	GSU_MODE_USB_DC_WLC_TX	= 4,	/* 2-2 1042, */

	GSU_MODE_WLC_RX		= 5,	/* 3-1, mode 0x4, mode 0x5 */
	GSU_MODE_WLC_DC		= 6,	/* 3-2, mode 0x0 */

	GSU_MODE_USB_OTG_WLC_RX = 7,	/* 4-1, 524, */
	GSU_MODE_USB_OTG_WLC_DC = 8,	/* 4-2, 532, */
	GSU_MODE_USB_OTG 	= 9,	/* 5-1, 516,*/
	GSU_MODE_USB_OTG_FRS	= 10,	/* 5-2, PMIC mode 0x0a */

	GSU_MODE_WLC_TX 	= 11,	/* 6-2, 1056, */
	GSU_MODE_USB_OTG_WLC_TX	= 12,	/* 7-2, 1060, */

	GSU_MODE_USB_WLC_RX	= 13,

	GSU_MODE_DOCK		= 14,
};

extern int gs101_wlc_en(struct max77759_usecase_data *uc_data, bool wlc_on);
extern int gs101_to_standby(struct max77759_usecase_data *uc_data, int use_case);
extern int gs101_to_usecase(struct max77759_usecase_data *uc_data, int use_case);
extern int gs101_force_standby(struct max77759_usecase_data *uc_data);
extern bool gs101_setup_usecases(struct max77759_usecase_data *uc_data,
				 struct device_node *node);
extern void gs101_dump_usecasase_config(struct max77759_usecase_data *uc_data);
extern int max77759_otg_vbyp_mv_to_code(u8 *code, int vbyp);

#endif
