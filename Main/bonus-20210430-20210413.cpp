// FCI – Programming 1 – 2022 - Assignment 3
// Program Name: bonus-20210430-20210413.cpp
// Last Modification Date: 20/4/2022
// Author1: Nour El-Din Ahmed Hussein - 20210430 - Group A - s5
// Author2 Mohanad Hisham El-Tahawy - 20210413 - Group A - s5
// Teaching Assistant: Hagar Ali
// Purpose: Filtering images in RGB.
// Note: Same algorithms from the gray scale filters used here.

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <array>
#include <algorithm>
#include "bmplib.cpp"

using namespace std;

unsigned char image[SIZE][SIZE][RGB];
unsigned char image2[SIZE][SIZE][RGB];

void loadImage(), loadImage2(), saveImage(), bnw(), merge(), rotate(), invert(), flipImage(), dnl(), edges(), shrink(), blur(), mirrorImage(), enlarge(), shuffle();
bool isEqualNum();

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
    int read = readRGBBMP(imageFileName, image);
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
    int read = readRGBBMP(imageFileName, image2);
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
        writeRGBBMP(imageFileName, image);
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
    long avg = 0;
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            for(int k = 0; k < RGB; k++){
                avg += image[i][j][k];
            }
        }
    }
    avg /= SIZE * SIZE * RGB;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            long pixel_avg = 0;
            for(int k = 0; k < RGB; k++){
                pixel_avg += image[i][j][k];
            }
            pixel_avg /= RGB;
            int pixel;
            if(pixel_avg < avg){
                pixel = 0;
            }
            else{
                pixel = 255;
            }
            for(int k = 0; k < RGB; k++){
                image[i][j][k] = pixel;
            }
        }
    }
}

void merge() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++){
            for(int k = 0; k < RGB; k++){
                image[i][j][k] = (image[i][j][k] + image2[i][j][k]) / 2;
            }
        }
    }
}

void rotate() {
    char ans;
    cout << "Enter the degree of rotation ('a' for 90 degree, 'b' for 180 degree, 'c' for 270 degree)";
    cin >> ans;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++){
            for(int k = 0; k < RGB; k++)
            {
                image2[i][j][k] = image[i][j][k];
            }
        }
    } // To avoid losing the main image pixels during rotation.
    switch (ans)
    {
    case 'a':
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++){
                for(int k = 0; k < RGB; k++)
                {
                    image[j][255 - i][k] = image2[i][j][k]; // Rows and columns swaps and the new columns shift by 265 which is the SIZE.
                }
            }
        }
        break;

    case 'b':
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++){
                for(int k = 0; k < RGB; k++)
                {
                    image[255 - i][255 - j][k] = image2[i][j][k]; // Rows and columns shift by 256.
                }
            }
        }
        break;

    case 'c':
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++){
                for(int k = 0; k < RGB; k++)
                {
                    image[255 - j][i][k] = image2[i][j][k]; // Rows and columns swaps and the new rows shift by 265 which is the SIZE.
                }
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
            for(int k = 0; k < RGB; k++){
                image[i][j][k] = 255 - image[i][j][k];
                //to make white pixel minus any pixel so it changes to the opposite number of it , if it's 10 pixels which is dark so it changes to 245 which is light
            }
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
            for (int j = 0; j < SIZE / 2; j++){
                for(int k = 0; k < RGB; k++)
                { //dividing SIZE by two because in one step two moves occur, so to avoid returning back to the initial position
                    tmp = image[i][j][k]; //saving the original image in temporary variable to avoid losing changes
                    image[i][j][k] = image[i][SIZE - 1 - j][k]; //this step means changing the initial column to the corresponding one to it on the other side
                    image[i][SIZE - 1 - j][k] = tmp; //returning back the temporary value to the new image
                }
            }
        }
        break;
    case 'H':
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE; j++){
                for(int k = 0; k < RGB; k++)
                {
                    tmp = image[i][j][k];
                    image[i][j][k] = image[SIZE - 1 - i][j][k];
                    image[SIZE - 1 - i][j][k] = tmp;
                }
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
    ans = toupper(ans);
    switch (ans) {
    case 'L':
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++){
                for(int k = 0; k < RGB; k++)
                {
                    image[i][j][k] = (255 + image[i][j][k]) / 2;
                }
            }
        }
        break;
    case 'D':
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++){
                for(int k = 0; k < RGB; k++)
                {
                    image[i][j][k] /= 2; // Which is the average with zero.
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

bool isEqualNum(unsigned char a[], int num){
    for(int i = 0; i < sizeof(a); i++){
        if(a[i] != num){
            return false;
        }
    }
    return true;
}

void edges(){
    bnw();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++){
            for(int k = 0; k < RGB; k++)
            {
                image2[i][j][k] = image[i][j][k];
            }
        }
    }
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(isEqualNum(image[i][j], 0)){
                j++;
                while(isEqualNum(image[i][j], 0)){
                    for(int k = 0; k < RGB; k++){
                        image[i][j][k] = 255;
                    }
                    j++;
                }
                for(int k = 0; k < RGB; k++){
                    image[i][j-1][k] = 0;
                }
            }
        }
    }
    for(int j = 0; j < SIZE; j++){
        for(int i = 0; i < SIZE; i++){
            if(isEqualNum(image2[i][j], 0)){
                i++;
                while(isEqualNum(image2[i][j], 0)){
                    i++;
                }
                for(int k = 0; k < RGB; k++){
                    image[i-1][j][k] = 0;
                }
            }
        }
    }
}

