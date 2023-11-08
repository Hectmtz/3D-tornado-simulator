#ifndef OBJ_H
#define OBJ_H

#pragma once
#include "Models.hpp"

class Obj : public Models
{
    public:
        Obj();
        void setObject(string file, double r, double g, double b);
    private:
        void load();
};

#endif