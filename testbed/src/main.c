#include "../../engine/src/core/logger.h"
#include "../../engine/src/core/asserts.h"

// TODO: TEST
#include "../../engine/src/platform/platform.h"

int main(void) {
    CFATAL("A test message: %f", 3.14f);
    CERROR("A test message: %f", 3.14f);
    CWARN("A test message: %f", 3.14f);
    CINFO("A test message: %f", 3.14f);
    CDEBUG("A test message: %f", 3.14f);
    CTRACE("A test message: %f", 3.14f);
    
    platform_state state;
    if(platform_startup(&state, "Chronos Engine testbed", 100,100, 1280, 720)) 
    {
        while(TRUE) 
        {
            if(!platform_pump_messages(&state))
            {
                platform_pump_messages(&state);
            }
        }
    }

    platform_shutdown(&state);

    return 0;
}
