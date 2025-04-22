#include "BitFieldMember.h"

#ifndef REGISTERS_H
#define REGISTERS_H

namespace Mcp2515 {
    namespace Registers {

        // -------------
        // EFLG Register
        // -------------
        union ErrorFlag {
            uint8_t value;

            // EWARN
            BitFieldMember<0, 1> errorWarning;

            // RXWAR
            BitFieldMember<1, 1> receiveErrorWarning;

            // TXWAR
            BitFieldMember<2, 1> transmitErrorWarning;

            // RXEP
            BitFieldMember<3, 1> receiveErrorPassive;

            // TXEP
            BitFieldMember<4, 1> transmitErrorPassive;

            // TXBO
            BitFieldMember<5, 1> busOffError;

            // RX0OVR
            BitFieldMember<6, 1> receiveBuffer0Overflow;

            // RX1OVR
            BitFieldMember<7, 1> receiveBuffer1Overflow;
        };


        // -------------
        // REC Register
        // -------------
        union ReceiveErrorCounter {
            uint8_t value;
        };

        // -------------
        // TEC Register
        // -------------
        union TransmitErrorCounter {
            uint8_t value;
        };



        // -------------
        // TXBnCTRL Register
        // -------------
        union TransmitBufferControl {
            uint8_t value;
            enum TXPriority
            {
                TXP_LOWEST,
                TXP_LOW_INTERMEDIATE,
                TXP_HIGH_INTERMEDIA,
                TXP_HIGHEST,
            };

            // TXP1 TXP0
            BitFieldMember<0, 2> transmitBufferPriority;

            // TXREQ
            BitFieldMember<3, 1> messageTransmitRequest;

            // TXERR
            BitFieldMember<4, 1> transmitErrorDetected;

            // MLOA
            BitFieldMember<5, 1> messageLostArbitration;

            // ABTF
            BitFieldMember<6, 1> messageAborted;
        };




        // -------------
        // TXRTSCTRL Register
        // -------------
        struct TransmitReadyToSendControl {
            uint8_t value;
            enum BxRTSMode
            {
                DIGITAL_INPUT,
                RTS_FALLING_EDGE
            };


            // B0RTSM
            BitFieldMember<0, 1> buffer0ReadyToSendMode;

            // B1RTSM
            BitFieldMember<1, 1> buffer1ReadyToSendMode;

            // B2RTSM
            BitFieldMember<2, 1> buffer2ReadyToSendMode;

            // B0RTS
            BitFieldMember<3, 1> buffer0PinState;

            // B1RTS
            BitFieldMember<4, 1> buffer1PinState;

            // B2RTS
            BitFieldMember<5, 1> buffer2PinState;

        };

        // -------------
        // CANINTE Register
        // -------------
        struct CanInterruptEnable {
            uint8_t value;

            // RX0IE
            BitFieldMember<0, 1> receiveBuffer0FullInterruptEnable;

            // RX1IE
            BitFieldMember<1, 1> receiveBuffer1FullInterruptEnable;

            // TX0IE
            BitFieldMember<2, 1> transmitBuffer0EmptyInterruptEnable;

            // TX1IE
            BitFieldMember<3, 1> transmitBuffer1EmptyInterruptEnable;

            // TX2IE
            BitFieldMember<4, 1> transmitBuffer2EmptyInterruptEnable;

            // ERRIE
            BitFieldMember<5, 1> errorInterruptEnable;

            // WAKIE
            BitFieldMember<6, 1> wakeUpInterruptEnable;

            // MERRE
            BitFieldMember<7, 1> messageErrorInterruptEnable;

        };

        // -------------
        // CANINTF Register
        // -------------
        struct CanInterruptFlag {
            uint8_t value;

            // RX0IF
            BitFieldMember<0, 1> receiveBuffer0FullInterruptFlag;

            // RX1IF
            BitFieldMember<1, 1> receiveBuffer1FullInterruptFlag;

            // TX0IF
            BitFieldMember<2, 1> transmitBuffer0EmptyInterruptFlag;

            // TX1IF
            BitFieldMember<3, 1> transmitBuffer1EmptyInterruptFlag;

            // TX2IF
            BitFieldMember<4, 1> transmitBuffer2EmptyInterruptFlag;

            // ERRIF
            BitFieldMember<5, 1> errorInterruptFlag;

            // WAKIF
            BitFieldMember<6, 1> wakeUpInterruptFlag;

            // MERRIF
            BitFieldMember<7, 1> messageErrorInterruptFlag;

        };


        // -------------
        // RXB0CTRL Register
        // -------------
        struct Receive0BufferControl {
            uint8_t value;

            enum FILTHITAcceptanceFilter
            {
                FILTHIT_ACCEPTANCE_FILTER_0,
                FILTHIT_ACCEPTANCE_FILTER_1
            };

            enum RXMOperatingMode
            {
                RXM_RECV_FILTERED_MASKED_ONLY = 0,
                RXM_RESERVED_0 = 1,
                RXM_RESERVED_1 = 2,
                RXM_RECV_ALL = 3
            };

            // FILTHIT0
            BitFieldMember<0, 1> filterHit;

            // BUKT1
            BitFieldMember<1, 1> readOnlyCopyBUKTBit;

            // BUKT
            BitFieldMember<2, 1> rolloverEnable;

            // RXRTR
            BitFieldMember<3, 1> receivedRemoteTransferRequest;

            // RXM
            BitFieldMember<5, 2> receiveBufferOperatingMode;

        };

        // -------------
        // RXB1CTRL Register
        // -------------
        struct Receive1BufferControl {
            uint8_t value;

            enum FILTHITAcceptanceFilter
            {
                FILTHIT_ACCEPTANCE_FILTER_0, // RXF0
                FILTHIT_ACCEPTANCE_FILTER_1, // RXF1 
                FILTHIT_ACCEPTANCE_FILTER_2, // RXF2 
                FILTHIT_ACCEPTANCE_FILTER_3, // RXF3 
                FILTHIT_ACCEPTANCE_FILTER_4, // RXF4 
                FILTHIT_ACCEPTANCE_FILTER_5, // RXF5 
            };

            enum RXMOperatingMode
            {
                RXM_RECV_FILTERED_MASKED_ONLY = 0,
                RXM_RESERVED_0 = 1,
                RXM_RESERVED_1 = 2,
                RXM_RECV_ALL = 3
            };

            // FILTHIT[2:0]
            BitFieldMember<0, 3> filterHit;

            // RXRTR
            BitFieldMember<3, 1> receivedRemoteTransferRequest;

            // RXM
            BitFieldMember<5, 2> receiveBufferOperatingMode;

        };

    }
}

#endif