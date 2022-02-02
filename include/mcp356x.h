/*
 * mcp356x.h
 *
 *  Created on: Jan 31, 2022
 *      Author: Luca Engelmann (derlucae98)
 */

#ifndef MCP356X_H_
#define MCP356X_H_

#include <stdint.h>
#include <stddef.h>
#include <string.h>

typedef void (*mcp356x_spi_move_array_t)(uint8_t *a, size_t len);
typedef void (*mcp356x_assert_cs_t)(void);
typedef void (*mcp356x_deassert_cs_t)(void);

typedef struct {
    mcp356x_spi_move_array_t spi_move_array;
    mcp356x_assert_cs_t assert_cs;
    mcp356x_deassert_cs_t deassert_cs;
} mcp356x_obj_t;

typedef struct {
    uint8_t VREF_SEL : 1;
    uint8_t CLK_SEL : 2;
    uint8_t CS_SEL : 2;
    uint8_t ADC_MODE : 2;
    uint8_t PRE : 2;
    uint8_t OSR : 4;
    uint8_t BOOST : 2;
    uint8_t GAIN : 3;
    uint8_t AZ_MUX : 1;
    uint8_t AZ_REF : 1;
    uint8_t CONV_MODE : 2;
    uint8_t DATA_FORMAT : 2;
    uint8_t CRC_FORMAT : 1;
    uint8_t EN_CRCCOM : 1;
    uint8_t EN_OFFCAL : 1;
    uint8_t EN_GAINCAL : 1;
    uint8_t IRQ_MODE : 1;
    uint8_t EN_FASTCMD : 1;
    uint8_t EN_STP : 1;
} mcp356x_config_t;

enum {
    VREF_SEL_EXT,
    VREF_SEL_INT
};

enum {
    CLK_SEL_EXT = 0,
    CLK_SEL_INT = 2,
    CLK_SEL_INT_AMCLK_OUT
};

enum {
    CS_SEL_OFF,
    CS_SEL_09,
    CS_SEL_37,
    CS_SEL_15
};

enum {
    ADC_MODE_SDN = 0,
    ADC_MODE_STB = 2,
    ADC_MODE_CONV
};

enum {
    PRE_1,
    PRE_2,
    PRE_4,
    PRE_8
};

enum {
    OSR_32,
    OSR_64,
    OSR_128,
    OSR_256,
    OSR_512,
    OSR_1024,
    OSR_2048,
    OSR_4096,
    OSR_8192,
    OSR_16384,
    OSR_20480,
    OSR_24576,
    OSR_40960,
    OSR_49152,
    OSR_81920,
    OSR_98304
};

enum {
    BOOST_05,
    BOOST_066,
    BOOST_1,
    BOOST_2
};

enum {
    GAIN_033,
    GAIN_1,
    GAIN_2,
    GAIN_4,
    GAIN_8,
    GAIN_16,
    GAIN_32,
    GAIN_64
};

enum {
    CONV_MODE_ONE_SHOT_SCAN_SDN = 0,
    CONV_MODE_ONE_SHOT_SCAN_STB = 2,
    CONV_MODE_CONT_SCAN
};

enum {
    DATA_FORMAT_24,
    DATA_FORMAT_32,
    DATA_FORMAT_32_SGN,
    DATA_FORMAT_32_SGN_CHID
};

enum {
    CRC_FORMAT_16,
    CRC_FORMAT_32
};

enum {
    IRQ_MODE_IRQ_HIGH_Z,
    IRQ_MODE_IRQ_HIGH,
    IRQ_MODE_MDAT_HIGH_Z,
    IRQ_MODE_MDAT_HIGH
};

typedef enum {
    MUX_CH0,
    MUX_CH1,
    MUX_CH2,
    MUX_CH3,
    MUX_CH4,
    MUX_CH5,
    MUX_CH6,
    MUX_CH7,
    MUX_AGND,
    MUX_AVDD,
    MUX_RESERVED,
    MUX_REFIN_POS,
    MUX_REFIN_NEG,
    MUX_INT_TEMP_P,
    MUX_INT_TEMP_M,
    MUX_INT_VCM
} mcp356x_channel_t;

typedef enum {
    MCP356X_ERROR_OK,
    MCP356X_ERROR_FAILED
} mcp356x_error_t;

mcp356x_obj_t mcp356x_init(mcp356x_spi_move_array_t mcp356x_spi_move_array, mcp356x_assert_cs_t mcp356x_assert_cs, mcp356x_deassert_cs_t mcp356x_deassert_cs);
mcp356x_error_t mcp356x_reset(mcp356x_obj_t *obj);
mcp356x_error_t mcp356x_set_config(mcp356x_obj_t *obj, mcp356x_config_t cfg);
mcp356x_error_t mcp356x_get_value(mcp356x_obj_t *obj, mcp356x_channel_t ch_pos, mcp356x_channel_t ch_neg, uint32_t *val);


#endif /* MCP356X_H_ */
