//
// Created by Max Tyson on 31/10/2026.
//

#ifndef LIBKPI_HARDWARE_USERINTERRUPTS_H
#define LIBKPI_HARDWARE_USERINTERRUPTS_H

#include <cstdint>
#include <libcommon/macros.h>
#include <libcommon/assert.h>

namespace MaxOS::KPI::hardware {

    enum InterruptResourceFlags {

        BLOCK,
        POLL,

    };

    /**
     * @class UserInterruptHandler
     * @brief Handles a certain interrupt number, in userspace
     *
     * @todo this needs to interrupt whatever the userspace program is running
     */
    class UserInterruptHandler {
        protected:
            uint8_t m_interrupt_number; ///<  The interrupt number this handler handles

        public:
            explicit UserInterruptHandler(uint8_t interrupt_number);
            virtual ~UserInterruptHandler();

            virtual void handle_interrupt();
            uint8_t irq();

    };

    class UserInterruptServer {

        private:
            UserInterruptHandler* m_interrupt_handler;
            uint64_t m_interrupt_handle = 0;

        public:
            UserInterruptServer(UserInterruptHandler* handler);
            ~UserInterruptServer();

            void start();
            bool poll();

    };

    uint64_t interrupt_register(uint8_t irq);
    uint32_t interrupt_wait(uint64_t handle);
    uint32_t interrupt_poll(uint64_t handle);
    void interrupt_ack(uint64_t handle);
    void interrupt_close(uint64_t handle);

}

#endif //LIBKPI_HARDWARE_USERINTERRUPTS_H
