cmake_minimum_required(VERSION 3.29)
project(huffman_compression)

set(CMAKE_CXX_STANDARD 20)

add_executable(huffman_compression main.cpp
        HuffmanTree.cpp
        HuffmanTree.h
)
