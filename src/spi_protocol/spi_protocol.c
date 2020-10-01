/*
 * spi_protocol.c
 *
 *  Created on: Mar 31, 2020
 *      Author: TheMarpe - Martin Peterlin
 *
 */

#include <spi_protocol/spi_protocol.h>

#include <string.h>
#include <math.h>
#include <assert.h>
#include <spi_protocol/checksum.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

static const uint8_t START_BYTE_MAGIC = 0b10101010;
//static const uint8_t END_BYTE_MAGIC = 0b01010101;
static const uint8_t END_BYTE_MAGIC = 0b00000000; // 0


#define STATE_RX_HEADER         (0) // 1B start
#define STATE_RX_PAYLOAD        (1) // PAYLOAD_SIZE bytes
#define STATE_RX_TAIL_CRC_0     (2) // LE first byte CRC
#define STATE_RX_TAIL_CRC_1     (3) // LE second byte CRC
#define STATE_RX_TAIL_END       (4) // 1 byte end byte

static SpiProtocolPacket* get_parsed_packet(SpiProtocolInstance* instance){
    assert(instance->currentPacketIndex == 0 || instance->currentPacketIndex == 1);
    return instance->packet + ( 1 - instance->currentPacketIndex);
}

static SpiProtocolPacket* get_current_packet(SpiProtocolInstance* instance){
    assert(instance->currentPacketIndex == 0 || instance->currentPacketIndex == 1);
    return instance->packet + instance->currentPacketIndex;
}

static SpiProtocolPacket* switch_current_packet(SpiProtocolInstance* instance){
    assert(instance->currentPacketIndex == 0 || instance->currentPacketIndex == 1);
    instance->payloadOffset = 0;
    instance->currentPacketIndex = 1 - instance->currentPacketIndex;
    return instance->packet + instance->currentPacketIndex;
}

static int is_packet_ok(SpiProtocolPacket* packet){

    if(packet->start != START_BYTE_MAGIC){
        return 0;
    }

    // Get CRC and compare with payload crc
    uint16_t crc = (packet->crc[0] & 0xFF) | ((((uint16_t) packet->crc[1]) << 8) & 0xFF00);
    
    // Calculated crc
    uint16_t crc_calculated = crc_16(packet->data, SPI_PROTOCOL_PAYLOAD_SIZE);

    // Compare 
    if(crc != crc_calculated){
        return 0;
    }

    if(packet->end != END_BYTE_MAGIC){
        return 0;
    }

    return 1;
}


/*
*   instance - SpiProtocolInstance pointer;
*/
void spi_protocol_init(SpiProtocolInstance *instance){
    instance->state = STATE_RX_HEADER;
    instance->payloadOffset = 0;
    instance->currentPacketIndex = 0;
    init_crc16_tab();
}


