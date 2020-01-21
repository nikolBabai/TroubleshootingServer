cmake_minimum_required(VERSION 3.15)
project(exx4)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS -pthread)

add_executable(exx4 main.cpp Server.h ClientHandler.h Solver.h CacheManager.h StringReverser.cpp StringReverser.h FIleCacheManager.h MyTestClientHandler.cpp MyTestClientHandler.h MySerialServer.cpp MySerialServer.h MyClientHandler.cpp MyClientHandler.h Searchable.h State.h Point.h Searcher.h CommonSearcher.h BestFirstSearch.h MatrixMySearch.cpp MatrixMySearch.h SearchSolver.h  BFS.h DFS.h Astar.h MyParallelServer.h MyParallelServer.cpp)