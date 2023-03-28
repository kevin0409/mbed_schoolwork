#include "Callback.h"
#include "mbed.h"
#include <cstdint>
#include <stdint.h>

// main() runs in its own thread in the OS
class Counter{
    InterruptIn _interrupt;
    volatile uint16_t _count;
    volatile uint16_t _updated;
    void isr(){
        _count++;
        _updated = 1;
    }
    public:
    Counter(PinName pin): _interrupt(pin){
        _count = 0; _updated = 0;
        _interrupt.fall(callback(this, &Counter::isr));
    }
    uint16_t read(){_updated = 0; return _count;}
    bool isUpdated(){return _updated;}
};

Counter cnt(BUTTON1);

int main()
{
    while (true) {
        if(cnt.isUpdated()){
            printf(" count = %3d\n", cnt.read());
            wait_us(100000);
        }

    }
}

