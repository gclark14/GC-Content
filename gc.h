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
	GCContentCalculator(){dataset = "";}	

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
		calculateGC(); 
		table.pop_back();
	}

	void printLargestFrequency(){
		Fasta largest = getLargestFasta();
		cout << "Largest Fasta:\n";
		cout << "ID: " << largest.id;
		cout << fixed << "\nFrequency: " << largest.frequency << '\n';
	}

	Fasta getLargestFasta(){
		double max = 0;
		int i;
		for(i = 0; i < table.size(); ++i){
			if(table.at(i).frequency > max) 
				max = table.at(i).frequency;
		}
		return table.at(i-1);
	}

	void printTable(){
		for_each(table.begin(), table.end(), printFasta);
	}

	static void printFasta(Fasta f){
		cout << '\n' << f.id;
		cout << fixed << '\n' << f.frequency << '\n';
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
};
