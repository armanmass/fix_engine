
add_executable(
    MatchingEngineServer
    MatchingEngineServer.cpp
    MatchingEngine.cpp
    FixOrderReceiver.cpp
)

target_sources(
    MatchingEngineServer
    PRIVATE
        ${CMAKE_SOURCE_DIR}/vendor/kdb/c.o
)

target_include_directories(
    MatchingEngineServer
    PRIVATE
        ${CMAKE_SOURCE_DIR}/vendor/kdb
)

target_link_libraries(
    MatchingEngineServer
    PRIVATE
        Common
        OrderBookLib
)
