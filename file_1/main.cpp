#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void main(){
	long size;
	int mid;
	char *buffer;
	string buff;
	fstream myfile, part1, part2, outfile;

	myfile.open("gambar.jpg", ios::binary | ios::in);
	outfile.open("clone.jpg", ios::binary | ios::out);
	if(myfile.is_open()){
		myfile.seekg(0, ios::end);
		size = myfile.tellg();
		myfile.seekg(ios::beg);

		buffer = new char[size];
		while(myfile.read(buffer, size)){
			outfile.write(buffer, myfile.gcount());
		}

		myfile.close();
		outfile.close();
	}
}