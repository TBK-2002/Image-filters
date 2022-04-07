// FCI – Programming 1 – 2022 - Assignment 3
// Program Name: assignment-3.cpp
// Last Modification Date: 3/4/2022
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
        switch (input)
        {
        case '1':
            loadImage();
            bnw();
            break;

        case '2':
            loadImage();
            invert();
            break;

        case '3':
            loadImage();
            loadImage2();
            merge();
            break;

        case '4':
            loadImage();
            flipImage();
            break;

        case '5':
            loadImage();
            rotate();
            break;

        case '6':
            loadImage();
            dnl();
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
                image[i][j] = 255;
            }
            else {
                image[i][j] = 0;
            }
        }
    }
    saveImage();
}

void merge() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = i % 2; j < SIZE; j += 2) // Keep even pixels and change odd ones and invert that in the next row.
        {
            image[i][j] = image2[i][j];
        }
    }
    saveImage();
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
                image[j][255 - i] = image2[i][j];
            }
        }
        break;

    case 'b':
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++)
            {
                image[255 - i][255 - j] = image2[i][j];
            }
        }
        break;

    case 'c':
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++)
            {
                image[255 - j][i] = image2[i][j];
            }
        }
        break;

    default:
        cout << "Invalid input!\n";
        rotate();
        break;
    }
    saveImage();
}

void invert() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = 255 - image[i][j];
            //to make white pixel minus any pixel so it inverts if it's negative
        }
    }
    saveImage();
}

void flipImage() {
    int tmp;
    char ans;
    cout << "Enter H to flip Horizontally or V to flip vertically: ";
    cin >> ans;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
        {
            image2[i][j] = image[i][j];
        }
    }
    switch (ans) {
    case 'V':
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++)
            {
                tmp = image[i][j];
                image[i][j] = image[i][SIZE - 1 - j];
                image[i][SIZE - 1 - j] = tmp;
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
        }
        break;

    default:
        cout << "Invalid input!\n";
        rotate();
        break;
    }
    saveImage();
}

void dnl() {
    //int c = 50;
    char ans;
    cout << "Enter D to darken or L to lighten the photo: ";
    cin >> ans;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
        {
            image2[i][j] = image[i][j];
        }
    }
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
        rotate();
        break;
    }
    saveImage();
}