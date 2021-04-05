#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using int16_t = short int;
using uint16_t = unsigned short int;

uint16_t centX = 0;
uint16_t centY = 0;
uint16_t arrSize = 0;

void printMatrix(vector<vector<int16_t>>& m)
{
    cout << m.size() << "\n";
    for (auto& v: m) {
        for(auto& el: v) {
          cout << el << " ";
        }
        cout << "\n";
    }
}

void printSpiralPart(vector<vector<int16_t>>& matrix, uint16_t x, uint16_t y)
{
   
    int16_t currY = y, currX = x;

    // up
    int16_t a = currY - 2 * abs(currY - centY) - 1;
    uint16_t newY = (a >= 0 ) ? a : 0;
    while (currY > newY) {
#ifdef DEBUG
        cout << "currY " << currY << " currX " << currX << "\n";   
#endif
        cout << matrix[currY--][currX] << "\n";
    }
    // base case
    if (currX == 0 && currY == 0) {
#ifdef DEBUG
        cout << "currY " << currY << " currX " << currX << "\n";   
        cout << " !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << "\n";
#endif
        cout << matrix[currY][currX] << "\n";
        return;
    }
 
    // right
    int16_t b = currX + 2 * abs(currX - centX) + 1;
    uint16_t newX = (b <= arrSize) ? b : arrSize;
    while (currX < newX) {
#ifdef DEBUG
        cout << "currY " << currY << " currX " << currX << "\n";   
#endif
        cout << matrix[currY][currX++] << "\n";
    }
#ifdef DEBUG
    cout << "currY " << currY << " currX " << currX << "\n";   
    cout << matrix[currX][currY] << "\n";
#endif
    // down
    int16_t c = currY + 2 * abs(currY - centY);
    newY = (c <= arrSize) ? c : arrSize;
    while (currY < newY) {
#ifdef DEBUG
        cout << "currY " << currY << " currX " << currX << "\n";   
#endif
        cout << matrix[currY++][currX] << "\n";
    }

    // left
    int16_t d = currX - 2 * abs(currX - centX);
    newX = (d >= 0) ? d : 0;
    while (currX > newX) {
#ifdef DEBUG
        cout << "currY " << currY << " currX " << currX << "\n";   
#endif
        cout << matrix[currY][currX--] << "\n";
    }
#ifdef DEBUG
    cout << "currY " << currY << " currX " << currX << "\n";   
#endif
    printSpiralPart(matrix, currX, currY);
}

int main()
{
    ios_base::sync_with_stdio(false);
    ifstream iFile("input.txt");
    ofstream oFile("output.txt");

    int16_t m = 0;
    int16_t buf = 0;
    iFile >> m;
    arrSize = m - 1;
    centX = centY = m / 2;
    vector<vector<int16_t>> matrix(m);
    for(auto& v: matrix)
        v.reserve(m);

    uint16_t count = 0;
    uint16_t currX = 0;
    uint16_t currY = 0;
    while (iFile >> buf) {
        matrix[currY].push_back(buf);
        currX++;
        if (currX > arrSize) {
            currX = 0; currY++;
        }
    }

//    printMatrix(matrix);
    if (m == 1) {
        cout << matrix[0][0];
        oFile << matrix[0][0];
    } else
        printSpiralPart(matrix, m / 2, m / 2);

    oFile.close();
    iFile.close();
}
