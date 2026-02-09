/**
 * @file    can_lib.c
 * @brief   CAN Library - Signal Table Implementation
 */

#include "can_lib.h"
#include <string.h>




CAN_Data_t VF_LIMO_Data;
CAN_Data_t VF_LIMO_Data;
CAN_Data_t VF789_Data;
CAN_Data_t VF5_Data;
CarProfile_t CurrentCarProfile = CAR_VF_LIMO; // Default Profile

const CAN_Message VF789_Msg[] =
{
    /* ================= BRAKE & GEAR SYSTEM ================= */
    /* Brake Switch - ID 0x109 */
    { .Name = Brake_Msg, .ID = 0x109, .Number_Signal = 1,
      .Signal = { 
          { .name = Brake_SwitchSts_Sig, .start_bit = 12, .length = 2, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f } 
      } 
    },
    
    /* Brake Regen Mode - ID 0x403 */
    { .Name = Brake_Msg, .ID = 0x403, .Number_Signal = 1,
      .Signal = { 
          { .name = Brake_RegenMode_Sig, .start_bit = 22, .length = 2, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f } 
      } 
    },
    
    /* Brake Pedal Value - ID 0x23C */
    { .Name = Brake_Msg, .ID = 0x23C, .Number_Signal = 1,
      .Signal = { 
          { .name = Brake_PedlVal_Sig, .start_bit = 33, .length = 15, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 0.1f, .offset = 0.0f } 
      } 
    },
    
    /* Shared Message - ID 0xD9 (Brake Light & Gear Actual) */
    { .Name = Brake_Msg, .ID = 0xD9, .Number_Signal = 2,
      .Signal = { 
          { .name = Brake_Light_Sig, .start_bit = 44, .length = 2, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f },
          { .name = Gear_Actual_Sig, .start_bit = 32, .length = 3, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f }
      } 
    },

    /* ================= KEY SYSTEM ================= */
    /* Key Valid - ID 0x12F */
    { .Name = Key_Msg, .ID = 0x12F, .Number_Signal = 1,
      .Signal = { 
          { .name = Key_VLD_Sig, .start_bit = 16, .length = 4, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f } 
      } 
    },
      
    /* Key Fob Left Car - ID 0x481 */
    { .Name = Key_Msg, .ID = 0x481, .Number_Signal = 1,
      .Signal = { 
          { .name = Key_fob_Leftcar_Sig, .start_bit = 40, .length = 1, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f } 
      } 
    },

    /* ================= GEAR SYSTEM ================= */
    /* Gear Target - ID 0x108 */
    { .Name = Gear_Msg, .ID = 0x108, .Number_Signal = 1,
      .Signal = { 
          { .name = Gear_Target_Sig, .start_bit = 21, .length = 3, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f } 
      } 
    },

    /* ================= TERMINAL SYSTEM ================= */
    /* STAT Terminal - ID 0x112 */
    { .Name = STAT_Terminal_Msg, .ID = 0x112, .Number_Signal = 1,
      .Signal = { 
          { .name = STAT_Terminal_Sig, .start_bit = 32, .length = 3, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f } 
      } 
    },

    /* ================= LV BATTERY SYSTEM ================= */
    /* LV Info 1 - ID 0x104 (Charging Req, Target Current, Target Voltage) */
    { .Name = LV_Msg, .ID = 0x104, .Number_Signal = 3,
      .Signal = { 
          { .name = LV_Batt_Charging_Req_Sig, .start_bit = 39, .length = 1, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f },
          { .name = LV_TargetCurrent_Sig, .start_bit = 46, .length = 10, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 0.25f, .offset = -128.0f },
          { .name = LV_TargetVoltage_Sig, .start_bit = 56, .length = 6, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 0.112903f, .offset = 9.0f }
      } 
    },
      
    /* LV Info 2 - ID 0x116 (Max Charge, Max Discharge, Wakeup) */
    { .Name = LV_Msg, .ID = 0x116, .Number_Signal = 3,
      .Signal = { 
          { .name = LV_MaxAllowChargeCurrent_Sig, .start_bit = 17, .length = 8, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f },
          { .name = LV_MaxAllowDischargeCurrent_Sig, .start_bit = 9, .length = 8, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f },
          { .name = LV_WakeupReason_Sig, .start_bit = 17, .length = 3, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f }
      } 
    },

    /* LV Info 3 - ID 0x10A (Current, Temp, Type, SOC) */
    { .Name = LV_Msg, .ID = 0x10A, .Number_Signal = 4,
      .Signal = { 
          { .name = LV_Batt_Current_Sig, .start_bit = 40, .length = 16, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 0.03125f, .offset = -1536.0f },
          { .name = LV_Batt_Temp_Sig, .start_bit = 32, .length = 8, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = -40.0f },
          { .name = LV_BatteryType_Sig, .start_bit = 12, .length = 2, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f },
          { .name = LV_SOC_Sig, .start_bit = 40, .length = 8, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f }
      } 
    },

    /* ================= HV BATTERY SYSTEM ================= */
    /* HV Status - ID 0x215 */
    { .Name = HV_Msg, .ID = 0x215, .Number_Signal = 2,
      .Signal = { 
          { .name = HV_OnOff_STS_Sig, .start_bit = 18, .length = 2, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f },
          { .name = HV_Sts_Sig, .start_bit = 56, .length = 8, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f }
      } 
    },

    /* ================= DCDC SYSTEM ================= */
    /* DCDC Request - ID 0x213 */
    { .Name = DCDC_Msg, .ID = 0x213, .Number_Signal = 1,
      .Signal = { 
          { .name = DCDC_Request_Sig, .start_bit = 12, .length = 2, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f } 
      } 
    },
      
    /* DCDC Status - ID 0x346 (Current, Voltage) */
    { .Name = DCDC_Msg, .ID = 0x346, .Number_Signal = 2,
      .Signal = { 
          { .name = DCDC_Current_Sig, .start_bit = 24, .length = 16, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 0.0625f, .offset = 0.0f },
          { .name = DCDC_Voltage_Sig, .start_bit = 40, .length = 16, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 0.0625f, .offset = 0.0f } 
      } 
    },

    /* ================= CREEP MODE ================= */
    /* MHU_EvSetting - ID 0x403 */
    { .Name = CreepMode_Msg, .ID = 0x403, .Number_Signal = 1,
      .Signal = { 
          { .name = Creep_Disable_Sts_Sig, .start_bit = 21, .length = 1, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f }
      } 
    },

    /* MHU_CarMode_Switch - ID 0x447 */
    { .Name = CreepMode_Msg, .ID = 0x447, .Number_Signal = 2,
      .Signal = { 
          { .name = Creep_Mode_Req_Sig, .start_bit = 27, .length = 3, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f },
          { .name = Creep_Mode_Set_Sig, .start_bit = 32, .length = 2, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f }
      } 
    },

    /* VCU_EDSControl_Front - ID 0x229 */
    { .Name = CreepMode_Msg, .ID = 0x229, .Number_Signal = 1,
      .Signal = { 
          { .name = Creep_Flag_FWD_Sig, .start_bit = 51, .length = 1, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f }
      } 
    },

    /* VCU_EDSControl_Rear - ID 0x230 */
    { .Name = CreepMode_Msg, .ID = 0x230, .Number_Signal = 1,
      .Signal = { 
          { .name = Creep_Flag_RWD_Sig, .start_bit = 55, .length = 1, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f }
      } 
    },
};

