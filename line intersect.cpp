#include <cmath>
const double eps = 1e-9;

struct node {double x, y;};

int sgn(double x) {return fabs(x) < eps ? 0 : x < 0 ? -1 : 1;}

double cross(node A, node B, node C)
{
    return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}

bool intersect(node A, node B, node C, node D)
{
    int a = sgn(cross(A, B, C) * cross(A, B, D));
    int b = sgn(cross(C, D, A) * cross(C, D, B));
    if (a <= 0 && b < 0) return true;
    if (a < 0 && b <= 0) return true;
    return false;
}
