#include <iostream>
#include <fstream>
using namespace std;

void main(){
	//fstream myfile, part1, part2;
	//myfile.open("gambar.jpg", ios::binary | ios::in );

	//if(myfile.is_open()){
	//	myfile.seekg(0, ios::end);
	//	double mid = myfile.tellg()/2;
	//	myfile.seekg(ios::beg);
	//	//cursor sudah balik ke awal

	//	part1.open("gambar_part1.jpg", ios::binary|ios::out);
	//	while(myfile.tellg()<mid){
	//		part1<<myfile;
	//	}
	//	part2.open("gambar_part2.jpg", ios::binary|ios::out);
	//	myfile.seekg(mid);
	//	while(myfile.tellg()<mid){
	//		part2<<myfile;
	//	}


	//	myfile.close();
	//	
	//}else{
	//	cout<<"File gagal dibuka\n";
	//}

	fstream mainfile, a, b;
	int mid =0;
	mainfile.open("coba.txt", ios::binary |ios::in);

	if(mainfile.is_open()){
		mainfile.seekg(0, ios::end);
		mid = mainfile.tellg();
		mainfile.seekg(ios::beg);

	}else
		cout<<"File gagal\n";
}