/* ============================================================================
 * VF_LIMO Signal 
 * ============================================================================ */
const CAN_Message VF_LIMO_Msg[] =
{
    /* ================= BRAKE SYSTEM ================= */
    /* CVC_Status - ID 0x166 (Brake Switch & Pedal & Creep Status) */
    { .Name = Brake_Msg, .ID = 0x166, .Number_Signal = 3,
      .Signal = { 
          { .name = Brake_SwitchSts_Sig, .start_bit = 29, .length = 2, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f },
          { .name = Brake_PedlVal_Sig, .start_bit = 29, .length = 2, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f },
          { .name = Creep_Disable_Sts_Sig, .start_bit = 25, .length = 2, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f }
      } 
    },

    /* ================= GEAR SYSTEM ================= */
    /* CVC_Ctrl - ID 0x162 (Gear Target) */
    { .Name = Gear_Msg, .ID = 0x162, .Number_Signal = 1,
      .Signal = { 
          { .name = Gear_Target_Sig, .start_bit = 20, .length = 3, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f }
      } 
    },
    
    /* PTC_Info2 - ID 0x379 (Gear Actual) */
    { .Name = Gear_Msg, .ID = 0x379, .Number_Signal = 1,
      .Signal = { 
          { .name = Gear_Actual_Sig, .start_bit = 58, .length = 4, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f }
      } 
    },

    /* ================= KEY/TERMINAL SYSTEM ================= */
    /* BCM_CLAMP_STAT - ID 0x117 */
    { .Name = STAT_Terminal_Msg, .ID = 0x117, .Number_Signal = 1,
      .Signal = { 
          { .name = STAT_Terminal_Sig, .start_bit = 34, .length = 3, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f }
      } 
    },

    /* ================= ACC/ADAS SYSTEM (LV Charging) ================= */
    /* EVCC_ACCharging_Req - ID 0x35B */
    { .Name = LV_Msg, .ID = 0x35B, .Number_Signal = 3,
      .Signal = { 
          { .name = LV_Batt_Charging_Req_Sig, .start_bit = 55, .length = 9, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 0.1f, .offset = 0.0f },
          { .name = LV_TargetCurrent_Sig, .start_bit = 24, .length = 16, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 0.1f, .offset = 0.0f },
          { .name = LV_TargetVoltage_Sig, .start_bit = 22, .length = 9, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f }
      } 
    },

    /* ================= LV BATTERY SYSTEM ================= */
    /* BCM_VOLTAGE - ID 0x10A */
    { .Name = LV_Msg, .ID = 0x10A, .Number_Signal = 4,
      .Signal = { 
          { .name = LV_Batt_Current_Sig, .start_bit = 55, .length = 16, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 0.03125f, .offset = -1536.0f },
          { .name = LV_Batt_Temp_Sig, .start_bit = 39, .length = 8, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = -40.0f },
          { .name = LV_BatteryType_Sig, .start_bit = 13, .length = 2, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f },
          { .name = LV_SOC_Sig, .start_bit = 47, .length = 8, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f }
      } 
    },

    /* ================= HV BATTERY SYSTEM ================= */
    /* BMS_Sts - ID 0x215 */
    { .Name = HV_Msg, .ID = 0x215, .Number_Signal = 2,
      .Signal = { 
          { .name = HV_OnOff_STS_Sig, .start_bit = 19, .length = 2, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f },
          { .name = HV_Sts_Sig, .start_bit = 63, .length = 8, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f }
      } 
    },

    /* ================= DCDC SYSTEM ================= */
    /* CVC_PDU_Ctrl - ID 0x234 */
    { .Name = DCDC_Msg, .ID = 0x234, .Number_Signal = 1,
      .Signal = { 
          { .name = DCDC_Request_Sig, .start_bit = 2, .length = 1, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f }
      } 
    },
    
    /* PDU_Status - ID 0x296 */
    { .Name = DCDC_Msg, .ID = 0x296, .Number_Signal = 2,
      .Signal = { 
          { .name = DCDC_Current_Sig, .start_bit = 3, .length = 12, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 0.1f, .offset = 0.0f },
          { .name = DCDC_Voltage_Sig, .start_bit = 31, .length = 8, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 0.1f, .offset = 0.0f }
      } 
    },
   
};

