#ifndef __M_LOOPER_H__
#define __M_LOOPER_H__
#include <memory>
#include "buffer.hpp"
#include <condition_variable>
#include <memory>
#include <functional>
#include <thread>
#include <atomic>

namespace lwlog{
    using Functor=std::function<void(Buffer &)>;
    enum class AsyncType{
        ASYNC_SAFE,
        ASYNC_UNSAFE
    };
    class AsyncLooper
    {
    public:
        using ptr=std::shared_ptr<AsyncLooper>;
        AsyncLooper(const Functor &cb,AsyncType looper_type=AsyncType::ASYNC_SAFE) :
        _callback(cb), 
        _looper_type(looper_type),
        _stop(false)  {}
        ~AsyncLooper(){stop();}
        void stop()
        {
            _stop=true;//将退出标志设为true
            _cond_con.notify_all();//唤醒所有的工作线程
            _thread.join();
        }

        void push(const char *data,size_t len)
        {
            std::unique_lock<std::mutex> lock(_mutex);
            //条件变量控制，如果缓冲区剩余空间大小大于数据长度就可以添加数据
            if(_looper_type==AsyncType::ASYNC_SAFE)
                //阻塞条件：缓冲区中的可写容量大于我们的数据长度则可以添加数据
                _cond_pro.wait(lock,[&]{return _pro_buf.writeAbleSize()>len;});
            //走到这里说明可以向缓冲区添加数据
            _pro_buf.push(data,len);
            //只要生产者缓冲区中有数据，立马唤醒消费者线程来进行处理
            _cond_con.notify_all();
        }
    private:
        //线程入口函数--对消费缓冲区中的数据进行处理，处理完毕后，初始化缓冲区，交换缓冲区
        void threadEnter()
        {
            while(1)
            {
                {
                //1.判断缓冲区里是否有数据，有则交换，没有就阻塞
                std::unique_lock<std::mutex> lock(_mutex);
                //若当前缓冲区无数据，这时候再退出
                if(_stop&&_pro_buf.empty()) break;
                //若退出前被唤醒，或者有数据被唤醒，则返回真，继续向下运行，否则重新陷入休眠
                _cond_con.wait(lock,[&](){return _stop||!_pro_buf.empty();});
                //交换缓冲区
                _con_buf.swap(_pro_buf);
                //交换完缓冲区就可以唤醒生产者了
                _cond_pro.notify_all();
                }
                //消费者被唤醒后，对数据进行处理
                _callback(_con_buf);
                //初始化消费者缓冲区
                _con_buf.reset();
            }
        }

    private:
        std::atomic<bool> _stop;
        AsyncType _looper_type;
        Functor _callback;
        Buffer _pro_buf;
        Buffer _con_buf;
        std::thread _thread;
        std::condition_variable _cond_pro;
        std::condition_variable _cond_con;
        std::mutex _mutex;
        

    };
}
#endif