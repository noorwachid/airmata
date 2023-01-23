#pragma once 

#include <string>
#include "uv.h"

namespace IO
{
    using LoopContext = uv_loop_t;

    enum class LoopMode
    {
        Default = 0,
        Once,
        NoWait
    };

    class Loop
    {
    public:
        Loop();

        ~Loop();

        void Run(LoopMode mode = LoopMode::Default);

        void Stop();

        LoopContext* GetContext();

    private:
        LoopContext _context;
    };
}
