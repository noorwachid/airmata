#pragma once 

#include "Core/IO/Loop.h"
#include "uv.h"
#include <string>
#include <functional>

namespace IO
{
    using String = std::string;

    using ResourceBuffer = uv_buf_t;
    using ResourceContext = uv_handle_t;

    class Resource 
    {
      public:
        virtual ~Resource() {}
    };

    using StreamContext = uv_stream_t;
    using StreamReadCallback = std::function<void(const String& buffer, int status)>;
    using StreamWriteCallback = std::function<void(int status)>;

    class Stream : public Resource 
    {
      public:
        void Read(const StreamReadCallback& callback);

        void StopReading();

        void Write(const String& buffer, const StreamWriteCallback& callback);

        void Write(const String& buffer);

        virtual StreamContext* GetContext() = 0;

    private:
        StreamReadCallback _readCallback = nullptr;
        StreamWriteCallback _writeCallback = nullptr;
    };

    using TTYContext = uv_tty_t;

    enum class TTYMode 
    {
        Normal = UV_TTY_MODE_NORMAL,
        Raw    = UV_TTY_MODE_RAW,
        IO     = UV_TTY_MODE_IO,
    };

    struct TTYSize 
    {
        int width;
        int height;
    };

    class TTY : public Stream
    {
      public:
        TTY(Loop& loop, int fd, bool readable = true);

        virtual StreamContext* GetContext() override;

        void SetMode(TTYMode mode);

        void ResetMode();

        const TTYSize& GetSize();

      private:
        TTYContext _context;
        TTYSize _size;
    };
}
