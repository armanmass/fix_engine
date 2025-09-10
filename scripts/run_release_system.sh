#!/bin/bash
set -e

CURRENT_DIR=$(pwd)
SESSION="FIX_DistributedSystem"

if [ ! -f "database/tradesdb" ]; then
	echo "tradesdb doesn't exist, creating..."
	q database/create_new_db.q
fi

tmux kill-session -t $SESSION 2>/dev/null || true
tmux new-session -d -s $SESSION

tmux split-window -v -t $SESSION
tmux split-window -h -t $SESSION:0.0
tmux split-window -h -t $SESSION:0.2

tmux set -g pane-border-status top
tmux set -g pane-border-format "#{pane_index}: #{pane_title}"

tmux select-pane -t $SESSION:0.0 -T "FIX Engine"
tmux select-pane -t $SESSION:0.1 -T "Matching Engine"  
tmux select-pane -t $SESSION:0.2 -T "q Database Server"  
tmux select-pane -t $SESSION:0.3 -T "FIX Client Simulator"

tmux send-keys -t $SESSION:0.0 "cd '$CURRENT_DIR' && ./build/Release/fix_engine/src/FIXEngine" Enter
tmux send-keys -t $SESSION:0.2 "cd '$CURRENT_DIR' && q database/load_db_server.q" Enter
tmux send-keys -t $SESSION:0.1 "cd '$CURRENT_DIR' && sleep 2 && ./build/Release/matching_engine/src/MatchingEngineServer" Enter
tmux send-keys -t $SESSION:0.3 "cd '$CURRENT_DIR' && sleep 5 && echo 'Starting clients...' && rm -rf ./client_simulator/tmp && ./venv/bin/python3.12 client_simulator/RunClients.py" Enter

tmux attach-session -t $SESSION
