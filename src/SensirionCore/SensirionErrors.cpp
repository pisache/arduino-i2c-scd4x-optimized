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

const char* errorToString(uint16_t error) {

    uint16_t hl = error & 0xFF00;
    uint16_t ll = error & 0x00FF;

    if (error & HighLevelError::SensorSpecificError) 
        return PSTR("Sensor Error");

    if (hl == HighLevelError::NoError && !error)
        return PSTR("No error");

    if (hl == HighLevelError::WriteError && ll == LowLevelError::SerialWriteError)
        return PSTR("Serial Write Error");
    if (hl == HighLevelError::WriteError && ll == LowLevelError::Undefined)
        return PSTR("Undefined Write Error");
    if (hl == HighLevelError::WriteError && ll == LowLevelError::InternalBufferSizeError)
        return PSTR("Data too long for transmit buffer");
    if (hl == HighLevelError::WriteError && ll == LowLevelError::I2cAddressNack)
        return PSTR("NACK on transmit of addr");
    if (hl == HighLevelError::WriteError && ll == LowLevelError::I2cDataNack)
        return PSTR("NACK on transmit of data");
    if (hl == HighLevelError::WriteError && ll == LowLevelError::I2cOtherError)
        return PSTR("Write to I2C bus Error");

    if (hl == HighLevelError::ReadError && ll == LowLevelError::Undefined)
        return PSTR("Undefined Read Error");
    if (hl == HighLevelError::ReadError && ll == LowLevelError::NonemptyFrameError)
        return PSTR("Frame already contains data");
    if (hl == HighLevelError::ReadError && ll == LowLevelError::TimeoutError)
        return PSTR("Read TIMEOUT");
    if (hl == HighLevelError::ReadError && ll == LowLevelError::ChecksumError)
        return PSTR("Checksum Error");
    if (hl == HighLevelError::ReadError && ll == LowLevelError::CRCError)
        return PSTR("CRC Error");
    if (hl == HighLevelError::ReadError && ll == LowLevelError::WrongNumberBytesError)
        return PSTR("# of Bytes != multiple of 3");
    if (hl == HighLevelError::ReadError && ll == LowLevelError::NotEnoughDataError)
        return PSTR("Not enough data recceived");
    if (hl == HighLevelError::ReadError && ll == LowLevelError::InternalBufferSizeError)
        return PSTR("Internal I2C buffer too small");
    
    if (hl == HighLevelError::ExecutionError)
        return PSTR("Execution Error");
}
