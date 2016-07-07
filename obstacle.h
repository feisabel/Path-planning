#include <vector>
#include <iostream>
#include <map>
#include "point.h"

class Point;

using namespace std;

class Obstacle{

  public:
    Obstacle(){};
    Obstacle(vector<Point*> vertices, unsigned int height);
    ~Obstacle();
    
    void add_vertices(vector<Point*> vertices, unsigned int height);
    unsigned int get_num_vert(unsigned int height);
    Point* next_vertice(unsigned int height, int x, int y);
    Point* previous_vertice(unsigned int height, int x, int y);
    unsigned int get_numPlanes();
    vector<Point*> get_vertices(unsigned int height_search);
    vector<Point*> get_Allvertices();
    unsigned int get_height();
    map<int,vector<Point*> > get_vert_map();
    unsigned int find_plane(unsigned int);
    //debugging
    void print_num_vertices(void);
    
  private:
    unsigned int height_;
    map<int,vector<Point*> > vertices_;
    vector<unsigned int> planes_;
    
    
};
