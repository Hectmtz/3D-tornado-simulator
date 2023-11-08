#include "../include/Ply.hpp"
#include <fstream>
#include <cstring>

using namespace std;

Ply::Ply()
{

}

void Ply::setObject(string file, double r, double g, double b)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->file = file;
    this->load();
    //this->calculate_normals();
}

void Ply::load()
{
    this->numVertex = 0;
    this->numFaces = 0;
    this->contVertex = 0;
    bool bandera = false;

    string line;

    ifstream archivoPLY(this->file);

    while (getline(archivoPLY, line))
    {
        vector<string> elems = split(line, " ");
        if(!elems.empty())
        {
            if(strcasecmp(elems[0].c_str(), "element") == 0)
            {
                if(strcasecmp(elems[1].c_str(), "vertex") == 0)
                {
                    this->numVertex = stoi(elems[2]);
                }
                if(strcasecmp(elems[1].c_str(), "face") == 0)
                {
                    this->numFaces = stoi(elems[2]);
                }
            }

            if(strcasecmp(elems[0].c_str(), "end_header") == 0)
            {
                bandera = true;
                continue;
            }
            if (bandera == true)
            {
                if(contVertex < numVertex)
                {
                    double x = stod(elems[0]);
                    double y = stod(elems[1]);
                    double z = stod(elems[2]);
                    Vertex v(x, y, z);
                    this->vertices.push_back(v);
                    contVertex++;
                }
                else
                {
                    vector<int> indices = {};
                    edges.clear();
                    
                    for(int i = 0; i < elems.size(); i++)
                    {
                        string v = elems[i];
                        unsigned long ind_v = stol(v);
                        indices.push_back(ind_v);
                    }
                    int lim = indices.size();
                    for (int i = 0; i < indices.size(); i++)
                    {
                        if(i == indices.size()-1)
                        {
                            Edge e(vertices[indices[i]], vertices[indices[0]]);
                            edges.push_back(e);
                        }
                        else
                        {
                            Edge e(vertices[indices[i]], vertices[indices[i+1]]);
                            edges.push_back(e);
                        }
                    }
                    Face f(edges);
                    this->faces.push_back(f);
                }
            }
            
        }
    }
    archivoPLY.close();
}