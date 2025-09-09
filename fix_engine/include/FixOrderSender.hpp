#pragma once

#include "FIXMessageOrder.hpp"
#include "fix_order.grpc.pb.h"

#include <grpcpp/grpcpp.h>
#include <memory>

class FixOrderSender 
{
public:
    FixOrderSender(std::shared_ptr<grpc::Channel> channel);

    bool SendOrder(const FIXMessageOrder& order);

private:
    std::unique_ptr<fixOrder::OrderReceiver::Stub> stub_;
};
