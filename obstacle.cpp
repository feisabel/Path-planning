/*-----------------------------------------------*/
/*  obstacle.cpp                                 */
/*  Obstacle class. Receive a list of vertices   */
/*  Leonardo Castilho                            */
/*  Start: June 15th                             */
/*-----------------------------------------------*/

#include "point.h"
#include "obstacle.h"


  Obstacle::Obstacle(vector<Point*>vertices, int height){
    //vertices_[0] = vertices;
    height_ = height;
  }
  
  Obstacle::~Obstacle(){

  }

  int Obstacle::get_num_vert(){
    return 0; //REMOVE
  }

  Point* Obstacle::next_vertice(int x, int y){
    return 0; //REMOVE
  }

  Point* Obstacle::previous_vertice(int x, int y){
    return 0; //REMOVE
  }
