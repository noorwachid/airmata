#pragma once

#include "Core/Container/Array.h"
#include "Core/Container/Function.h"
#include "Core/Container/String.h"
#include "Core/IO/LoopContext.h"
#include "Core/Integer.h"

namespace IO
{
    class FileSystem
    {
    public:
        using Context = uv_fs_t;
        using OpenFileCallback = Function<void(int fd)>;
        using ReadFileCallback = Function<void(const String& buffer)>;

        void OpenFile(const String& path, const OpenFileCallback& callback = nullptr);

        void ReadFile(int fd, UintSize rpc, const ReadFileCallback& callback);

    private:
        LoopContext* loopContext = nullptr;

        friend class Loop;
    };
}
