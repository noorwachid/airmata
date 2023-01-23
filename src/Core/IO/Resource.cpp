#include "Core/IO/Resource.h"

namespace IO {
    void Stream::read(const StreamReadCallback& callback) {
        readCallback = callback;
        uv_read_start(
            getContext(),

            [](ResourceContext* stream, size_t recomendedSize, Buffer* buf) {
                buf->len = 64; // Enough to contain common sequence
                buf->base = new char[buf->len];

                for (int i = 0; i < buf->len; ++i)
                    buf->base[i] = 0;
            },

            [](StreamContext* stream, ssize_t result, const Buffer* buf) {
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

    void Stream::stopReading() { uv_read_stop(getContext()); }

    void Stream::write(const String& bytes, const StreamWriteCallback& callback) {
        writeCallback = callback;

        uv_buf_t* buf = new uv_buf_t;
        uv_write_t* writeRequest = new uv_write_t;
        buf->base = new char[bytes.size()];
        buf->len = bytes.size();

        std::memcpy(buf->base, bytes.data(), bytes.size());

        writeRequest->data = buf;

        uv_write(writeRequest, getContext(), buf, 1, [](uv_write_t* writeRequest, int status) {
            auto callback = reinterpret_cast<Stream*>(writeRequest->handle->data)->writeCallback;

            if (callback != nullptr)
                callback(status);

            auto data = reinterpret_cast<uv_buf_t*>(writeRequest->data);
            delete data->base;
            delete writeRequest;
        });
    }

    TTY::TTY(Loop& loop, int fd, bool readable) {
        uv_tty_init(loop.getContext(), &context, fd, readable);
        context.data = this;
    }

    StreamContext* TTY::getContext() { return reinterpret_cast<StreamContext*>(&context); }

    void TTY::setMode(TTYMode mode) { uv_tty_set_mode(&context, static_cast<uv_tty_mode_t>(mode)); }

    void TTY::resetMode() { uv_tty_reset_mode(); }

    const TTYSize& TTY::getSize() {
        uv_tty_get_winsize(&context, &size.width, &size.height);
        return size;
    }

}
