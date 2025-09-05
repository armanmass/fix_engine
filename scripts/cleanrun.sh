#!/bin/bash
set -e
echo "Starting clients..."
rm -rf ./client_simulator/tmp
./venv/bin/python3.12 client_simulator/run_clients.py