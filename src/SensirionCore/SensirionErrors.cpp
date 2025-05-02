/*
 * Copyright (c) 2020, Sensirion AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Sensirion AG nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include "SensirionErrors.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

// helper function to copy string to PROGMEM
static void safeCopy_P(char *dst, const char *src_P, size_t len)
{ strlcpy_P(dst, src_P, len); }

void errorToString(uint16_t error, char errorMessage[],
                   size_t errorMessageSize) {

    uint16_t highLevelError = error & 0xFF00;
    uint16_t lowLevelError = error & 0x00FF;

    if (error & HighLevelError::SensorSpecificError) {
        snprintf(errorMessage, errorMessageSize, "Sensor specific error: 0x%2x",
                 lowLevelError);
        return;
    }

    switch (highLevelError) {
        case HighLevelError::NoError:
            safeCopy_P(errorMessage, PSTR("No error"), errorMessageSize);
            break;

        case HighLevelError::WriteError:
            switch (lowLevelError) {
                case LowLevelError::Undefined:
                    safeCopy_P(errorMessage, PSTR("Write error"), errorMessageSize);
                    return;
                case LowLevelError::SerialWriteError:
                    safeCopy_P(errorMessage, PSTR("Error writing to serial"),
                            errorMessageSize);
                    return;
                case LowLevelError::InternalBufferSizeError:
                    safeCopy_P(errorMessage,
                            PSTR("Data too long to fit in transmit buffer"),
                            errorMessageSize);
                    return;
                case LowLevelError::I2cAddressNack:
                    safeCopy_P(errorMessage,
                            PSTR("Received NACK on transmit of address"),
                            errorMessageSize);
                    return;
                case LowLevelError::I2cDataNack:
                    safeCopy_P(errorMessage, PSTR("Received NACK on transmit of data"),
                            errorMessageSize);
                    return;
                case LowLevelError::I2cOtherError:
                    safeCopy_P(errorMessage, PSTR("Error writing to I2C bus"),
                            errorMessageSize);
                    return;
            }
            break;
        case HighLevelError::ReadError:
            switch (lowLevelError) {
                case LowLevelError::Undefined:
                    safeCopy_P(errorMessage, PSTR("Read error"), errorMessageSize);
                    return;
                case LowLevelError::NonemptyFrameError:
                    safeCopy_P(errorMessage, PSTR("Frame already contains data"),
                            errorMessageSize);
                    return;
                case LowLevelError::TimeoutError:
                    safeCopy_P(errorMessage, PSTR("Timeout while reading data"),
                            errorMessageSize);
                    return;
                case LowLevelError::ChecksumError:
                    safeCopy_P(errorMessage, PSTR("Checksum is wrong"),
                            errorMessageSize);
                    return;
                case LowLevelError::CRCError:
                    safeCopy_P(errorMessage, PSTR("Wrong CRC found"), errorMessageSize);
                    return;
                case LowLevelError::WrongNumberBytesError:
                    safeCopy_P(errorMessage, PSTR("Number of bytes not a multiple of 3"),
                            errorMessageSize);
                    return;
                case LowLevelError::NotEnoughDataError:
                    safeCopy_P(errorMessage, PSTR("Not enough data received"),
                            errorMessageSize);
                    return;
                case LowLevelError::InternalBufferSizeError:
                    safeCopy_P(errorMessage, PSTR("Internal I2C buffer too small"),
                            errorMessageSize);
                    return;
            }
            break;
        case HighLevelError::ExecutionError: {
            char format[] = "Execution error, status register: 0x%x";
            snprintf(errorMessage, errorMessageSize, format, lowLevelError);
            return;
        }
        case HighLevelError::TxFrameError:
            switch (lowLevelError) {
                case LowLevelError::Undefined:
                    safeCopy_P(errorMessage, PSTR("Tx frame error"), errorMessageSize);
                    return;
                case LowLevelError::BufferSizeError:
                    safeCopy_P(errorMessage, PSTR("Not enough space in buffer"),
                            errorMessageSize);
                    return;
            }
            break;
        case HighLevelError::RxFrameError:
            switch (lowLevelError) {
                case LowLevelError::Undefined:
                    safeCopy_P(errorMessage, PSTR("Rx frame error"), errorMessageSize);
                    return;
                case LowLevelError::BufferSizeError:
                    safeCopy_P(errorMessage, PSTR("Not enough space in buffer"),
                            errorMessageSize);
                    return;
                case LowLevelError::NoDataError:
                    safeCopy_P(errorMessage, PSTR("No more data in frame"),
                            errorMessageSize);
                    return;
                case LowLevelError::RxAddressError:
                    safeCopy_P(errorMessage, PSTR("Wrong address in return frame"),
                            errorMessageSize);
                    return;
                case LowLevelError::RxCommandError:
                    safeCopy_P(errorMessage, PSTR("Wrong command in return frame"),
                            errorMessageSize);
                    return;
            }
    }
    safeCopy_P(errorMessage, PSTR("Error processing error"), errorMessageSize);
    return;
}
