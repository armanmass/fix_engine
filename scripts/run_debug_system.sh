#!/bin/bash
# TODO: UPDATE
set -e

CURRENT_DIR=$(pwd)

tmux kill-session -t FIX_DistributedSystem 2>/dev/null || true

tmux new-session -d -s FIX_DistributedSystem
tmux split-window -v -t FIX_DistributedSystem
tmux split-window -h -t FIX_DistributedSystem:0.0

tmux set -g pane-border-status top
tmux set -g pane-border-format "#{pane_index}: #{pane_title}"

tmux select-pane -t FIX_DistributedSystem:0.0 -T "FIX Engine"
tmux select-pane -t FIX_DistributedSystem:0.1 -T "Matching Engine"  
tmux select-pane -t FIX_DistributedSystem:0.2 -T "Client Simulator"

tmux send-keys -t FIX_DistributedSystem:0.0 "cd '$CURRENT_DIR' && ./build/Debug/fix_engine/src/FIXEngine" Enter
tmux send-keys -t FIX_DistributedSystem:0.1 "cd '$CURRENT_DIR' && ./build/Debug/matching_engine/src/MatchingEngineServer" Enter
tmux send-keys -t FIX_DistributedSystem:0.2 "cd '$CURRENT_DIR' && sleep 12 && echo 'Starting clients...' && rm -rf ./client_simulator/tmp && ./venv/bin/python3.12 client_simulator/RunClients.py" Enter

tmux attach-session -t FIX_DistributedSystem