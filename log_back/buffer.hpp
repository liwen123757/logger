#ifndef __M_BUFFER_H__
#define __M_BUFFER_H__
#include <vector>
#include <iostream>
#include <assert.h>

#define INIT_BUFFER_SIZE (1*1024*1024)
#define THRESHOLD_BUFFER_SIZE (8*1024*1024)
#define INCRESE_BUFFER_SIZE (1*1024*1024)
namespace lwlog{
    class Buffer{
    public:
        Buffer():_buffer(INIT_BUFFER_SIZE),_writer_idx(0),_reader_idx(0) {}
        //向缓冲区中写入数据
        void Push(const char *data,size_t len)
        {   // 如果缓冲区容量不够则扩容
            ensureEnoughSize(len);
            //将数据拷贝进缓冲区
            std::copy(data,data+len,&_buffer[_writer_idx]);
            //将当前写入位置向后移
            movewrite(len);

        }
        size_t writeAbleSize()
        {
            return _buffer.size()-_writer_idx;
        }
        //获取可读数据起始地址
        const char* begin()
        {
            return &_buffer[_reader_idx];
        }
        size_t readAbleSize()
        {
            return (_writer_idx-_reader_idx);
        }
        void movereader(size_t len)
        {
            assert(len<readAbleSize());
            _reader_idx+=len;
        }
        void swap(Buffer &buffer)
        {
            _buffer.swap(buffer._buffer);
            std::swap(_reader_idx,buffer._reader_idx);
            std::swap(_writer_idx,buffer._writer_idx);
        }
        bool empty()
        {
            return (_reader_idx==_writer_idx);
        }
    private:
        void ensureEnoughSize(size_t len)
        {
            if(len<=writeAbleSize())
            {
                return;
            }
            size_t newsize=0;
            if(_buffer.size()<THRESHOLD_BUFFER_SIZE)
            {
                newsize=_buffer.size()*2+len;
            }
            else{
                newsize=_buffer.size()+INCRESE_BUFFER_SIZE+len;
            }
            _buffer.resize(newsize);
        }
        void movewrite(size_t len)
        {
            if((_writer_idx+len)<_buffer.size())
            {
                _writer_idx+=len;
            }
        }
    private:
        std::vector<char> _buffer;
        size_t _writer_idx;
        size_t _reader_idx;

    };
}


#endif
