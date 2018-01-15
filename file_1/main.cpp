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
	fstream *parts;
public:
	~Split(){
		if(isopen){
			infile.close();
		}
		if(parts){
			delete [] parts;
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
	void join(string outname, string inname, int jumlah){
		outfile.open(outname, ios::binary | ios::out);
		string addr = inname + ".00";
		char a[2];
		parts = new fstream[jumlah];
		for(int i=0; i<jumlah; i++){
			itoa(i+1,a,10);
			parts[i].open(addr+a, ios::binary | ios::in);
			if(!parts[i].is_open())
			{
				cout<<"File "<<i<<" Tidak bisa dibuka!.\n";
				i=100; //keluar loop langsung
			}
		}

		for(int i=0; i<jumlah; i++)
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
			printf("FILE %d ON PROGRESS...\n", i+1);
		}

		outfile.close();
		cout<<"\n\n---SELESAI---\n";

	}
};

void main(){
	int angka;
	cout<<"	===================="<<endl;
	cout<<"	***SELAMAT DATANG***"<<endl<<endl;
	cout<<"	   PILIHAN  MENU:"<<endl;
	cout<<"	   1. JOIN FILE"<<endl;
	cout<<"	   2. SPLIT FILE"<<endl;
	cout<<"	===================="<<endl;
	cout<<"MASUKKAN ANGKA PILIHAN: ";
	cin>>angka;

	if(angka==1){
		system("CLS");
		string in, out;
		int jumlah;
		cout<<"Masukkan path beserta nama file ASAL dengan format ekst videonya : ";
		cin>>in;
		cout<<"Masukkan path beserta nama file TUJUAN dengan format ekst videonya : ";
		fflush(stdin);
		cin>>out;
		cout<<"Masukkan jumlah part file : ";
		cin>>jumlah;
		system("CLS");
		Split s;
		cout<<"\nLOADING...\n\n";
		s.join(out,in,jumlah);
	}
}