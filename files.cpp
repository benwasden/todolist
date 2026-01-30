#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
using namespace std;

struct Reminder {
    int id;
    string text;
    bool completed;
};

class ManageFile {
    public:
        map<string, string> openFile(const string filename) {
            map<string, string> data_map;
            ifstream file(filename);

            if (!file.is_open()) {
                cerr << "Error: couldn't open file " << filename << "\n";
                return data_map;
            };

            string line;
            while (getline(file, line)) {
                stringstream lineToParse(line);
                string key, value;

                if (getline(lineToParse, key, ',') && getline(lineToParse, value)) {
                    if (!value.empty() && value.back() == '\r') {
                        value.pop_back();
                    }
                    data_map[key] = value;
                };
            };

            file.close();
            return data_map;
        }

        void writeFile(const string filename, const string newLine) {
            fstream file;
            file.open(filename, ios::out | ios::app);

            if (!file.is_open()) {
                cerr << "Error: couldn't open file " << filename << "\n";
            }
            file << newLine << endl;
            cerr << "Reminder successfully added!";
        };
    
        map<string, string> readAllFiles() {
            map<string, string> genFile = openFile("data/general.csv");
            map<string, string> homeFile = openFile("data/home.csv");
            map<string, string> persFile = openFile("data/personal.csv");
            map<string, string> workFile = openFile("data/work.csv");
            genFile.insert(homeFile.begin(), homeFile.end());
            genFile.insert(persFile.begin(), persFile.end());
            genFile.insert(workFile.begin(), workFile.end());
            return genFile;
        };
};