/*
 * Copyright (c) 2015-2017, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <debug.h>
#include <rcar_def.h>
#include "../qos_common.h"
#include "qos_init_h3_v11.h"

#define	RCAR_QOS_VERSION		"rev.0.37"

#define	RCAR_QOS_NONE			(3U)
#define	RCAR_QOS_TYPE_DEFAULT		(0U)

#define	RCAR_DRAM_SPLIT_LINEAR		(0U)
#define	RCAR_DRAM_SPLIT_4CH		(1U)
#define	RCAR_DRAM_SPLIT_2CH		(2U)
#define	RCAR_DRAM_SPLIT_AUTO		(3U)

#define	RST_BASE			(0xE6160000U)
#define	RST_MODEMR			(RST_BASE + 0x0060U)

#define	RCAR_PWRSR8			(0xE6180340U)	/* A3VP_PWRSR0 */
#define	RCAR_PWRONCR8			(0xE618034CU)	/* A3VP_PWRONCR */
#define	RCAR_PWRSR9			(0xE6180380U)	/* A3VC_PWRSR0 */
#define	RCAR_PWRONCR9			(0xE618038CU)	/* A3VC_PWRONCR */
#define	RCAR_PWRSR10			(0xE61803C0U)	/* A2VC_PWRSR0 */
#define	RCAR_PWRONCR10			(0xE61803CCU)	/* A2VC_PWRONCR */

