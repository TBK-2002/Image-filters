// FCI – Programming 1 – 2022 - Assignment 3
// Program Name: assignment-3.cpp
// Last Modification Date: 15/4/2022
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

const int size = 256;
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];

void loadImage(), loadImage2(), saveImage(), bnw(), merge(), rotate(), invert(), flipImage(), dnl(), edges(), shrink(), blur(),mirrorImage(),enlarge(),shuffle(),quad1(),quad2(),quad3(),quad4();

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
        if(input == '0'){
            return 0;
            break;
        }
        input = toupper(input);
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

        case '7':
            edges();
            break;

        case '8':
            enlarge();
            break;

        case '9':
            shrink();
            break;

        case 'A':
            mirrorImage();
            break;

        case 'B':
            shuffle();
            break;
        
        case 'C':
            blur();
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
    int read = readGSBMP(imageFileName, image);
    if(read == 1){
        loadImage();
    }
}

void loadImage2() {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the second source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    int read = readGSBMP(imageFileName, image2);
    if(read == 1){
        loadImage2();
    }
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

void edges(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
        {
            image2[i][j] = image[i][j];
        }
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(image[i][j] < 127){
                image[i][j] = 0;
                j++;
                while(image[i][j] < 127){
                    image[i][j] = 255;
                    j++;
                }
                image[i][j-1] = 0;
            }
            else{
                image[i][j] = 255;
            }
        }
    }
    for(int j = 0; j < size; j++){
        for(int i = 0; i < size; i++){
            if(image2[i][j] < 127){
                image[i][j] = 0;
                i++;
                while(image2[i][j] < 127){
                    i++;
                }
                image[i-1][j] = 0;
            }
        }
    }
    // for(int i = 0; i < size; i++){
    //     for(int j = 0; j < size; j++){
    //         if(abs(image[i][j] - image[i][j+1]) > 48 || abs(image[i][j] - image[i+1][j]) > 48){
    //             image[i][j] = 0;
    //         }
    //         else{
    //             image[i][j] = 255;
    //         }
    //     }
    // }
}

void shrink(){
    char input;
    cout << "Choose the shrink scale: enter A to shrink it to half, B for one third, C for quarter.\n";
    cin >> input;
    input = toupper(input);
    switch (input)
    {
    case 'A':
        for(int i = 0, c = 0; i < size; i++, c += 2){
            for(int j = 0, k = 0; j < size; j++, k += 2){
                if(c < size && k < size){
                    image[i][j] = image[c][k];
                }
                else{
                    image[i][j] = 255;
                }
            }
        }
        break;

    case 'B':
        for(int i = 0, c = 0; i < size; i++, c += 3){
            for(int j = 0, k = 0; j < size; j++, k += 3){
                if(c < size && k < size){
                    image[i][j] = image[c][k];
                }
                else{
                    image[i][j] = 255;
                }
            }
        }
        break;

    case 'C':
        for(int i = 0, c = 0; i < size; i++, c += 4){
            for(int j = 0, k = 0; j < size; j++, k += 4){
                if(c < size && k < size){
                    image[i][j] = image[c][k];
                }
                else{
                    image[i][j] = 255;
                }
            }
        }
        break;

    default:
        cout << "invalid input!\n";
        shrink();
        break;
    }
}

