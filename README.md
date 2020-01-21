# Assignment 4
In this project we were asked to build a server which can support 10 clients in paralle.
The server recieves Clients and gets their problems and returns to the clients solutions in paralle.
in this project we focus on search problems, although our code is generic to any problem.
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