#define	DBSC_BASE			(0xE6790000U)
#define DBSC_DBCAM0CNF0			(DBSC_BASE + 0x0900U)
#define DBSC_DBCAM0CNF1			(DBSC_BASE + 0x0904U)
#define DBSC_DBCAM0CNF2			(DBSC_BASE + 0x0908U)
#define DBSC_DBCAM0CNF3			(DBSC_BASE + 0x090CU)
#define DBSC_DBCAMDIS			(DBSC_BASE + 0x09fCU)
#define DBSC_DBSCHCNT0			(DBSC_BASE + 0x1000U)
#define DBSC_DBSCHCNT1			(DBSC_BASE + 0x1004U)
#define DBSC_DBSCHSZ0			(DBSC_BASE + 0x1010U)
#define DBSC_DBSCHRW0			(DBSC_BASE + 0x1020U)
#define DBSC_DBSCHQOS_0_0		(DBSC_BASE + 0x1030U)
#define DBSC_DBSCHQOS_0_1		(DBSC_BASE + 0x1034U)
#define DBSC_DBSCHQOS_0_2		(DBSC_BASE + 0x1038U)
#define DBSC_DBSCHQOS_0_3		(DBSC_BASE + 0x103CU)
#define DBSC_DBSCHQOS_1_0		(DBSC_BASE + 0x1040U)
#define DBSC_DBSCHQOS_1_1		(DBSC_BASE + 0x1044U)
#define DBSC_DBSCHQOS_1_2		(DBSC_BASE + 0x1048U)
#define DBSC_DBSCHQOS_1_3		(DBSC_BASE + 0x104CU)
#define DBSC_DBSCHQOS_2_0		(DBSC_BASE + 0x1050U)
#define DBSC_DBSCHQOS_2_1		(DBSC_BASE + 0x1054U)
#define DBSC_DBSCHQOS_2_2		(DBSC_BASE + 0x1058U)
#define DBSC_DBSCHQOS_2_3		(DBSC_BASE + 0x105CU)
#define DBSC_DBSCHQOS_3_0		(DBSC_BASE + 0x1060U)
#define DBSC_DBSCHQOS_3_1		(DBSC_BASE + 0x1064U)
#define DBSC_DBSCHQOS_3_2		(DBSC_BASE + 0x1068U)
#define DBSC_DBSCHQOS_3_3		(DBSC_BASE + 0x106CU)
#define DBSC_DBSCHQOS_4_0		(DBSC_BASE + 0x1070U)
#define DBSC_DBSCHQOS_4_1		(DBSC_BASE + 0x1074U)
#define DBSC_DBSCHQOS_4_2		(DBSC_BASE + 0x1078U)
#define DBSC_DBSCHQOS_4_3		(DBSC_BASE + 0x107CU)
#define DBSC_DBSCHQOS_5_0		(DBSC_BASE + 0x1080U)
#define DBSC_DBSCHQOS_5_1		(DBSC_BASE + 0x1084U)
#define DBSC_DBSCHQOS_5_2		(DBSC_BASE + 0x1088U)
#define DBSC_DBSCHQOS_5_3		(DBSC_BASE + 0x108CU)
#define DBSC_DBSCHQOS_6_0		(DBSC_BASE + 0x1090U)
#define DBSC_DBSCHQOS_6_1		(DBSC_BASE + 0x1094U)
#define DBSC_DBSCHQOS_6_2		(DBSC_BASE + 0x1098U)
#define DBSC_DBSCHQOS_6_3		(DBSC_BASE + 0x109CU)
#define DBSC_DBSCHQOS_7_0		(DBSC_BASE + 0x10A0U)
#define DBSC_DBSCHQOS_7_1		(DBSC_BASE + 0x10A4U)
#define DBSC_DBSCHQOS_7_2		(DBSC_BASE + 0x10A8U)
#define DBSC_DBSCHQOS_7_3		(DBSC_BASE + 0x10ACU)
#define DBSC_DBSCHQOS_8_0		(DBSC_BASE + 0x10B0U)
#define DBSC_DBSCHQOS_8_1		(DBSC_BASE + 0x10B4U)
#define DBSC_DBSCHQOS_8_2		(DBSC_BASE + 0x10B8U)
#define DBSC_DBSCHQOS_8_3		(DBSC_BASE + 0x10BCU)
#define DBSC_DBSCHQOS_9_0		(DBSC_BASE + 0x10C0U)
#define DBSC_DBSCHQOS_9_1		(DBSC_BASE + 0x10C4U)
#define DBSC_DBSCHQOS_9_2		(DBSC_BASE + 0x10C8U)
#define DBSC_DBSCHQOS_9_3		(DBSC_BASE + 0x10CCU)
#define DBSC_DBSCHQOS_10_0		(DBSC_BASE + 0x10D0U)
#define DBSC_DBSCHQOS_10_1		(DBSC_BASE + 0x10D4U)
#define DBSC_DBSCHQOS_10_2		(DBSC_BASE + 0x10D8U)
#define DBSC_DBSCHQOS_10_3		(DBSC_BASE + 0x10DCU)
#define DBSC_DBSCHQOS_11_0		(DBSC_BASE + 0x10E0U)
#define DBSC_DBSCHQOS_11_1		(DBSC_BASE + 0x10E4U)
#define DBSC_DBSCHQOS_11_2		(DBSC_BASE + 0x10E8U)
#define DBSC_DBSCHQOS_11_3		(DBSC_BASE + 0x10ECU)
#define DBSC_DBSCHQOS_12_0		(DBSC_BASE + 0x10F0U)
#define DBSC_DBSCHQOS_12_1		(DBSC_BASE + 0x10F4U)
#define DBSC_DBSCHQOS_12_2		(DBSC_BASE + 0x10F8U)
#define DBSC_DBSCHQOS_12_3		(DBSC_BASE + 0x10FCU)
#define DBSC_DBSCHQOS_13_0		(DBSC_BASE + 0x1100U)
#define DBSC_DBSCHQOS_13_1		(DBSC_BASE + 0x1104U)
#define DBSC_DBSCHQOS_13_2		(DBSC_BASE + 0x1108U)
#define DBSC_DBSCHQOS_13_3		(DBSC_BASE + 0x110CU)
#define DBSC_DBSCHQOS_14_0		(DBSC_BASE + 0x1110U)
#define DBSC_DBSCHQOS_14_1		(DBSC_BASE + 0x1114U)
#define DBSC_DBSCHQOS_14_2		(DBSC_BASE + 0x1118U)
#define DBSC_DBSCHQOS_14_3		(DBSC_BASE + 0x111CU)
#define DBSC_DBSCHQOS_15_0		(DBSC_BASE + 0x1120U)
#define DBSC_DBSCHQOS_15_1		(DBSC_BASE + 0x1124U)
#define DBSC_DBSCHQOS_15_2		(DBSC_BASE + 0x1128U)
#define DBSC_DBSCHQOS_15_3		(DBSC_BASE + 0x112CU)
#define DBSC_SCFCTST2			(DBSC_BASE + 0x170CU)

#define	AXI_BASE			(0xE6784000U)
#define	AXI_ADSPLCR0			(AXI_BASE + 0x0008U)
#define	AXI_ADSPLCR1			(AXI_BASE + 0x000CU)
#define	AXI_ADSPLCR2			(AXI_BASE + 0x0010U)
#define	AXI_ADSPLCR3			(AXI_BASE + 0x0014U)
#define	ADSPLCR0_ADRMODE_DEFAULT	((uint32_t)0U << 31U)
#define	ADSPLCR0_ADRMODE_GEN2		((uint32_t)1U << 31U)
#define	ADSPLCR0_SPLITSEL(x)		((uint32_t)(x) << 16U)
#define	ADSPLCR0_AREA(x)		((uint32_t)(x) <<  8U)
#define	ADSPLCR0_SWP			(0x0CU)

