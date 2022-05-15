/* -*- c++ -*- */
/*
 * gr-satnogs: SatNOGS GNU Radio Out-Of-Tree Module
 *
 *  Copyright (C) 2019, 2020 Libre Space Foundation <http://libre.space>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include <satnogs/crc.h>
#include <cstring>
#include <arpa/inet.h>

namespace gr {
namespace satnogs {


const uint16_t crc::crc16_ccitt_table_reverse[256] = {
  0x0000, 0x1189, 0x2312, 0x329B, 0x4624, 0x57AD, 0x6536, 0x74BF, 0x8C48,
  0x9DC1, 0xAF5A, 0xBED3, 0xCA6C, 0xDBE5, 0xE97E, 0xF8F7, 0x1081, 0x0108,
  0x3393, 0x221A, 0x56A5, 0x472C, 0x75B7, 0x643E, 0x9CC9, 0x8D40, 0xBFDB,
  0xAE52, 0xDAED, 0xCB64, 0xF9FF, 0xE876, 0x2102, 0x308B, 0x0210, 0x1399,
  0x6726, 0x76AF, 0x4434, 0x55BD, 0xAD4A, 0xBCC3, 0x8E58, 0x9FD1, 0xEB6E,
  0xFAE7, 0xC87C, 0xD9F5, 0x3183, 0x200A, 0x1291, 0x0318, 0x77A7, 0x662E,
  0x54B5, 0x453C, 0xBDCB, 0xAC42, 0x9ED9, 0x8F50, 0xFBEF, 0xEA66, 0xD8FD,
  0xC974, 0x4204, 0x538D, 0x6116, 0x709F, 0x0420, 0x15A9, 0x2732, 0x36BB,
  0xCE4C, 0xDFC5, 0xED5E, 0xFCD7, 0x8868, 0x99E1, 0xAB7A, 0xBAF3, 0x5285,
  0x430C, 0x7197, 0x601E, 0x14A1, 0x0528, 0x37B3, 0x263A, 0xDECD, 0xCF44,
  0xFDDF, 0xEC56, 0x98E9, 0x8960, 0xBBFB, 0xAA72, 0x6306, 0x728F, 0x4014,
  0x519D, 0x2522, 0x34AB, 0x0630, 0x17B9, 0xEF4E, 0xFEC7, 0xCC5C, 0xDDD5,
  0xA96A, 0xB8E3, 0x8A78, 0x9BF1, 0x7387, 0x620E, 0x5095, 0x411C, 0x35A3,
  0x242A, 0x16B1, 0x0738, 0xFFCF, 0xEE46, 0xDCDD, 0xCD54, 0xB9EB, 0xA862,
  0x9AF9, 0x8B70, 0x8408, 0x9581, 0xA71A, 0xB693, 0xC22C, 0xD3A5, 0xE13E,
  0xF0B7, 0x0840, 0x19C9, 0x2B52, 0x3ADB, 0x4E64, 0x5FED, 0x6D76, 0x7CFF,
  0x9489, 0x8500, 0xB79B, 0xA612, 0xD2AD, 0xC324, 0xF1BF, 0xE036, 0x18C1,
  0x0948, 0x3BD3, 0x2A5A, 0x5EE5, 0x4F6C, 0x7DF7, 0x6C7E, 0xA50A, 0xB483,
  0x8618, 0x9791, 0xE32E, 0xF2A7, 0xC03C, 0xD1B5, 0x2942, 0x38CB, 0x0A50,
  0x1BD9, 0x6F66, 0x7EEF, 0x4C74, 0x5DFD, 0xB58B, 0xA402, 0x9699, 0x8710,
  0xF3AF, 0xE226, 0xD0BD, 0xC134, 0x39C3, 0x284A, 0x1AD1, 0x0B58, 0x7FE7,
  0x6E6E, 0x5CF5, 0x4D7C, 0xC60C, 0xD785, 0xE51E, 0xF497, 0x8028, 0x91A1,
  0xA33A, 0xB2B3, 0x4A44, 0x5BCD, 0x6956, 0x78DF, 0x0C60, 0x1DE9, 0x2F72,
  0x3EFB, 0xD68D, 0xC704, 0xF59F, 0xE416, 0x90A9, 0x8120, 0xB3BB, 0xA232,
  0x5AC5, 0x4B4C, 0x79D7, 0x685E, 0x1CE1, 0x0D68, 0x3FF3, 0x2E7A, 0xE70E,
  0xF687, 0xC41C, 0xD595, 0xA12A, 0xB0A3, 0x8238, 0x93B1, 0x6B46, 0x7ACF,
  0x4854, 0x59DD, 0x2D62, 0x3CEB, 0x0E70, 0x1FF9, 0xF78F, 0xE606, 0xD49D,
  0xC514, 0xB1AB, 0xA022, 0x92B9, 0x8330, 0x7BC7, 0x6A4E, 0x58D5, 0x495C,
  0x3DE3, 0x2C6A, 0x1EF1, 0x0F78
};

const uint16_t crc::crc16_ccitt_table[256] = {
  0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7, 0x8108,
  0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF, 0x1231, 0x0210,
  0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6, 0x9339, 0x8318, 0xB37B,
  0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE, 0x2462, 0x3443, 0x0420, 0x1401,
  0x64E6, 0x74C7, 0x44A4, 0x5485, 0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE,
  0xF5CF, 0xC5AC, 0xD58D, 0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6,
  0x5695, 0x46B4, 0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D,
  0xC7BC, 0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
  0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B, 0x5AF5,
  0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12, 0xDBFD, 0xCBDC,
  0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A, 0x6CA6, 0x7C87, 0x4CE4,
  0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41, 0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD,
  0xAD2A, 0xBD0B, 0x8D68, 0x9D49, 0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13,
  0x2E32, 0x1E51, 0x0E70, 0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A,
  0x9F59, 0x8F78, 0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E,
  0xE16F, 0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
  0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E, 0x02B1,
  0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256, 0xB5EA, 0xA5CB,
  0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D, 0x34E2, 0x24C3, 0x14A0,
  0x0481, 0x7466, 0x6447, 0x5424, 0x4405, 0xA7DB, 0xB7FA, 0x8799, 0x97B8,
  0xE75F, 0xF77E, 0xC71D, 0xD73C, 0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657,
  0x7676, 0x4615, 0x5634, 0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9,
  0xB98A, 0xA9AB, 0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882,
  0x28A3, 0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
  0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92, 0xFD2E,
  0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9, 0x7C26, 0x6C07,
  0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1, 0xEF1F, 0xFF3E, 0xCF5D,
  0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8, 0x6E17, 0x7E36, 0x4E55, 0x5E74,
  0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
};

/*
 * Slicing-by-8 software
 *
 * The following CRC lookup table was generated automagically
 * using the following model parameters:
 *
 * Generator Polynomial = ................. 0x1EDC6F41
 * Generator Polynomial Length = .......... 32 bits
 * Reflected Bits = ....................... TRUE
 * Table Generation Offset = .............. 32 bits
 * Number of Slices = ..................... 8 slices
 * Slice Lengths = ........................ 8 8 8 8 8 8 8 8
 * Directory Name = ....................... .\
 * File Name = ............................ 8x256_tables.c
 */