/* ============================================================================
 * VF5 Signal 
 * ============================================================================ */
const CAN_Message VF5_Msg[] =
{
    /* ================= BRAKE SYSTEM ================= */
    /* VCU_HMI_0x1A9 - ID 0x1A9 (Brake Switch) */
    { .Name = Brake_Msg, .ID = 0x1A9, .Number_Signal = 1,
      .Signal = { 
          { .name = Brake_SwitchSts_Sig, .start_bit = 63, .length = 2, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f }
      } 
    },

    /* VCU_Sts2_0x379 - ID 0x379 (Brake Pedal, Gear Actual) */
    { .Name = Brake_Msg, .ID = 0x379, .Number_Signal = 2,
      .Signal = { 
          { .name = Brake_PedlVal_Sig, .start_bit = 47, .length = 8, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 0.4f, .offset = 0.0f },
          { .name = Gear_Actual_Sig, .start_bit = 26, .length = 3, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f }
      } 
    },

    /* ================= KEY/TERMINAL SYSTEM ================= */
    /* GW_BCM_CLAMP_STAT_0x112 - ID 0x112 */
    { .Name = STAT_Terminal_Msg, .ID = 0x112, .Number_Signal = 1,
      .Signal = { 
          { .name = STAT_Terminal_Sig, .start_bit = 34, .length = 3, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f }
      } 
    },

    /* ================= HV BATTERY SYSTEM ================= */
    /* BMS_Sts_0x215 - ID 0x215 (HV Status, SOC) */
    { .Name = HV_Msg, .ID = 0x215, .Number_Signal = 3,
      .Signal = { 
          { .name = HV_OnOff_STS_Sig, .start_bit = 19, .length = 2, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f },
          { .name = HV_Sts_Sig, .start_bit = 63, .length = 8, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f },
          { .name = LV_SOC_Sig, .start_bit = 25, .length = 10, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 0.1f, .offset = 0.0f } // BMS_SocActual_EST
      } 
    },

    /* ================= DCDC & LV BAT SYSTEM ================= */
    /* DCDC_Sts_0x20B - ID 0x20B (DCDC Out V/I/Status) */
    { .Name = DCDC_Msg, .ID = 0x20B, .Number_Signal = 2,
      .Signal = { 
          { .name = DCDC_Voltage_Sig, .start_bit = 45, .length = 10, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f },
          { .name = DCDC_Current_Sig, .start_bit = 31, .length = 8, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f }
      } 
    },

    /* ================= CREEP MODE ================= */
    /* VCU_EDSControl_0x229 - ID 0x229 */
    { .Name = CreepMode_Msg, .ID = 0x229, .Number_Signal = 1,
      .Signal = { 
          { .name = Creep_Flag_FWD_Sig, .start_bit = 51, .length = 1, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f }
      } 
    },

    /* VCU_HMI_charging_0x3E0 - ID 0x3E0 */
    { .Name = CreepMode_Msg, .ID = 0x3E0, .Number_Signal = 1,
      .Signal = { 
          { .name = Creep_Disable_Sts_Sig, .start_bit = 56, .length = 1, .is_signed = 0, .endian = CAN_MOTOROLA, .factor = 1.0f, .offset = 0.0f }
      } 
    },
};


