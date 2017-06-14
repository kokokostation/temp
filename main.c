#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double EPS = 1e-6;

struct Dot
{
    double x, y;
};

struct Dot create_dot(double x, double y)
{
    struct Dot result;
    result.x = x;
    result.y = y;

    return result;
}

double cross(const struct Dot* a, const struct Dot* b)
{
    return a->x * b->y - a->y * b->x;
}

double dot(const struct Dot* a, const struct Dot* b)
{
    return a->x * b->x + a->y * b->y;
}

struct Dot uminus(const struct Dot* a)
{
    return create_dot(-a->x, -a->y);
}

struct Dot add(const struct Dot* a, const struct Dot* b)
{
    return create_dot(a->x + b->x, a->y + b->y);
}

struct Dot sub(const struct Dot* a, const struct Dot* b)
{
    struct Dot mb = uminus(b);
    return add(a, &mb);
}

double norm(const struct Dot* a)
{
    return sqrt(dot(a, a));
}

double angle(const struct Dot* a, const struct Dot* b)
{
    return acos(dot(a, b) / (norm(a) * norm(b))) * (cross(a, b) < 0 ? -1 : 1);
}

char in(const struct Dot* a, const struct Dot* polygon, int polygon_size)
{
    double angle_sum = 0;
    char on_line = 0;
    for(int i = 0; i < polygon_size; ++i)
    {
        struct Dot left = sub(polygon + i , a);
        struct Dot right = sub(polygon + (i + 1) % polygon_size, a);

        // border case hadling
        if( (norm(&left) < EPS || norm(&right) < EPS) || // a is a vertex
            (fabs(cross(&left, &right)) < EPS && dot(&left, &right) < 0)) // a lays on an edge
            return 0;

        angle_sum += angle(&left, &right);
    }

    return fabs(angle_sum) > EPS;
}

int main()
{
    int polygon_size, dots_num;

    scanf("%d %d", &polygon_size, &dots_num);

    struct Dot* polygon = (struct Dot*)malloc(polygon_size * sizeof(struct Dot));

    for(int i = 0; i < polygon_size; ++i)
        scanf("%lf %lf", &polygon[i].x, &polygon[i].y);

    for(int i = 0; i < dots_num; ++i)
    {
        struct Dot dot;
        scanf("%lf %lf", &dot.x, &dot.y);

        if(in(&dot, polygon, polygon_size))
            printf("YES\n");
        else
            printf("NO\n");
    }

    free(polygon);

    return 0;
}
