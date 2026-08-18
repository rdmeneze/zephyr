/** @file
 * @brief Simcom SIM7000 modem public API header file.
 * @ingroup simcom_sim7000_interface
 *
 * Copyright (C) 2026 Rafael Dias Menezes <rdmeneze@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_DRIVERS_MODEM_SIMCOM_SIM7000_H
#define ZEPHYR_INCLUDE_DRIVERS_MODEM_SIMCOM_SIM7000_H

#include <zephyr/types.h>

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup simcom_sim7000_interface SIMCom SIM7000
 * @brief SIMCom SIM7000 cellular modems.
 * @ingroup cellular_interface_ext
 * @{
 */

/** Maximum number of DNS retries */
#define SIM7000_DNS_MAX_RECOUNT 10
/** Maximum timeout for DNS queries in milliseconds */
#define SIM7000_DNS_MAX_TIMEOUT_MS 60000

/** Channel Mask for NB-IoT */
#define SIM7000_LTE_CHANNEL_MASK_NB1 0x7BEFFU
/** Channel Mask for CAT-M1 */
#define SIM7000_LTE_CHANNEL_MASK_M1  0x5FFFFU
/** Number of LTE channels supported by the modem */
#define SIM7000_NUM_LTE_CHANNELS     19U

/** Sim7000 modem state */
enum sim7000_state {
	SIM7000_STATE_INIT = 0, /**< Initial modem state */
	SIM7000_STATE_IDLE, /**< Modem idle */
	SIM7000_STATE_NETWORKING, /**< Network active */
	SIM7000_STATE_OFF, /**< Modem off */
};

/** Modem radio access technology */
enum sim7000_rat {
	SIM7000_RAT_LTE_NB1,  /**< NB-IoT only */
	SIM7000_RAT_LTE_M1,   /**< LTE CAT M1 only */
	SIM7000_RAT_LTE_AUTO, /**< Modem automatically selects M1 or NB1 */
	SIM7000_RAT_GSM,      /**< GSM */
};

/** Supported LTE channels */
enum sim7000_lte_chan {
	SIM7000_LTE_CHAN_B1 = BIT(0),   /**< LTE Band 1 */
	SIM7000_LTE_CHAN_B2 = BIT(1),   /**< LTE Band 2 */
	SIM7000_LTE_CHAN_B3 = BIT(2),   /**< LTE Band 3 */
	SIM7000_LTE_CHAN_B4 = BIT(3),   /**< LTE Band 4 */
	SIM7000_LTE_CHAN_B5 = BIT(4),   /**< LTE Band 5 */
	SIM7000_LTE_CHAN_B8 = BIT(5),   /**< LTE Band 8 */
	SIM7000_LTE_CHAN_B12 = BIT(6),  /**< LTE Band 12 */
	SIM7000_LTE_CHAN_B13 = BIT(7),  /**< LTE Band 13 */
	SIM7000_LTE_CHAN_B14 = BIT(8),  /**< LTE Band 14 */
	SIM7000_LTE_CHAN_B18 = BIT(9),  /**< LTE Band 18 */
	SIM7000_LTE_CHAN_B19 = BIT(10), /**< LTE Band 19 */
	SIM7000_LTE_CHAN_B20 = BIT(11), /**< LTE Band 20 */
	SIM7000_LTE_CHAN_B25 = BIT(12), /**< LTE Band 25 */
	SIM7000_LTE_CHAN_B26 = BIT(13), /**< LTE Band 26 */
	SIM7000_LTE_CHAN_B27 = BIT(14), /**< LTE Band 27 */
	SIM7000_LTE_CHAN_B28 = BIT(15), /**< LTE Band 28 */
	SIM7000_LTE_CHAN_B66 = BIT(16), /**< LTE Band 66 */
	SIM7000_LTE_CHAN_B71 = BIT(17), /**< LTE Band 71 */
	SIM7000_LTE_CHAN_B85 = BIT(18), /**< LTE Band 85 */
};

/**
 * Get the current state of the modem.
 *
 * @return The current state.
 */
enum sim7000_state mdm_sim7000_get_state(void);

