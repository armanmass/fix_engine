add_executable(
    MatchingEngine
    MatchingEngine.cpp
)

target_link_libraries(
    MatchingEngine
    PRIVATE
        OrderBookLib
)