/**
  * @brief  Decode Generic CAN Message
  * @param  ID: CAN ID
  * @param  RxData: Pointer to 8-byte data buffer
  * @param  MsgTable: Message definition table (VF789 or LIMO)
  * @param  TableSize: Size of the message table
  * @param  Data: Pointer to output data structure
  * @retval None
  */
void CAN_Decode_Message(uint32_t ID, uint8_t *RxData, const CAN_Message *MsgTable, uint16_t TableSize, CAN_Data_t *Data)
{
    /* Iterate through the message table to find the matching ID */
    for (uint16_t i = 0; i < TableSize; i++)
    {
        if (MsgTable[i].ID == ID)
        {
            /* Iterate through every signal defined for this message */
            for (uint8_t s = 0; s < MsgTable[i].Number_Signal; s++)
            {
                const CAN_SignalDef_t *sig = &MsgTable[i].Signal[s];
                uint64_t raw_val = 0;

                /* 1. Extract Raw Value based on Endianness */
                if (sig->endian == CAN_MOTOROLA)
                {
                    /* Motorola (Big Endian): start_bit is the Most Significant Bit (MSB) */
                    for (int bit = 0; bit < sig->length; bit++)
                    {
                        int current_bit_pos = sig->start_bit - bit;
                        int byte_idx = current_bit_pos / 8;
                        int bit_idx  = current_bit_pos % 8;

                        if (byte_idx >= 0 && byte_idx < 8)
                        {
                            if ((RxData[byte_idx] >> bit_idx) & 0x01)
                            {
                                raw_val |= (1ULL << (sig->length - 1 - bit));
                            }
                        }
                    }
                }
                else /* CAN_INTEL */
                {
                    /* Intel (Little Endian): start_bit is the Least Significant Bit (LSB) */
                    for (int bit = 0; bit < sig->length; bit++)
                    {
                        int current_bit_pos = sig->start_bit + bit;
                        int byte_idx = current_bit_pos / 8;
                        int bit_idx  = current_bit_pos % 8;

                        if (byte_idx >= 0 && byte_idx < 8)
                        {
                            if ((RxData[byte_idx] >> bit_idx) & 0x01)
                            {
                                raw_val |= (1ULL << bit);
                            }
                        }
                    }
                }

                /* 2. Apply Factor & Offset */
                float phys_val = (raw_val * sig->factor) + sig->offset;

                /* 3. Store into Data Struct based on Signal Name */
                switch (sig->name)
                {
                    /* Brake System */
                    case Brake_SwitchSts_Sig: Data->Brake.SwitchSts = (uint8_t)phys_val; break;
                    case Brake_RegenMode_Sig: Data->Brake.RegenMode = (uint8_t)phys_val; break;
                    case Brake_PedlVal_Sig:   Data->Brake.PedalVal  = phys_val; break;
                    case Brake_Light_Sig:     Data->Brake.Light     = (uint8_t)phys_val; break;

                    /* Gear System */
                    case Gear_Target_Sig:     Data->Gear.Target = (uint8_t)phys_val; break;
                    case Gear_Actual_Sig:     Data->Gear.Actual = (uint8_t)phys_val; break;

                    /* Key / Terminal */
                    case Key_VLD_Sig:         Data->Key.Key_Valid     = (uint8_t)phys_val; break;
                    case Key_fob_Leftcar_Sig: Data->Key.Key_Fob_Left  = (uint8_t)phys_val; break;
                    case STAT_Terminal_Sig:   Data->Key.Terminal_Stat = (uint8_t)phys_val; break;

                    /* LV Battery */
                    case LV_Batt_Charging_Req_Sig:        Data->LV_Bat.Charging_Req = (uint8_t)phys_val; break;
                    case LV_TargetCurrent_Sig:            Data->LV_Bat.TargetCurrent = phys_val; break;
                    case LV_TargetVoltage_Sig:            Data->LV_Bat.TargetVoltage = phys_val; break;
                    case LV_MaxAllowChargeCurrent_Sig:    Data->LV_Bat.MaxAllowChargeCurrent = (uint8_t)phys_val; break;
                    case LV_MaxAllowDischargeCurrent_Sig: Data->LV_Bat.MaxAllowDischargeCurrent = (uint8_t)phys_val; break;
                    case LV_WakeupReason_Sig:             Data->LV_Bat.WakeupReason = (uint8_t)phys_val; break;
                    case LV_Batt_Current_Sig:             Data->LV_Bat.Current = phys_val; break;
                    case LV_Batt_Temp_Sig:                Data->LV_Bat.Temp = (uint8_t)phys_val; break;
                    case LV_BatteryType_Sig:              Data->LV_Bat.BatteryType = (uint8_t)phys_val; break;
                    case LV_SOC_Sig:                      Data->LV_Bat.SOC = (uint8_t)phys_val; break;

                    /* HV Battery */
                    case HV_OnOff_STS_Sig:    Data->HV_Bat.OnOff_Sts = (uint8_t)phys_val; break;
                    case HV_Sts_Sig:          Data->HV_Bat.Status = (uint8_t)phys_val; break;

                    /* DCDC System */
                    case DCDC_Request_Sig:    Data->DCDC.Request = (uint8_t)phys_val; break;
                    case DCDC_Current_Sig:    Data->DCDC.Current = phys_val; break;
                    case DCDC_Voltage_Sig:    Data->DCDC.Voltage = phys_val; break;

                    /* Creep Mode */
                    case Creep_Disable_Sts_Sig: Data->CreepMode.Disable_Sts = (uint8_t)phys_val; break;
                    case Creep_Mode_Req_Sig:    Data->CreepMode.Mode_Req    = (uint8_t)phys_val; break;
                    case Creep_Mode_Set_Sig:    Data->CreepMode.Mode_Set    = (uint8_t)phys_val; break;
                    case Creep_Flag_FWD_Sig:    Data->CreepMode.Flag_FWD    = (uint8_t)phys_val; break;
                    case Creep_Flag_RWD_Sig:    Data->CreepMode.Flag_RWD    = (uint8_t)phys_val; break;

                    default: break;
                }
            }
            return; /* Found correct ID and processed it */
        }
    }
}