const uint32_t crc::crc32_c_table[256] = {
  0x00000000, 0xF26B8303, 0xE13B70F7, 0x1350F3F4, 0xC79A971F, 0x35F1141C, 0x26A1E7E8, 0xD4CA64EB,
  0x8AD958CF, 0x78B2DBCC, 0x6BE22838, 0x9989AB3B, 0x4D43CFD0, 0xBF284CD3, 0xAC78BF27, 0x5E133C24,
  0x105EC76F, 0xE235446C, 0xF165B798, 0x030E349B, 0xD7C45070, 0x25AFD373, 0x36FF2087, 0xC494A384,
  0x9A879FA0, 0x68EC1CA3, 0x7BBCEF57, 0x89D76C54, 0x5D1D08BF, 0xAF768BBC, 0xBC267848, 0x4E4DFB4B,
  0x20BD8EDE, 0xD2D60DDD, 0xC186FE29, 0x33ED7D2A, 0xE72719C1, 0x154C9AC2, 0x061C6936, 0xF477EA35,
  0xAA64D611, 0x580F5512, 0x4B5FA6E6, 0xB93425E5, 0x6DFE410E, 0x9F95C20D, 0x8CC531F9, 0x7EAEB2FA,
  0x30E349B1, 0xC288CAB2, 0xD1D83946, 0x23B3BA45, 0xF779DEAE, 0x05125DAD, 0x1642AE59, 0xE4292D5A,
  0xBA3A117E, 0x4851927D, 0x5B016189, 0xA96AE28A, 0x7DA08661, 0x8FCB0562, 0x9C9BF696, 0x6EF07595,
  0x417B1DBC, 0xB3109EBF, 0xA0406D4B, 0x522BEE48, 0x86E18AA3, 0x748A09A0, 0x67DAFA54, 0x95B17957,
  0xCBA24573, 0x39C9C670, 0x2A993584, 0xD8F2B687, 0x0C38D26C, 0xFE53516F, 0xED03A29B, 0x1F682198,
  0x5125DAD3, 0xA34E59D0, 0xB01EAA24, 0x42752927, 0x96BF4DCC, 0x64D4CECF, 0x77843D3B, 0x85EFBE38,
  0xDBFC821C, 0x2997011F, 0x3AC7F2EB, 0xC8AC71E8, 0x1C661503, 0xEE0D9600, 0xFD5D65F4, 0x0F36E6F7,
  0x61C69362, 0x93AD1061, 0x80FDE395, 0x72966096, 0xA65C047D, 0x5437877E, 0x4767748A, 0xB50CF789,
  0xEB1FCBAD, 0x197448AE, 0x0A24BB5A, 0xF84F3859, 0x2C855CB2, 0xDEEEDFB1, 0xCDBE2C45, 0x3FD5AF46,
  0x7198540D, 0x83F3D70E, 0x90A324FA, 0x62C8A7F9, 0xB602C312, 0x44694011, 0x5739B3E5, 0xA55230E6,
  0xFB410CC2, 0x092A8FC1, 0x1A7A7C35, 0xE811FF36, 0x3CDB9BDD, 0xCEB018DE, 0xDDE0EB2A, 0x2F8B6829,
  0x82F63B78, 0x709DB87B, 0x63CD4B8F, 0x91A6C88C, 0x456CAC67, 0xB7072F64, 0xA457DC90, 0x563C5F93,
  0x082F63B7, 0xFA44E0B4, 0xE9141340, 0x1B7F9043, 0xCFB5F4A8, 0x3DDE77AB, 0x2E8E845F, 0xDCE5075C,
  0x92A8FC17, 0x60C37F14, 0x73938CE0, 0x81F80FE3, 0x55326B08, 0xA759E80B, 0xB4091BFF, 0x466298FC,
  0x1871A4D8, 0xEA1A27DB, 0xF94AD42F, 0x0B21572C, 0xDFEB33C7, 0x2D80B0C4, 0x3ED04330, 0xCCBBC033,
  0xA24BB5A6, 0x502036A5, 0x4370C551, 0xB11B4652, 0x65D122B9, 0x97BAA1BA, 0x84EA524E, 0x7681D14D,
  0x2892ED69, 0xDAF96E6A, 0xC9A99D9E, 0x3BC21E9D, 0xEF087A76, 0x1D63F975, 0x0E330A81, 0xFC588982,
  0xB21572C9, 0x407EF1CA, 0x532E023E, 0xA145813D, 0x758FE5D6, 0x87E466D5, 0x94B49521, 0x66DF1622,
  0x38CC2A06, 0xCAA7A905, 0xD9F75AF1, 0x2B9CD9F2, 0xFF56BD19, 0x0D3D3E1A, 0x1E6DCDEE, 0xEC064EED,
  0xC38D26C4, 0x31E6A5C7, 0x22B65633, 0xD0DDD530, 0x0417B1DB, 0xF67C32D8, 0xE52CC12C, 0x1747422F,
  0x49547E0B, 0xBB3FFD08, 0xA86F0EFC, 0x5A048DFF, 0x8ECEE914, 0x7CA56A17, 0x6FF599E3, 0x9D9E1AE0,
  0xD3D3E1AB, 0x21B862A8, 0x32E8915C, 0xC083125F, 0x144976B4, 0xE622F5B7, 0xF5720643, 0x07198540,
  0x590AB964, 0xAB613A67, 0xB831C993, 0x4A5A4A90, 0x9E902E7B, 0x6CFBAD78, 0x7FAB5E8C, 0x8DC0DD8F,
  0xE330A81A, 0x115B2B19, 0x020BD8ED, 0xF0605BEE, 0x24AA3F05, 0xD6C1BC06, 0xC5914FF2, 0x37FACCF1,
  0x69E9F0D5, 0x9B8273D6, 0x88D28022, 0x7AB90321, 0xAE7367CA, 0x5C18E4C9, 0x4F48173D, 0xBD23943E,
  0xF36E6F75, 0x0105EC76, 0x12551F82, 0xE03E9C81, 0x34F4F86A, 0xC69F7B69, 0xD5CF889D, 0x27A40B9E,
  0x79B737BA, 0x8BDCB4B9, 0x988C474D, 0x6AE7C44E, 0xBE2DA0A5, 0x4C4623A6, 0x5F16D052, 0xAD7D5351
};

