#pragma once

#include "Core/Container/Array.h"
#include "Core/Container/Function.h"
#include "Core/Container/String.h"
#include "Core/IO/LoopContext.h"
#include "Core/Integral.h"

namespace IO
{
    using FileSystemContext = uv_fs_t;

    class FileSystem
    {
    public:
        using OpenFileCallback = Function<void(int fd)>;
        using ReadFileCallback = Function<void(const String& buffer)>;

        void OpenFile(const String& path, const OpenFileCallback& callback = nullptr);

        void ReadFile(int fd, usize rpc, const ReadFileCallback& callback);

    private:
        LoopContext* loopContext = nullptr;

        friend class Loop;
    };
}
