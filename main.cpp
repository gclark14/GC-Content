#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>

using namespace std;

class GCContentCalculator{
	
private:
	string dataset;
	struct Fasta{
		string id;
		string dna;
		double frequency;
	};

	vector<Fasta> table;

	static void setFrequency(Fasta& f){
		if(f.dna.length() == 0) return;
		int gcCount = 0;
		for(int i = 0; i < f.dna.length(); ++i){
			if(f.dna.at(i) == 'G' or f.dna.at(i) == 'C')
				gcCount++;
		}
		f.frequency = ((double)gcCount/f.dna.length())*100;
	}

	void resetInputFileStream(ifstream& fin){
		fin.clear();
		fin.seekg(0, std::ios::beg);
	}

public:
	void calculateGC(){
		for_each(table.begin(), table.end(), setFrequency); 
	}

	void popTable(ifstream& fin){
		int max = getFastaCount(fin);
		resetInputFileStream(fin);
		for(int i = 0; i <= max; i++){
			Fasta f;
			string s;
			getline(fin,f.id);
			while(fin.peek() != '>' and fin){ 
				char c = fin.peek();
				string temp;
				getline(fin,temp);
				f.dna += temp;
			}
			table.push_back(f);
		}
		calculateGC(); // Faulty function
		table.pop_back();
	}

	void printTable(){
		for_each(table.begin(), table.end(), printFasta);
	}

	static void printFasta(Fasta f){
		cout << '\n' << f.id;
		cout << '\n' << f.frequency << '\n';
	}

	int getFastaCount(ifstream& fin){
		int fastaCount = 0;
		char c;
		while(fin){
			fin >> c;
			if(c == '>')
				fastaCount++;	
		}
		return fastaCount;
	}

	GCContentCalculator(){dataset = "";}	

};

int main(int, char *argv[]){	
	ifstream fin;
	GCContentCalculator gcalc; 
	//fin.open(argv[1]);
	fin.open("test.txt");
	gcalc.popTable(fin);
	gcalc.printTable();
}
