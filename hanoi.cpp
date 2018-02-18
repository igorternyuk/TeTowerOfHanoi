#include "hanoi.hpp"
#include <stack>
#include <iostream>

void tower_recursive(int height, int src, int dest, int tmp)
{
    if(height == 0) return;
    tower_recursive(height - 1, src, tmp, dest);
    std::cout << src << " --> " << dest << std::endl;
    tower_recursive(height - 1, tmp, dest, src);
}

void tower_interative(int height, int src, int dest, int tmp)
{
    std::stack<Tower> stack;
    stack.push({height, src, dest, tmp, 0});

    while(!stack.empty())
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
            ++curr_tower.state;
            stack.push({curr_tower.height - 1, curr_tower.tmp,
                        curr_tower.destination, curr_tower.source, 0});
            break;
        case 2:
            stack.pop();
            break;
        }
    }
}