uint16_t
crc::crc16_ccitt_reversed(const uint8_t *data, size_t len)
{
  uint16_t crc = 0xFFFF;
  for (size_t i = 0; i < len; i++) {
    crc = (crc >> 8) ^ crc16_ccitt_table_reverse[(crc ^ data[i]) & 0xff];
  }
  return crc ^ 0xFFFF;
}

uint16_t
crc::crc16_ccitt(const uint8_t *data, size_t len)
{
  uint16_t crc = 0;
  while (len-- != 0) {
    crc = crc16_ccitt_table[((crc >> 8) ^ *data++) & 0xff] ^ (crc << 8);
  }
  return crc;
}

uint16_t
crc::crc16_aug_ccitt(const uint8_t *data, size_t len)
{
  uint16_t crc = 0x1D0F;
  while (len-- != 0) {
    crc = crc16_ccitt_table[((crc >> 8) ^ *data++) & 0xff] ^ (crc << 8);
  }
  return crc ^ 0xFFFF;
}

uint16_t
crc::crc16_ax25(const uint8_t *data, size_t len)
{
  uint16_t fcs = 0xFFFF;
  while (len--) {
    fcs = (fcs >> 8) ^ crc16_ccitt_table_reverse[(fcs ^ *data++) & 0xFF];
  }
  return fcs ^ 0xFFFF;
}

