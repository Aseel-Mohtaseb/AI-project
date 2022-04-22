#include <iostream>
#include <cmath>
#include <time.h>
using namespace std;

#define mapLength 100
#define numOfParticles 50
#define stepSize 1

//each array element has its own sensor value (which is a char)
char map[mapLength];

struct Particle {
    int position;
    int direction; // 0 means left and 1 means right
    double weight;
    double cumulativeWeight;
};

//set of particles
Particle particles[numOfParticles];
Particle selectedParticles[numOfParticles];

//robot value reflects its position
// int robot = robotPosition;

struct Robot {
    int robotPosition = 30;
    int robotDirection = 1; //to right
} robot;


void calcCumulativeWeights(){
    // cout<<"\n\ntheir cumulative Weight: \n" ;
    for (int i = 1; i <= numOfParticles; i++)
    {
        particles[i].cumulativeWeight = particles[i].weight;
        for (int j = 1; j < i; j++)
        {
            particles[i].cumulativeWeight += particles[j].weight;
        }
        // cout<<"[" << i << " , " << particles[i].cumulativeWeight << "]" <<" ";
    }
    cout << endl;
}

//inital values
void setParticles(){
    for (int i = 1; i <= numOfParticles; i++)
    {
        particles[i].position = rand() % 100 + 1;
        particles[i].direction = rand() %2; //Either 0 or 1
        particles[i].weight = 1.0/numOfParticles;
    }
    calcCumulativeWeights();
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

void particleFilter(){
    calcCumulativeWeights();
    int sumOfWeights = 0;
    // Random numbers generated between 0 and 1:
    // srand( (unsigned)time( NULL ) );
    double randNum;
    // cout<<"\n\nrandom numbers generated: "<<endl;
    for (int i = 1; i <= numOfParticles; i++)
    {
        randNum = (double) rand()/RAND_MAX;
        // cout<<randNum<<" ";
        for (int j = 1; j <= numOfParticles; j++)
        {
            //1. select particle
            if(randNum <= particles[j].cumulativeWeight){
                selectedParticles[i] = particles[j];
                break;
            }
        }
        // printselectedParticles(); /////////

        //2. update position
        // rotate the particle if needed
        if ((selectedParticles[i].position == mapLength && selectedParticles[i].direction == 1) 
                || (selectedParticles[i].position == 1 && selectedParticles[i].direction == 0))
            {
                if (selectedParticles[i].direction == 1)        
                    selectedParticles[i].direction = 0; // Move it's direction to left
                else
                    selectedParticles[i].direction = 1; // Move it's direction to right
            }

        if(selectedParticles[i].direction == 1){
            selectedParticles[i].position += stepSize;
        }
        else {
            selectedParticles[i].position -= stepSize;
        }

        //3. update weight
        selectedParticles[i].weight = 26 -abs(map[robot.robotPosition] - map[selectedParticles[i].position]);
        // cout<<"selected weight: "<<selectedParticles[i].weight<<endl;
        sumOfWeights += selectedParticles[i].weight;
    }
            cout <<endl;

    //4. normalized weight
    for (int i = 1; i <= numOfParticles; i++)
    {
        selectedParticles[i].weight /= sumOfWeights;
        // cout<<"selected norm weight: "<<selectedParticles[i].weight<<endl;
    }
    
    //5. set the new selectedParticles[] as particles[] 
    for (int i = 1; i <= numOfParticles; i++)
    {
        particles[i] = selectedParticles[i];
    }
    
    
}

void move(){
    if ((robot.robotPosition == mapLength && robot.robotDirection == 1) || (robot.robotPosition == 1 && robot.robotDirection == 0))
    {
        cout << robot.robotPosition << ", " << robot.robotDirection << endl;
        cout<< "bbb" <<endl;
        if (robot.robotDirection == 1)        
            robot.robotDirection = 0; // Move it's direction to left
        else
            robot.robotDirection = 1; // Move it's direction to right

        
        for (int i = 1; i <= numOfParticles; i++)
        {
            // Update particles direction (rotate)
            if(particles[i].direction == 0)
                particles[i].direction = 1;
            else
                particles[i].direction = 0;
        }
                cout << robot.robotPosition << ", " << robot.robotDirection << endl;

    }

    if(robot.robotDirection == 1){
        robot.robotPosition += stepSize;
    }
    else{
        robot.robotPosition -= stepSize;
    }
    particleFilter();

}

void printselectedParticles(){
    cout << "\n\nweights of selected particles:"<< endl;
    for (int i = 1; i <= numOfParticles; i++)
    {
        cout<<selectedParticles[i].weight<<" ";
    }
}

void printOutput(){
    double mean = 0, standardDeviation = 0;
    for (int i = 1; i <= numOfParticles; i++)
    {
        mean += particles[i].position;
    }
    mean /= numOfParticles;

    for (int i = 1; i <= numOfParticles; i++)
    {
        standardDeviation += pow(particles[i].position - mean, 2);
    }

    standardDeviation /= numOfParticles;
    standardDeviation = sqrt(standardDeviation);
    
    cout << "Robot position: " << robot.robotPosition << "\t Mean: " << mean << "\t Standard deviation: "  << standardDeviation << endl << endl;

}

int main(){
    srand( (unsigned)time( NULL ) );

    setParticles();
    setMap();
    printMap();
    printOutput();

    //after move => printMap
    int i = 0;
    while (i<100)
    {
        move();
        printMap();
        printOutput();
        i++;
        // cout<<particles[5].weight<<" "<<particles[5].position<<" "<<particles[5].direction<<" "<<particles[5].cumulativeWeight;
    }
    
    

    // particlesWeight();

    return 0;
}