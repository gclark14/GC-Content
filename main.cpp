#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class GCContentCalculator{
	
private:
	string dataset;
	struct Fasta{
		string id;
		string dna;
	};
	vector<Fasta> table;

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

	void popTable(ifstream& fin){
		//table.resize(getFastaCount(fin));	
		for(int i = 0; i < getFastaCount(fin); i++){
			Fasta f;
			getline(fin,f.id);
			getline(fin,f.dna);
			table.push_back(f);
		}
	}

	void printTable(){
		for(int i = 0; i < table.size(); i++){
			cout << table.at(i).id;
			cout << '\n' << table.at(i).dna;
		}
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
	fin.open(argv[1]);
	gcalc.popTable(fin);
	gcalc.printTable();
	//gcalc.setDataset(fin);
	//gcalc.setTable();
	//cout << "\n\n";
	//cout << gcalc.getDataset();
}
