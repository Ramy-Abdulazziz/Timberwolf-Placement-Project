/*
comments: The picture I have posted is basically what the output is looking like. It takes me 6 and half minutes to print the whole grid and still some grids are omitted
due to the size,so if you want to know what the grid looks like, I highly recommend that you use the two benchmark files I have made and change the infile of scl and nodes to the name
of the benchmark. And I will start working on the perturbation of the algorithm, which is either moving the cell to a random place or swap it with another cell.
You can work on finding the total minimum length. Any questions, please email me or message me
Description: This program initialize the placement by placing all the cells inside the given rectangle.
Update: Now the program could do perturbation, just need to find the minimum length now
*/

#include <iostream>
#include <iomanip> 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

//use to get the integer in a line of string,since the integers are stored in a vector
//if there are more than 1 integer, than just check the vector's second index
void extractIntegerWords(string str, vector<int>& num)
{
    stringstream ss;
    /* Storing the whole string into string stream */
    ss << str;

    /* Running loop till the end of the stream */
    string temp;
    int found;
    while (!ss.eof()) {

        /* extracting word by word from stream */
        ss >> temp;

        /* Checking the given word is integer or not */
        if (stringstream(temp) >> found)
        {
            num.push_back(found);
        }

        /* To save from space at the end of string */
        temp = "";
    }
}

//use to get the index of descending order of the elements in a vector
void sortArr(vector<int> arr, int n, vector <int>& index)
{

    // Vector to store element
    // with respective present index
    vector<pair<int, int> > vp;

    // Inserting element in pair vector
    // to keep track of previous indexes
    for (int i = 0; i < n; ++i) {
        vp.push_back(make_pair(arr[i], i));
    }

    // Sorting pair vector
    sort(vp.begin(), vp.end());

    // Displaying sorted element
    // with previous indexes
    // corresponding to each element
    //cout << "Element\t"
       // << "index" << endl;
    for (int i = 0; i < vp.size(); i++) {
        //cout << vp[vp.size()-i-1].first << "\t"
             //<< vp[vp.size()-i-1].second << endl;
        index.push_back(vp[vp.size() - i - 1].second);
    }
}

//The grid, the number of nodes, width and length of each block, number of rows and columns
void initialize(vector<vector<string>>& grid, int numNodes, int numRow, int numColumn, vector<vector<int>> parameters, vector<int> index, vector<vector<float>> &coor, vector < vector<int>> &bot_left_coor) {
    int x_coor = 0, y_coor = 0;
    //use to check if the block can fit into the coordinate
    bool empty = false;
    //initialize loop control variable
    int j = 0, k = 0;
    srand(time(0));
    //place every node
    for (int i = 0; i < numNodes; i++) {
        empty = false;
        //check if the grid is empty
        while (empty == false)
        {
            //get a random x and y coordinate
            x_coor = rand() % numColumn;
            y_coor = rand() % numRow;
            //since all cells have to be placed in the rows
            //and the row height is 16 units, i am assuming the 
            //upper side and bottom side have to touch the row boundary
            for (j = 0; j < parameters[index[i]][1]; j = j + 16)
            {
                //check if the cell will pop out of the rectangle by rows
                if ((y_coor * 16 + j) >= numRow * 16)
                {
                    empty = false;
                    break;
                }
                //fit into the column
                for (k = 0; k < parameters[index[i]][0]; k++)
                {
                    //check if the cell will pop out of the rectangle by columns
                    if ((x_coor + k) >= numColumn)
                    {
                        empty = false;
                        break;
                    }
                    //check if the unit is empty
                    if (grid[y_coor * 16 + j][x_coor + k] != "U")
                    {
                        empty = false;
                        break;
                    }
                    else
                        empty = true;
                }
                if (empty == false)
                    break;
            }
        }
        //get the center coordinate for every nodes
        coor[index[i]][1] = float(y_coor*16) + float(parameters[index[i]][1]/2)-0.5;
        coor[index[i]][0] = float(x_coor) + float(parameters[index[i]][0] / 2)-0.5;
        bot_left_coor[index[i]][1] = y_coor * 16;
        bot_left_coor[index[i]][0] = x_coor;
        //if portion area is empty such that the block can fit in
        //then all these units will be written the block's index
        for (int j = 0; j < parameters[index[i]][1]; j++)
        {
            for (int k = 0; k < parameters[index[i]][0]; k++)
            {
                grid[y_coor * 16 + j][x_coor + k] = to_string(index[i]);
            }
        }
    }
}

void swap_cell(vector<vector<string>> &grid,vector<int> wts, vector<vector<int>> size,int numNodes,vector<vector<int>> coor) {
    int index1, index2;
    //swap two random nodes
    index1 = rand() % numNodes;
    index2 = rand() % numNodes;
    //check if they are the same index and they have the same weights
    while (!(index2 != index1 && wts[index2] == wts[index1]))
    {
        index2 = rand() % numNodes;
    }
    //swap two nodes
    for (int i = 0; i < size[index1][1]; i++)
    {
        for (int j = 0; j < size[index1][0]; j++)
        {
            //swap two nodes
            swap(grid[coor[index1][1]+i][coor[index1][0]+j], grid[coor[index2][1]+i][coor[index2][0]+j]);
        }
    }
}

