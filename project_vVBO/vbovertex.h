#pragma once
//#include <GL/glew.h>

struct vboVertex {
    struct Position{
        float x;
        float y;
        float z;
    } position;

    struct Normal{
        float x;
        float y;
        float z;
    } normal;

    struct Color{
        GLubyte r;
        GLubyte g;
        GLubyte b;
        GLubyte a;
    } color;
};
