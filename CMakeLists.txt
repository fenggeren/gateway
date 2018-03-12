cmake_minimum_required(VERSION 3.10)
project(gateway)

set(CMAKE_CXX_STANDARD 14)


include_directories(class/client class/common class/net_work)

set(BOOST_ROOT "/usr/local/include/boost")
set(Boost_DEBUG ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

find_package(Boost COMPONENTS system REQUIRED)
if(Boost_FOUND)

    set(SOURCE_FILES main.cpp class/client/tcp_acceptor.cpp class/client/tcp_acceptor.h class/client/client_session.cpp class/client/client_session.h class/gateway_server.cpp class/gateway_server.h class/data_transfer_manager.cpp class/data_transfer_manager.h class/client/client_data_processor.cpp class/client/client_data_processor.h class/client/client_session_manager.cpp class/client/client_session_manager.h class/net_config.h class/common/log.cpp class/common/log.h class/net_work/net_receiver_buffer.cpp class/net_work/net_receiver_buffer.h class/common/timer_manager.cpp class/common/timer_manager.h class/net_config.cpp class/net_work/net_packet_config.h class/net_work/net_packet.cpp class/net_work/net_packet.h class/net_work/net_send_buffer.cpp class/net_work/net_send_buffer.h class/net_work/receive_packet_processor.cpp class/net_work/send_packet_processor.cpp class/net_work/send_packet_processor.h class/net_work/receive_packet_processor.h)
    add_executable(gateway ${SOURCE_FILES})
    target_link_libraries(gateway ${Boost_LIBRARIES})
    include_directories(${Boost_INCLUDE_DIRS})
endif()

