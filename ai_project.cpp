#include <iostream>
using namespace std;

#define mapLength 100
#define numOfParticle 50
#define robotPosition 1

//each array element has its own sensor value (which is a char)
char map[mapLength];

struct Particle {
    int position;
    double weight;
};

Particle particles[numOfParticle];

//robot value reflects its position
int robot = robotPosition;

int main(){
    for (int i = 1; i <= mapLength; i++)
    {
        cout<<i<<" ";
    }
    

    return 0;
}