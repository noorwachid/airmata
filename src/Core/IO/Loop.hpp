#pragma once

#include "Core/Container/RC.hpp"
#include "Core/IO/Action.hpp"
#include <string>

namespace IO {
    enum class LoopMode { 
        default_ = UV_RUN_DEFAULT,
        once = UV_RUN_ONCE, 
        noWait = UV_RUN_NOWAIT 
    };

    class Loop {
      public:
        Loop();

        ~Loop();

        void run(LoopMode mode = LoopMode::default_);

        void stop();

        LoopContext* getContext();

      private:
        LoopContext context;
    };
}
