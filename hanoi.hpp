#ifndef HANOI_H
#define HANOI_H

struct Tower
{
    int height;
    int source;
    int destination;
    int tmp;
    int state;
};

void tower_recursive(int height, int src, int dest, int tmp);
void tower_interative(int height, int src, int dest, int tmp);

#endif // HANOI_H
