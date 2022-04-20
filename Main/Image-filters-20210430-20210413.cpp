// FCI – Programming 1 – 2022 - Assignment 3
// Program Name: Image-filters-20210430-20210413.cpp
// Last Modification Date: 19/4/2022
// Author1: Nour El-Din Ahmed Hussein - 20210430 - Group A - S5
// Author2 Mohanad Hisham El-Tahawy - 20210413 - Group A - S5
// Teaching Assistant: Hagar Ali
// Purpose: Filtering images.

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include "bmplib.cpp"

using namespace std;

unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];

void loadImage(), loadImage2(), saveImage(), bnw(), merge(), rotate(), invert(), flipImage(), dnl(), edges(), shrink(), blur(), mirrorImage(), enlarge(), shuffle();

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
    long avg = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            avg += image[i][j];
        }
    }
    avg /= SIZE * SIZE;
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(image[i][j] < avg) // If the pixel is darker than the average change it to black.
            {
                image[i][j] = 0;
            }
            else // If the pixel is lighter than the average change it to white.
            {
                image[i][j] = 255;
            }
        }
    }
}

void merge() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = (image2[i][j] + image[i][j]) / 2; // Average of the two pixels from the two images.
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
            { //dividing SIZE by two because in one step two moves occur, so to avoid returning back to the initial position
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
    bnw(); // Change the image into black and white image.
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
        {
            image2[i][j] = image[i][j]; // Make a copy of the orignal image to avoid losing any pixels.
        }
    }
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(image[i][j] == 0) // Detect the first black pixel in the row.
            {
                j++;
                while(image[i][j] == 0) // Keep iterating over the pixels in the same row until black pixels end.
                {
                    image[i][j] = 255; // Change all the middle pixels into white.
                    j++;
                }
                image[i][j-1] = 0; // Keep the last pixel in the black line as black.
            }
        }
    }
    for(int j = 0; j < SIZE; j++){
        for(int i = 0; i < SIZE; i++){
            if(image2[i][j] == 0) // Detect the first black pixel in the column.
            {
                image[i][j] = 0; // If the first pixel in the black line was changed during the previous loop change it to black back.
                i++;
                while(image2[i][j] == 0)
                {
                    i++; // Keep iterating over the pixels in the black line in the original image without changing values in the new image.
                }
                image[i-1][j] = 0; // Make the last pixel in the black line black.
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
                if(c < SIZE && k < SIZE){
                    image[i][j] = image[c][k]; // Take a pixel from every two pixels and put it in the first quad.
                }
                else{
                    image[i][j] = 255; // Make the rest of the picture white.
                }
            }
        }
        break;

    case 'B':
        for(int i = 0, c = 0; i < SIZE; i++, c += 3){
            for(int j = 0, k = 0; j < SIZE; j++, k += 3){
                if(c < SIZE && k < SIZE){
                    image[i][j] = image[c][k]; // Take a pixel from every three pixels.
                }
                else{
                    image[i][j] = 255;
                }
            }
        }
        break;

    case 'C':
        for(int i = 0, c = 0; i < SIZE; i++, c += 4){
            for(int j = 0, k = 0; j < SIZE; j++, k += 4){
                if(c < SIZE && k < SIZE){
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
    int level = 4; // To easily change blur level.
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
        {
            image2[i][j] = image[i][j]; // Make a copy of the orignal image to avoid losing any pixels.
        }
    }
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            int avg = 0;
            for(int k = 1; k < (level+1); k++){
                avg += image2[i+k][j] + image2[i][j+k] + image2[i-k][j] + image2[i][j-k] + image2[i+k][j+k] + image2[i-k][j-k] + image2[i+k][j-k] + image2[i-k][j+k];
            } // Calculate the average of pixels in the same vertical and horizontal line and diagonal from the pixel.
            avg = avg / (8 * level); // Calcualate the average until the specified level.
            image[i][j] = avg;
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
                    image[i][j] = image[i][SIZE - 1 - j]; //switching columns which are corresponding to each other
                    image[i][SIZE - 1 - j] = image[i][j]; //returning back the changes to the original image in which this makes some pixels to be lost
                }
            }
            break;

        case 'D' :
            for (int i =0;i < SIZE;i++){
                for (int j=0;j < SIZE; j++){
                    image[i][j]=image[SIZE - 1 -i][j]; //switching rows which are corresponding to each other
                    image[SIZE - 1 -i][j] = image[i][j]; //returning back the changes to the original image in which this makes some pixels to be lost
                }
            }
            break;

        case 'U' :
            for (int i =0;i < SIZE;i++){
                for (int j=0;j < SIZE; j++){
                    image[SIZE - 1 -i][j] = image[i][j]; //switching columns which are corresponding to each other but starting from bottom first
                    image[i][j]=image[SIZE - 1 -i][j]; //returning back the changes to the original image in which this makes some pixels to be lost
                }
            }
            break;

        case 'L' :
            for (int i =0;i < SIZE;i++){
                for (int j=0;j < SIZE; j++){
                    image[i][SIZE - 1 - j] = image[i][j]; //switching rows which are corresponding to each other but starting from bottom first
                    image[i][j] = image[i][SIZE - 1 - j]; //returning back the changes to the original image in which this makes some pixels to be lost
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
    cin >> ans;

    for(int i = 0;i < SIZE;i++){
        for(int j = 0;j < SIZE;j++){
            image2[i][j] = image[i][j]; //making the second image equal to the first one to avoid losing pixels
        }
    }

    switch(ans){
        case '1':
            for(int i =0;i < SIZE/2;i++){
                for(int j=0;j < SIZE/2;j++){
                    image[r][c] = image2[i][j];
                    image[r][c+1] = image2[i][j];
                    image[r+1][c] = image2[i][j];
                    image[r+1][c+1] = image2[i][j];
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

                    image[r][c] = image2[i][j];
                    image[r][c+1] = image2[i][j];
                    image[r+1][c] = image2[i][j];
                    image[r+1][c+1] = image2[i][j];
                    c+=2;
                }
                c=0;
                r+=2;
            }
            break; //same as first quad but now working on second

        case '3':
            for(int i =SIZE/2;i < SIZE;i++){
                for(int j=0;j < SIZE/2;j++){

                    image[r][c] = image2[i][j];
                    image[r][c+1] = image2[i][j];
                    image[r+1][c] = image2[i][j];
                    image[r+1][c+1] = image2[i][j];
                    c+=2;
                }
                c=0;
                r+=2;
            }
            break; //third quad

        case '4':
            for(int i =SIZE/2;i < SIZE;i++){
                for(int j=SIZE/2;j < SIZE;j++){

                    image[r][c] = image2[i][j];
                    image[r][c+1] = image2[i][j];
                    image[r+1][c] = image2[i][j];
                    image[r+1][c+1] = image2[i][j];
                    c+=2;
                }
                c=0;
                r+=2;
            }
            break; //fourth quad

    }
}



void shuffle(){
    unsigned char quads[4][SIZE/2][SIZE/2]; // Make an array of four small images to store quads form the original image.

    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++) // Store the pixels from the original image to quads.
        {
            int p = image[i][j];
            if(i < 128 && j < 128){
                quads[0][i][j] = p;
            }
            else if(i < 128 && j > 127){
                quads[1][i][j-128] = p;
            }
            else if(i > 127 && j < 128){
                quads[2][i-128][j] = p;
            }
            else if(i > 127 && j > 127){
                quads[3][i-128][j-128] = p;
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
    for(int i = 0; i < 4; i++) // Checking if the user's numbers are valid.
    {
        if(check[i] != inputs[i]){
            checker = false;
            break;
        }
    }
    if(checker) // If the users's numbers are valid store the pixels from the quads into the image in the new order.
    {
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                if(i < 128 && j < 128){
                    image[i][j] = quads[i1-1][i][j]; 
                } // i1, i2, i3 and i4 are the new order, we use them to decide which quad to take pixels from.

                else if(i < 128 && j > 127){
                    image[i][j] = quads[i2-1][i][j-128];
                }

                else if(i > 127 && j < 128){
                    image[i][j] = quads[i3-1][i-128][j];
                }

                else{
                    image[i][j] = quads[i4-1][i-128][j-128];
                }
            }
        }
    }
    else{
        cout << "invalid input!\n";
        shuffle();
    }
}



// void shuffle() {
//         unsigned char quad1[SIZE][SIZE];
//         unsigned char quad2[SIZE][SIZE];
//         unsigned char quad3[SIZE][SIZE];
//         unsigned char quad4[SIZE][SIZE];
//         //declaring four images for each quad to shuffle between them
//         char w, x, y, z;
//         int r = 0, c = 0;
//         for (int i = 0; i < SIZE / 2; i++) {
//             for (int j = 0; j < SIZE / 2; j++) {
//                 quad1[r][c] = image[i][j];
//                 c += 1;
//             }
//             r += 1;
//             c = 0;
//         }
//         //this loop for making first quad equal to the first quad in original picture
//         r=0,c=0; //returning back to zero for each loop so not to work on increased value for them
//         for (int i = 0; i < SIZE/2; i++) {
//             for (int j = SIZE / 2; j < SIZE; j++) {
//                 quad2[r][c] = image[i][j];
//                 c += 1;
//             }
//             r += 1;
//             c = 0;
//         }
//         //this loop for making second quad equal to the second quad in original picture
//         r=0,c=0;
//         for (int i = SIZE / 2; i < SIZE; i++) {
//             for (int j = 0; j < SIZE / 2; j++) {
//                 quad3[r][c] = image[i][j];
//                 c += 1;
//             }
//             r += 1;
//             c=0;
//         }
//         //this loop for making third quad equal to the third quad in original picture
//         r=0,c=0;
//         for (int i = SIZE / 2; i < SIZE; i++) {
//             for (int j = SIZE / 2; j < SIZE; j++) {
//                 quad4[r][c] = image[i][j];
//                 c += 1;
//             }
//             r += 1;
//             c = 0;
//         }
//         //this loop for making fourth quad equal to the fourth quad in original picture
//         cout << "Please enter shuffle order ";
//         cin >> w >> x >> y >> z;
//         r = 0,c = 0;
//         switch (w) {
//             case '1' :
//                 for (int i = 0; i < SIZE / 2; i++) {
//                     for (int j = 0; j < SIZE / 2; j++) {
//                         image[i][j] = quad1[r][c];
//                         c += 1;
//                     }
//                     r += 1;
//                     c = 0;
//                 }   //the increments for replacing each pixel in the photo
//                 break;
//                 //if the user enters first quad to be replaced with first quad , the new declared quad image will be replaced in the original photo
//             case '2' :
//                 for (int i = 0; i < SIZE/2; i++) {
//                     for (int j = 0; j < SIZE/2; j++) {
//                         image[i][j] = quad2[r][c];
//                         c += 1;
//                     }
//                     r += 1;
//                     c = 0;
//                 }
//                 break;
//                 //if the user enters first quad to be replaced with second quad , the new declared quad image will be replaced in the original photo
//             case '3':
//                 for (int i = 0; i < SIZE/2; i++) {
//                     for (int j = 0; j < SIZE / 2; j++) {
//                         image[i][j] =quad3[r][c];
//                         c += 1;
//                     }
//                     r += 1;
//                     c = 0;
//                 }
//                 break;
//                 //if the user enters first quad to be replaced with third quad , the new declared quad image will be replaced in the original photo
//             case '4' :
//                 for (int i = 0; i < SIZE/2; i++) {
//                     for (int j = 0; j < SIZE/2; j++) {
//                         image[i][j] = quad4[r][c];
//                         c += 1;
//                     }
//                     r += 1;
//                     c = 0;
//                 }
//                 break;
//                 //if the user enters first quad to be replaced with fourth quad , the new declared quad image will be replaced in the original photo
//         }
//         r=0,c=0;
//         switch (x) { //the same as first case goes here but instead we're working on the second quad and putting in it what the user ordered
//             case '1' :
//                 for (int i = 0; i < SIZE / 2; i++) {
//                     for (int j = SIZE/2; j < SIZE; j++) {
//                         image[i][j] = quad1[r][c];
//                         c += 1;
//                     }
//                     r += 1;
//                     c = 0;
//                 }
//                 break;
//             case '2' :
//                 for (int i = 0; i < SIZE/2; i++) {
//                     for (int j = SIZE/2; j < SIZE; j++) {
//                         image[i][j] = quad2[r][c];
//                         c += 1;
//                     }
//                     r += 1;
//                     c = 0;
//                 }
//                 break;
//             case '3':
//                 for (int i = 0; i < SIZE/2; i++) {
//                     for (int j = SIZE/2; j < SIZE; j++) {
//                         image[i][j] =quad3[r][c];
//                         c += 1;
//                     }
//                     r += 1;
//                     c = 0;
//                 }
//                 break;
//             case '4' :
//                 for (int i = 0; i < SIZE/2; i++) {
//                     for (int j = SIZE/2; j < SIZE; j++) {
//                         image[i][j] = quad4[r][c];
//                         c += 1;
//                     }
//                     r += 1;
//                     c = 0;
//                 }
//                 break;
//         }
//         r=0,c=0;
//         switch (y) { //working the third quad
//             case '1' :
//                 for (int i = SIZE/2; i < SIZE; i++) {
//                     for (int j = 0; j < SIZE / 2; j++) {
//                         image[i][j] = quad1[r][c];
//                         c += 1;
//                     }
//                     r += 1;
//                     c = 0;
//                 }
//                 break;
//             case '2' :
//                 for (int i = SIZE/2; i < SIZE; i++) {
//                     for (int j = 0; j < SIZE/2; j++) {
//                         image[i][j] = quad2[r][c];
//                         c += 1;
//                     }
//                     r += 1;
//                     c = 0;
//                 }
//                 break;
//             case '3':
//                 for (int i = SIZE/2; i < SIZE; i++) {
//                     for (int j = 0; j < SIZE / 2; j++) {
//                         image[i][j] =quad3[r][c];
//                         c += 1;
//                     }
//                     r += 1;
//                     c = 0;
//                 }
//                 break;
//             case '4' :
//                 for (int i = SIZE/2; i < SIZE; i++) {
//                     for (int j = 0; j < SIZE/2; j++) {
//                         image[i][j] = quad4[r][c];
//                         c += 1;
//                     }
//                     r += 1;
//                     c = 0;
//                 }
//                 break;
//         }
//         r=0,c=0;

//         switch (z) { //working on fourth quad
//             case '1' :
//                 for (int i = SIZE/2; i < SIZE; i++) {
//                     for (int j = SIZE/2; j < SIZE; j++) {
//                         image[i][j] = quad1[r][c];
//                         c += 1;
//                     }
//                     r += 1;
//                     c = 0;
//                 }
//                 break;

//             case '2' :
//                 for (int i =SIZE/2; i < SIZE; i++) {
//                     for (int j = SIZE/2; j < SIZE; j++) {
//                         image[i][j] = quad2[r][c];
//                         c += 1;
//                     }
//                     r += 1;
//                     c = 0;
//                 }
//                 break;

//             case '3':
//                 for (int i = SIZE/2; i < SIZE; i++) {
//                     for (int j = SIZE/2; j < SIZE ; j++) {
//                         image[i][j] =quad3[r][c];
//                         c += 1;
//                     }
//                     r += 1;
//                     c = 0;
//                 }
//                 break;

//             case '4' :
//                 for (int i = SIZE/2; i < SIZE; i++) {
//                     for (int j = SIZE/2; j < SIZE; j++) {
//                         image[i][j] = quad4[r][c];
//                         c += 1;
//                     }
//                     r += 1;
//                     c = 0;
//                 }
//                 break;

//             default:
//                 cout << "invalid input!\n";
//                 shuffle();
//                 break;
//         }
// }