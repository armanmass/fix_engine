#include "MatchingEngine.hpp"
#include "OrderReceiver.hpp"
#include <grpcpp/grpcpp.h>
#include <iostream>

void RunServer(MatchingEngine& matchingEngine) 
{
    std::string serverAddress("0.0.0.0:9787");
    OrderReceiverImpl service(matchingEngine);

    grpc::ServerBuilder builder;
    builder.AddListeningPort(serverAddress, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << serverAddress << std::endl;
    server->Wait();
}

int main() {
    MatchingEngine matchingEngine;
    RunServer(matchingEngine);
    return 0;
}
