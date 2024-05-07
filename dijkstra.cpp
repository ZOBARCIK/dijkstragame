//cpp file to implement dijkstra algorithm
//trying out my PLC project before implementing it with ST and ladder logic

#include<iostream>
#include<cstdlib>
#include<string>
using namespace std;

//notes:
// modify it two show equally short multiple paths if they exist


//********** global variables
int D = 12; //number of doors
int source= 0; //source node(starting room index is 0), this index to be updated to players location everytime he makes a move, hence recalculation, destination room is to be always room 12(index 11)
int inf = 9999;
int dist[12]; //distance array to the source node
bool checked[12]={0}; //whether if the nodes are checked, initially all unchecked
int parent[12]; //parent node of the current node, previous door

// weight matrix of the grid, distance of each node to its neighbors
int weight[12][12] = {
    //1  2  3  4  5  6  7  8  9  10  11 12
    {0, 1, inf, 1, inf, inf, inf, inf, inf, inf, inf, inf}, //1
    {1, 0, 1, inf, 1, inf, inf, inf, inf, inf, inf, inf}, //2
    {inf, 1, 0, inf, inf, 1, inf, inf, inf, inf, inf, inf}, //3
    {1, inf, inf, 0, 1, inf, 1, inf, inf, inf, inf, inf}, //4
    {inf, 1, inf, 1, 0, 1, inf, 1, inf, inf, inf, inf}, //5
    {inf, inf, 1, inf, 1, 0, inf, inf, 1, inf, inf, inf}, //6
    {inf, inf, inf, 1, inf, inf, 0, 1, inf, 1, inf, inf}, //7
    {inf, inf, inf, inf, 1, inf, 1, 0, 1, inf, 1, inf}, //8
    {inf, inf, inf, inf, inf, 1, inf, 1, 0, inf, inf, 1}, //9
    {inf, inf, inf, inf, inf, inf, 1, inf, inf, 0, 1, inf}, //10
    {inf, inf, inf, inf, inf, inf, inf, 1, inf, 1, 0, 1}, //11
    {inf, inf, inf, inf, inf, inf, inf, inf, 1, inf, 1, 0}, //12
};


void printables();
void init();
int getClosest();
void algorithm();

int main(void)
{
    system("cls");
    init();
    algorithm();
    printables();

    return 0;
}

//print the results
void printables(){
    cout<<"PLC Project preview, Dijkstra's Algorithm\n";
    cout<<"Number of doors: "<<D<<"\n";
    cout<<"Source node:"<<source<<" Room number:"<< to_string(source+1)<<"\n";
    cout << "\n";
    cout<<"Weight Matrix: "<<"\n";
    for(int i=0; i<D; i++)
    {
        for(int j=0; j<D; j++)
        {
            cout << weight[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    cout<<"Distance\t Room:\t\t Path:\n";
    cout << "------------------------------------------\n";

    for(int i=0; i<D; i++)
    {
        cout << dist[i] << "\t\t" << i+1 << "\t\t"; //room and distance
        cout << "<--" << i<<" "; //path

        int prevroom = parent[i];
        while(prevroom != source)
        {
            cout << "<--" << prevroom << " ";
            prevroom = parent[prevroom];
        }
        cout << "\n";

    }
    system("start grid.png");

}

//set all distances to infinity except the source node
void init() 
{
    for(int i=0; i<D; i++)
    {
        dist[i] = inf;
    }
    dist[source] = 0;
}

// get the closest node to the source node 
int getClosest() {
    int min_dist=inf;
    int closenode;
    for(int i=0; i<D; i++)
    {
        if ( !checked[i] && dist[i]<min_dist)
                {
                    min_dist = dist[i];
                    closenode = i;
                }           
    }
    return closenode;   
}


void algorithm()
{

    for(int i=0; i<D; i++)
    {
        int closestnode = getClosest();
        checked[closestnode] = true;

        for(int nbr=0; nbr<D; nbr++)
        {
            if(weight[closestnode][nbr] != inf && dist[nbr] > dist[closestnode] + weight[closestnode][nbr])
            {
                dist[nbr] = dist[closestnode] + weight[closestnode][nbr];
                parent[nbr] = closestnode;
            }
           
        }
           
        }
    }


