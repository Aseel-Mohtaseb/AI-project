#include <iostream>
using namespace std;

#define mapLength 100
#define numOfParticles 50
// #define robotPosition 20
#define stepSize 1

//each array element has its own sensor value (which is a char)
char map[mapLength];

struct Particle {
    int position;
    int direction; // 0 means left and 1 means right
    double weight;
};

//set of particles
Particle particles[numOfParticles];

//robot value reflects its position
// int robot = robotPosition;

struct Robot {
    int robotPosition = 1;
    int robotDirection = 1; //to right
} robot;


//inital values
void setParticles(){
    for (int i = 1; i <= numOfParticles; i++)
    {
        particles[i].position = rand() % 100 + 1;
        particles[i].direction = rand() %2; //Either 0 or 1
        particles[i].weight = 1.0/numOfParticles; 
    }
}

void printParticlesDetails(){
    cout << "particles positions: ";
    for (int i = 1; i <= numOfParticles; i++)
    {
        cout <<particles[i].position << " ";
    }
    cout << endl;
    cout << "particles directions: ";
    for (int i = 1; i <= numOfParticles; i++)
    {
        cout <<particles[i].direction << " ";
    }
    cout << endl;
    cout << "particles weights: ";
    for (int i = 1; i <= numOfParticles; i++)
    {
        cout <<particles[i].weight << " ";
    }
    cout << endl << endl;
    
}
//i used charachter as sensor value
void setMap(){
    printParticlesDetails();
    for (int i = 1; i <= mapLength; i++)
    {
        map[i] = (rand() % 26) + 'A'; 
    }    
}

void printMap(){
    for (int i = 1; i <= mapLength; i++)
    {
        cout << map[i] << "  " << "|" << " ";
    }
    cout << endl;

    for (int i = 1; i <= mapLength; i++)
    {
        
        cout << i ;
        if(i<10)
            cout << " ";
        cout << " " << "|" << " ";
    }
    cout << endl;

    for (int i = 1; i < robot.robotPosition; i++){
        cout<<"     ";
    }
    cout << "R" << endl;

    int pNum;
    for (int i = 1; i <= mapLength; i++)
    {
        pNum = 0;
        for (int j = 1; j <= numOfParticles; j++)
        {
            if(particles[j].position == i)
                pNum++;
        }

        cout << pNum;
        if(pNum <=9)
            cout << " ";
        cout << " | ";
        
    }
    cout << endl << endl << endl;
}

void move(){
    if(robot.robotDirection == 1){
        robot.robotPosition += stepSize;

    }
    else{
        robot.robotPosition -+ stepSize;
    }
}

int main(){

    setParticles();
    setMap();
    printMap();


    //after move => printMap
    move();
    printMap();


    return 0;
}