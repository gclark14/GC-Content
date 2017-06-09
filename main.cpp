#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

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

	static void setFrequency(Fasta f){
		int gcCount;
		for(int i = 0; i < f.dna.length(); ++i){
			if(f.dna.at(i) == 'G' or f.dna.at(i) == 'C')
				gcCount++;
		}
		f.frequency = ceil((double)gcCount/f.dna.length())/100;	
	}

	void resetInputFileStream(ifstream& fin){
		fin.clear();
		fin.seekg(0, std::ios::beg);
	}

public:
	void setTable(){
		for(int i = 0; i < dataset.length(); i++){
			if(dataset.at(i) == '>'){
				Fasta currentFasta;
				currentFasta.id = dataset.substr(i+1,i+13);
				cout << "\nConditional char: " << dataset.at(i) << '\n';
				cout << "Fasta ID: " << currentFasta.id;
			}
		}

	}

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
	}

	void printTable(){
		for_each(table.begin(), table.end(), printFasta);
	}

	static void printFasta(Fasta f){
		cout << '\n' << f.id;
		cout << '\n' << f.dna;
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

	void setDataset(ifstream& fin){
		while(fin){	
			string currentLine;
			getline(fin, currentLine); 
			dataset = dataset + '\n' + currentLine;
		}
	}

	string getDataset(){
		return dataset;
	}

};

int main(int, char *argv[]){	
	ifstream fin;
	GCContentCalculator gcalc; 
	//fin.open(argv[1]);
	fin.open("test.txt");
	gcalc.popTable(fin);
	gcalc.printTable();
}