static uint16_t
update_crc16_ibm(uint8_t crc, uint16_t reg)
{
  const uint16_t crc_poly = 0x8005;
  for (size_t i = 0; i < 8; i++) {
    if (((reg & 0x8000) >> 8) ^ (crc & 0x80)) {
      reg = (reg << 1) ^ crc_poly;
    }
    else {
      reg = (reg << 1);
    }
    crc <<= 1;
  }
  return reg;
}

uint16_t
crc::crc16_ibm(const uint8_t *data, size_t len)
{
  uint16_t crc = 0xFFFF;
  for (size_t i = 0; i < len; i++) {
    crc = update_crc16_ibm(data[i], crc);
  }
  return crc;
}

/**
 *
 * @param t the CRC method
 * @return the size of the specified CRC in bytes
 */
size_t
crc::crc_size(crc_t t)
{
  switch (t) {
  case CRC_NONE:
    return 0;
  case CRC16_CCITT:
  case CRC16_AUG_CCITT:
  case CRC16_CCITT_REVERSED:
  case CRC16_AX25:
  case CRC16_IBM:
    return sizeof(uint16_t);
  case CRC32_C:
    return sizeof(uint32_t);
  default:
    throw std::invalid_argument("crc: Invalid CRC method");
  }
}

uint32_t
crc::crc32_c(const uint8_t *data, size_t len)
{
  uint32_t crc = 0xFFFFFFFF;
  for (size_t i = 0; i < len; i++) {
    crc = (crc >> 8) ^ crc::crc32_c_table[(crc ^ data[i]) & 0xff];
  }
  return crc ^ 0xFFFFFFFF;
}

/**
 * @fn size_t append(crc_t, uint8_t*, const uint8_t*, size_t, bool)
 *
 * Appends a CRC at the end of the buffer
 * @param t the CRC type
 * @param out the output buffer
 * @param data the input buffer
 * @param len the size of the input buffer in bytes
 * @param nbo if set to true, the CRC will be appended in network byte order, otherwise
 * in the native byte order
 * @return the number of bytes appended
 */
