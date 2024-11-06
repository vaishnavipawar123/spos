#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <tuple>
using namespace std;

int LC = 0;  // Location counter initialization

// Mnemonic dictionary for assembly language
map<string, tuple<string, string, int>> mnemonics = {
    {"STOP", make_tuple("00", "IS", 0)},
    {"ADD", make_tuple("01", "IS", 2)},
    {"SUB", make_tuple("02", "IS", 2)},
    {"MUL", make_tuple("03", "IS", 2)},
    {"MOVER", make_tuple("04", "IS", 2)},
    {"MOVEM", make_tuple("05", "IS", 2)},
    {"COMP", make_tuple("06", "IS", 2)},
    {"BC", make_tuple("07", "IS", 2)},
    {"DIV", make_tuple("08", "IS", 2)},
    {"READ", make_tuple("09", "IS", 1)},
    {"PRINT", make_tuple("10", "IS", 1)},
    {"LTORG", make_tuple("05", "AD", 0)},
    {"ORIGIN", make_tuple("03", "AD", 1)},
    {"START", make_tuple("01", "AD", 1)},
    {"EQU", make_tuple("04", "AD", 2)},
    {"DS", make_tuple("01", "DL", 1)},
    {"DC", make_tuple("02", "DL", 1)},
    {"END", make_tuple("AD", "", 0)}
};

// Register map
map<string, int> REG = {
    {"AREG", 1}, {"BREG", 2}, {"CREG", 3}, {"DREG", 4}
};

map<string, pair<int, int>> symtab;  // Symbol Table
vector<int> pooltab;  // Pool Table
vector<string> lit;  // Literal Table
int symindex = 0;

// Function to print symbol table
void printSymTab() {
    cout << "Symbol Table:\n";
    for (const auto& sym : symtab) {
        cout << sym.first << "\t" << sym.second.first << "\n";
    }
}

// Function to print literal table
void printLitTab() {
    cout << "Literal Table:\n";
    for (const auto& literal : lit) {
        cout << literal << "\n";
    }
}

// Function to print pool table
void printPoolTab() {
    cout << "Pool Table:\n";
    for (const auto& pool : pooltab) {
        cout << pool << "\n";
    }
}

// Function to handle END directive
void END(ofstream &ifp) {
    int z = 0;
    ifp << "\t(AD,02)\n";
    for (auto &x : lit) {
        if (x.find("**") != string::npos) {
            pooltab.push_back(z);
            ifp << "\t(AD,05)\t(DL,02)\n";
            LC++;
        }
        z++;
    }
    printLitTab();
    printPoolTab();
}

// Function to handle LTORG mnemonic
void LTORG(ofstream &ifp) {
    int z = 0;
    for (auto &x : lit) {
        if (x.find("**") != string::npos) {
            pooltab.push_back(z);
            ifp << "\t(AD,05)\t(DL,02)\n";
            LC++;
        }
        z++;
    }
}

// Function to handle ORIGIN mnemonic
void ORIGIN(ofstream &ifp, string addr) {
    ifp << "\t(AD,03)\t(C," << addr << ")\n";
    LC = stoi(addr);
}

// Function to handle DS mnemonic
void DS(ofstream &ifp, string size) {
    ifp << "\t(DL,01)\t(C," << size << ")\n";
    LC += stoi(size);
}

// Function to handle DC mnemonic
void DC(ofstream &ifp, string value) {
    ifp << "\t(DL,02)\t(C," << value << ")\n";
    LC++;
}

// Function to detect and handle mnemonic
void detectMnemonic(ofstream &ifp, vector<string> words) {
    if (words[0] == "START") {
        LC = stoi(words[1]);
        ifp << "\t(AD,01)\t(C," << LC << ")\n";
    } else if (words[0] == "END") {
        END(ifp);
    } else if (words[0] == "LTORG") {
        LTORG(ifp);
    } else if (words[0] == "ORIGIN") {
        ORIGIN(ifp, words[1]);
    } else if (words[0] == "DS") {
        DS(ifp, words[1]);
    } else if (words[0] == "DC") {
        DC(ifp, words[1]);
    } else {
        ifp << "\t(IS," << get<0>(mnemonics[words[0]]) << ")\n";
        LC++;
    }
}

int main() {
    ifstream file("input.txt");
    ofstream ifp("inter_code.txt", ios::trunc);
    if (!file.is_open()) {
        cout << "Error: input.txt file not found!\n";
        return 1;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> words;
        string word;

        while (ss >> word) {
            words.push_back(word);
        }

        if (words.size() == 0) continue;

        cout << "Processing: " << line << "\n";
        detectMnemonic(ifp, words);
    }

    file.close();
    ifp.close();

    // Writing Symbol Table and Pool Table
    ofstream symFile("SymTab.txt", ios::trunc);
    for (const auto& sym : symtab) {
        symFile << sym.first << "\t" << sym.second.first << "\n";
    }
    symFile.close();

    ofstream poolFile("PoolTab.txt", ios::trunc);
    for (const auto& pool : pooltab) {
        poolFile << pool << "\n";
    }
    poolFile.close();

    return 0;
}

//Input.txt File:

START 100
MOVER AREG, =5
ADD BREG, =10
LTORG
END


//Output:

inter_code.txt file:
	(AD,01)	(C,100)
	(IS,04)
	(DL,02)	(C,5)
	(IS,01)
	(DL,02)	(C,10)
	(AD,05)	(DL,02)
	(AD,02)

PoolTab.txt:
0
1

