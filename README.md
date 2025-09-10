# FIX Engine w/ Client FIX Message Simulation, Matching Engine, and Trade History Database

# [Click here for Demo](https://streamable.com/865u5w)

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

Clone repo and run these scripts in project root, initial build may be long due to gRPC.
```bash
./scripts/release_build.sh
```
After building to run:
```bash
./scripts/run_release_system.sh
```
