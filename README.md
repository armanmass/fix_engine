# FIX Engine w/ Client Order Simulation, Order History, and Matching Engine

# WIP DEMO (Recording real demo this is outdated)
![demo](https://i.imgur.com/TZIh901.gif)

## Architecture
![architecture](https://i.imgur.com/uwrEFne.png)

## Status
### FIX Engine :white_check_mark:
### Client Sim :white_check_mark:
### Connect Clients to FIX Engine :white_check_mark:
### Matching Engine :white_check_mark:
### gRPC Connection :white_check_mark:
### Database :white_check_mark:

## Usage
Requires: tmux, conan, cmake 3.30.3, q (rest of dependencies are handled)
Clone repo and run these scripts in root, initial build may be long due to gRPC.
```bash
./scripts/release_build.sh
```
After building to run:
```bash
./scripts/run_release_system.sh
```
