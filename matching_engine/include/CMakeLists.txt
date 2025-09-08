add_library(
    OrderBookLib
    STATIC
    ../src/OrderBook.cpp
)

target_include_directories(
    OrderBookLib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)