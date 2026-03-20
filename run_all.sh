#!/bin/bash
mkdir -p results
for config in configs/*.xml; do
    echo "Running simulation for $config"
    ./build/src/financeSimulation $config
done
