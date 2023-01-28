#include "Core/IO/Action.h"

namespace IO
{
    void FileSystem::OpenFile(const String& path, const OpenFileCallback& callback)
    {
        struct Data
        {
            OpenFileCallback callback;
        };

        Data* data = new Data();
        data->callback = callback;

        FileSystemContext* context = new FileSystemContext;
        context->data = data;

        uv_fs_open(
            loopContext, context, path.c_str(), O_RDONLY, 0,
            [](FileSystemContext* context)
            {
                Data* data = static_cast<Data*>(context->data);
                data->callback(context->result);

                delete data;
                delete context;
            }
        );
    }
    void FileSystem::ReadFile(int fd, UintSize rpc, const ReadFileCallback& callback)
    {
        struct Data
        {
            int fd;
            Buffer placeholder;
            String buffer;
            ReadFileCallback callback;

            static void OnRead(FileSystemContext* context)
            {
                Data* data = static_cast<Data*>(context->data);

                if (context->result <= 0)
                {
                    return data->callback(data->buffer);

                    delete data->placeholder.base;
                    delete data;
                    delete context;

                    return;
                }

                data->buffer.append(data->placeholder.base, data->placeholder.len);

                for (int i = 0; i < data->placeholder.len; ++i)
                    data->placeholder.base[i] = 0;

                uv_fs_read(context->loop, context, data->fd, &data->placeholder, 1, -1, OnRead);
            }
        };

        Data* data = new Data();
        data->fd = fd;
        data->placeholder.len = rpc;
        data->placeholder.base = new char[rpc];
        data->callback = callback;

        for (int i = 0; i < rpc; ++i)
            data->placeholder.base[i] = 0;

        FileSystemContext* context = new FileSystemContext;
        context->data = data;

        uv_fs_read(loopContext, context, fd, &data->placeholder, 1, -1, Data::OnRead);
    }
}
