#pragma once

#include "Core/Container/RC.h"
#include "Core/IO/Action.h"
#include <string>

namespace IO
{
    enum class LoopMode
    {
        default_ = UV_RUN_DEFAULT,
        once = UV_RUN_ONCE,
        noWait = UV_RUN_NOWAIT
    };

    class Loop
    {
    public:
        FileSystem fs;

    public:
        Loop();

        ~Loop();

        void Run(LoopMode mode = LoopMode::default_);

        void Stop();

        LoopContext* GetContext();

    private:
        LoopContext context;
    };
}