void blur(){
    int level = 5;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
        {
            image2[i][j] = image[i][j];
        }
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            int avg = 0;
            for(int k = 1; k < (level+1); k++){
                avg += image2[i+k][j] + image2[i][j+k] + image2[i-k][j] + image2[i][j-k] + image2[i+k][j+k] + image2[i-k][j-k] + image2[i+k][j-k] + image2[i-k][j+k];
            }
            avg = avg / (8 * level);
            image[i][j] = avg;
        }
    }
}
void mirrorImage(){
    char ans;
    cout << "Enter to mirror: L for left or R for right or U for up or D for down " ;
    cin >> ans;
    switch(ans){
        case 'R' :
            for (int i =0;i < size;i++){
                for (int j=0;j < size; j++){
                    image[i][j] = image[i][SIZE - 1 - j];
                    image[i][SIZE - 1 - j] = image[i][j];
                }
            }
            break;

        case 'D' :
            for (int i =0;i < size;i++){
                for (int j=0;j < size; j++){
                    image[i][j]=image[SIZE - 1 -i][j];
                    image[SIZE - 1 -i][j] = image[i][j];
                }
            }
            break;

        case 'U' :
            for (int i =0;i < size;i++){
                for (int j=0;j < size; j++){
                    image[SIZE - 1 -i][j] = image[i][j];
                    image[i][j]=image[SIZE - 1 -i][j];
                }
            }
            break;

        case 'L' :
            for (int i =0;i < size;i++){
                for (int j=0;j < size; j++){
                    image[i][SIZE - 1 - j] = image[i][j];
                    image[i][j] = image[i][SIZE - 1 - j];
                }
            }
            break;

        default:
            cout << "invalid input!\n";
            mirrorImage();
            break;
    }
}
void enlarge(){
    int r = 0;
    int c = 0;
    unsigned char image2[size][size];
    char ans;
    cout << "Enter the quarter you want to enlarge ";
    cin >> ans;

    for(int i =0;i < size;i++){
        for(int j =0;j <size;j++){
            image2[i][j]=image[i][j];
        }
    }


    switch(ans){
        case '1':
            for(int i =0;i < size/2;i++){
                for(int j=0;j < size/2;j++){

                    image[r][c] = image2[i][j];
                    image[r][c+1] = image2[i][j];
                    image[r+1][c] = image2[i][j];
                    image[r+1][c+1] = image2[i][j];
                    c+=2;
                }
                c=0;
                r+=2;
            }
            break;

        case '2':
            for(int i =0;i < size/2;i++){
                for(int j=size/2;j < size;j++){

                    image[r][c] = image2[i][j];
                    image[r][c+1] = image2[i][j];
                    image[r+1][c] = image2[i][j];
                    image[r+1][c+1] = image2[i][j];
                    c+=2;
                }
                c=0;
                r+=2;
            }
            break;

        case '3':
            for(int i =size/2;i < size;i++){
                for(int j=0;j < size/2;j++){

                    image[r][c] = image2[i][j];
                    image[r][c+1] = image2[i][j];
                    image[r+1][c] = image2[i][j];
                    image[r+1][c+1] = image2[i][j];
                    c+=2;
                }
                c=0;
                r+=2;
            }
            break;

        case '4':
            for(int i =size/2;i < size;i++){
                for(int j=size/2;j < size;j++){

                    image[r][c] = image2[i][j];
                    image[r][c+1] = image2[i][j];
                    image[r+1][c] = image2[i][j];
                    image[r+1][c+1] = image2[i][j];
                    c+=2;
                }
                c=0;
                r+=2;
            }
            break;

    }
}

