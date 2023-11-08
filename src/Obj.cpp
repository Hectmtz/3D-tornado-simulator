#include "../include/Obj.hpp"
#include <fstream>

using namespace std;

Obj::Obj()
{

}

void Obj::setObject(string file, double r, double g, double b)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->file = file;
    this->load();
    //this->calculate_normals();
}

void Obj::load()
{
    string line;    
    
    ifstream archivoOBJ(this->file);

    while (getline(archivoOBJ, line))
    {
        vector<string> elems = split(line, " ");
        if(!elems.empty())
        {
            if(elems[0] == "v")
            {
                double x = stod(elems[1]);
                double y = stod(elems[2]);
                double z = stod(elems[3]);
                Vertex v(x, y, z);
                this->vertices.push_back(v);
            }
            if(elems[0] == "f")
            {
                vector<int> indices = {};
                edges.clear();
                
                for(int i = 1; i < elems.size(); i++)
                {
                    string v = split(elems[i],"/")[0];
                    unsigned long ind_v = stol(v)-1;
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
    archivoOBJ.close();
}