void move_cell(vector<vector<string>> &grid,vector<vector<int>> size,int numNodes, int numRow, int numColumn, vector<vector<int>> coor) {
    int x_coor = 0, y_coor = 0;
    bool empty = false;
    int index;
    index = rand() / numNodes;
    index = 22;
    while (empty == false)
    {
        x_coor = rand() % numColumn;
        y_coor = rand() % numRow;
        for (int i = 0; i < size[index][1]; i = i + 16)
        {
            if ((y_coor * 16 + i) >= numRow * 16)
            {
                empty = false;
                break;
            }
            for (int j = 0; j < size[index][0]; j++)
            {
                if ((x_coor + j) >= numColumn)
                {
                    empty = false;
                    break;
                }
                if (!(grid[y_coor * 16 + i][x_coor + j] == "U" || grid[y_coor * 16 + i][x_coor + j] == to_string(index)))
                {
                    empty = false;
                    break;
                }
                else
                    empty = true;
            }
            if (empty == false)
                break;
        }
    }
        for (int i = 0; i < size[index][1]; i++)
        {
            for (int j = 0; j < size[index][0]; j++)
            {
                //place the block to a new place
                swap(grid[y_coor*16+i][x_coor+j],grid[coor[index][1]+i][coor[index][0]+j]);
            }
        }
}
int main() {
    //read all the files
    ifstream sclfile("mybenchmark.scl");
    ifstream nodesfile("mybenchmark.nodes");
    ifstream wtsfile("ibm01.wts");
    ifstream plfile("ibm01.pl");
    ifstream netsfile("ibm01.nets");
    string line;
    vector <int> num;
    vector <int> terminalWt;
    vector <int> nodeWt;
    vector <int> descendingIndex;
    vector <vector<float>> center_coor;
    vector <vector<int>> bot_left_coor;
    int i = 0, numRow = 0, numSite = 0, numNode = 0, numTerminal = 0;
    /*
    read the scl file and get its number of rows and number of columns
    */
    while (getline(sclfile, line) && i < 5)
    {
        i++;
    }
    i = 0;
    if (getline(sclfile, line))
    {
        extractIntegerWords(line, num);
        numRow = num[0];
    }
    num.clear();
    while (getline(sclfile, line) && i < 7)
    {
        i++;
    }
    i = 0;
    if (getline(sclfile, line))
    {
        extractIntegerWords(line, num);
        numSite = num[1];
    }
    num.clear();
    vector < vector<string >> grid;
    for (int j = 0; j < numRow * 16; j++)
    {
        vector <string> v1;
        for (int k = 0; k < numSite; k++)
        {
            v1.push_back("U");
        };
        grid.push_back(v1);
    }

    /*
    read the node file and the number of nodes and number of terminals
    */
    while (getline(nodesfile, line) && i < 4)
    {
        i++;
    }
    i = 0;
    if (getline(nodesfile, line))
    {
        extractIntegerWords(line, num);
    }
    if (getline(nodesfile, line))
    {
        extractIntegerWords(line, num);
    }
    numNode = num[0];
    numTerminal = num[1];
    num.clear();
    vector <vector <int>> terminal;
    vector <vector <int>> nodes;
    for (int j = 0; j < numTerminal; j++)
    {
        vector<int> v2;
        getline(nodesfile, line);
        extractIntegerWords(line, v2);
        terminal.push_back(v2);
        v2.clear();
    }
    while (getline(nodesfile, line))
    {
        vector<int> v2;
        vector<float> initial_Coor;
        extractIntegerWords(line, v2);
        nodes.push_back(v2);
        v2.clear();
        v2.push_back(0);
        v2.push_back(0);
        initial_Coor.push_back(0);
        initial_Coor.push_back(0);
        center_coor.push_back(initial_Coor);
        bot_left_coor.push_back(v2);
        initial_Coor.clear();
        v2.clear();
    }
    for (int i = 0; i < 5; i++)
    {
        getline(wtsfile,line);
    }
    for (int i = 0; i < numTerminal; i++)
    {
        getline(wtsfile, line);
        extractIntegerWords(line, terminalWt);
    }
    for (int i = 0; i < nodes.size(); i++)
    {
        getline(wtsfile, line);
        extractIntegerWords(line, nodeWt);
    }
    //get the descending index of the nodes
    sortArr(nodeWt, nodeWt.size(), descendingIndex);

    //initialize the grid
    initialize(grid, nodes.size(), numRow, numSite, nodes,descendingIndex,center_coor,bot_left_coor);
    //print the grid
    for (int j = 0; j < numRow * 16; j++)
    {
        for (int k = 0; k < numSite; k++)
        {
            cout << grid[j][k] << " ";
        }
        cout << "\n";
    }
    //system("CLS");
    //swap_cell(grid, nodeWt, nodes, numNode, bot_left_coor);
    //move_cell(grid, nodes, numNode, numRow, numSite, bot_left_coor);
   // for (int j = 0; j < numRow * 16; j++)
  //  {
   //     for (int k = 0; k < numSite; k++)
   //     {
   //         cout << grid[j][k] << " ";
   //     }
    //    cout << "\n";
    //}

}





