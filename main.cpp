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
        MatrixMySearch *checkMatrix() {
            const int rowsIn = 3;
            const int columnsIn = 3;
            deque<string> dequeStrings;
            dequeStrings.push_back("1,2,6");
            dequeStrings.push_back("4,5,1");
            dequeStrings.push_back("4,2,60");
            dequeStrings.push_back("0,0");
            dequeStrings.push_back("2,2");
            MatrixMySearch *m = new MatrixMySearch(rowsIn, columnsIn, dequeStrings);
            return m;
        }

        int main(int port) {
            /**
            // checking part 2
            // part2();
             **/
            // checking part 3
            part3();
            return 0;
        };

        void part2() {
            Solver<string, string> *solver = new StringReverser<string, string>();
            CacheManager<string, string> *cacheManager = new FileCacheManager<string>(0);
            ClientHandler *clientHandler = new MyTestClientHandler(solver, cacheManager);
            /*
            server_side::Server *serialServer = new MySerialServer();
            serialServer->open(8081, clientHandler);
             */
            server_side::Server * MyParallelServerIn = new MyParallelServer();
            MyParallelServerIn->open(5600, clientHandler);
        }

        void part3() {
            // building the searcher
           CommonSearcher<string, Point> *commonSearcher = new Astar<Point, string>();
            //CommonSearcher<string, Point> *commonSearcher = new BestFirstSearch<Point, string>();
          // CommonSearcher<string, Point> *commonSearcher = new DFS<Point, string>();
           //  CommonSearcher<string, Point> *commonSearcher = new BFS<Point, string>();

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
            //server_side::Server *serialServer = new MySerialServer();
            //serialServer->open(5600, clientHandler);

            server_side::Server * MyParallelServerIn = new MyParallelServer();
            MyParallelServerIn->open(5600, clientHandler);
            /*
            // building the searchable
            MatrixMySearch *m = checkMatrix();
            // solving the problem
            string sol = searcherBFS->search(m);
            cout << sol << endl;
            cout << searcherBFS->getNumberOfNodesEvaluated() << endl;
             */

        }
    };

}

int main(int argsc, char *argv[]) {
    boot::Main main;
    main.main(atoi(argv[1]));
}
