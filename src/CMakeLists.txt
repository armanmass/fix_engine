add_executable(
    FIXEngine
    main.cpp
)

target_link_libraries(
    FIXEngine
    PRIVATE
        FIXEngineLib    
)