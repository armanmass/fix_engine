
add_executable(
    MatchingEngineServer
    MatchingEngineServer.cpp
    MatchingEngine.cpp
    OrderReceiver.cpp
)

target_link_libraries(
    MatchingEngineServer
    PRIVATE
        Common
        OrderBookLib
)
