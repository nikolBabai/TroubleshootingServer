#include <iostream>
#include <cstdlib>
#include "string"
#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include "StringReverser.h"
#include "MyTestClientHandler.h"
#include "FIleCacheManager.h"
#include "Server.h"
#include "MySerialServer.h"
#include "SearchSolver.h"
#include "Point.h"
#include "BestFirstSearch.h"
#include "MyClientHandler.h"
#include "MatrixMySearch.h"
#include "Astar.h"
#include "DFS.h"
#include "BFS.h"
#include "MyParallelServer.h"

namespace boot {
    class Main {
    public:
        int main(int port) {
            // checking part 3
            part3(port);
            return 0;
        };

        void part3(int port) {
            // building the searcher
         //  CommonSearcher<string, Point> *commonSearcher = new Astar<Point, string>();
            CommonSearcher<string, Point> *commonSearcher = new DFS<Point, string>();


            // building the solver
            Searcher<string, Point> *searcherBFS = commonSearcher;
            SearchSolver<Searchable<Point>*, string, Point> *searchSolver;
            searchSolver = new SearchSolver<Searchable<Point>*, string, Point>(
                    searcherBFS);
            Solver<Searchable<Point>*, string> *solver = searchSolver;

            // building cacheManager
            CacheManager<string, string> *cacheManager = new FileCacheManager<string>(0);

            // building client handler
            ClientHandler *clientHandler = new MyClientHandler(solver, cacheManager);

            // building serial Server
            server_side::Server * MyParallelServerIn = new MyParallelServer();
            MyParallelServerIn->open(port, clientHandler);
        }
    };

}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        boot::Main main;
        main.main(atoi(argv[1]));
    }
}
