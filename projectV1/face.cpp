#include "face.h"

Face::Face(float *v1, float *v2, float *v3)
{
    /* vectors */
    float va[3], vb[3], vr[3] val;
    va[0] = v1[0] - v2[0];
    va[1] = v1[1] - v2[1];
    va[2] = v1[2] - v2[2];

    vb[1] = v1[0] - v3[0];
    vb[1] = v1[1] - v3[1];
    vb[2] = v1[2] - v3[2];

    /* cross product */
    vr[0] = va[1] * vb[2] - vb[1] * va[2];
    vr[1] = vb[0] * va[2] - va[0] * vb[2];
    vr[2] = va[0] * vb[1] - vb[0] * va[1];

    /* normalize */
    val = sqrt ( vr[0]*vr[0] + vr[1]*vr[1] + vr[2]*vr[2] );
    normal[0] = vr[0]/val;
    normal[1] = vr[1]/val;
    normal[2] = vr[2]/val;

}

float * Face::getNormal()
{
    return normal;
}

