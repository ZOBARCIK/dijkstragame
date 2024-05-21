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
int dest=11; // only wanted destination room
int inf = 9999;
int dist[12]; //distance array to the source node
bool checked[12]={0}; //whether if the nodes are checked, initially all unchecked
//int parent[12]; //parent node of the current node, previous door
int parent[166]; // 2D array parent[i][j] is parent[i*D + j] "i" is the destination node, "j" is the parent node
int parent_count[12]; // keeps track of how many parents each node has

int max_path_length = 144; // Maximum total length of all paths
int paths[144]; // Array to store all paths
int path_start[12] = {0}; // Array to store the start index of each path in the paths array
int path_end[12] = {0}; // Array to store the end index of each path in the paths array

int p_i = 0; // Index to keep track of the current position in the paths array


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


        //table print
    cout << "\n";
    cout<<"Distance\t\t Room:\t\t\t Path:\n";
    cout << "------------------------------------------\n";

//for(int i=0; i<D; i++)
    //{
        
        //     distance               room
        cout << dist[dest] << "\t\t\t" << dest+1 << "\t\t\t"; //room and distance


        int max_paths = 3; // Maximum number of paths
        int max_path_length = dist[dest]; // Maximum length of each path
        int path1[max_path_length]; // 2D array to store the path1
        int path2[max_path_length]; // 2D array to store the path2
        int path3[max_path_length]; // 2D array to store the path3
        int path_lengths[max_paths] = {0}; // Array to store the actual length of each path

        //print the path
        for(int j=0; j<parent_count[dest]; j++) //number of different paths equals to the number of parents
        {
            cout << dest << " "; // print which is the destination node
            int prevroom = parent[dest*D + j]; //prevroom is addressed at the chield node i-j
            int p_i = 0; //path index to keep track of the current position in the path array
            while(prevroom != source) //store the path in the arrays
            {
                if (j==0)
                {
                    path1[p_i] = prevroom;
                }
                else if (j==1)
                {
                    path2[p_i] = prevroom;
                }
                else if (j==2)
                {
                    path3[p_i] = prevroom;
                }
                p_i++;
                cout << "<--" << prevroom << " ";
                prevroom = parent[prevroom*D];
            }

            if (j==0) //after the while loop, lastly store and print source node
            {
                path1[p_i] = source;
                path_lengths[0] = p_i + 1;
            }
            else if (j==1)
            {
                path2[p_i] = source;
                path_lengths[1] = p_i + 1;
            }
            else if (j==2)
            {
                path3[p_i] = source;
                path_lengths[2] = p_i + 1;
            }
            cout << "<--" << source; // print the source
            cout << "\n";
        }

        // Print path1
        cout<<"path 1: "<<endl;
        for(int i = 0; i < path_lengths[0]; i++) {
            cout << path1[i] << " ";
        }
        cout << "\n";

        // Print path2
        cout<<"path 2: "<<endl;
        for(int i = 0; i < path_lengths[1]; i++) {
            cout << path2[i] << " ";
        }
        cout << "\n";

        // Print path3
        cout<<"path 3: "<<endl;
        for(int i = 0; i < path_lengths[2]; i++) {
            cout << path3[i] << " ";
        }
        cout << "\n";

    system("start grid.png"); //show the 3x4 grid image

}

//set all distances to infinity except the source node
void init() 
{
    for(int i=0; i<D; i++)
    {
        dist[i] = inf;
        parent_count[i] = 0;
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


//Each iteration of this selects a node to visit
void algorithm() 
{
    for(int i=0; i<D; i++) {
        int closestnode = getClosest();
        checked[closestnode] = true;

        for(int nbr=0; nbr<D; nbr++) {
            if(weight[closestnode][nbr] != inf) {
                int new_dist = dist[closestnode] + weight[closestnode][nbr];
                if(new_dist < dist[nbr]) {
                    dist[nbr] = new_dist;
                    parent_count[nbr] = 1;
                    parent[nbr*D] = closestnode;
                } else if(new_dist == dist[nbr]) {
                    parent[nbr*D + parent_count[nbr]] = closestnode;
                    parent_count[nbr]++;
                }
            }
        }
    }
}


