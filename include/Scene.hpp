#ifndef SCENE_H
#define SCENE_H

#pragma once

#include "../include/Scene.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <armadillo>
#include <iostream>
#include "../include/Models.hpp"
#include "../include/Obj.hpp"
#include "../include/Ply.hpp"
#include "../include/Vertex.hpp"
#include "../include/Transform.hpp"
#include "../include/Tornado.hpp"
#include "../include/Box.hpp"
#include "../include/Ball.hpp"
#include <vector>

class Scene
 {
    private:
        Tornado tornado_1;
        Ball box_2;
        Box box_3;
        bool b2; 
        bool b3;
        int select_box;
        Transform tr;
        double e_angle;
        double m_angle;
        double height;
        vector<Vertex>launch_trajectory = {};
        int trajectory_index = 0;
        bool shooted;
        Vertex box_1_pos;
        void shoot();
        Vertex aux;
        arma::Mat<double> transf;
        bool bandera_shoot = false;
    public:
        Scene();
        int draw(GLFWwindow *window);
        int start_box(double Ia, double Ip, arma::vec F);
        int start_ball(double Ia, double Ip, arma::vec F);
 };

#endif