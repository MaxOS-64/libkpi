//
// Created by Max Tyson on 31/10/2026.
//

#include <libkpi/hardware/userinterrupts.h>

using namespace MaxOS::KPI;
using namespace MaxOS::KPI::hardware;

UserInterruptHandler::UserInterruptHandler(uint8_t interrupt_number)
: m_interrupt_number(interrupt_number)
{
}

UserInterruptHandler::~UserInterruptHandler() = default;

void UserInterruptHandler::handle_interrupt() {
    NOT_IMPLEMENTED;
}

uint8_t UserInterruptHandler::irq() {
    return m_interrupt_number;
}


UserInterruptServer::UserInterruptServer(UserInterruptHandler* handler)
: m_interrupt_handler(handler)
{
    m_interrupt_handle = interrupt_register(handler->irq());
}

UserInterruptServer::~UserInterruptServer() {
    interrupt_close(m_interrupt_handle);
}

void UserInterruptServer::start() {

    while (true) {

        // Wait for a interrupt
        interrupt_wait(m_interrupt_handle);

        m_interrupt_handler->handle_interrupt();
        interrupt_ack(m_interrupt_handle);
    }
}

bool UserInterruptServer::poll() {

    // Nothing fired (or no interrupt was claimed)
    if (!m_interrupt_handle || !interrupt_poll(m_interrupt_handle))
        return false;

    m_interrupt_handler->handle_interrupt();
    interrupt_ack(m_interrupt_handle);
    return true;
}

uint64_t hardware::interrupt_register(uint8_t irq) {

    string irq_name = string("irq/") + string(irq);

    // Register the interrupt
    if(!resource_create(ResourceType::INTERRUPT, irq_name.c_str(), irq, 0))
        return 0;

    return resource_open(ResourceType::INTERRUPT, irq_name.c_str(), 0);
}

uint32_t hardware::interrupt_wait(uint64_t handle) {

    return resource_read(handle, nullptr, 0, InterruptResourceFlags::BLOCK);

}

uint32_t hardware::interrupt_poll(uint64_t handle) {

    return resource_read(handle, nullptr, 0, InterruptResourceFlags::POLL);
}

void hardware::interrupt_ack(uint64_t handle) {

    resource_write(handle, nullptr, 0, 0);
}

void hardware::interrupt_close(uint64_t handle) {
    resource_close(handle, 0);
}