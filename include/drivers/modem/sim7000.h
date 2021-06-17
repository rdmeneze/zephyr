/** @file
 * @brief SIM7000 modem public API header file.
 *
 * Allows an application to control the SIM7000 modem.
 *
 * Copyright (c) 2021 Rafael Dias <rdmeneze@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_DRIVERS_MODEM_SIM7000_H_
#define ZEPHYR_INCLUDE_DRIVERS_MODEM_SIM7000_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_NEWLIB_LIBC
#include <time.h>
#endif

/* The size includes the NUL character, the strlen doesn't */
#define MDM_SIM7000_REVISION_MAX_SIZE 29
#define MDM_SIM7000_REVISION_MAX_STRLEN (MDM_SIM7000_REVISION_MAX_SIZE - 1)

#define MDM_SIM7000_IMEI_SIZE 16
#define MDM_SIM7000_IMEI_STRLEN (MDM_SIM7000_IMEI_SIZE - 1)

#define MDM_SIM7000_ICCID_SIZE 21
#define MDM_SIM7000_ICCID_STRLEN (MDM_SIM7000_ICCID_SIZE - 1)

#define MDM_SIM7000_SERIAL_NUMBER_SIZE 15
#define MDM_SIM7000_SERIAL_NUMBER_STRLEN (MDM_SIM7000_SERIAL_NUMBER_SIZE - 1)

#define MDM_SIM7000_APN_MAX_SIZE 64
#define MDM_SIM7000_APN_USERNAME_MAX_SIZE 65
#define MDM_SIM7000_APN_PASSWORD_MAX_SIZE 65

#define MDM_SIM7000_APN_MAX_STRLEN (MDM_SIM7000_APN_MAX_SIZE - 1)
#define MDM_SIM7000_APN_USERNAME_MAX_STRLEN                                     \
	(MDM_SIM7000_APN_USERNAME_MAX_SIZE - 1)
#define MDM_SIM7000_APN_PASSWORD_MAX_STRLEN                                     \
	(MDM_SIM7000_APN_PASSWORD_MAX_SIZE - 1)

#define MDM_SIM7000_APN_CMD_MAX_SIZE                                            \
	(32 + MDM_SIM7000_APN_USERNAME_MAX_STRLEN +                             \
	 MDM_SIM7000_APN_PASSWORD_MAX_STRLEN)

#define MDM_SIM7000_APN_CMD_MAX_STRLEN (MDM_SIM7000_APN_CMD_MAX_SIZE - 1)

struct mdm_sim7000_apn {
	char value[MDM_SIM7000_APN_MAX_SIZE];
	char username[MDM_SIM7000_APN_USERNAME_MAX_SIZE];
	char password[MDM_SIM7000_APN_PASSWORD_MAX_SIZE];
};

#define MDM_SIM7000_LTE_BAND_STR_SIZE 21
#define MDM_SIM7000_LTE_BAND_STRLEN (MDM_SIM7000_LTE_BAND_STR_SIZE - 1)

enum mdm_sim7000_radio_mode { MDM_RAT_CAT_M1 = 0, MDM_RAT_CAT_NB1 };

enum mdm_sim7000_event {
	SIM7000_EVENT_RESERVED = 0,
	SIM7000_EVENT_NETWORK_STATE_CHANGE,
	SIM7000_EVENT_APN_UPDATE,
	SIM7000_EVENT_RSSI,
	SIM7000_EVENT_SINR,
	SIM7000_EVENT_STARTUP_STATE_CHANGE,
	SIM7000_EVENT_SLEEP_STATE_CHANGE,
	SIM7000_EVENT_RAT,
	SIM7000_EVENT_BANDS,
	SIM7000_EVENT_ACTIVE_BANDS,
	SIM7000_EVENT_FOTA_STATE,
	SIM7000_EVENT_FOTA_COUNT,
	SIM7000_EVENT_REVISION
};

enum mdm_sim7000_startup_state {
	SIM7000_STARTUP_STATE_READY = 0,
	SIM7000_STARTUP_STATE_WAITING_FOR_ACCESS_CODE,
	SIM7000_STARTUP_STATE_SIM_NOT_PRESENT,
	SIM7000_STARTUP_STATE_SIMLOCK,
	SIM7000_STARTUP_STATE_UNRECOVERABLE_ERROR,
	SIM7000_STARTUP_STATE_UNKNOWN,
	SIM7000_STARTUP_STATE_INACTIVE_SIM
};

enum mdm_sim7000_network_state {
	SIM7000_NOT_REGISTERED = 0,
	SIM7000_HOME_NETWORK,
	SIM7000_SEARCHING,
	SIM7000_REGISTRATION_DENIED,
	SIM7000_OUT_OF_COVERAGE,
	SIM7000_ROAMING,
	SIM7000_EMERGENCY = 8,
	/* Laird defined states */
	SIM7000_UNABLE_TO_CONFIGURE = 0xf0
};

enum mdm_sim7000_sleep_state {
	SIM7000_SLEEP_STATE_UNINITIALIZED = 0,
	SIM7000_SLEEP_STATE_ASLEEP,
	SIM7000_SLEEP_STATE_AWAKE
};

