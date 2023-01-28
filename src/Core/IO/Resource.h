#pragma once

#include "Core/Container/Function.h"
#include "Core/Container/String.h"
#include "Core/Container/Vector.h"
#include "Core/IO/Loop.h"
#include "uv.h"

namespace IO
{
    using ResourceContext = uv_handle_t;

    template <typename U>
    class Resource
    {
    public:
        template <typename T>
        T* GetContext()
        {
            return reinterpret_cast<T*>(&context);
        }

    private:
        U context;
    };

    using StreamContext = uv_stream_t;
    using StreamReadCallback = Function<void(const String& data, int status)>;
    using StreamWriteCallback = Function<void(int status)>;

    template <typename U>
    class Stream : public Resource<U>
    {
    public:
        void Read(const StreamReadCallback& callback)
        {
            readCallback = callback;

            uv_read_start(
                this->template GetContext<StreamContext>(),

                [](ResourceContext* stream, UintSize recomendedSize, Buffer* buf)
                {
                    buf->len = 64; // Enough to contain common sequence
                    buf->base = new char[buf->len];

                    for (int i = 0; i < buf->len; ++i)
                        buf->base[i] = 0;
                },

                [](StreamContext* stream, IntSize result, const Buffer* buf)
                {
                    if (result < 0)
                    {
                        delete[] buf->base;
                    }

                    auto callback = reinterpret_cast<Stream*>(stream->data)->readCallback;

                    if (callback != nullptr)
                        callback(buf->base, result);

                    delete[] buf->base;
                }
            );
        }

        void StopReading() { uv_read_stop(this->template GetContext<StreamContext>()); }

        void Write(const String& buffer, const StreamWriteCallback& callback = nullptr)
        {
            struct Data 
            {
                Buffer buffer;
                StreamWriteCallback callback;
            };

            Data* data = new Data;
            data->buffer.base = new char[buffer.size()];
            data->buffer.len = buffer.size();
            data->callback = callback;

            uv_write_t* writeRequest = new uv_write_t;
            writeRequest->data = data;

            std::memcpy(data->buffer.base, buffer.data(), buffer.size());

            uv_write(
                writeRequest, this->template GetContext<StreamContext>(), &data->buffer, 1,
                [](uv_write_t* writeRequest, int status)
                {
                    auto data = reinterpret_cast<Data*>(writeRequest->data);

                    if (data->callback)
                        data->callback(status);

                    delete data->buffer.base;
                    delete data;
                    delete writeRequest;
                }
            );
        }

    private:
        StreamReadCallback readCallback;
    };

    using TTYContext = uv_tty_t;

    enum class TTYMode
    {
        Normal = UV_TTY_MODE_NORMAL,
        Raw = UV_TTY_MODE_RAW,
        IO = UV_TTY_MODE_IO,
    };

    class TTY final : public Stream<TTYContext>
    {
    public:
        TTY(Loop& loop, int fd, bool readable = true)
        {
            uv_tty_init(loop.GetContext(), GetContext<TTYContext>(), fd, readable);
            GetContext<TTYContext>()->data = this;
        }

        void SetMode(TTYMode mode) { uv_tty_set_mode(GetContext<TTYContext>(), static_cast<uv_tty_mode_t>(mode)); }

        void ResetMode() { uv_tty_reset_mode(); }

        const Vector2& GetSize()
        {
            uv_tty_get_winsize(GetContext<TTYContext>(), &size.x, &size.y);
            return size;
        }

    private:
        Vector2 size;
    };
}
