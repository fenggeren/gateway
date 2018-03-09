//
// Created by HuanaoGroup on 2018/3/9.
//

#ifndef GATEWAY_NET_PACKET_CONFIG_H
#define GATEWAY_NET_PACKET_CONFIG_H

#define PORT_START 7289

#define SOCKET_TCP_BUFFER   16384
#define SOCKET_TCP_PACKET   (SOCKET_TCP_BUFFER - sizeof(tcp_head))

//#define SOCKET_UDP_BUFFER   16384
//#define SOCKET_UDP_PACKET   (SOCKET_UDP_BUFFER - sizeof)

typedef unsigned char byte;
typedef unsigned short word;

struct tcp_info
{
//    byte data_kind;             // 数据类型
//    byte check_code;            // 校验字段
    word packet_size;           // 数据大小
};

struct tcp_command
{
    word main_cmd_id;
    word sub_cmd_id;
};

struct tcp_head
{
    tcp_info    info;
    tcp_command command;
};

struct tcp_buffer
{
    tcp_head    head;
    byte        buffer[SOCKET_TCP_PACKET];
};

#endif //GATEWAY_NET_PACKET_H
