//
// Created by HuanaoGroup on 2018/3/10.
//

#include "net_send_buffer.h"
#include "client_session.h"
#include "net_packet.h"
#include "log.h"

#define SEND_BUF_FIRST_ALLOC_CHUNKSIZE 4096
#define MAX_SEND_BUF_SIZE SEND_BUF_FIRST_ALLOC_CHUNKSIZE * 246

net_send_buffer::net_send_buffer(std::shared_ptr<client_session> session)
: client_session_(session),
  send_buffer_(nullptr),
  cur_write_buffer_(nullptr),
  send_buffer_used_(0),
  send_buf_allocated_(0),
  cur_write_buffer_used_(0),
  cur_write_buffer_allocated_(0),
  close_after_send_(false)
{

}

net_send_buffer::~net_send_buffer()
{
    if (send_buffer_)
    {
        std::free(send_buffer_);
        send_buffer_ = nullptr;
    }
    if (cur_write_buffer_)
    {
        std::free(cur_write_buffer_);
        cur_write_buffer_ = nullptr;
    }

}

void net_send_buffer::send_packet(word main_id, word sub_id, std::shared_ptr<net_packet> packet)
{
    size_t  size = packet->get_size() + sizeof(tcp_head);
    byte buffer[size];
    tcp_head* header = (tcp_head*)buffer;
    header->command.main_cmd_id = main_id;
    header->command.sub_cmd_id = sub_id;
    std::memmove(header + 1, packet->get_buffer(), packet->get_size());
    processor_data(buffer, size);
}

void net_send_buffer::processor_data(const byte *buffer, size_t size)
{
    while(get_send_buffer_left() < size)
    {
        if (!realloc_send_buffer())
        {
            return ;
        }
    }

    std::memcpy(send_buffer_ + send_buffer_used_, buffer, size);
    send_buffer_used_ += size;

    auto session = client_session_.lock();
    if (session)
    {
        async_send_data(session);
    }
}

void net_send_buffer::async_send_data(std::shared_ptr<client_session> session)
{
    if (!cur_write_buffer_used_)
    {
        std::swap(cur_write_buffer_, send_buffer_);
        std::swap(cur_write_buffer_allocated_, send_buf_allocated_);
        std::swap(cur_write_buffer_used_, send_buffer_used_);

        if (cur_write_buffer_used_)
        {
            boost::asio::async_write(session->get_socket(),
                        boost::asio::buffer(cur_write_buffer_, cur_write_buffer_used_),
                        [this, session](const boost::system::error_code& ec, std::size_t)
                                     {
                                         if (!ec)
                                         {
                                             cur_write_buffer_used_ = 0;
                                             async_send_data(session);
                                         }
                                     });
        }
        else if (close_after_send_)
        {
            session->close();
        }

    }

}

void net_send_buffer::send_data(const byte *data, size_t size)
{
    processor_data(data, size);
}

void net_send_buffer::send_after_close()
{
    close_after_send_ = true;
}

bool net_send_buffer::realloc_send_buffer()
{
    bool ret = false;
    size_t alloc_amount = send_buf_allocated_ * 2;
    if (!alloc_amount)
    {
        alloc_amount = SEND_BUF_FIRST_ALLOC_CHUNKSIZE;
    }
    if (alloc_amount > MAX_SEND_BUF_SIZE)
    {
        send_buf_allocated_ = 0;
        send_buffer_used_ = 0;
        alloc_amount = SEND_BUF_FIRST_ALLOC_CHUNKSIZE;
    }

    try
    {
        byte* tmp_buf = (byte*)std::realloc(send_buffer_, alloc_amount);
        if (tmp_buf)
        {
            send_buffer_ = tmp_buf;
            send_buf_allocated_ = alloc_amount;
            ret = true;
        }
        else
        {

        }

    }
    catch (std::exception& e)
    {

    }
    return ret;
}