#define	MSTAT_BASE			(0xE67E0000U)
#define	MSTAT_FIX_QOS_BANK0		(MSTAT_BASE + 0x0000U)
#define	MSTAT_FIX_QOS_BANK1		(MSTAT_BASE + 0x1000U)
#define	MSTAT_BE_QOS_BANK0		(MSTAT_BASE + 0x2000U)
#define	MSTAT_BE_QOS_BANK1		(MSTAT_BASE + 0x3000U)
#define	MSTAT_SL_INIT			(MSTAT_BASE + 0x8000U)
#define	MSTAT_REF_ARS			(MSTAT_BASE + 0x8004U)
#define	MSTAT_STATQC			(MSTAT_BASE + 0x8008U)

#define	RALLOC_BASE			(0xE67F0000U)
#define	RALLOC_RAS			(RALLOC_BASE + 0x0000U)
#define	RALLOC_FIXTH			(RALLOC_BASE + 0x0004U)
#define	RALLOC_RAEN			(RALLOC_BASE + 0x0018U)
#define	RALLOC_REGGD			(RALLOC_BASE + 0x0020U)
#define	RALLOC_DANN			(RALLOC_BASE + 0x0030U)
#define	RALLOC_DANT			(RALLOC_BASE + 0x0038U)
#define	RALLOC_EC			(RALLOC_BASE + 0x003CU)
#define	RALLOC_EMS			(RALLOC_BASE + 0x0040U)
#define	RALLOC_INSFC			(RALLOC_BASE + 0x0050U)
#define	RALLOC_BERR			(RALLOC_BASE + 0x0054U)
#define	RALLOC_RACNT0			(RALLOC_BASE + 0x0080U)

