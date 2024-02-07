#!/bin/bash

# Test script for running so_long with different maps

# List of map files
maps=("maps/invalidpath.ber" "maps/line_error.ber" "maps/map_collecterr.ber" "maps/invalid_exit.ber" \
	"maps/map_exiterr.ber" "maps/map_wallerr.ber"  "maps/invalidchar.ber" "textures/0.xpm")

for map_file in "${maps[@]}"; do
    echo "Running so_long with map: $map_file"
    ./so_long "$map_file"
    echo "---------------------------"
done
