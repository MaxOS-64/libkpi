//
// Created by Max Tyson on 31/10/2026.
//

#ifndef LIBKPI_HARDWARE_USERINTERRUPTS_H
#define LIBKPI_HARDWARE_USERINTERRUPTS_H

#include <cstdint>
#include <libcommon/macros.h>
#include <libcommon/assert.h>

namespace MaxOS::KPI::hardware {

    /**
     * @class UserInterruptHandler
     * @brief Handles a certain interrupt number, in userspace
     */
    class UserInterruptHandler {
        protected:
            uint8_t m_interrupt_number; ///<  The interrupt number this handler handles

        public:
            explicit UserInterruptHandler(uint8_t interrupt_number, int64_t redirect = -1, uint64_t redirect_index = 0);
            virtual ~UserInterruptHandler();

            virtual void handle_interrupt();

    };

}

#endif //LIBKPI_HARDWARE_USERINTERRUPTS_H
