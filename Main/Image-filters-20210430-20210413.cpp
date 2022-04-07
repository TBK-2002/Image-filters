// FCI – Programming 1 – 2022 - Assignment 3
// Program Name: assignment-3.cpp
// Last Modification Date: 7/4/2022
// Author1: Nour El-Din Ahmed Hussein - 20210430 - Group A - s5
// Author2 Mohanad Hisham El-Tahawy - 20210413 - Group A - s5
// Teaching Assistant: Hagar Ali
// Purpose: Filtering images.

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;

int size = 256;
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];

void loadImage(), loadImage2(), saveImage(), bnw(), merge(), rotate(), invert(), flipImage(), dnl();

int main() {
    char input;
    cout << "Ezayak ya user we hope you are doing well, ";
    while (true) {
        cout << "Please choose one of the following filters: " << endl
            << "1- Black & White Filter" << endl
            << "2- Invert Filter" << endl
            << "3- Merge Filter" << endl
            << "4- Flip Image" << endl
            << "5- Rotate Image" << endl
            << "6- Darken and Lighten Image" << endl
            << "7- Detect Image Edges" << endl
            << "8- Enlarge Image" << endl
            << "9- Shrink Image" << endl
            << "a- Mirror 1/2 Image" << endl
            << "b- Shuffle Image" << endl
            << "c- Blur Image" << endl
            << "s- Save the image to a file" << endl
            << "0- Exit" << endl;
        cin >> input;
        loadImage();
        switch (input)
        {
        case '1':
            bnw();
            break;

        case '2':
            invert();
            break;

        case '3':
            loadImage2();
            merge();
            break;

        case '4':
            flipImage();
            break;

        case '5':
            rotate();
            break;

        case '6':
            dnl();
            break;

        case '0':
            return 0;
            break;

        default:
            cout << "Sorry, invalid input" << endl;
            break;
        }
        saveImage();
    }
    return 0;
}

void loadImage() {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

void loadImage2() {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the second source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image2);
}

//_________________________________________
void saveImage() {
    char ans;
    cout << "Do you want to save? [Y/n]\n";
    cin >> ans;
    ans = tolower(ans);
    if (ans == 'y') {
        char imageFileName[100];

        // Get gray scale image target file name
        cout << "Enter the target image file name: ";
        cin >> imageFileName;

        // Add to it .bmp extension and load image
        strcat(imageFileName, ".bmp");
        writeGSBMP(imageFileName, image);
    }
    else if (ans == 'n') {
        // Do nothing and continue.
    }
    else {
        cout << "invalid input!\n";
        saveImage(); // Keep asking the user if he wants to save or not until he enters y or n.
    }

}

void bnw() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] > 128) {
                image[i][j] = 255; // If the pixel is dark make it black.
            }
            else {
                image[i][j] = 0; // If not then its light to make it white.
            }
        }
    }
}

void merge() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = i % 2; j < SIZE; j += 2) // Keep even pixels and change odd ones and invert that in the next row.
        {
            image[i][j] = image2[i][j];
        }
    }
}

void rotate() {
    char ans;
    cout << "Enter the degree of rotation ('a' for 90 degree, 'b' for 180 degree, 'c' for 270 degree)";
    cin >> ans;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
        {
            image2[i][j] = image[i][j];
        }
    } // To avoid losing the main image pixels during rotation.
    switch (ans)
    {
    case 'a':
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++)
            {
                image[j][255 - i] = image2[i][j]; // Rows and columns swaps and the new columns shift by 265 which is the SIZE.
            }
        }
        break;

    case 'b':
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++)
            {
                image[255 - i][255 - j] = image2[i][j]; // Rows and columns shift by 256.
            }
        }
        break;

    case 'c':
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++)
            {
                image[255 - j][i] = image2[i][j]; // Rows and columns swaps and the new rows shift by 265 which is the SIZE.
            }
        }
        break;

    default:
        cout << "Invalid input!\n";
        rotate();
        break;
    }
}

void invert() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = 255 - image[i][j];
            //to make white pixel minus any pixel so it changes to the opposite number of it , if it's 10 pixels which is dark so it changes to 245 which is light
        }
    }
}

void flipImage() {
    int tmp;
    char ans;
    cout << "Enter H to flip Horizontally or V to flip vertically: ";
    cin >> ans;
    ans = toupper(ans);
    switch (ans) {
    case 'V':
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++)
            { //dividing size by two because in one step two moves occur, so to avoid returning back to the initial position
                tmp = image[i][j]; //saving the original image in temporary variable to avoid losing changes
                image[i][j] = image[i][SIZE - 1 - j]; //this step means changing the initial column to the corresponding one to it on the other side
                image[i][SIZE - 1 - j] = tmp; //returning back the temporary value to the new image
            }
        }
        break;
    case 'H':
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE; j++)
            {
                tmp = image[i][j];
                image[i][j] = image[SIZE - 1 - i][j];
                image[SIZE - 1 - i][j] = tmp;
            }
        }//same as veticall instead working on rows not columns
        break;

    default:
        cout << "Invalid input!\n";
        flipImage();
        break;
    }
}

void dnl() {
    char ans;
    cout << "Enter D to darken or L to lighten the photo: ";
    cin >> ans;
    switch (ans) {
    case 'L':
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (image[i][j] + 64 < 256) {
                    image[i][j] += 64;
                    //if adding 64 pixels won't exceed 256 , then it'll get brighter
                }
                else {
                    image[i][j] = 255;
                }
            }
        }
        break;
    case 'D':
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (image[i][j] - 64 > 0) {
                    image[i][j] -= 64;
                    //if subtracting 64 pixels won't be less than zero, then it'll get darker
                }
                else {
                    image[i][j] = 0;
                }
            }
        }
        break;
        
    default:
        cout << "Invalid input!\n";
        dnl();
        break;
    }
}