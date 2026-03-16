#ifndef __M_LOOPER_H__
#define __M_LOOPER_H__
#include <memory>

namespace lwlog{
    class AsyncLooper
    {
    public:
        using ptr=std::shared_ptr<AsyncLooper>;
    }
    ;
}
#endif