size_t
crc::append(crc_t t, uint8_t *out, const uint8_t *data, size_t len,
            bool nbo)
{
  switch (t) {
  case CRC_NONE:
    return 0;
  case CRC16_CCITT: {
    uint16_t x = crc16_ccitt(data, len);
    if (nbo) {
      x = htons(x);
    }
    memcpy(out, &x, sizeof(x));
    return sizeof(x);
  }
  case CRC16_AUG_CCITT: {
    uint16_t x = crc16_aug_ccitt(data, len);
    if (nbo) {
      x = htons(x);
    }
    memcpy(out, &x, sizeof(x));
    return sizeof(x);
  }
  case CRC16_CCITT_REVERSED: {
    uint16_t x = crc16_ccitt_reversed(data, len);
    if (nbo) {
      x = htons(x);
    }
    memcpy(out, &x, sizeof(x));
    return sizeof(x);
  }
  case CRC16_AX25: {
    uint16_t x = crc16_ax25(data, len);
    if (nbo) {
      x = htons(x);
    }
    memcpy(out, &x, sizeof(x));
    return sizeof(x);
  }
  case CRC16_IBM: {
    uint16_t x = crc16_ibm(data, len);
    if (nbo) {
      x = htons(x);
    }
    memcpy(out, &x, sizeof(x));
    return sizeof(x);
  }
  case CRC32_C: {
    uint32_t x = crc32_c(data, len);
    if (nbo) {
      x = htonl(x);
    }
    memcpy(out, &x, sizeof(x));
    return sizeof(x);
  }
  default:
    throw std::invalid_argument("crc: Invalid CRC method");
  }
}


/**
 * @fn bool check(crc_t, const uint8_t*, size_t, bool)
 *
 * Checks for the validity of the buffer containing at its end a CRC.
 * @param t the CRC type
 * @param data the buffer containing the data and the CRC bytes at the end
 * @param len the length of the buffer including the CRC bytes
 * @param nbo if set to true. the method assumes Network Byte Order at the CRC field,
 * otherwise the native endianess is used
 * @return true if the CRC is correct, false otherwise
 */
bool
crc::check(crc_t t, const uint8_t *data, size_t len, bool nbo)
{
  if (len + 1 < crc_size(t)) {
    throw std::invalid_argument("crc: Invalid payload length");
  }
  const size_t payload_len = len -  crc_size(t);
  const size_t crc_len = crc_size(t);
  switch (t) {
  case CRC_NONE:
    return true;
  case CRC16_CCITT: {
    uint16_t x = crc16_ccitt(data, payload_len);
    uint16_t crc_recv;
    memcpy(&crc_recv, data + payload_len, crc_len);
    if (nbo) {
      x = htons(x);
    }
    return x == crc_recv;
  }
  case CRC16_AUG_CCITT: {
    uint16_t x = crc16_aug_ccitt(data, payload_len);
    uint16_t crc_recv;
    memcpy(&crc_recv, data + payload_len, crc_len);
    if (nbo) {
      x = htons(x);
    }
    return x == crc_recv;
  }
  case CRC16_CCITT_REVERSED: {
    uint16_t x = crc16_ccitt_reversed(data, payload_len);
    uint16_t crc_recv;
    memcpy(&crc_recv, data + payload_len, crc_len);
    if (nbo) {
      x = htons(x);
    }
    return x == crc_recv;
  }
  case CRC16_AX25: {
    uint16_t x = crc16_ax25(data, payload_len);
    uint16_t crc_recv;
    memcpy(&crc_recv, data + payload_len, crc_len);
    if (nbo) {
      x = htons(x);
    }
    return x == crc_recv;
  }
  case CRC16_IBM: {
    uint16_t x = crc16_ibm(data, payload_len);
    uint16_t crc_recv;
    memcpy(&crc_recv, data + payload_len, crc_len);
    if (nbo) {
      x = htons(x);
    }
    return x == crc_recv;
  }
  case CRC32_C: {
    uint32_t x = crc32_c(data, payload_len);
    uint32_t crc_recv;
    memcpy(&crc_recv, data + payload_len, crc_len);
    if (nbo) {
      x = htonl(x);
    }
    return x == crc_recv;
  }
  default:
    throw std::invalid_argument("crc: Invalid CRC method");
  }
}

} /* namespace satnogs */
} /* namespace gr */