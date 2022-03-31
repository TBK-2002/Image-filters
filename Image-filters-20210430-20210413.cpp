// FCI – Programming 1 – 2022 - Assignment 3
// Program Name: assignment-3.cpp
// Last Modification Date: 31/3/2022
// Author1: Nour El-Din Ahmed Hussein - 20210430 - Group A - s5
// Author2 Mohanad Hisham - 20210413 - Group A - s5
// Author3 and ID and Group: xxxxx xxxxx
// Teaching Assistant: Hagar
// Purpose: Filtering images.

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];

int main(){
    char input;
    cout << "Ezayk ya user we hope you are doing well, ";
    while(true){
        cout << "Please choose one of the following filters: " << endl
             << "1- Black & White Filter" << endl
             << "2- Invert Filter" << endl
             << "3- Merge Filter" << endl
             << "4- Flip Image" << endl
             << "5- Darken and Lighten Image" << endl
             << "6- Rotate Image" << endl
             << "7- Detect Image Edges" << endl
             << "8- Enlarge Image" << endl
             << "9- Shrink Image" << endl
             << "a- Mirror 1/2 Image" << endl
             << "b- Shuffle Image" << endl
             << "c- Blur Image" << endl
             << "s- Save the image to a file" << endl
             << "0- Exit" << endl;
        cin >> input;
        switch (input)
        {
            case '1':
                /* code */
                break;
            
            case '2':
                /* code */
                break;

            case '3':
                /* code */
                break;

            case '4':
                /* code */
                break;

            case '5':
                /* code */
                break;

            case '6':
                /* code */
                break;

            case '0':
                return 0;
                break;

            default:
                cout << "Sorry, invalid input" << endl;
                break;
        }
    }
    return 0;
}