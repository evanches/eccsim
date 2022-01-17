cmake_minimum_required(VERSION 3.12)

project(eccsim)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

set (ECCSIM_HDRS
  ConvolutionalCode.hpp
)

set (ECCSIM_SRCS
  ConvolutionalCode.cpp
  Simulator.cpp
)


add_executable(eccsim ${ECCSIM_SRCS})
