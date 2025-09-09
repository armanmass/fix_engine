#pragma once

#include "fix_order.grpc.pb.h"

class MatchingEngine;

class FixOrderReceiver final : public fixOrder::OrderReceiver::Service 
{
public:
    FixOrderReceiver(MatchingEngine& matchingEngine);

    grpc::Status SendOrder([[maybe_unused]] grpc::ServerContext* context, const fixOrder::FIXOrder* request, fixOrder::OrderReply* reply) override;

private:
    MatchingEngine& matchingEngine_;
};
