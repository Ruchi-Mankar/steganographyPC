# steganographyPC
git clone https://github.com/Ruchi-Mankar/steganographyPC.git  
go to directory then open terminal  
then: g++ encode.cpp -o encode2 \`pkg-config --cflags --libs opencv4\` -lstdc++ -fopenmp  
then: g++ decode.cpp -o decode2 \`pkg-config --cflags --libs opencv4\` -lstdc++ -fopenmp  
add text in text.txt  
to run:  
./en lenna.png text.txt len.png  
./decode len.png  
