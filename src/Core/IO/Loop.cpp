#include "Core/IO/Loop.h"
#include "uv.h"

namespace IO {
    Loop::Loop() { uv_loop_init(getContext()); }

    Loop::~Loop() { uv_loop_close(getContext()); }

    void Loop::run(LoopMode mode) { uv_run(getContext(), static_cast<uv_run_mode>(mode)); }

    void Loop::stop() { uv_stop(getContext()); }

    LoopContext* Loop::getContext() { return &context; }
}
