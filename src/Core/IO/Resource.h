#pragma once

#include "Core/Container/Function.h"
#include "Core/Container/String.h"
#include "Core/IO/Loop.h"
#include "uv.h"

namespace IO {
    using ResourceContext = uv_handle_t;

    class Resource {
      public:
        virtual ~Resource() {}
    };

    using StreamContext = uv_stream_t;
    using StreamReadCallback = Function<void(const String& data, int status)>;
    using StreamWriteCallback = Function<void(int status)>;

    class Stream : public Resource {
      public:
        void read(const StreamReadCallback& callback);

        void stopReading();

        void write(const String& data, const StreamWriteCallback& callback = nullptr);

        virtual StreamContext* getContext() = 0;

      private:
        StreamReadCallback readCallback = nullptr;
        StreamWriteCallback writeCallback = nullptr;
    };

    using TTYContext = uv_tty_t;

    enum class TTYMode {
        Normal = UV_TTY_MODE_NORMAL,
        Raw = UV_TTY_MODE_RAW,
        IO = UV_TTY_MODE_IO,
    };

    struct TTYSize {
        int width;
        int height;
    };

    class TTY final : public Stream {
      public:
        TTY(Loop& loop, int fd, bool readable = true);

        virtual StreamContext* getContext() override;

        void setMode(TTYMode mode);

        void resetMode();

        const TTYSize& getSize();

      private:
        TTYContext context;
        TTYSize size;
    };
}
