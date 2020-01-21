# Assignment 4
In this project we were asked to build a server which can support 10 clients in paralle.
The server recieves Clients and gets their problems and returns to the clients solutions in paralle.
in this project we focus on search problems, although our code is generic to any problem.
![1200px-Server-based-network svg](https://user-images.githubusercontent.com/46217802/72810934-4a0ebf80-3c67-11ea-993e-089e34746b16.png)
### How to compile?
```sh
g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
```
### How to run?
first:
```sh
./a.out 5600
```
### Note: 
after 2 minutes there will be time out because no client connected. in order to actually run this code with clients you can write code that creats clients which send problems to port 5600.
for example:
```sh
phython3 auto _client.py -vv
```
### Our github page:
https://github.com/nikolbashirsa/ex4
- this project has a serious amount of code and because of that this file will make everything clear to you.
### The main
```sh
namespace boot {
int main(int port){
//checking part 3
          part3(port);
            return 0;
}
}
```
### Part 3
```sh
part3(port);
```
 * building the searcher
 * building the solver
 * building cacheManager
 * building client handler
 * building serial Server
In this part we chose to run A* algorithm, because this it returnes the cheapest cost in comparison to the others (BFS,DFS,Best first search).
 ### Server
 ```sh
 virtual int open(int port, ClientHandler *client_handler) = 0;
  virtual int close(int port) = 0;
 virtual ~Server() = default;
  ```
### MySerialServer:
```sh
 # trying to connect to a client
  int open(int port, ClientHandler *client_handler);
#creating thread and solving the problem we get from the client using the client handle
    void start(int* sock, socklen_t * clil ,ClientHandler* client_handler);
#closing the socket
    int close(int port);
```

# MyClientHandler
```sh
    #  read line by line
    MyClientHandler(Solver<Searchable<Point> *, string> *solverIn, CacheManager<string, string> *cmIn);
  ```
  ```sh
    MyClientHandler(const MyClientHandler &);
    # read line by line
    void handleClient(int client_socket);
  ```
```sh
    # builds a string from the problem 
    MatrixMySearch *buildProblem();
 ``` 
 ```sh
 #edit the string in order to build problem
    string edit(string s);
 ```
  ```sh
  # building a matrix
    MatrixMySearch *buildMatrix(int rows, int cols);
 ```
 ```sh
  #deleting the elements in the deque
  void deleteDeque(deque<string> *deque);
ClientHandler *copy();
 string edit(string s)
 ```
 ### Solver
 ```sh
 template<class problem, class solution> class Solver {
 #solves the problem
 virtual solution solve(problem pb) = 0;
 #copies the object(deep copy)
virtual Solver *copy() = 0;
#destructor
 virtual ~Solver() = default;
 }
  ```
 ### CacheManager
  ```sh
      virtual bool isSolutionExist(problem p) = 0;
```
    virtual solution getSolution(problem p) = 0;
  ```sh
    virtual void saveSolution(problem p, solution *s) = 0;
```
 ```sh
    virtual CacheManager *copy() = 0;
```
  ```sh 
    virtual ~CacheManager() = default;
 ```
### FileCacheManager
knows in o(1) whether a problem has been solved before.
if so returns it, else the problem gets solved.
 ```sh
   # Constructor
    FileCacheManager(int capacityIn);
```
 ```sh
   # saving the solution in a file
    void saveToFile(string key, solution *obj);
```
 ```sh
    #saving a solution by inserting to the map and saving the solution in a file
    void saveSolution(string key, solution *obj) ;
 ```
 ```sh
     # returning a solution in the files
    solution getSolution(string key);
 ```
 ```sh
    virtual ~FileCacheManager();
```
 ```sh
    bool dataContaines(vector<string> data, string s);
```
 ```sh
    # searching a solution in the files
    bool fexists(const std::string &filename);
```
```sh
    # clone
    FileCacheManager *copy() ;
```
### Searcher
![astar](https://user-images.githubusercontent.com/46217802/72811037-7f1b1200-3c67-11ea-82d0-5de337c338f1.png)

Abstract class which contains Pointer to Searchable<T> .
The algorithm we will choose will be from this type.
```sh
    virtual solution search(Searchable<T> *searchable) = 0;
```
```sh
    virtual Searcher *copy() = 0;
```
```sh
    virtual int getNumberOfNodesEvaluated() = 0;
```
```sh
    Searchable<T> *getSearchable();
```
```sh
    void setSearchable(Searchable<T> *searchableIn);
```
```sh
    virtual ~Searcher() = default;
```
 ### CommonSearcher
```sh
    virtual solution search(Searchable<T> *searchable) = 0;
```
```sh
    virtual ~CommonSearcher();
```
```sh
    # returning the trace staring from the initial state until the goal state
    solution backTrace(State<T> *step);
```
```sh
   # return the direction we need to move from a step to another
    string getDirection(State<T> *step, State<T> *prev);
```
### SearchSolver
This class implements the solver interface by getting a searcher and solving a problem from type searchable.
```sh
    solution solve(problem pb);
```
```sh
 SearchSolver(Searcher<solution, T> *searcherIn) : searcher(searcherIn);
```
```sh
    SearchSolver(const SearchSolver &obj);
```
```sh
    Searcher<solution, T> *getSearcher();
```
```sh
    # clone
    SearchSolver *copy();
```
### MatrixMySearch
* read line by line
* when getting to last two lines get the point x,y of the first
* create searchable matrix
* call matrix constructor with start point end point
**Type**: Searchable<Point>
**private fields**:
    State<Point> *startState;
    State<Point> *goalState;
    Point *start;
    Point *destination;
    int rows;
    int columns;
    State<Point> ***matrixOfStates;
    deque <string> dequeStrings;
 ```sh
 #Constructor
    MatrixMySearch(const int rowsIn, const int columnsIn, deque <string> dequeStrings);
```
 ```sh
 # returns the start state in the matrix
    State<Point> *getInitialeState();
```
 ```sh
  # returns the goal state in the matrix
    State<Point> *getGoalState();
```
```sh
#entering all the valids neighbor states into a list nd returning it
    list<State<Point> *> createSuccessors(State<Point> *s);
```
```sh
    void initializeMatrix();
```
```sh
#removes spaces in line
    string edit(string s);
```
```sh
# returns the cost (x and y) of a state in the matrix
    double getCostInMatrix(int row, int col);
```
```sh
#Checks if this is the goal state
    bool isGoal(State<Point> *s);
```
```sh
    int *editcomma(string line);
```
```sh
 creating the initial and goal states according to the information we received from the client
    void initializeStates();
```
```sh
    std::pair<int, int> getLocationInSearchable(State<Point> *state);
```
```sh
    bool isValidState(State<Point> *s);
```
```sh
#   returns "";
    string noPath();
```
### Searchable
```sh
    virtual State<T> *getInitialeState() = 0;
```
```sh
    virtual State<T> *getGoalState() = 0;
```
```sh
    virtual list<State<T> *> createSuccessors(State<T> *s) = 0;
```
```sh
    virtual bool isGoal(State<T> *s) = 0;
```
```sh
    virtual std::pair<int, int> getLocationInSearchable(State<T> *state) = 0;
```
```sh
    virtual ~Searchable() = default;
```
### State
holds information about the components in the searchable clas
```sh
    bool Equals(State<T> *s);
```
```sh
    State(T stateIn, double costIn, double costTrailIn) : state(stateIn), cost(costIn), trailCost(costTrailIn);
```
```sh
    T getLocationT();
```
```sh
    void setCost(double costIn);
```
```sh
void setTrailCost(double costIn);
```
```sh
    double getCost();
```
```sh
    double getTrailCost();
```
```sh
    void setCameFRom(State<T> *cameFromIn);
```
```sh
    State<T> *getCameFRom();
```
```sh
    T getState() ;
```
```sh
    double getHeuristic();
```
```sh
    void setHeuristic(double heuristicIn);
```
### Point
Fields:
const int x;
const int y;
```sh
    Point getLocation();
```
```sh
    Point(const int xIn, const int yIn);
```
```sh
#returns true if thie points are equal.
    bool operator==(Point s);
```
```sh
    int getX();
```
```sh
    int getY();
```
### Astar
**inerClass**:
```sh
    class ComparatorAStar {
    public:
        virtual bool operator()(State<T> *left, State<T> *right);
        virtual ~ComparatorAStar() = default;
    };
```
**Functions**
```sh
   # looking for a path to the given goal state with the smallest cost
    solution search(Searchable<T> *searchable);
```
```sh
    # returns the number of nodes we visited in the algorithm
    int getNumberOfNodesEvaluated();
```
```sh
   # improving the path by changing the came from state of a node
   # void improvePath(State<T> *neighbour, State<T> *currentState, double possible_Trail, priority_queue<State<T> *, vector<State<T> *>, ComparatorAStar> *openPriority_queue);
```
```sh
# initializing a node after checking it's not in any vector/ priority queue
void notInOpenClose(State<T> *neighbour, State<T> *currentState, double possible_Trail, priority_queue<State<T> *, vector<State<T> *>, ComparatorAStar>*openPriority_queue, vector<State<T> *> *openCopy);    
```
```sh
# entering a node to the priority queue
 void enterToOpen(State<T> *neighbour,
priority_queue<State<T> *, vector<State<T> *>, ComparatorAStar> *openPriority_queue, vector<State<T> *> *openCopy);
```
```sh
# checking if a state is in the vector
 bool dataContaines(vector<State<T> *> data, State<T> *state);
```
```sh
# *removing a node from the vector
 void deleteFromOpen(State<T> *cur, vector<State<T> *> *openCopy);
```
```sh
 # setting heuristic
void setHeuristic(State<T> *neighbour, State<T> *goalState);
```
```sh
# updating the priority queue
priority_queue<State<T> *, vector<State<T> *>, ComparatorAStar>
updatePriorityQueqe(priority_queue<State<T> *, vector<State<T> *>, ComparatorAStar>enteredQueqe);
```
```sh
 # clone
 Astar *copy();
```
### BFS
```sh
 #looking for a path to the given goal state with the smallest cost
solution search(Searchable<T> *searchable);
```
```sh
# clone
```
```sh
 BFS *copy();
```
```sh
# returns the number of nodes we visited in the algorithm
    int getNumberOfNodesEvaluated();
 ```
 ### BestFirstSearch
**innerClass**:
    class MyComperator {
    public:
        bool operator()(State<T> *left, State<T> *right);
    };
 ```sh
 # entering a node to the priority queue and the vector
    void
    addToOpenList(State<T> *state, priority_queue<State<T> *vector<State<T> *>, MyComperator> *openPriority_queue,
 vector<State<T> *> *statesInOpenPriority);
```
```sh
# removing from the open list because we finished processing this node's information
    State<T> *popOpenList(priority_queue<State<T> *, vector<State<T> *>,MyComperator> *openPriority_queue);
```
```sh
# checking if a state is in the vector (meaning in the open priority queue)
    bool openContaines(State<T> *state, vector<State<T> *> statesInOpenPriority);
```
```sh
# looking for a path to the given goal state with the smallest cost
    solution search(Searchable<T> *searchable);
```
```sh
# checking if a state is in the closed vector
    bool closedCOntaines(State<T> *s, vector<State<T> *> closed);
```
```sh
#returns the number of nodes we visited in the algorithm
    int getNumberOfNodesEvaluated() ;
```
```sh
# updating the priority queue
    priority_queue<State<T> *, vector<State<T> *>, MyComperator>
    updatePriorityQueqe(priority_queue<State<T> *, vector<State<T> *>, MyComperator> enteredQueqe);
```
```sh
# clone
    BestFirstSearch *copy();
```
### DFS
```sh
# looking for a path to the given goal state with the smallest cost
    solution search(Searchable<T> *searchable);
```
```sh
# iterating over the visited vector in order to see if a certain state is already in it
    bool checkIfVisitedContains(vector<State<T> *> visited, State<T> *curState);
```
```sh
#clone
    DFS *copy();
```
```sh
#returns the number of nodes we visited in the algorithm**/
    int getNumberOfNodesEvaluated();
```
