#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

string searchQuery1, searchQuery2;
int arraySize, count, totalQueries;
bool found;

void appendToQuery(string array[])
{
    for (int i = 0; i < count; i++)
    {
        found = false;
        if (array[i].find(searchQuery1) != -1 && array[i].find(searchQuery2) == -1)
        {
            array[i] += "-";
            array[i] += searchQuery2;
            found = true;
        }
        else if (array[i].find(searchQuery2) != -1 && array[i].find(searchQuery1) == -1)
        {
            array[i] += "-";
            array[i] += searchQuery1;
            found = true;
        }
        else if (array[i].find(searchQuery1) != -1 && array[i].find(searchQuery2) != -1)
        {
            found = true;
        }
    }
    if (!found)
    {
        array[count] += searchQuery1;
        array[count] += "-";
        array[count] += searchQuery2;
        count++;
        found = false;
    }
}

int main()
{
    found = false;
    count = 0;

    ifstream input("input.txt");
    input >> arraySize;

    string dataArray[arraySize];
    bool population[arraySize];

    for (int i = 0; i < arraySize; i++)
    {
        population[i] = true;
    }

    while (input >> searchQuery1 >> searchQuery2)
    {
        if (searchQuery1 == "0" && searchQuery2 == "0")
            break;

        population[stoi(searchQuery1)] = false;
        population[stoi(searchQuery2)] = false;
        appendToQuery(dataArray);
    }

    for (int i = 0; i < count; i++)
    {
        cout << dataArray[i] << endl;
    }

    for (int i = 0; i < arraySize; i++)
    {
        if (population[i])
        {
            cout << i << endl;
        }
    }

    return 0;
}