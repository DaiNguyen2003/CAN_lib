/**
 * @file    can_lib.h
 * @brief   CAN Library - Cấu hình signal từ DBC
 */

#ifndef CAN_LIB_H
#define CAN_LIB_H

#include "main.h"
#include <stdint.h>

/* ============================================================================
 * ============================================================================ */

typedef enum{
	Brake_Msg = 0,
	Key_Msg,
	Gear_Msg,
	STAT_Terminal_Msg,
    LV_Msg,
	HV_Msg,
	DCDC_Msg,
	CreepMode_Msg,
}MessName;
typedef enum{
	Brake_SwitchSts_Sig = 0,
	Brake_RegenMode_Sig,
	Brake_PedlVal_Sig,
	Brake_Light_Sig,

	Key_VLD_Sig,
	Key_fob_Leftcar_Sig,

	Gear_Target_Sig,
	Gear_Actual_Sig,

	STAT_Terminal_Sig,

	LV_Batt_Charging_Req_Sig,
	LV_TargetCurrent_Sig,
	LV_TargetVoltage_Sig,
	LV_MaxAllowChargeCurrent_Sig,
	LV_MaxAllowDischargeCurrent_Sig,
	LV_WakeupReason_Sig,
	LV_Batt_Current_Sig,
	LV_Batt_Temp_Sig,
	LV_BatteryType_Sig,
	LV_SOC_Sig,

	HV_OnOff_STS_Sig,
	HV_Sts_Sig,

	DCDC_Request_Sig,
    DCDC_Current_Sig,
	DCDC_Voltage_Sig,

	Creep_Disable_Sts_Sig,
	Creep_Mode_Req_Sig,
	Creep_Mode_Set_Sig,
	Creep_Flag_FWD_Sig,
	Creep_Flag_RWD_Sig

}SignalName;

// Endian type: Intel (Little-Endian) or Motorola (Big-Endian)
typedef enum {
    CAN_INTEL = 0,
    CAN_MOTOROLA
} CAN_Endian_t;

typedef struct {
    SignalName    name;            // Name in typedef name

    uint8_t       start_bit;       // (0-63)
    uint8_t       length;          // (1-64)
    uint8_t       is_signed;       // 0: unsigned, 1: signed
    CAN_Endian_t  endian;          // Intel / Motorola

    float         factor;          // scale
    float         offset;          // offset
} CAN_SignalDef_t;
typedef struct{
	MessName Name;
	uint16_t ID;
	uint8_t Number_Signal;
	CAN_SignalDef_t Signal[8];
} CAN_Message;


typedef struct {
	// Brake System
	struct {
		uint8_t SwitchSts;
		uint8_t RegenMode;
		float   PedalVal;
		uint8_t Light;
	} Brake;

	// Gear System
	struct {
		uint8_t Target;
		uint8_t Actual;
	} Gear;

	// Key / Terminal
	struct {
		uint8_t Key_Valid;
		uint8_t Key_Fob_Left;
		uint8_t Terminal_Stat;
	} Key;

	// LV Battery
	struct {
		uint8_t Charging_Req;
		float   TargetCurrent;
		float   TargetVoltage;
		float   Current;
		float   Voltage; // DCDC logic could go here too or separate
		uint8_t SOC;
		uint8_t Temp;
		uint8_t MaxAllowChargeCurrent;
		uint8_t MaxAllowDischargeCurrent;
		uint8_t WakeupReason;
		uint8_t BatteryType;
	} LV_Bat;

	// HV Battery
	struct {
		uint8_t OnOff_Sts;
		uint8_t Status;
	} HV_Bat;

	// DCDC System
	struct {
		uint8_t Request;
		float   Current;
		float   Voltage;
	} DCDC;

	// Creep Mode
	struct {
		uint8_t Disable_Sts;    // Trạng thái tắt/bật (MHU_VCU_CreepDisable_stt)
		uint8_t Mode_Req;       // Yêu cầu chế độ (MHU_Req_StoppingMode)
		uint8_t Mode_Set;       // Cài đặt hiện tại (MHU_SET_StopMode)
		uint8_t Flag_FWD;       // Cờ báo cho EDU trước (VCU_EDS_CreepFlg_FWD)
		uint8_t Flag_RWD;       // Cờ báo cho EDU sau (VCU_EDS_CreepFlg_RWD)
	} CreepMode;

} CAN_Data_t;



extern CAN_Data_t VF_LIMO_Data;
extern CAN_Data_t VF789_Data;

/* Message Tables & Sizes */
extern const CAN_Message VF789_Msg[];
extern const uint16_t SIZE_VF789_Msg;

extern const CAN_Message VF_LIMO_Msg[];
extern const uint16_t SIZE_VF_LIMO_Msg;

/* Function Prototypes */
void CAN_Decode_Message(uint32_t ID, uint8_t *RxData, const CAN_Message *MsgTable, uint16_t TableSize, CAN_Data_t *Data);
void CAN_Process_Rx(uint32_t ID, uint8_t *RxData);
void CAN_Config_Init(CAN_HandleTypeDef *hcan);

/* Vehicle Selection */
typedef enum {
    CAR_VF_LIMO = 0,
    CAR_VF789,
    // Add more profiles here
} CarProfile_t;

extern CarProfile_t CurrentCarProfile;

// #define USE_VF_LIMO     1  <-- Commented out to use dynamic profile
// #define USE_VF789       1

#endif