#if RCAR_QOS_TYPE  == RCAR_QOS_TYPE_DEFAULT
static const mstat_slot_t mstat_fix[] = {
	{0x0000U, 0x0000000000000000UL},
	{0x0008U, 0x0000000000000000UL},
	{0x0010U, 0x0000000000000000UL},
	{0x0018U, 0x0000000000000000UL},
	{0x0020U, 0x0000000000000000UL},
	{0x0028U, 0x0000000000000000UL},
	{0x0030U, 0x001004030000FFFFUL},
	{0x0038U, 0x001008060000FFFFUL},
	{0x0040U, 0x001414090000FFFFUL},
	{0x0048U, 0x0000000000000000UL},
	{0x0050U, 0x001410010000FFFFUL},
	{0x0058U, 0x00140C0C0000FFFFUL},
	{0x0060U, 0x00140C0C0000FFFFUL},
	{0x0068U, 0x0000000000000000UL},
	{0x0070U, 0x001410010000FFFFUL},
	{0x0078U, 0x001008060000FFFFUL},
	{0x0080U, 0x001004020000FFFFUL},
	{0x0088U, 0x001414090000FFFFUL},
	{0x0090U, 0x00140C0C0000FFFFUL},
	{0x0098U, 0x001408080000FFFFUL},
	{0x00A0U, 0x000C08020000FFFFUL},
	{0x00A8U, 0x000C04010000FFFFUL},
	{0x00B0U, 0x000C04010000FFFFUL},
	{0x00B8U, 0x0000000000000000UL},
	{0x00C0U, 0x000C08020000FFFFUL},
	{0x00C8U, 0x000C04010000FFFFUL},
	{0x00D0U, 0x000C04010000FFFFUL},
	{0x00D8U, 0x000C04030000FFFFUL},
	{0x00E0U, 0x000C100F0000FFFFUL},
	{0x00E8U, 0x0000000000000000UL},
	{0x00F0U, 0x001010080000FFFFUL},
	{0x00F8U, 0x001010080000FFFFUL},
	{0x0100U, 0x0000000000000000UL},
	{0x0108U, 0x000C04030000FFFFUL},
	{0x0110U, 0x001010080000FFFFUL},
	{0x0118U, 0x001010080000FFFFUL},
	{0x0120U, 0x0000000000000000UL},
	{0x0128U, 0x000C100E0000FFFFUL},
	{0x0130U, 0x0000000000000000UL},
	{0x0138U, 0x001008050000FFFFUL},
	{0x0140U, 0x001008050000FFFFUL},
	{0x0148U, 0x001008050000FFFFUL},
	{0x0150U, 0x001008050000FFFFUL},
	{0x0158U, 0x001008050000FFFFUL},
	{0x0160U, 0x001008050000FFFFUL},
	{0x0168U, 0x001008050000FFFFUL},
	{0x0170U, 0x001008050000FFFFUL},
	{0x0178U, 0x001004030000FFFFUL},
	{0x0180U, 0x001004030000FFFFUL},
	{0x0188U, 0x001004030000FFFFUL},
	{0x0190U, 0x001014140000FFFFUL},
	{0x0198U, 0x001014140000FFFFUL},
	{0x01A0U, 0x001008050000FFFFUL},
	{0x01A8U, 0x001008050000FFFFUL},
	{0x01B0U, 0x001008050000FFFFUL},
	{0x01B8U, 0x0000000000000000UL},
	{0x01C0U, 0x0000000000000000UL},
	{0x01C8U, 0x0000000000000000UL},
	{0x01D0U, 0x0000000000000000UL},
	{0x01D8U, 0x0000000000000000UL},
	{0x01E0U, 0x0000000000000000UL},
	{0x01E8U, 0x0000000000000000UL},
	{0x01F0U, 0x0000000000000000UL},
	{0x01F8U, 0x0000000000000000UL},
	{0x0200U, 0x0000000000000000UL},
	{0x0208U, 0x0000000000000000UL},
	{0x0210U, 0x0000000000000000UL},
	{0x0218U, 0x0000000000000000UL},
	{0x0220U, 0x0000000000000000UL},
	{0x0228U, 0x0000000000000000UL},
	{0x0230U, 0x0000000000000000UL},
	{0x0238U, 0x0000000000000000UL},
	{0x0240U, 0x0000000000000000UL},
	{0x0248U, 0x0000000000000000UL},
	{0x0250U, 0x0000000000000000UL},
	{0x0258U, 0x0000000000000000UL},
	{0x0260U, 0x0000000000000000UL},
	{0x0268U, 0x001408010000FFFFUL},
	{0x0270U, 0x001404010000FFFFUL},
	{0x0278U, 0x0000000000000000UL},
	{0x0280U, 0x0000000000000000UL},
	{0x0288U, 0x0000000000000000UL},
	{0x0290U, 0x001408010000FFFFUL},
	{0x0298U, 0x001404010000FFFFUL},
	{0x02A0U, 0x000C04010000FFFFUL},
	{0x02A8U, 0x000C04010000FFFFUL},
	{0x02B0U, 0x001404010000FFFFUL},
	{0x02B8U, 0x0000000000000000UL},
	{0x02C0U, 0x0000000000000000UL},
	{0x02C8U, 0x0000000000000000UL},
	{0x02D0U, 0x000C04010000FFFFUL},
	{0x02D8U, 0x000C04010000FFFFUL},
	{0x02E0U, 0x001404010000FFFFUL},
	{0x02E8U, 0x0000000000000000UL},
	{0x02F0U, 0x0000000000000000UL},
	{0x02F8U, 0x0000000000000000UL},
	{0x0300U, 0x0000000000000000UL},
	{0x0308U, 0x0000000000000000UL},
	{0x0310U, 0x0000000000000000UL},
	{0x0318U, 0x0000000000000000UL},
	{0x0320U, 0x0000000000000000UL},
	{0x0328U, 0x0000000000000000UL},
	{0x0330U, 0x0000000000000000UL},
	{0x0338U, 0x0000000000000000UL},
};

