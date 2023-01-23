#include "Core/IO/Resource.h"

namespace IO
{
    void Stream::Read(const StreamReadCallback& callback)
    {
        _readCallback = callback;
        uv_read_start(
            GetContext(),

            [](ResourceContext* stream, size_t recomendedSize, ResourceBuffer* buf)
            {
                buf->len = 64; // Enough to contain common sequence
                buf->base = new char[buf->len];

                for (int i = 0; i < buf->len; ++i)
                    buf->base[i] = 0;
            },

            [](StreamContext* stream, ssize_t result, const ResourceBuffer* buf)
            {
                if (result < 0) 
                {
                    delete[] buf->base;
                }

                auto callback = reinterpret_cast<Stream*>(stream->data)->_readCallback;

                if (callback != nullptr)
                    callback(buf->base, result);

                delete[] buf->base;
            }
        );
    }

    void Stream::StopReading()
    {
        uv_read_stop(GetContext());
    }

    void Stream::Write(const String& bytes)
    {
        Write(bytes, nullptr);
    }

    void Stream::Write(const String& bytes, const StreamWriteCallback& callback)
    {
        _writeCallback= callback;

        uv_buf_t* buf = new uv_buf_t;
        uv_write_t* writeRequest = new uv_write_t;
        buf->base = new char[bytes.size()];
        buf->len = bytes.size();

        std::memcpy(buf->base, bytes.data(), bytes.size());

        writeRequest->data = buf;

        uv_write(writeRequest, GetContext(), buf, 1,
            [](uv_write_t* writeRequest, int status)
            {
                auto callback = reinterpret_cast<Stream*>(writeRequest->handle->data)->_writeCallback;

                if (callback != nullptr)
                    callback(status);

                auto data = reinterpret_cast<uv_buf_t*>(writeRequest->data);
                delete data->base;
                delete writeRequest;
            }
        );
    }
    
    TTY::TTY(Loop& loop, int fd, bool readable)
    {
        uv_tty_init(loop.GetContext(), &_context, fd, readable);
        _context.data = this;
    }

    StreamContext* TTY::GetContext()
    {
        return reinterpret_cast<StreamContext*>(&_context);
    }

    void TTY::SetMode(TTYMode mode)
    {
        uv_tty_set_mode(&_context, static_cast<uv_tty_mode_t>(mode));
    }

    void TTY::ResetMode()
    {
        uv_tty_reset_mode();
    }

    const TTYSize& TTY::GetSize()
    {
        uv_tty_get_winsize(&_context, &_size.width, &_size.height);
        return _size;
    }
    
}
