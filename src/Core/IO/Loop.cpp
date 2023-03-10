#include "Core/IO/Loop.h"
#include "uv.h"

namespace IO
{
    Loop::Loop()
    {
        uv_loop_init(GetContext());
        fs.loopContext = GetContext();
    }

    Loop::~Loop() 
    { 
        uv_loop_close(GetContext()); 
    }

    void Loop::Run(LoopMode mode) { uv_run(GetContext(), static_cast<uv_run_mode>(mode)); }

    void Loop::Stop() 
    { 
        uv_stop(GetContext()); 
    }

    LoopContext* Loop::GetContext() { return &context; }
}