static const mstat_slot_t mstat_be[] = {
	{0x0000U, 0x001200100C89C401UL},
	{0x0008U, 0x001200100C89C401UL},
	{0x0010U, 0x001200100C89C401UL},
	{0x0018U, 0x001200100C89C401UL},
	{0x0020U, 0x001100100C803401UL},
	{0x0028U, 0x001100100C80FC01UL},
	{0x0030U, 0x0000000000000000UL},
	{0x0038U, 0x0000000000000000UL},
	{0x0040U, 0x0000000000000000UL},
	{0x0048U, 0x0000000000000000UL},
	{0x0050U, 0x0000000000000000UL},
	{0x0058U, 0x0000000000000000UL},
	{0x0060U, 0x0000000000000000UL},
	{0x0068U, 0x001100100C803401UL},
	{0x0070U, 0x0000000000000000UL},
	{0x0078U, 0x0000000000000000UL},
	{0x0080U, 0x0000000000000000UL},
	{0x0088U, 0x0000000000000000UL},
	{0x0090U, 0x0000000000000000UL},
	{0x0098U, 0x0000000000000000UL},
	{0x00A0U, 0x0000000000000000UL},
	{0x00A8U, 0x0000000000000000UL},
	{0x00B0U, 0x0000000000000000UL},
	{0x00B8U, 0x001100100C803401UL},
	{0x00C0U, 0x0000000000000000UL},
	{0x00C8U, 0x0000000000000000UL},
	{0x00D0U, 0x0000000000000000UL},
	{0x00D8U, 0x0000000000000000UL},
	{0x00E0U, 0x0000000000000000UL},
	{0x00E8U, 0x001100100C803401UL},
	{0x00F0U, 0x0000000000000000UL},
	{0x00F8U, 0x0000000000000000UL},
	{0x0100U, 0x0000000000000000UL},
	{0x0108U, 0x0000000000000000UL},
	{0x0110U, 0x0000000000000000UL},
	{0x0118U, 0x0000000000000000UL},
	{0x0120U, 0x0000000000000000UL},
	{0x0128U, 0x0000000000000000UL},
	{0x0130U, 0x001100100C803401UL},
	{0x0138U, 0x0000000000000000UL},
	{0x0140U, 0x0000000000000000UL},
	{0x0148U, 0x0000000000000000UL},
	{0x0150U, 0x0000000000000000UL},
	{0x0158U, 0x0000000000000000UL},
	{0x0160U, 0x0000000000000000UL},
	{0x0168U, 0x0000000000000000UL},
	{0x0170U, 0x0000000000000000UL},
	{0x0178U, 0x0000000000000000UL},
	{0x0180U, 0x0000000000000000UL},
	{0x0188U, 0x0000000000000000UL},
	{0x0190U, 0x0000000000000000UL},
	{0x0198U, 0x0000000000000000UL},
	{0x01A0U, 0x0000000000000000UL},
	{0x01A8U, 0x0000000000000000UL},
	{0x01B0U, 0x0000000000000000UL},
	{0x01B8U, 0x001100100C803401UL},
	{0x01C0U, 0x001100800C8FFC01UL},
	{0x01C8U, 0x001100800C8FFC01UL},
	{0x01D0U, 0x001100800C8FFC01UL},
	{0x01D8U, 0x001100800C8FFC01UL},
	{0x01E0U, 0x001100100C80FC01UL},
	{0x01E8U, 0x001200100C80FC01UL},
	{0x01F0U, 0x001100100C80FC01UL},
	{0x01F8U, 0x001100100C803401UL},
	{0x0200U, 0x001100100C80FC01UL},
	{0x0208U, 0x001200100C80FC01UL},
	{0x0210U, 0x001100100C80FC01UL},
	{0x0218U, 0x001100100C825801UL},
	{0x0220U, 0x001100100C825801UL},
	{0x0228U, 0x001100100C803401UL},
	{0x0230U, 0x001100100C825801UL},
	{0x0238U, 0x001100100C825801UL},
	{0x0240U, 0x001200100C8BB801UL},
	{0x0248U, 0x001100200C8FFC01UL},
	{0x0250U, 0x001200100C8BB801UL},
	{0x0258U, 0x001100200C8FFC01UL},
	{0x0260U, 0x001100100C84E401UL},
	{0x0268U, 0x0000000000000000UL},
	{0x0270U, 0x0000000000000000UL},
	{0x0278U, 0x001100100C81F401UL},
	{0x0280U, 0x001100100C803401UL},
	{0x0288U, 0x001100100C803401UL},
	{0x0290U, 0x0000000000000000UL},
	{0x0298U, 0x0000000000000000UL},
	{0x02A0U, 0x0000000000000000UL},
	{0x02A8U, 0x0000000000000000UL},
	{0x02B0U, 0x0000000000000000UL},
	{0x02B8U, 0x001100100C803401UL},
	{0x02C0U, 0x001100100C803401UL},
	{0x02C8U, 0x001100100C803401UL},
	{0x02D0U, 0x0000000000000000UL},
	{0x02D8U, 0x0000000000000000UL},
	{0x02E0U, 0x0000000000000000UL},
	{0x02E8U, 0x001100100C803401UL},
	{0x02F0U, 0x001100300C8FFC01UL},
	{0x02F8U, 0x001100500C8FFC01UL},
	{0x0300U, 0x001100100C803401UL},
	{0x0308U, 0x001100300C8FFC01UL},
	{0x0310U, 0x001100500C8FFC01UL},
	{0x0318U, 0x001200100C803401UL},
	{0x0320U, 0x001100300C8FFC01UL},
	{0x0328U, 0x001100500C8FFC01UL},
	{0x0330U, 0x001100300C8FFC01UL},
	{0x0338U, 0x001100500C8FFC01UL},
};
#endif