void shrink(){
    char input;
    cout << "Choose the shrink scale: enter A to shrink it to half, B for one third, C for quarter.\n";
    cin >> input;
    input = toupper(input);
    switch (input)
    {
    case 'A':
        for(int i = 0, c = 0; i < SIZE; i++, c += 2){
            for(int j = 0, k = 0; j < SIZE; j++, k += 2){
                for(int g = 0; g < RGB; g++)
                {
                    if(c < SIZE && k < SIZE){
                        image[i][j][g] = image[c][k][g];
                    }
                    else{
                        image[i][j][g] = 255;
                    }
                }
            }
        }
        break;

    case 'B':
        for(int i = 0, c = 0; i < SIZE; i++, c += 3){
            for(int j = 0, k = 0; j < SIZE; j++, k += 3){
                for(int g = 0; g < RGB; g++)
                {
                    if(c < SIZE && k < SIZE){
                        image[i][j][g] = image[c][k][g];
                    }
                    else{
                        image[i][j][g] = 255;
                    }
                }
            }
        }
        break;

    case 'C':
        for(int i = 0, c = 0; i < SIZE; i++, c += 4){
            for(int j = 0, k = 0; j < SIZE; j++, k += 4){
                for(int g = 0; g < RGB; g++)
                {
                    if(c < SIZE && k < SIZE){
                        image[i][j][g] = image[c][k][g];
                    }
                    else{
                        image[i][j][g] = 255;
                    }
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
        for (int j = 0; j < SIZE; j++){
            for(int k = 0; k < RGB; k++)
            {
                image2[i][j][k] = image[i][j][k];
            }
        }
    }
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            for(int g = 0; g < RGB; g++)
            {
                int avg = 0;
                for(int k = 1; k < (level+1); k++){
                    avg += image2[i+k][j][g] + image2[i][j+k][g] + image2[i-k][j][g] + image2[i][j-k][g] + image2[i+k][j+k][g] + image2[i-k][j-k][g] + image2[i+k][j-k][g] + image2[i-k][j+k][g];
                }
                avg = avg / (8 * level);
                image[i][j][g] = avg;
            }
        }
    }
}

void mirrorImage(){
    char ans;
    cout << "Enter to mirror: L for left or R for right or U for up or D for down " ;
    cin >> ans;
    ans = toupper(ans);
    switch(ans){
        case 'R' :
            for (int i =0;i < SIZE;i++){
                for (int j=0;j < SIZE; j++){
                    for(int k = 0; k < RGB; k++)
                    {
                        image[i][j][k] = image[i][SIZE - 1 - j][k]; //switching columns which are corresponding to each other
                        image[i][SIZE - 1 - j][k] = image[i][j][k]; //returning back the changes to the original image in which this makes some pixels to be lost
                    }
                }
            }
            break;

        case 'D' :
            for (int i =0;i < SIZE;i++){
                for (int j=0;j < SIZE; j++){
                    for(int k = 0; k < RGB; k++)
                    {
                        image[i][j][k] = image[SIZE - 1 -i][j][k]; //switching rows which are corresponding to each other
                        image[SIZE - 1 -i][j][k] = image[i][j][k]; //returning back the changes to the original image in which this makes some pixels to be lost
                    }
                }
            }
            break;

        case 'U' :
            for (int i =0;i < SIZE;i++){
                for (int j=0;j < SIZE; j++){
                    for(int k = 0; k < RGB; k++)
                    {
                        image[SIZE - 1 -i][j][k] = image[i][j][k]; //switching columns which are corresponding to each other but starting from bottom first
                        image[i][j][k] = image[SIZE - 1 -i][j][k]; //returning back the changes to the original image in which this makes some pixels to be lost
                    }
                }
            }
            break;

        case 'L' :
            for (int i =0;i < SIZE;i++){
                for (int j=0;j < SIZE; j++){
                    for(int k = 0; k < RGB; k++)
                    {
                        image[i][SIZE - 1 - j][k] = image[i][j][k]; //switching rows which are corresponding to each other but starting from bottom first
                        image[i][j][k] = image[i][SIZE - 1 - j][k]; //returning back the changes to the original image in which this makes some pixels to be lost
                    }
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
    char ans;
    cout << "Enter the quarter you want to enlarge ";
    ans = toupper(ans);
    cin >> ans;

    for(int i = 0; i < SIZE;i++){
        for(int j = 0;j < SIZE;j++){
            for(int k = 0; k < RGB; k++)
            {
                image2[i][j][k] = image[i][j][k]; //making the second image equal to the first one to avoid losing pixels
            }
        }
    }


    switch(ans){
        case '1':
            for(int i =0;i < SIZE/2;i++){
                for(int j=0;j < SIZE/2;j++){
                    for(int k = 0; k < RGB; k++)
                    {
                        image[r][c][k] = image2[i][j][k];
                        image[r][c+1][k] = image2[i][j][k];
                        image[r+1][c][k] = image2[i][j][k];
                        image[r+1][c+1][k] = image2[i][j][k];
                    }
                    c+=2;
                }
                c=0;
                r+=2;
            }
            break; //choosing the 1st quad , each pixel in position 00 01 10 11 equals 1 pixel in new image
                   //the second increment starting from 02 03 12 13 to avoid taking pixels from first increment and keeps going until the whole quad fits into the new image

        case '2':
            for(int i =0;i < SIZE/2;i++){
                for(int j=SIZE/2;j < SIZE;j++){
                    for(int k = 0; k < RGB; k++)
                    {
                        image[r][c][k] = image2[i][j][k];
                        image[r][c+1][k] = image2[i][j][k];
                        image[r+1][c][k] = image2[i][j][k];
                        image[r+1][c+1][k] = image2[i][j][k];
                    }
                    c+=2;
                }
                c=0;
                r+=2;
            }
            break; //same as first quad but now working on second

        case '3':
            for(int i =SIZE/2;i < SIZE;i++){
                for(int j=0;j < SIZE/2;j++){
                    for(int k = 0; k < RGB; k++)
                    {
                        image[r][c][k] = image2[i][j][k];
                        image[r][c+1][k] = image2[i][j][k];
                        image[r+1][c][k] = image2[i][j][k];
                        image[r+1][c+1][k] = image2[i][j][k];
                    }
                    c+=2;
                }
                c=0;
                r+=2;
            }
            break; //third quad

        case '4':
            for(int i =SIZE/2;i < SIZE;i++){
                for(int j=SIZE/2;j < SIZE;j++){
                    for(int k = 0; k < RGB; k++)
                    {
                        image[r][c][k] = image2[i][j][k];
                        image[r][c+1][k] = image2[i][j][k];
                        image[r+1][c][k] = image2[i][j][k];
                        image[r+1][c+1][k] = image2[i][j][k];
                    }
                    c+=2;
                }
                c=0;
                r+=2;
            }
            break; //fourth quad

        default:
            cout << "invalid input!\n";
            enlarge();
            break;
    }
}

void shuffle(){
    unsigned char quads[4][SIZE/2][SIZE/2][RGB];

    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            for(int k = 0; k < RGB; k++)
            {
                int p = image[i][j][k];
                if(i < 128 && j < 128){
                    quads[0][i][j][k] = p;
                }
                else if(i < 128 && j > 127){
                    quads[1][i][j-128][k] = p;
                }
                else if(i > 127 && j < 128){
                    quads[2][i-128][j][k] = p;
                }
                else if(i > 127 && j > 127){
                    quads[3][i-128][j-128][k] = p;
                }
            }
        }
    }
    char w, x, y, z;
    cout << "Please enter shuffle order ";
    cin >> w >> x >> y >> z;
    int i1 = w - '0', i2 = x - '0', i3 = y - '0', i4 = z - '0';
    int check[4] = {1, 2, 3, 4};
    int inputs[4] = {i1, i2, i3, i4};
    sort(std::begin(inputs), std::end(inputs));
    bool checker = true;
    for(int i = 0; i < 4; i++){
        if(check[i] != inputs[i]){
            checker = false;
            break;
        }
    }
    if(checker){
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                for(int k = 0; k < RGB; k++)
                {
                    if(i < 128 && j < 128){
                        image[i][j][k] = quads[i1-1][i][j][k];
                    }
                    else if(i < 128 && j > 127){
                        image[i][j][k] = quads[i2-1][i][j-128][k];
                    }
                    else if(i > 127 && j < 128){
                        image[i][j][k] = quads[i3-1][i-128][j][k];
                    }
                    else{
                        image[i][j][k] = quads[i4-1][i-128][j-128][k];
                    }
                }
            }
        }
    }
    else{
        cout << "invalid input!\n";
        shuffle();
    }
}