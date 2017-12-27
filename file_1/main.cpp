#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Split{
private:
	long size,mid;
	string namafile;
	char *buffer;
	bool isopen;
	string buff;
	fstream infile, part1, part2, outfile;
public:
	~Split(){
		if(isopen){
			infile.close();
		}
	}
	Split(){
		size = 1025;
	}
	Split(string namafile){
		this->namafile = namafile;
		infile.open(namafile, ios::binary | ios::in);

		if(infile.is_open()){ 
			isopen = true;
			infile.seekg(0, ios::end);
			size = infile.tellg();
			infile.seekg(ios::beg);
			mid = floor(size/2.0);
		}
		else{ isopen = false;
				cout<<"File gagal dibuka, cek kembali nama file"; 
		}
	}
	void clone_file(){
		outfile.open(namafile + "(copy).jpg", ios::binary | ios::out);
		
		if(isopen){
			infile.seekg(0, ios::end);
			size = infile.tellg();
			infile.seekg(ios::beg);

			buffer = new char[size];
			while(infile.read(buffer, size)){
				outfile.write(buffer, infile.gcount());
			}

			infile.close();
			outfile.close();
		}
	}
	void split_them(){
		if(isopen)
		{
			part1.open("clone.Part1", ios::binary | ios::out); 
			part2.open("clone.Part2", ios::binary | ios::out);

			buffer = new char[mid];
			infile.read(buffer, mid);
				part1.write(buffer, mid);
			delete [] buffer;
			part1.close();

			infile.seekg(mid+1);
			buffer = new char[size-mid];
			infile.read(buffer, size-mid);
				part2.write(buffer, size-mid);
			delete[] buffer;
			part2.close();

			cout<<"File berhasil di split menjadi 2 part.\n";
		}else{
			cout<<"File gagal dibuka, cek kembali nama file";
		}
	}
	void join_them(){
		outfile.open("Hasil_join.jpg", ios::binary | ios::out);
		part1.open("clone.Part1", ios::binary | ios::in);
		part2.open("clone.Part2", ios::binary | ios::in); 

		part1.seekg(0, ios::end);
		size = part1.tellg();
		part1.seekg(ios::beg);
		buffer = new char[size];
		while(part1.read(buffer, size)){
			outfile.write(buffer, part1.gcount());
		}
		delete[] buffer;
		part1.close();

		outfile.seekg(size+1);
		part2.seekg(0, ios::end);
		size = part2.tellg();
		part2.seekg(ios::beg);
		buffer = new char[size];
		while(part2.read(buffer, size)){
			outfile.write(buffer, part2.gcount());
		}
		delete[] buffer;
		part2.close();

		cout<<"Rejoining File selesai!!!\n";
	}
};
void main(){
	Split split("gambar.jpg");
	split.split_them();
	split.join_them();
}