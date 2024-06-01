#include <bits/stdc++.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <omp.h>

using namespace std;
using namespace cv;

string LSB(Mat& image) {
    const int imageByte = image.step * image.rows;
    int image_size = image.cols * image.rows;

    // Allocate memory for message
    char* message = new char[imageByte];

    // Parallelize the LSB extraction process
    #pragma omp parallel for
    for (int offset = 0; offset < imageByte; ++offset) {
        // If RGB value's last bit is 1, set corresponding message bit to 1, otherwise use default 0
        message[offset] = (image.data[offset] & 1) ? 1 : 0;
    }

    // Decode the message from LSB bits
    string decodedMessage = "";
    int i = 0;
    while (i < imageByte - 8) {
        string oneChar = "";
        // Extract 8 bits to form one character
        for (int j = 0; j < 8; ++j) {
            int index = i + j;
            oneChar += to_string(message[index]);
        }

        // Break loop if we encounter 8 consecutive zeros, indicating end of message
        if (oneChar == "00000000") {
            break;
        }

        // Convert binary string to character and append to decoded message
        decodedMessage += (char)stoi(oneChar, nullptr, 2);
        i += 8;
    }

    // Free dynamically allocated memory
    delete[] message;

    return decodedMessage;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "Arguments Error\n";
        exit(-1);
    }

    Mat image = imread(argv[1]);
    if (image.empty()) {
        cout << "Image Error\n";
        exit(-1);
    }

    string decodedMessage = LSB(image);
    cout << "Decoded message: \n" << decodedMessage << endl;

    return 0;
}