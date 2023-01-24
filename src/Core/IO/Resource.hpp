#pragma once

#include "Core/Container/Function.hpp"
#include "Core/Container/String.hpp"
#include "Core/IO/Loop.hpp"
#include "uv.h"

namespace IO {
    using ResourceContext = uv_handle_t;

    template <typename U>
    class Resource {
      public:
        template <typename T>
        T* getContext() {
            return reinterpret_cast<T*>(&context);
        }

      private:
        U context;
    };

    using StreamContext = uv_stream_t;
    using StreamReadCallback = Function<void(const String& data, int status)>;
    using StreamWriteCallback = Function<void(int status)>;

    template <typename U>
    class Stream : public Resource<U> {
      public:
        void read(const StreamReadCallback& callback) {
            readCallback = callback;
            uv_read_start(
                this->template getContext<StreamContext>(),

                [](ResourceContext* stream, UintSize recomendedSize, Buffer* buf) {
                    buf->len = 64; // Enough to contain common sequence
                    buf->base = new char[buf->len];

                    for (int i = 0; i < buf->len; ++i)
                        buf->base[i] = 0;
                },

                [](StreamContext* stream, IntSize result, const Buffer* buf) {
                    if (result < 0) {
                        delete[] buf->base;
                    }

                    auto callback = reinterpret_cast<Stream*>(stream->data)->readCallback;

                    if (callback != nullptr)
                        callback(buf->base, result);

                    delete[] buf->base;
                }
            );
        }

        void stopReading() {
            uv_read_stop(this->template getContext<StreamContext>()); 
        }

        void write(const String& data, const StreamWriteCallback& callback = nullptr) {
            writeCallback = callback;

            Buffer* buf = new Buffer;
            uv_write_t* writeRequest = new uv_write_t;
            buf->base = new char[data.size()];
            buf->len = data.size();

            std::memcpy(buf->base, data.data(), data.size());

            writeRequest->data = buf;

            uv_write(writeRequest, this->template getContext<StreamContext>(), buf, 1, [](uv_write_t* writeRequest, int status) {
                auto callback = reinterpret_cast<Stream*>(writeRequest->handle->data)->writeCallback;

                if (callback != nullptr)
                    callback(status);

                auto data = reinterpret_cast<Buffer*>(writeRequest->data);
                delete data->base;
                delete writeRequest;
            });
        }

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

    class TTY final : public Stream<TTYContext> {
      public:
        TTY(Loop& loop, int fd, bool readable = true) {
            uv_tty_init(loop.getContext(), this->template getContext<TTYContext>(), fd, readable);
            this->template getContext<TTYContext>()->data = this;
        }

        void setMode(TTYMode mode) { 
            uv_tty_set_mode(this->template getContext<TTYContext>(), static_cast<uv_tty_mode_t>(mode));
        }

        void resetMode() { uv_tty_reset_mode(); }

        const TTYSize& getSize() {
            uv_tty_get_winsize(this->template getContext<TTYContext>(), &size.width, &size.height);
            return size;
        }

      private:
        TTYSize size;
    };
}