/**
 * @brief Power on the Sim7000.
 *
 * @return 0 on success. Otherwise -1 is returned.
 */
int mdm_sim7000_power_on(void);

/**
 * @brief Power off the Sim7000.
 *
 * @return 0 on success. Otherwise -1 is returned.
 */
int mdm_sim7000_power_off(void);

/**
 * Forcefully reset the modem by pulling pwrkey for 15 seconds.
 * @note The state of the modem may be undefined after calling
 * this function. Call mdm_sim7000_power_on after force reset.
 */
void mdm_sim7000_force_reset(void);

/**
 * @brief Activates the network operation mode of the modem.
 *
 * @return 0 on success. Otherwise <0 is returned.
 * @note The modem needs to be booted for this function to work.
 */
int mdm_sim7000_start_network(void);

/**
 * @brief Stops the networking operation mode of the modem.
 *
 * @return 0 on success. Otherwise <0 is returned.
 */
int mdm_sim7000_stop_network(void);

/**
 * Get the sim7000 manufacturer.
 */
const char *mdm_sim7000_get_manufacturer(void);

/**
 * Get the sim7000 model information.
 */
const char *mdm_sim7000_get_model(void);

/**
 * Get the sim7000 revision.
 */
const char *mdm_sim7000_get_revision(void);

/**
 * Get the sim7000 imei number.
 */
const char *mdm_sim7000_get_imei(void);

/**
 * Get the sim7000 iccid number.
 */
const char *mdm_sim7000_get_iccid(void);

/**
 * Set the dns query lookup parameters.
 *
 * @param recount Number of retries per query.
 *				  Maximum @c SIM7000_DNS_MAX_RECOUNT
 * @param timeout Timeout for a dns query in milliseconds.
 *				  Maximum @c SIM7000_DNS_MAX_TIMEOUT_MS
 * @return 0 on success. Otherwise a negative error is returned.
 */
int mdm_sim7000_dns_set_lookup_params(uint8_t recount, uint16_t timeout);

/**
 * Get the dns query lookup parameters.
 *
 * @param recount [out] Number of retries per query.
 * @param timeout [out] Timeout for a dns query in milliseconds.
 */
void mdm_sim7000_dns_get_lookup_params(uint8_t *recount, uint16_t *timeout);

/**
 * @brief Get the currently selected radio technology.
 *
 * @param rat [out] Gets set to the current technology.
 */
void mdm_sim7000_get_rat(enum sim7000_rat *rat);

/**
 * @brief Set the radio technology.
 *
 * @param rat The radio technology.
 * @retval 0 Success.
 * @retval -EINVAL The selected technology is not available.
 *
 * @note This function needs to be called before mdm_sim7000_start_network().
 *       If networking is already active, the change will not affect the current session.
 *		 To apply changes, networking has to be restarted.
 *		 A power cycle may be needed for the modem to forget the last working configuration.
 */
int mdm_sim7000_set_rat(enum sim7000_rat rat);

/**
 * @brief Get the currently used LTE bands.
 *
 * @param nb1 [out] Used NB-IoT bands. May be NULL.
 * @param m1 [out] Used CAT-M1 bands. May be NULL.
 */
void mdm_sim7000_get_lte_bands(uint32_t *nb1, uint32_t *m1);

/**
 * @brief Set the LTE bands to use.
 *
 * @param nb1 NB-IoT bands to use. 0 to not change the bands.
 * @param m1 CAT-M1 bands to use. 0 to not change the bands.
 * @retval 0 Success.
 * @retval -EINVAL The band selection is illegal.
 *
 * @note This function needs to be called before mdm_sim7000_start_network().
 *       If networking is already active, the change will not affect the current session.
 *		 To apply changes, networking has to be restarted.
 *		 A power cycle may be needed for the modem to forget the last working configuration.
 * @note Available NB-IoT and CAT-M1 differ. Refer to SIM7000_LTE_CHANNEL_MASK_NB1
 *       and SIM7000_LTE_CHANNEL_MASK_M1.
 */
int mdm_sim7000_set_lte_bands(uint32_t nb1, uint32_t m1);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* ZEPHYR_INCLUDE_DRIVERS_MODEM_SIMCOM_SIM7000_H */
