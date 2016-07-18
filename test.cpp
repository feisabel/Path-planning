/*-----------------------------------------------*/
/*  test.cpp                                     */
/*  Main program to run and test partial parts   */
/*  Leonardo Castilho                            */
/*  Start: June 15th                             */
/*-----------------------------------------------*/

#include "boost/config.hpp"
#include "boost/graph/graph_traits.hpp"
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/dijkstra_shortest_paths.hpp"
#include "boost/property_map/property_map.hpp"

#include <fstream>
#include <string>
#include <map>
#include "obstacle.h"
#include "point.h"
#include "plane.h"

using namespace std;

int main (){
    unsigned int option = 0, vertices_ = 0, planesInserted = 0, flag_planes = 0;
    double height;
    vector<double> total_planes;
    vector<Obstacle*> obstacles;
    map<double, Plane*> planes;
    Point* source_;
    Point* target_;
    
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, Point > Graph;
    typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;
    typedef boost::graph_traits<Graph>::edge_descriptor edge_t;
    //vector<double> graphsZs;
    //map<double, Graph> graphsMap;
    
    do{
        cout << endl;
        cout << "Select an option:" << endl;
        cout << "1 - Create a new obstacle" << endl;
        cout << "2 - Use default map" << endl; //Default map is drawn
        cout << "0 - Proceed" << endl;
        cin >> option;
        
        switch(option){
            case 0:{
                vector<double>::iterator it;
                int z;
                for (it = total_planes.begin() ; it != total_planes.end(); ++it) {
                    cout << "NEW PLANE" << endl;
                    z = *it;
                    Plane* plane = new Plane(z);
                    planes[z] = plane;
                    plane -> findObstaclesInPlane(obstacles);
                    plane -> lineSweep();
                }
                //                    plane -> findObstaclesInPlane(obstacles);
                //                    plane -> lineSweep();
                //                    vector<Segment*> edges_ = plane -> getEdges();
                //                    Graph myGraph;
                //
                //                    for(vector<Segment*>::iterator it = edges_.begin(); it != edges_.end(); it++) {
                //                        Point right = *(*it)->getRight();
                //                        Point left = *(*it)->getLeft();
                //                        vertex_t u = boost::add_vertex(right, myGraph);
                //                        vertex_t v = boost::add_vertex(left, myGraph);
                //                        boost::add_edge(u, v, myGraph);
                //                        cout << "Edge from: " << right.getX() << " "<< right.getY() << " "<< right.getZ() << " to: "<< left.getX() << " "<< left.getY()<< " "<< left.getZ() << endl;
                //                    }
                //                    graphsZs.push_back(z);
                //                    graphsMap[z] = myGraph;
                //                    planes.push_back(plane);
                
                
                
                break;
            }
                
            case 1:{
                do{
                    cout << "How many planes does this object have? ";
                    cin >> planesInserted;
                    if(planesInserted<2) cout << "An object of are non-zero must "
                        << "have at least 2 plane." << endl;
                }while(planesInserted < 2);
                flag_planes = 0;
                while(planesInserted > 1){
                    vector<Point*> vertices_input;
                    cout << endl << "Input for the new plane..." << endl;
                    do{
                        cout << "How many vertices does this plane have? ";
                        cin >> vertices_;
                        if(vertices_<3) cout << "An object of are non-zero must "
                            << "have at least 3 vertices." << endl;
                    }while(vertices_ < 3);
                    cout << "What is the height of these segments? ";
                    cin >> height;
                    while(vertices_ > 0){
                        double x, y;
                        cout << "Enter x y: ";
                        cin >> x;
                        cin >> y;
                        vertices_input.push_back(new Point(x,y));
                        vertices_ --;
                    }
                    if(flag_planes == 0){
                        obstacles.push_back(new Obstacle(vertices_input,height));
                        if(std::find(total_planes.begin(), total_planes.end(), height) != total_planes.end()) {
                            //vector of all planes already contains this height
                        } else {
                            total_planes.push_back(height);
                        }
                        flag_planes = 1;
                    }
                    else{
                        unsigned int height_ = obstacles[obstacles.size()-1]->add_vertices(vertices_input, height);
                        if(std::find(total_planes.begin(), total_planes.end(), height) != total_planes.end()) {
                            //vector of all planes already contains this height
                        } else {
                            total_planes.push_back(height_);
                        }
                    }
                    planesInserted--;
                    height = 0;
                }
                
                //cout << "Plane is " << obstacles[0]->find_plane(5) << endl;
                //obstacles[0]->print_num_vertices();
                break;
            }
                
            case 2:{
                vector<Point*> vertices_input;
                //First obstacle
                vertices_input.push_back(new Point(0,0));
                vertices_input.push_back(new Point(0,9));
                vertices_input.push_back(new Point(15,9));
                vertices_input.push_back(new Point(15,0));
                obstacles.push_back(new Obstacle(vertices_input,8));
                vertices_input.clear();
                
                vertices_input.push_back(new Point(3.2,2.2));
                vertices_input.push_back(new Point(3.2,6.7));
                vertices_input.push_back(new Point(11.2,6.7));
                vertices_input.push_back(new Point(11.2,2.2));
                obstacles[obstacles.size()-1]->add_vertices(vertices_input, 11);
                vertices_input.clear();
                
                //Second obstacle
                vertices_input.push_back(new Point(10,20));
                vertices_input.push_back(new Point(10,32));
                vertices_input.push_back(new Point(30,32));
                vertices_input.push_back(new Point(30,20));
                obstacles.push_back(new Obstacle(vertices_input,15));
                vertices_input.clear();
                
                vertices_input.push_back(new Point(10,24));
                vertices_input.push_back(new Point(10,32));
                vertices_input.push_back(new Point(24,32));
                vertices_input.push_back(new Point(24,24));
                obstacles[obstacles.size()-1]->add_vertices(vertices_input, 3);
                vertices_input.clear();
                
                total_planes.push_back(0);
                total_planes.push_back(8);
                total_planes.push_back(15);
                total_planes.push_back(18);
                total_planes.push_back(19);
                
                //---------DEBUG----REMOVE---------
                cout << endl << "Obstacle 1...";
                obstacles[0]->print_num_vertices();
                cout << endl << "Obstacle 2...";
                obstacles[1]->print_num_vertices();
                //---------------------------------
                
                //TEST PLANE
                //Plane* plane = new Plane(0);
                //plane -> findObstaclesInPlane(obstacles);
                //plane -> lineSweep();
                
                break;
            }
        }
        
    }while(option != 0 && option != 2);
    
    option = 0;
    do{ //Start menu
        //test
        cout << endl;
        cout << "Select an option:" << endl;
        cout << "1 - Number of obstacles" << endl;
        cout << "2 - Find shortest path" << endl;
        cout << "0 - Quit" << endl;
        cin >> option;
        
        switch(option){
                // =================== CASE 0 ===================
            case 0:{
                break;
            }
                // =================== CASE 1 ===================
            case 1:{
                cout << obstacles.size() << " object(s)." << endl << endl;
                break;
            }
                // =================== CASE 2 ===================
            case 2:{
                double sourceX, sourceY, sourceZ, targetX, targetY, targetZ;
                double highestZ;
                Graph myGraph;
                vector<Plane*> planesToGraph; //planes above that will be added to the graph
                
                cout << " What is the source point of the search? (x, y and z)" << endl;
                cin >> sourceX;
                cin >> sourceY;
                cin >> sourceZ;
                cout << " What is the target point of the search? (x, y and z)" << endl;
                cin >> targetX;
                cin >> targetY;
                cin >> targetZ;
                
                Point* source_ = new Point(sourceX, sourceY, sourceZ);
                Point* target_ = new Point(targetX, targetY, targetZ);
                
                //case 1
                if(sourceZ == targetZ){
                    //check if there is a plane in that z already
                    if(std::find(total_planes.begin(), total_planes.end(), sourceZ) != total_planes.end()) {
                        //if it is, just adds the point to the plane
                        Plane* plane = planes[sourceZ];
                        //plane -> addSourceAndTarget(source_, target_); //function to insert S and T to nodes and project the edges
                        planesToGraph.push_back(plane);
                    } else {
                        //if it is not, a plane in that Z coordinate must be created
                        Plane* plane = new Plane(sourceZ);
                        plane -> findObstaclesInPlane(obstacles);
                        plane -> lineSweep();
                        //plane -> addSourceAndTarget(source_, target_);
                        planesToGraph.push_back(plane);
                    }
                    highestZ = sourceZ;
                }
                else{
                    //case 2
                    if(sourceZ > targetZ){
                        highestZ = sourceZ;
                        Point* targetProjection = new Point(targetX, targetY, sourceZ);
                        //check if there is a plane in that z already
                        if(std::find(total_planes.begin(), total_planes.end(), sourceZ) != total_planes.end()) {
                            //if it is, just adds the point to the plane
                            
                            Plane* plane = planes[sourceZ];
                            //plane -> addSourceAndTarget(source_, targetProjection);
                            planesToGraph.push_back(plane);
                             //add edge connecting target and target projection to the graph
                        }//case 3
                        else {
                            //if it is not, a plane in that Z coordinate must be created
                            Plane* plane = new Plane(sourceZ);
                            plane -> findObstaclesInPlane(obstacles);
                            plane -> lineSweep();
                            //plane -> addSourceAndTarget(source_, targetProjection);
                            planesToGraph.push_back(plane);
                            //add edge connecting target and target projection to the graph
                        }
                    }
                    //case 4
                    else if(targetZ > sourceZ){
                        highestZ = targetZ;
                        Point* sourceProjection = new Point(sourceX, sourceY, targetZ);
                        //check if there is a plane in that z already
                        if(std::find(total_planes.begin(), total_planes.end(), targetZ) != total_planes.end()) {
                            //if it is, just adds the point to the plane
                             Plane* plane = planes[sourceZ];
                            //plane -> addSourceAndTarget(sourceProjection, target_);
                            planesToGraph.push_back(plane);
                            //add edge connecting source and source projection to the graph
                        }//case 5
                        else {
                            //if it is not, a plane in that Z coordinate must be created
                            Plane* plane = new Plane(targetZ);
                            plane -> findObstaclesInPlane(obstacles);
                            plane -> lineSweep();
                            //plane -> addSourceAndTarget(sourceProjection, target_);
                            planesToGraph.push_back(plane);
                            //add edge connecting source and source projection to the graph
                        }
                    }
                }
                
                
                //TO DO FIND SHORTEST PATH;
                break;
            }
                // ================== DEFAULT ===================
            default:{
                break;
            }
        }//End switch(option)
        
    }while(option != 0);//End menu
    
    
    
    //------ Free memory ----------
    Obstacle *deleting;
    while(obstacles.size() != 0){ //Delete items
        deleting = obstacles[obstacles.size()-1];
        delete deleting;
        obstacles.pop_back();
    }
    //-----------------------------
    
    
    
    return 0;
}
