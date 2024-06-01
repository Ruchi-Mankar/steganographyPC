#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <opencv2/opencv.hpp>
#include <omp.h>
using namespace std;
using namespace cv;

void LSB(unsigned char *input, char *message, int message_size, int image_size) {
  #pragma omp parallel for
  for (int offset = 0; offset < image_size * 3; ++offset) {//loops through each byte in image
    // 8 threads process one char of 8 bits
    int charno = offset / 8;
    if (charno >= message_size) {
      continue;//skip if current byte in the image data exceeds the size of the message
    }
    //  process start from the first bit on the left
    int bit_count = 7 - (offset % 8);//calculates bit position in current byte of message
    char ch = message[charno] >> bit_count;
    // if this bit is 1, then put 1 to the image RGB value, if bit == 0, put 0
    if (ch & 1) {
      input[offset] |= 1;
    } else {
      input[offset] &= ~1;
    }
  }
}

int main(int argc, char **argv) {

  // Checks if proper number of arguments are passed
  if (argc != 4) {
    cout << "Number of Arguments Error" << endl;
    exit(-1);
  }

  // Stores original image
  Mat image = imread(argv[1]);
  if (image.empty()) {
    cout << "Load Image Error" << endl;
    exit(-1);
  }

  // Open file for text information
  ifstream file;
  file.open(argv[2]); // open the input file
  if (!file.is_open()) {
    cout << "File Error" << endl;
    exit(-1);
  }

  stringstream strStream;
  strStream << file.rdbuf();    // read the file
  string str = strStream.str(); // str holds the content of the file
  // +1 is space for end of string '\0'
  char arr[str.length() + 1];
  cout << "Encoded Successfully" << endl;
  cout << "load text file size is " << str.size() << endl;
  strcpy(arr, str.c_str());

  // check if text's bit of size larger than image  bit of RGB
  const int image_size = image.step * image.rows;
  int message_size = str.size() + 1;
  if ((message_size) * 8 > image_size * 3) {
    printf("The input text file is too big, choose a larger image");
    exit(-1);
  }

  unsigned char *input_data = image.data;

  LSB(input_data, arr, message_size, image_size);

  // Writes the steganographic image
  imwrite(argv[3], image);

  return 0;
}
