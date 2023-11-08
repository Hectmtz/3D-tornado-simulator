#include "../include/Scene.hpp"

using namespace std;

Scene::Scene()
{
    tornado_1.setTornado(0.0, 0.0, 0.0);
    box_2.setBall(-0.9, -0.5, 0.0, 1.0, 1.0, 0.0);
    box_3.setBox(-0.9, -0.5, 0.0, 0.7, 0.4, 0.5);
    this->b2 = true;
    this->b3 = false;
    this->select_box = 1;
    this->e_angle = 0.0f;
    this->m_angle = 0.0f;
    this->height = -0.5;
    this->launch_trajectory = {};
    this->trajectory_index = 0;
    this->shooted = false;
}

int Scene::draw(GLFWwindow *window)
{
    arma::frowvec eye = {0.0, 0.0, 10.0};
    arma::frowvec camera = {0.0, 0.0, 0.0};
    //GLFWwindow *window;
    double Ia = 0.6;
    double Ip = 0.85;
    //Ip = intensidad de la fuente de luz
    
    if (!glfwInit())
    {
        cout << stderr << "Fallo al inicializar GLFW." << endl;
        getchar();
        return -1;
    }
    

    window = glfwCreateWindow(1024, 768, "Simulacion de tornado", NULL, NULL);
    if (window == NULL)
    {
        cout << stderr << "Error opening GLFW." << endl;
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    //  Proyecciones
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    float ar = width / height;

    glViewport(0, 0, width, height);
    glOrtho(-ar, ar, -1.0, 1.0, -20.0, 20.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    double b_angle = 0;
    bool starFlag = false;
    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        int state_4 = glfwGetKey(window, GLFW_KEY_ENTER);

        //
        tornado_1.draw(Ia, Ip, {0.0, 0.8, 0.8});
        if(b2 == true && starFlag == false)
        {
            box_3.draw(tr.S(0.0, 0.0, 0.0), Ia, Ip, {0.0, 0.8, 0.8});
            box_2.draw(tr.S(0.3, 0.3, 0.3) * tr.S(0.4, 0.4, 0.4), Ia, Ip, {0.0, 0.8, 0.8});
        }

        if(b3 == true && starFlag == false)
        {
            box_2.draw(tr.S(0.0, 0.0, 0.0), Ia, Ip, {0.0, 0.8, 0.8});
            box_3.draw(tr.S(0.15, 0.15, 0.15) * tr.S(0.4, 0.4, 0.4), Ia, Ip, {0.0, 0.8, 0.8});
        }

        int state_2 = glfwGetKey(window, GLFW_KEY_1);
        if(state_2 == GLFW_PRESS)
        {
            b2 = true;
            b3 = false;
        }

        int state_3 = glfwGetKey(window, GLFW_KEY_2);
        if(state_3 == GLFW_PRESS)
        {
            b2 = false;
            b3 = true;
        }
        
        if(state_4 == GLFW_PRESS)
        {
            starFlag = true;
            if(b2 == true)
            {
                box_2.draw(tr.S(0.0, 0.0, 0.0), Ia, Ip, {0.0, 0.8, 0.8});
                int s = start_ball(Ia, Ip, {0.0, 0.8, 0.8});
            }

            if(b3 == true)
            {
                box_3.draw(tr.S(0.0, 0.0, 0.0), Ia, Ip, {0.0, 0.8, 0.8});
                int s = start_box(Ia, Ip, {0.0, 0.8, 0.8});
            }
        }
        //

        glfwSwapBuffers(window);
        glfwPollEvents();
        int state_off = glfwGetKey(window, GLFW_KEY_O);
        if(state_off == GLFW_PRESS)
        {
            exit(0);
        }

    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             glfwWindowShouldClose(window) == 0);

    glfwTerminate();
    
    return 0;
}

int Scene::start_ball(double Ia, double Ip, arma::vec F)
{
    Transform tr;
    this->m_angle = (this->m_angle < 360.0) ? this->m_angle + 3.0 : 0.0;
    if(this->height < 0.75)
    {
        this->height += 0.005;
        transf = tornado_1.trMatrix() * tr.Ry(this->m_angle) * tr.T(-0.8, this->height, 0.0) * tr.S(0.3, 0.3, 0.3);
        vector<Face> box_1_faces = box_2.box_1.getFaces();
        for (Face f : box_1_faces)
        {
            arma::vec v = f.getEdges()[0].getVi().vec();
            arma::vec L = F - v;
            double dL = sqrt(powf(L[0],2) + powf(L[1],2) + powf(L[2],2));
            L = L / dL;
            double fatt = 1 / powf(dL, 2);


            arma::vec LNormalise = arma::normalise(L);
            //aplicar transformacion a la normal
            arma::Col<double> nhomg = {f.getNormal()[0], f.getNormal()[1], f.getNormal()[2], 1};
            arma::Mat<double> nt = transf * nhomg;
            arma::vec normal_transf = {nt[0]/nt[3], nt[1]/nt[3], nt[2]/nt[3]};
            double light = arma::dot(LNormalise, normal_transf);


            double I = Ia * this->box_2.box_1.getKa() + (fatt * Ip * this->box_2.box_1.getKd() * light);

            double r = this->box_2.box_1.getR() * I;
            double g = this->box_2.box_1.getG() * I;
            double b = this->box_2.box_1.getB() * I;

            glColor3f(r, g, b);
            glBegin(GL_POLYGON);
            // Recorrer los vértices de la cara
            for (Edge e : f.getEdges())
            {
                // Dibujar el objeto....
                arma::Col<double> vp = transf * e.getVi().h();
                glVertex3f(vp.at(0), vp.at(1), vp.at(2));
            }
            arma::Col<double> vp = transf * f.getEdges().back().getVf().h();
            glVertex3f(vp.at(0), vp.at(1), vp.at(2));
        }
        glEnd();
    }
    else
    {
        this->bandera_shoot = true;
        Vertex auxp(this->box_2.getX(), this->box_2.getY(), this->box_2.getZ());
        arma::Col<double> vp = transf * auxp.h();
        aux.setVertex(vp(0), vp(1), vp(2));
        shoot();
        this->box_1_pos.setVertex(this->launch_trajectory[this->trajectory_index].getX(),
                                this->launch_trajectory[this->trajectory_index].getY(),
                                this->launch_trajectory[this->trajectory_index].getZ());
        if(this->trajectory_index < this->launch_trajectory.size())
        {
            this->trajectory_index++;
        }

        transf = tr.T(this->box_1_pos.getX(), this->box_1_pos.getY(), this->box_1_pos.getZ()) * tr.S(0.3, 0.3, 0.3) * tr.S(0.4, 0.4, 0.4);

        vector<Face> box_1_faces = this->box_2.box_1.getFaces();
        for (Face f : box_1_faces)
        {
            arma::vec v = f.getEdges()[0].getVi().vec();
            arma::vec L = F - v;
            double dL = sqrt(powf(L[0],2) + powf(L[1],2) + powf(L[2],2));
            L = L / dL;
            double fatt = 1 / powf(dL, 2);


            arma::vec LNormalise = arma::normalise(L);
            //aplicar transformacion a la normal
            arma::Col<double> nhomg = {f.getNormal()[0], f.getNormal()[1], f.getNormal()[2], 1};
            arma::Mat<double> nt = transf * nhomg;
            arma::vec normal_transf = {nt[0]/nt[3], nt[1]/nt[3], nt[2]/nt[3]};
            double light = arma::dot(LNormalise, normal_transf);


            double I = Ia * this->box_2.box_1.getKa() + (fatt * Ip * this->box_2.box_1.getKd() * light);

            double r = this->box_2.box_1.getR() * I;
            double g = this->box_2.box_1.getG() * I;
            double b = this->box_2.box_1.getB() * I;

            glColor3f(r, g, b);
            glBegin(GL_POLYGON);
            // Recorrer las aristas de la cara
            for (Edge e : f.getEdges())
            {
                // Dibujar la cara....
                arma::Col<double> vp = transf * e.getVi().h();
                glVertex3f(vp.at(0), vp.at(1), vp.at(2));
            }
            arma::Col<double> vp = transf * f.getEdges().back().getVf().h();
            glVertex3f(vp.at(0), vp.at(1), vp.at(2));
        }
        glEnd();
        //fin dibujado de la bala del cañon
    }
    return 0;

}

int Scene::start_box(double Ia, double Ip, arma::vec F)
{
    Transform tr;
    this->m_angle = (this->m_angle < 360.0) ? this->m_angle + 3.0 : 0.0;
    if(this->height < 0.75)
    {
        this->height += 0.005;
        transf = tornado_1.trMatrix() * tr.Ry(this->m_angle) * tr.T(-0.8, this->height, 0.0) * tr.S(0.2, 0.20, 0.2);
        vector<Face> box_1_faces = box_3.box_1.getFaces();    
        glBegin(GL_POLYGON);
        for (Face f : box_1_faces)
        {
            arma::vec v = f.getEdges()[0].getVi().vec();
            arma::vec L = F - v;
            double dL = sqrt(powf(L[0],2) + powf(L[1],2) + powf(L[2],2));
            L = L / dL;
            double fatt = 1 / powf(dL, 2);


            arma::vec LNormalise = arma::normalise(L);
            //aplicar transformacion a la normal
            arma::Col<double> nhomg = {f.getNormal()[0], f.getNormal()[1], f.getNormal()[2], 1};
            arma::Mat<double> nt = transf * nhomg;
            arma::vec normal_transf = {nt[0]/nt[3], nt[1]/nt[3], nt[2]/nt[3]};
            double light = arma::dot(LNormalise, normal_transf);


            double I = Ia * this->box_3.box_1.getKa() + (fatt * Ip * this->box_3.box_1.getKd() * light);

            double r = this->box_3.box_1.getR() * I;
            double g = this->box_3.box_1.getG() * I;
            double b = this->box_3.box_1.getB() * I;

            glColor3f(r, g, b);
            // Recorrer los vértices de la cara
            for (Edge e : f.getEdges())
            {
                // Dibujar el objeto....
                arma::Col<double> vp = transf * e.getVi().h();
                glVertex3f(vp.at(0), vp.at(1), vp.at(2));
            }
            arma::Col<double> vp = transf * f.getEdges().back().getVf().h();
            glVertex3f(vp.at(0), vp.at(1), vp.at(2));
        }
        glEnd();
    }
    else
    {
        Vertex auxp(this->box_3.getX(), this->box_3.getY(), this->box_3.getZ());
        arma::Col<double> vp = transf * auxp.h();
        aux.setVertex(vp(0), vp(1), vp(2));
        shoot();
        
        this->box_1_pos.setVertex(this->launch_trajectory[this->trajectory_index].getX(),
                                this->launch_trajectory[this->trajectory_index].getY(),
                                this->launch_trajectory[this->trajectory_index].getZ());
        if(this->trajectory_index < this->launch_trajectory.size())
        {
            this->trajectory_index++;
        }

        transf = tr.T(this->box_1_pos.getX(), this->box_1_pos.getY(), this->box_1_pos.getZ()) * tr.S(0.2, 0.20, 0.2) * tr.S(0.4, 0.4, 0.4);

        vector<Face> box_1_faces = this->box_3.box_1.getFaces();
        glBegin(GL_POLYGON);
        for (Face f : box_1_faces)
        {
            arma::vec v = f.getEdges()[0].getVi().vec();
            arma::vec L = F - v;
            double dL = sqrt(powf(L[0],2) + powf(L[1],2) + powf(L[2],2));
            L = L / dL;
            double fatt = 1 / powf(dL, 2);


            arma::vec LNormalise = arma::normalise(L);
            //aplicar transformacion a la normal
            arma::Col<double> nhomg = {f.getNormal()[0], f.getNormal()[1], f.getNormal()[2], 1};
            arma::Mat<double> nt = transf * nhomg;
            arma::vec normal_transf = {nt[0]/nt[3], nt[1]/nt[3], nt[2]/nt[3]};
            double light = arma::dot(LNormalise, normal_transf);


            double I = Ia * this->box_3.box_1.getKa() + (fatt * Ip * this->box_3.box_1.getKd() * light);

            double r = this->box_3.box_1.getR() * I;
            double g = this->box_3.box_1.getG() * I;
            double b = this->box_3.box_1.getB() * I;

            glColor3f(r, g, b);
            // Recorrer las aristas de la cara
            for (Edge e : f.getEdges())
            {
                // Dibujar la cara....
                arma::Col<double> vp = transf * e.getVi().h();
                glVertex3f(vp.at(0), vp.at(1), vp.at(2));
            }
            arma::Col<double> vp = transf * f.getEdges().back().getVf().h();
            glVertex3f(vp.at(0), vp.at(1), vp.at(2));
        }
        glEnd();
    }
    return 0;

}


void Scene::shoot()
{
    this->bandera_shoot = true;
    Transform tr;
    Vertex p1(this->aux.getX(), this->aux.getY(), this->aux.getZ());
    if(this->aux.getZ() > 0)
    {
        arma::Mat<double> transf_1 = tr.T(this->aux.getX() -0.5, this->aux.getY() - 0.5, this->aux.getZ() - 0.5);
        arma::Col<double> vp = transf_1 * p1.h();
        Vertex p2(vp(0), vp(1), vp(2));
        transf_1 = tr.T(this->aux.getX() - 0.2, this->aux.getY() - 0.2, this->aux.getZ() - 0.2) * transf_1;
        Vertex p3(-vp(0), -vp(1), -0.8      );       
        this->launch_trajectory = box_3.box_1.bezier(p1, p2, p2, p3, 0.000008);
    }
    else
    {
        arma::Mat<double> transf_1 = tr.T(this->aux.getX() -0.5, this->aux.getY() - 0.5, this->aux.getZ() - 0.5);
        arma::Col<double> vp = transf_1 * p1.h();
        Vertex p2(vp(0), vp(1), vp(2));
        transf_1 = tr.T(this->aux.getX() - 0.2, this->aux.getY() - 0.2, this->aux.getZ() - 0.2) * transf_1;
        Vertex p3(vp(0), vp(1), 0.8);       
        this->launch_trajectory = box_3.box_1.bezier(p1, p2, p2, p3, 0.000008);
    }

}