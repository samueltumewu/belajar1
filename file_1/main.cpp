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
	fstream infile, part1, part2, parts[5], outfile;
public:
	~Split(){
		if(isopen){
			infile.close();
		}
	}
	Split(){
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
	void join(string outname){
		outfile.open(outname, ios::binary | ios::out);
		string addr = "C:/SAMUEL/skiptrace/skrptcecbric31.mkv.00";
		char a[2];
		for(int i=1; i<=4; i++){
			itoa(i,a,10);
			parts[i].open(addr+a, ios::binary | ios::in);
			if(!parts[i].is_open())
			{
				cout<<"File "<<i<<" Tidak bisa dibuka!.\n";
				i=100; //keluar loop langsung
			}
		}

		for(int i=1; i<=4; i++)
		{
			parts[i].seekg(0, ios::end);
			size = parts[i].tellg();
			parts[i].seekg(ios::beg);

			buffer = new char[size];
			outfile.seekg(0, ios::end);
			while(parts[i].read(buffer, size)){
				outfile.write(buffer, parts[i].gcount());
			}
			delete[] buffer;
			parts[i].close();
			cout<<size<<endl;
		}

		outfile.close();
		cout<<"SELESAI\n";
	}
	void tambah(){
		outfile.open("c:/samuel/skiptrace.mkv", ios::binary | ios::app);
		infile.open("c:/samuel/skiptrace/skrptcecbric31.mkv.005", ios::binary | ios::in);
		
		infile.seekg(0, ios::end);
		size = infile.tellg();
		infile.seekg(ios::beg);
		
		buffer = new char[size];
		outfile.seekg(0, ios::end);
		while(infile.read(buffer, size)){
			outfile.write(buffer, infile.gcount());
		}
		delete[] buffer;
		infile.close();
		outfile.close();
		cout<<"SELESAI\n";
	}
};

void main(){
	/*
	Split s("gambar.jpg");
	s.split_them();
	s.join_them();
	*/

	Split s;
	s.tambah();

}