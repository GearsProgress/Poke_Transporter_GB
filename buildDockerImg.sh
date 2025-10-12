#!/bin/bash
mkdir -p docker-build && cd docker-build
docker build -t ptgb-builder:latest -f ../Dockerfile .
cd .. && rm -rf docker-build

