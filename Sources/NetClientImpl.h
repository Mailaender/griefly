#pragma once

#include "NetInterface.h"

#include <queue>
#include <memory>

#include <SDL_net.h>

class NetClient: public INetClient
{
public:
    static NetClient* Init(Manager* man);

    virtual bool Connect(const std::string& ip, unsigned int port, LoginData data) override;
    virtual bool Disconnect() override;
    virtual bool Reconnect() override;

    virtual bool Process() override;

    virtual bool Ready() override;
    virtual bool Recv(Message* msg) override;
    virtual bool Send(const Message& msg) override;
    virtual bool IsFail() override;
private:
    NetClient() {}
    std::string ip_;
    unsigned int port_;
    LoginData data_;

    TCPsocket* main_socket_;

    std::queue<Message> messages_;
    unsigned int number_last_message_;

    unsigned int amount_ticks_;

    bool connected_;
    bool fail_;
    bool ready_;

    unsigned int hash_;

    Manager* man_;
};