static void dbsc_setting(void)
{
	uint32_t md = 0;

	/* BUFCAM settings */
	/* DBSC_DBCAM0CNF0 not set */
	io_write_32(DBSC_DBCAM0CNF1, 0x00044218);	/* dbcam0cnf1 */
	io_write_32(DBSC_DBCAM0CNF2, 0x000000F4);	/* dbcam0cnf2 */
	/* DBSC_DBCAM0CNF3 not set */
	io_write_32(DBSC_DBSCHCNT0, 0x080F0037);	/* dbschcnt0 */
	io_write_32(DBSC_DBSCHCNT1, 0x00001010);	/* dbschcnt1 */
	io_write_32(DBSC_DBSCHSZ0, 0x00000001);	/* dbschsz0 */
	io_write_32(DBSC_DBSCHRW0, 0x22421111);	/* dbschrw0 */

	md = (*((volatile uint32_t *)RST_MODEMR) & 0x000A0000) >> 17;

	switch (md) {
	case 0x0:
		/* DDR3200 */
		io_write_32(DBSC_SCFCTST2, 0x012F1123);
		break;
	case 0x1:		/* MD19=0,MD17=1 : LPDDR4-3000, 4GByte(1GByte x4) */
		/* DDR2800 */
		io_write_32(DBSC_SCFCTST2, 0x012F1123);
		break;
	case 0x4:		/* MD19=1,MD17=0 : LPDDR4-2400, 4GByte(1GByte x4) */
		/* DDR2400 */
		io_write_32(DBSC_SCFCTST2, 0x012F1123);
		break;
	default:		/* MD19=1,MD17=1 : LPDDR4-1600, 4GByte(1GByte x4) */
		/* DDR1600 */
		io_write_32(DBSC_SCFCTST2, 0x012F1123);
		break;
	}

	/* QoS Settings */
	io_write_32(DBSC_DBSCHQOS_0_0, 0x0000F000);
	io_write_32(DBSC_DBSCHQOS_0_1, 0x0000E000);
	io_write_32(DBSC_DBSCHQOS_0_2, 0x00007000);
	io_write_32(DBSC_DBSCHQOS_0_3, 0x00000000);
	/* DBSC_DBSCHQOS_1_0 not set */
	/* DBSC_DBSCHQOS_1_1 not set */
	/* DBSC_DBSCHQOS_1_2 not set */
	/* DBSC_DBSCHQOS_1_3 not set */
	/* DBSC_DBSCHQOS_2_0 not set */
	/* DBSC_DBSCHQOS_2_1 not set */
	/* DBSC_DBSCHQOS_2_2 not set */
	/* DBSC_DBSCHQOS_2_3 not set */
	/* DBSC_DBSCHQOS_3_0 not set */
	/* DBSC_DBSCHQOS_3_1 not set */
	/* DBSC_DBSCHQOS_3_2 not set */
	/* DBSC_DBSCHQOS_3_3 not set */
	io_write_32(DBSC_DBSCHQOS_4_0, 0x00000E00);
	io_write_32(DBSC_DBSCHQOS_4_1, 0x00000DFF);
	io_write_32(DBSC_DBSCHQOS_4_2, 0x00000400);
	io_write_32(DBSC_DBSCHQOS_4_3, 0x00000200);
	/* DBSC_DBSCHQOS_5_0 not set */
	/* DBSC_DBSCHQOS_5_1 not set */
	/* DBSC_DBSCHQOS_5_2 not set */
	/* DBSC_DBSCHQOS_5_3 not set */
	/* DBSC_DBSCHQOS_6_0 not set */
	/* DBSC_DBSCHQOS_6_1 not set */
	/* DBSC_DBSCHQOS_6_2 not set */
	/* DBSC_DBSCHQOS_6_3 not set */
	/* DBSC_DBSCHQOS_7_0 not set */
	/* DBSC_DBSCHQOS_7_1 not set */
	/* DBSC_DBSCHQOS_7_2 not set */
	/* DBSC_DBSCHQOS_7_3 not set */
	/* DBSC_DBSCHQOS_8_0 not set */
	/* DBSC_DBSCHQOS_8_1 not set */
	/* DBSC_DBSCHQOS_8_2 not set */
	/* DBSC_DBSCHQOS_8_3 not set */
	io_write_32(DBSC_DBSCHQOS_9_0, 0x00000C00);
	io_write_32(DBSC_DBSCHQOS_9_1, 0x00000BFF);
	io_write_32(DBSC_DBSCHQOS_9_2, 0x00000400);
	io_write_32(DBSC_DBSCHQOS_9_3, 0x00000200);
	/* DBSC_DBSCHQOS_10_0 not set */
	/* DBSC_DBSCHQOS_10_1 not set */
	/* DBSC_DBSCHQOS_10_2 not set */
	/* DBSC_DBSCHQOS_10_3 not set */
	/* DBSC_DBSCHQOS_11_0 not set */
	/* DBSC_DBSCHQOS_11_1 not set */
	/* DBSC_DBSCHQOS_11_2 not set */
	/* DBSC_DBSCHQOS_11_3 not set */
	/* DBSC_DBSCHQOS_12_0 not set */
	/* DBSC_DBSCHQOS_12_1 not set */
	/* DBSC_DBSCHQOS_12_2 not set */
	/* DBSC_DBSCHQOS_12_3 not set */
	io_write_32(DBSC_DBSCHQOS_13_0, 0x00000980);
	io_write_32(DBSC_DBSCHQOS_13_1, 0x0000097F);
	io_write_32(DBSC_DBSCHQOS_13_2, 0x00000300);
	io_write_32(DBSC_DBSCHQOS_13_3, 0x00000180);
	io_write_32(DBSC_DBSCHQOS_14_0, 0x00000800);
	io_write_32(DBSC_DBSCHQOS_14_1, 0x000007FF);
	io_write_32(DBSC_DBSCHQOS_14_2, 0x00000300);
	io_write_32(DBSC_DBSCHQOS_14_3, 0x00000180);
	io_write_32(DBSC_DBSCHQOS_15_0, 0x000007D0);
	io_write_32(DBSC_DBSCHQOS_15_1, 0x000007CF);
	io_write_32(DBSC_DBSCHQOS_15_2, 0x000005D0);
	io_write_32(DBSC_DBSCHQOS_15_3, 0x000003D0);
}