void shuffle() {
/*        unsigned char image1[size][size];
        unsigned char image2[size][size];
        unsigned char image3[size][size];
        unsigned char image4[size][size];*/
        unsigned char quad1[size][size];
        unsigned char quad2[size][size];
        unsigned char quad3[size][size];
        unsigned char quad4[size][size];
        char w, x, y, z;
        int r = 0, c = 0;
        for (int i = 0; i < size / 2; i++) {
            for (int j = 0; j < size / 2; j++) {
                quad1[r][c] = image[i][j];
                c += 1;
            }
            r += 1;
            c = 0;
        }
        r=0,c=0;
        for (int i = 0; i < size/2; i++) {
            for (int j = size / 2; j < size; j++) {
                quad2[r][c] = image[i][j];
                c += 1;
            }
            r += 1;
            c = 0;
        }
        r=0,c=0;
        for (int i = size / 2; i < size; i++) {
            for (int j = 0; j < size / 2; j++) {
                quad3[r][c] = image[i][j];
                c += 1;
            }
            r += 1;
            c=0;
        }
        r=0,c=0;
        for (int i = size / 2; i < size; i++) {
            for (int j = size / 2; j < size; j++) {
                quad4[r][c] = image[i][j];
                c += 1;
            }
            r += 1;
            c = 0;
        }
        cout << "Please enter shuffle order ";
        cin >> w >> x >> y >> z;
        r=0,c=0;
        switch (w) {
            case '1' :
                for (int i = 0; i < size / 2; i++) {
                    for (int j = 0; j < size / 2; j++) {
                        image[i][j] = quad1[r][c];
                        c += 1;
                    }
                    r += 1;
                    c = 0;
                }
                break;
            case '2' :
                for (int i = 0; i < size/2; i++) {
                    for (int j = 0; j < size/2; j++) {
                        image[i][j] = quad2[r][c];
                        c += 1;
                    }
                    r += 1;
                    c = 0;
                }
                break;
            case '3':
                for (int i = 0; i < size/2; i++) {
                    for (int j = 0; j < size / 2; j++) {
                        image[i][j] =quad3[r][c];
                        c += 1;
                    }
                    r += 1;
                    c = 0;
                }
                break;
            case '4' :
                for (int i = 0; i < size/2; i++) {
                    for (int j = 0; j < size/2; j++) {
                        image[i][j] = quad4[r][c];
                        c += 1;
                    }
                    r += 1;
                    c = 0;
                }
                break;
        }
        r=0,c=0;
        switch (x) {
            case '1' :
                for (int i = 0; i < size / 2; i++) {
                    for (int j = size/2; j < size; j++) {
                        image[i][j] = quad1[r][c];
                        c += 1;
                    }
                    r += 1;
                    c = 0;
                }
                break;
            case '2' :
                for (int i = 0; i < size/2; i++) {
                    for (int j = size/2; j < size; j++) {
                        image[i][j] = quad2[r][c];
                        c += 1;
                    }
                    r += 1;
                    c = 0;
                }
                break;
            case '3':
                for (int i = 0; i < size/2; i++) {
                    for (int j = size/2; j < size; j++) {
                        image[i][j] =quad3[r][c];
                        c += 1;
                    }
                    r += 1;
                    c = 0;
                }
                break;
            case '4' :
                for (int i = 0; i < size/2; i++) {
                    for (int j = size/2; j < size; j++) {
                        image[i][j] = quad4[r][c];
                        c += 1;
                    }
                    r += 1;
                    c = 0;
                }
                break;
        }
        r=0,c=0;
        switch (y) {
            case '1' :
                for (int i = size/2; i < size; i++) {
                    for (int j = 0; j < size / 2; j++) {
                        image[i][j] = quad1[r][c];
                        c += 1;
                    }
                    r += 1;
                    c = 0;
                }
                break;
            case '2' :
                for (int i = size/2; i < size; i++) {
                    for (int j = 0; j < size/2; j++) {
                        image[i][j] = quad2[r][c];
                        c += 1;
                    }
                    r += 1;
                    c = 0;
                }
                break;
            case '3':
                for (int i = size/2; i < size; i++) {
                    for (int j = 0; j < size / 2; j++) {
                        image[i][j] =quad3[r][c];
                        c += 1;
                    }
                    r += 1;
                    c = 0;
                }
                break;
            case '4' :
                for (int i = size/2; i < size; i++) {
                    for (int j = 0; j < size/2; j++) {
                        image[i][j] = quad4[r][c];
                        c += 1;
                    }
                    r += 1;
                    c = 0;
                }
                break;
        }
        r=0,c=0;
        switch (z) {
            case '1' :
                for (int i = size/2; i < size; i++) {
                    for (int j = size/2; j < size; j++) {
                        image[i][j] = quad1[r][c];
                        c += 1;
                    }
                    r += 1;
                    c = 0;
                }
                break;
            case '2' :
                for (int i =size/2; i < size; i++) {
                    for (int j = size/2; j < size; j++) {
                        image[i][j] = quad2[r][c];
                        c += 1;
                    }
                    r += 1;
                    c = 0;
                }
                break;
            case '3':
                for (int i = size/2; i < size; i++) {
                    for (int j = size/2; j < size ; j++) {
                        image[i][j] =quad3[r][c];
                        c += 1;
                    }
                    r += 1;
                    c = 0;
                }
                break;
            case '4' :
                for (int i = size/2; i < size; i++) {
                    for (int j = size/2; j < size; j++) {
                        image[i][j] = quad4[r][c];
                        c += 1;
                    }
                    r += 1;
                    c = 0;
                }
                break;
        }

}