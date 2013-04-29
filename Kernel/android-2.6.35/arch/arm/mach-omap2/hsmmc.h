/*
 * MMC definitions for OMAP2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

struct omap2_hsmmc_info {
	u8	mmc;		/* controller 1/2/3 */
	u32	caps;		/* 4/8 wires and any additional host
				 * capabilities OR'd (ref. linux/mmc/host.h) */
	bool	transceiver;	/* MMC-2 option */
	bool	ext_clock;	/* use external pin for input clock */
	bool	cover_only;	/* No card detect - just cover switch */
	bool	nonremovable;	/* Nonremovable e.g. eMMC */
	bool	power_saving;	/* Try to sleep or power off when possible */
	bool	no_off;		/* power_saving and power is not to go off */
	bool	vcc_aux_disable_is_sleep; /* Regulator off remapped to sleep */
	int	gpio_cd;	/* or -EINVAL */
	bool    cd_active_high; /* active high card detect */
	int	gpio_wp;	/* or -EINVAL */
	char	*name;		/* or NULL for default */
	struct device *dev;	/* returned: pointer to mmc adapter */
	int	ocr_mask;	/* temporary HACK */
	/* Remux (pad configuation) when powering on/off */
	void (*remux)(struct device *dev, int slot, int power_on);
//&*&*&*SJ1_20110607, Add SIM card detection.
#if defined (CONFIG_SIM_CARD_DETECTION) && defined (CONFIG_CHANGE_INAND_MMC_SCAN_INDEX)
	int	gpio_sim_cd;	/* or -EINVAL */
#endif /* End CONFIG_SIM_CARD_DETECTION */
//&*&*&*SJ2_20110607, Add SIM card detection.	
};

#ifdef CONFIG_TIWLAN_SDIO
int omap_wifi_status_register(void (*callback)(int card_present,
        void *dev_id), void *dev_id);
int omap_wifi_status(struct device *dev, int slot);
#endif

#if defined(CONFIG_MMC_OMAP_HS) || defined(CONFIG_MMC_OMAP_HS_MODULE)

void omap2_hsmmc_init(struct omap2_hsmmc_info *);

#else

static inline void omap2_hsmmc_init(struct omap2_hsmmc_info *info)
{
}

#endif