/**
  * @brief  Configure CAN Filter and Start CAN
  * @param  hcan: Pointer to CAN handle
  * @retval None
  */
void CAN_Config_Init(CAN_HandleTypeDef *hcan)
{
    CAN_FilterTypeDef canfilterconfig;

    canfilterconfig.FilterActivation = CAN_FILTER_ENABLE;
    canfilterconfig.FilterBank = 10;
    canfilterconfig.FilterFIFOAssignment = CAN_RX_FIFO0;
    canfilterconfig.FilterIdHigh = 0x0000;
    canfilterconfig.FilterIdLow = 0x0000;
    canfilterconfig.FilterMaskIdHigh = 0x0000;
    canfilterconfig.FilterMaskIdLow = 0x0000;
    canfilterconfig.FilterMode = CAN_FILTERMODE_IDMASK;
    canfilterconfig.FilterScale = CAN_FILTERSCALE_32BIT;
    canfilterconfig.SlaveStartFilterBank = 20;

    if (HAL_CAN_ConfigFilter(hcan, &canfilterconfig) != HAL_OK)
    {
        Error_Handler();
    }

    if (HAL_CAN_Start(hcan) != HAL_OK)
    {
        Error_Handler();
    }

    if (HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
    {
        Error_Handler();
    }
}

/* Exported sizes for external use */
const uint16_t SIZE_VF789_Msg = sizeof(VF789_Msg) / sizeof(CAN_Message);
const uint16_t SIZE_VF_LIMO_Msg = sizeof(VF_LIMO_Msg) / sizeof(CAN_Message);
const uint16_t SIZE_VF5_Msg = sizeof(VF5_Msg) / sizeof(CAN_Message);

/**
  * @brief  Process Received CAN Message based on Current Profile
  * @param  ID: Standard ID
  * @param  RxData: 8-byte Data
  * @retval None
  */
void CAN_Process_Rx(uint32_t ID, uint8_t *RxData)
{
    switch (CurrentCarProfile)
    {
        case CAR_VF_LIMO:
            CAN_Decode_Message(ID, RxData, VF_LIMO_Msg, sizeof(VF_LIMO_Msg)/sizeof(CAN_Message), &VF_LIMO_Data);
            break;

        case CAR_VF789:
            CAN_Decode_Message(ID, RxData, VF789_Msg, sizeof(VF789_Msg)/sizeof(CAN_Message), &VF789_Data);
            break;

        case CAR_VF5:
            CAN_Decode_Message(ID, RxData, VF5_Msg, sizeof(VF5_Msg)/sizeof(CAN_Message), &VF5_Data);
            break;

        default:
            break;
    }
}


