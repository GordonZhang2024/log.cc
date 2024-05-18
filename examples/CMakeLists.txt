cmake_minimum_required(VERSION 3.15)

project(log.cc-example)

add_executable(example src/log.cc src/main.cc)

target_include_directories(example
	PUBLIC
	src/
)
