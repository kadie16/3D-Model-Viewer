#pragma once
struct vboVertex {
    struct Position{
        float x;
        float y;
        float z;
    } position;

    struct Color{
        double r;
        double g;
        double b;
        double a;
    } color;
};
