#/bin/sh

mkdir -p cpp
protoc --cpp_out=cpp *.proto
