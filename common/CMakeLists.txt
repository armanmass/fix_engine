add_library(Common INTERFACE)

target_include_directories(
    Common 
    INTERFACE 
        include
)

add_library(FIXOrderProto)

target_sources(
    FIXOrderProto
    PRIVATE
        protos/fix_order.proto
)


protobuf_generate(TARGET FIXOrderProto)

protobuf_generate(
    TARGET FIXOrderProto
    LANGUAGE grpc
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
    PLUGIN "protoc-gen-grpc=$<TARGET_FILE:gRPC::grpc_cpp_plugin>"
)

target_include_directories(
    FIXOrderProto
    PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}/protos 
)

target_link_libraries(
    FIXOrderProto 
    PUBLIC 
        gRPC::grpc++ 
        protobuf::libprotobuf
)

set_target_properties(FIXOrderProto PROPERTIES UNITY_BUILD OFF)

target_link_libraries(
    Common 
    INTERFACE 
        FIXOrderProto
)