enum mdm_sim7000_fota_state {
	SIM7000_FOTA_IDLE,
	SIM7000_FOTA_START,
	SIM7000_FOTA_WIP,
	SIM7000_FOTA_PAD,
	SIM7000_FOTA_SEND_EOT,
	SIM7000_FOTA_FILE_ERROR,
	SIM7000_FOTA_INSTALL,
	SIM7000_FOTA_REBOOT_AND_RECONFIGURE,
	SIM7000_FOTA_COMPLETE,
};

/* The modem reports state values as an enumeration and a string */
struct mdm_sim7000_compound_event {
	uint8_t code;
	char *string;
};

/**
 * event - The type of event
 * event_data - Pointer to event specific data structure
 * SIM7000_EVENT_NETWORK_STATE_CHANGE - compound event
 * SIM7000_EVENT_APN_UPDATE - struct mdm_sim7000_apn
 * SIM7000_EVENT_RSSI - int
 * SIM7000_EVENT_SINR - int
 * SIM7000_EVENT_STARTUP_STATE_CHANGE - compound event
 * SIM7000_EVENT_SLEEP_STATE_CHANGE - compound event
 * SIM7000_EVENT_RAT - int
 * SIM7000_EVENT_BANDS - string
 * SIM7000_EVENT_ACTIVE_BANDS - string
 * SIM7000_EVENT_FOTA_STATE - compound event
 * SIM7000_EVENT_FOTA_COUNT - uint32_t
 * SIM7000_EVENT_REVISION - string
 */
typedef void (*mdm_sim7000_event_callback_t)(enum mdm_sim7000_event event,
					    void *event_data);

/**
 * @brief Power off the SIM7000
 *
 * @return int32_t 0 for success
 */
int32_t mdm_sim7000_power_off(void);

/**
 * @brief Reset the SIM7000
 *
 * @return int32_t 0 for success
 */
int32_t mdm_sim7000_reset(void);

/**
 * @brief Control the wake signals to the SIM7000.
 * @note this API should only be used for debug purposes.
 *
 * @param awake True to keep the SIM7000 awake, False to allow sleep
 */
void mdm_sim7000_wakeup(bool awake);

/**
 * @brief Send an AT command to the SIM7000.
 * @note this API should only be used for debug purposes.
 *
 * @param data AT command string
 * @return int32_t 0 for success
 */
int32_t mdm_sim7000_send_at_cmd(const uint8_t *data);

/**
 * @brief Get the signal quality of the SIM7000
 *
 * @param rsrp Reference Signals Received Power (dBm)
 *             Range = -140 dBm to -44 dBm
 * @param sinr Signal to Interference plus Noise Ratio (dBm)
 *             Range = -128 dBm to 40dBm
 */
void mdm_sim7000_get_signal_quality(int *rsrp, int *sinr);

/**
 * @brief Get the SIM card ICCID
 *
 */
char *mdm_sim7000_get_iccid(void);

/**
 * @brief Get the SIM7000 serial number
 *
 */
char *mdm_sim7000_get_sn(void);

/**
 * @brief Get the SIM7000 IMEI
 *
 */
char *mdm_sim7000_get_imei(void);

/**
 * @brief Get the SIM7000 firmware version
 *
 */
char *mdm_sim7000_get_fw_version(void);

/**
 * @brief Update the Access Point Name in the modem.
 *
 * @retval 0 on success, negative on failure.
 */
int32_t mdm_sim7000_update_apn(char *access_point_name);

/**
 * @brief Update the Radio Access Technology (mode).
 *
 * @retval 0 on success, negative on failure.
 */
int32_t mdm_sim7000_update_rat(enum mdm_sim7000_radio_mode value);

/**
 * @retval true if RAT value is valid
 */
bool mdm_sim7000_valid_rat(uint8_t value);

/**
 * @brief Register a function that is called when a modem event occurs.
 *
 * @param cb event callback
 */
void mdm_sim7000_register_event_callback(mdm_sim7000_event_callback_t cb);

/**
 * @brief Force modem module to generate status events.
 *
 * @note This can be used to get the current state when a module initializes
 * later than the modem.
 */
void mdm_sim7000_generate_status_events(void);

#ifdef CONFIG_NEWLIB_LIBC
/**
 * @brief Get the local time from the modem's real time clock.
 *
 * @param tm time structure
 * @param offset The amount the local time is offset from GMT/UTC in seconds.
 *
 * @param 0 if successful
 */
int32_t mdm_sim7000_get_local_time(struct tm *tm, int32_t *offset);
#endif

#ifdef CONFIG_MODEM_SIM7000_FW_UPDATE
/**
 * @brief Update the SIM7000 via XMODEM protocol.  During the firmware update
 * no other modem fuctions will be available.
 *
 * @param file_path Absolute path of the update file
 *
 * @param 0 if successful
 */
int32_t mdm_sim7000_update_fw(char *file_path);
#endif

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_INCLUDE_DRIVERS_MODEM_SIM7000_H_ */