void qos_init_h3_v11(void)
{
	dbsc_setting();

	/* DRAM Split Address mapping */
#if (RCAR_DRAM_SPLIT == RCAR_DRAM_SPLIT_4CH) || \
    (RCAR_DRAM_SPLIT == RCAR_DRAM_SPLIT_AUTO)
	NOTICE("BL2: DRAM Split is 4ch\n");
	io_write_32(AXI_ADSPLCR0, ADSPLCR0_ADRMODE_DEFAULT
		    | ADSPLCR0_SPLITSEL(0xFFU)
		    | ADSPLCR0_AREA(0x1BU)
		    | ADSPLCR0_SWP);
	io_write_32(AXI_ADSPLCR1, 0x00000000U);
	io_write_32(AXI_ADSPLCR2, 0xA8A90000U);
	io_write_32(AXI_ADSPLCR3, 0x00000000U);
#elif RCAR_DRAM_SPLIT == RCAR_DRAM_SPLIT_2CH
	NOTICE("BL2: DRAM Split is 2ch\n");
	io_write_32(AXI_ADSPLCR0, 0x00000000U);
	io_write_32(AXI_ADSPLCR1, ADSPLCR0_ADRMODE_DEFAULT
		    | ADSPLCR0_SPLITSEL(0xFFU)
		    | ADSPLCR0_AREA(0x1BU)
		    | ADSPLCR0_SWP);
	io_write_32(AXI_ADSPLCR2, 0x00000000U);
	io_write_32(AXI_ADSPLCR3, 0x00000000U);
#else
	NOTICE("BL2: DRAM Split is OFF\n");
#endif

#if !(RCAR_QOS_TYPE == RCAR_QOS_NONE)
#if RCAR_QOS_TYPE  == RCAR_QOS_TYPE_DEFAULT
	NOTICE("BL2: QoS is default setting(%s)\n", RCAR_QOS_VERSION);
#endif

	/* AR Cache setting */
	io_write_32(0xE67D1000U, 0x00000100U);
	io_write_32(0xE67D1008U, 0x00000100U);

	/* Resource Alloc setting */
#if RCAR_DRAM_SPLIT == RCAR_DRAM_SPLIT_2CH
	io_write_32(RALLOC_RAS, 0x00000020U);
#else
	io_write_32(RALLOC_RAS, 0x00000040U);
#endif
	io_write_32(RALLOC_FIXTH, 0x000F0005U);
	io_write_32(RALLOC_REGGD, 0x00000000U);
#if RCAR_DRAM_SPLIT == RCAR_DRAM_SPLIT_2CH
	io_write_64(RALLOC_DANN, 0x0101010102020201UL);
	io_write_32(RALLOC_DANT, 0x00181008U);
#else
	io_write_64(RALLOC_DANN, 0x0101000004040401UL);
	io_write_32(RALLOC_DANT, 0x003C2010U);
#endif
	io_write_32(RALLOC_EC, 0x00080001U);	/* need for H3 v1.* */
	io_write_64(RALLOC_EMS, 0x0000000000000000UL);
	io_write_32(RALLOC_INSFC, 0xC7840001U);
	io_write_32(RALLOC_BERR, 0x00000000U);
	io_write_32(RALLOC_RACNT0, 0x00000000U);

	/* MSTAT setting */
	io_write_32(MSTAT_SL_INIT,
		    SL_INIT_REFFSSLOT | SL_INIT_SLOTSSLOT | SL_INIT_SSLOTCLK);
	io_write_32(MSTAT_REF_ARS, 0x00330000U);

	/* MSTAT SRAM setting */
	{
		uint32_t i;

		for (i = 0U; i < ARRAY_SIZE(mstat_fix); i++) {
			io_write_64(MSTAT_FIX_QOS_BANK0 + mstat_fix[i].addr,
				    mstat_fix[i].value);
			io_write_64(MSTAT_FIX_QOS_BANK1 + mstat_fix[i].addr,
				    mstat_fix[i].value);
		}
		for (i = 0U; i < ARRAY_SIZE(mstat_be); i++) {
			io_write_64(MSTAT_BE_QOS_BANK0 + mstat_be[i].addr,
				    mstat_be[i].value);
			io_write_64(MSTAT_BE_QOS_BANK1 + mstat_be[i].addr,
				    mstat_be[i].value);
		}
	}

	/* 3DG bus Leaf setting */
	io_write_32(0xFD820808U, 0x00001234U);
	io_write_32(0xFD820800U, 0x0000003FU);
	io_write_32(0xFD821800U, 0x0000003FU);
	io_write_32(0xFD822800U, 0x0000003FU);
	io_write_32(0xFD823800U, 0x0000003FU);
	io_write_32(0xFD824800U, 0x0000003FU);
	io_write_32(0xFD825800U, 0x0000003FU);
	io_write_32(0xFD826800U, 0x0000003FU);
	io_write_32(0xFD827800U, 0x0000003FU);

	/* VIO bus Leaf setting */
	io_write_32(0xFEB89800, 0x00000001U);
	io_write_32(0xFEB8A800, 0x00000001U);
	io_write_32(0xFEB8B800, 0x00000001U);
	io_write_32(0xFEB8C800, 0x00000001U);

	/* HSC bus Leaf setting */
	io_write_32(0xE6430800, 0x00000001U);
	io_write_32(0xE6431800, 0x00000001U);
	io_write_32(0xE6432800, 0x00000001U);
	io_write_32(0xE6433800, 0x00000001U);

	/* MP bus Leaf setting */
	io_write_32(0xEC620800, 0x00000001U);
	io_write_32(0xEC621800, 0x00000001U);

	/* PERIE bus Leaf setting */
	io_write_32(0xE7760800, 0x00000001U);
	io_write_32(0xE7768800, 0x00000001U);

	/* PERIW bus Leaf setting */
	io_write_32(0xE6760800, 0x00000001U);
	io_write_32(0xE6768800, 0x00000001U);

	/* RT bus Leaf setting */
	io_write_32(0xFFC50800, 0x00000001U);
	io_write_32(0xFFC51800, 0x00000001U);

	/* CCI bus Leaf setting */
	{

		uint32_t modemr = io_read_32(RCAR_MODEMR);

		modemr &= MODEMR_BOOT_CPU_MASK;

		if ((modemr == MODEMR_BOOT_CPU_CA57) ||
		    (modemr == MODEMR_BOOT_CPU_CA53)) {
			io_write_32(0xF1300800, 0x00000001U);
			io_write_32(0xF1340800, 0x00000001U);
			io_write_32(0xF1380800, 0x00000001U);
			io_write_32(0xF13C0800, 0x00000001U);
		}
	}

	/* Resource Alloc start */
	io_write_32(RALLOC_RAEN, 0x00000001U);

	/* MSTAT start */
	io_write_32(MSTAT_STATQC, 0x00000001U);
#else
	NOTICE("BL2: QoS is None\n");

	/* Resource Alloc setting */
	io_write_32(RALLOC_EC, 0x00080001U);	/* need for H3 v1.* */
#endif /* !(RCAR_QOS_TYPE == RCAR_QOS_NONE) */
}
