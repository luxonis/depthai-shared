/*
 * spi_protocol.h
 *
 *  Created on: Mar 31, 2020
 *      Author: TheMarpe - Martin Peterlin
 *
 */

#ifndef SHARED_SPI_PROTOCOL_H
#define SHARED_SPI_PROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define SPI_PROTOCOL_PAYLOAD_SIZE (252)

typedef struct {
    uint8_t start;
    uint8_t data[SPI_PROTOCOL_PAYLOAD_SIZE];
    uint8_t crc[2];
    uint8_t end;
} SpiProtocolPacket;

typedef struct {
    int state;
    int payloadOffset;
    int currentPacketIndex;
    // 2 packets can be decoded at a time max
    SpiProtocolPacket packet[2]; 
} SpiProtocolInstance;


enum SPI_PROTOCOL_RETURN_CODE {
    SPI_PROTOCOL_OK = 0,
    SPI_PROTOCOL_PACKET_NULL = -1,
    SPI_PROTOCOL_PAYLOAD_BUFFER_NULL = -2
};



/*
*   instance - SpiProtocolInstance pointer;
*/
void spi_protocol_init(SpiProtocolInstance *instance);



/*
*  instance - spi protocol instance pointer
*  buffer - uint8_t pointer to buffer where packet bytes reside
*  size - number of bytes to parse (max SPI_PROTOCOL_PAYLOAD_SIZE)
*
*  returns: SpiProtocolPacket pointer, NULL if packet wasn't parsed
*/
SpiProtocolPacket* spi_protocol_parse(SpiProtocolInstance* instance, uint8_t* buffer, int size);


/*
* packet - pointer to SpiProtocolPacket where it will be written
* payload_buffer - Input buffer with payload data
* Returns: 0 OK, -1 packet is NULL, -2 payload_buffer is NULL
*/
int spi_protocol_write_packet(SpiProtocolPacket* packet, uint8_t* payload_buffer, int size);


/*
* packet - pointer to SpiProtocolPacket where header, crc and tail will be written
* Returns: 0 OK, -1 packet is NULL
*/
int spi_protocol_inplace_packet(SpiProtocolPacket* packet);


#ifdef __cplusplus
}
#endif


#endif