/*
*  instance - spi protocol instance pointer
*  buffer - uint8_t pointer to buffer where packet bytes reside
*  size - number of bytes to parse (max sizeof(SpiProtocolPacket))
*
*  returns: SpiProtocolPacket pointer, NULL if packet wasn't parsed
*/
SpiProtocolPacket* spi_protocol_parse(SpiProtocolInstance* instance, uint8_t* buffer, int size){

    // max bytes to parse: SPI_PROTOCOL_PAYLOAD_SIZE
    assert(size >= 0 && size <= (int) sizeof(SpiProtocolPacket));

    // Get current packet
    SpiProtocolPacket* packet = get_current_packet(instance);

    // Packet counter
    int packetCount = 0;

    // Parse each byte individually (except payload)
    for(int i = 0; i < size; i++){
        uint8_t curByte = buffer[i];

        switch(instance->state){

            case STATE_RX_HEADER:
            {
                if(curByte == START_BYTE_MAGIC){
                    packet->start = curByte;
                    instance->state = STATE_RX_PAYLOAD;
                }   
            }
            break;

            case STATE_RX_PAYLOAD:
            {
                int remainingBytesAvailable = size - i;
                int remainingBytes = SPI_PROTOCOL_PAYLOAD_SIZE - instance->payloadOffset;
                int numBytes = MIN(remainingBytes, remainingBytesAvailable);
                memcpy(packet->data + instance->payloadOffset, buffer + i, numBytes);

                // Increment payloadOffset
                instance->payloadOffset += numBytes;

                // Increment "i" to a position after numBytes
                i += numBytes - 1; // one byte will be incremented by the for loop

                // Assert: payload offset must be less or equal than actual payload size
                assert(instance->payloadOffset <= SPI_PROTOCOL_PAYLOAD_SIZE);
                
                // if payloadOffset is at the end, whole packet was read, change state
                if(instance->payloadOffset == SPI_PROTOCOL_PAYLOAD_SIZE){
                    instance->state = STATE_RX_TAIL_CRC_0;
                    instance->payloadOffset = 0;
                }

            }
            break;

            case STATE_RX_TAIL_CRC_0:
            {
                packet->crc[0] = curByte;
                instance->state = STATE_RX_TAIL_CRC_1;
            }
            break;


            case STATE_RX_TAIL_CRC_1:
            {
                packet->crc[1] = curByte;
                instance->state = STATE_RX_TAIL_END;
            }
            break;
            

            case STATE_RX_TAIL_END:
            {
                packet->end = curByte;
                
                // This is the end of the current packet, check if packet is okay
                if(is_packet_ok(packet)){
                    
                    // Increment packet count
                    packetCount++;

                    // Switch to other packet
                    packet = switch_current_packet(instance);
                    
                }

                // Jump to beginning state 
                instance->state = STATE_RX_HEADER;

            }
            break;
            
            default:
                // if any other value is in state variable, instance wasn't initialized properly
                assert(false);
        }

    }

    if(packetCount > 0){
        return get_parsed_packet(instance); 
    } else {
        return NULL;
    }

}


/*
* packet - pointer to SpiProtocolPacket where it will be written
* payload_buffer - Input buffer with payload data
* Returns: 0 OK, -1 packet is NULL, -2 payload_buffer is NULL
*/
int spi_protocol_write_packet(SpiProtocolPacket* packet, uint8_t* payload_buffer, int size){
    if(packet == NULL){
        return SPI_PROTOCOL_PACKET_NULL;
    }
    if(payload_buffer == NULL){
        return SPI_PROTOCOL_PAYLOAD_BUFFER_NULL;
    } 
    
    // Start byte
    packet->start = START_BYTE_MAGIC;
    
    // Payload
    memcpy(packet->data, payload_buffer, size);
    // Zero out the rest of buffer
    memset(packet->data + size, 0, SPI_PROTOCOL_PAYLOAD_SIZE - size);

    uint16_t crc = crc_16(packet->data, SPI_PROTOCOL_PAYLOAD_SIZE);

    // CRC - little endian 
    packet->crc[0] = crc & 0xFF;
    packet->crc[1] = ((crc >> 8) & 0xFF);

    // End byte    
    packet->end = END_BYTE_MAGIC;
    
    return SPI_PROTOCOL_OK;
}

/*
* packet - pointer to SpiProtocolPacket where header, crc and tail will be written
* Returns: 0 OK, -1 packet is NULL
*/
int spi_protocol_inplace_packet(SpiProtocolPacket* packet){

    if(packet == NULL){
        return SPI_PROTOCOL_PACKET_NULL;
    }

    packet->start = START_BYTE_MAGIC;

    // Calculate CRC
    uint16_t crc = crc_16(packet->data, SPI_PROTOCOL_PAYLOAD_SIZE);
    
    // CRC - little endian 
    packet->crc[0] = crc & 0xFF;
    packet->crc[1] = ((crc >> 8) & 0xFF);

    // End byte    
    packet->end = END_BYTE_MAGIC;
    
    return SPI_PROTOCOL_OK;

}
