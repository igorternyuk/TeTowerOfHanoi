#include "hanoi.hpp"
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <stack>

enum
{
    WINDOW_WIDTH = 900,
    WINDOW_HEIGHT = 480,
    TIMER_DELAY = 300,
    NUM_RODS = 3,
    RING_RADIUS_MAX = WINDOW_WIDTH / 6,
    RING_HEIGHT = 20,
    GAP_BETWEEN_RINGS = 5
};

std::stack<Tower> stack;
std::vector<int> rings[NUM_RODS];
int tower_height_max {0};
int rod_height {0};

void init_tower(int height, int src, int dest, int tmp)
{
    tower_height_max = height;
    rod_height = GAP_BETWEEN_RINGS + (RING_HEIGHT + GAP_BETWEEN_RINGS) * height;
    stack.push({height, src, dest, tmp, 0});
    for(int i{0}; i < height; ++i)
        rings[src].push_back(i);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    for(int i{0}; i < NUM_RODS; ++i)
    {
        //Rod

        int curr_rod_center { WINDOW_WIDTH / 6 + i * WINDOW_WIDTH / 3 };
        glColor3f(1,0,0);
        glLineWidth(3);
        glBegin(GL_LINE_STRIP);
            glVertex2f(curr_rod_center, WINDOW_HEIGHT);
            glVertex2f(curr_rod_center, WINDOW_HEIGHT - rod_height);
        glEnd();

        //Rings

        glLineWidth(1);
        glColor3f(1,1,0);

        for(size_t j{0}; j < rings[i].size(); ++j)        {

            size_t curr_ring_y { WINDOW_HEIGHT - j * RING_HEIGHT };
            int curr_ring_radius { RING_RADIUS_MAX -  rings[i][j] * RING_RADIUS_MAX / tower_height_max };
            glBegin(GL_QUADS);
                glVertex2f(curr_rod_center - curr_ring_radius, curr_ring_y - RING_HEIGHT);
                glVertex2f(curr_rod_center + curr_ring_radius, curr_ring_y - RING_HEIGHT);
                glVertex2f(curr_rod_center + curr_ring_radius, curr_ring_y - 5);
                glVertex2f(curr_rod_center - curr_ring_radius, curr_ring_y - 5);
            glEnd();
        }
    }
    glutSwapBuffers();
}

void timer(int = 0)
{
    if(!stack.empty())
    {
        Tower &curr_tower = stack.top();
        switch (curr_tower.state) {
        case 0:
            if(curr_tower.height == 0)
                stack.pop();
            else
            {
                ++curr_tower.state;
                stack.push({curr_tower.height - 1, curr_tower.source,
                            curr_tower.tmp, curr_tower.destination, 0});
            }
            break;
        case 1:
            std::cout << curr_tower.source << " --> " << curr_tower.destination << std::endl;
            rings[curr_tower.destination].push_back(*rings[curr_tower.source].rbegin());
            rings[curr_tower.source].pop_back();
            ++curr_tower.state;
            stack.push({curr_tower.height - 1, curr_tower.tmp,
                        curr_tower.destination, curr_tower.source, 0});
            break;
        case 2:
            stack.pop();
            break;
        }
        display();
        glutTimerFunc(TIMER_DELAY, timer, 0);
    }
}

int main(int argc, char *argv[])
{
    /*std::cout << "Recursive algorithm: " << std::endl;
    tower_recursive(3, 1, 2, 3);
    std::cout << "Iterative algorithm: " << std::endl;
    tower_interative(3, 1, 2, 3);*/
    init_tower(5, 0, 2, 1);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Tower of Hanoi!");
    glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,WINDOW_WIDTH, WINDOW_HEIGHT,0,-1,1);
    glutDisplayFunc(display);
    glutTimerFunc(TIMER_DELAY, timer, 0);
    glutMainLoop();
    return 0;
}
