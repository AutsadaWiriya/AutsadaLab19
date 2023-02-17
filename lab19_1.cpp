#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream source(filename);
    char format[] = "%[^:]: %d %d %d";
    char n[100] ;
    int a, b, c;
    string textline;
    while(getline(source, textline)){
        sscanf(textline.c_str(), format, n, &a, &b, &c);
        scores.push_back(a+b+c);
        names.push_back( n ) ;
        grades.push_back(score2grade(a+b+c));
    }
}

void getCommand(string &command, string &key){
    cout << "Please input your command: " ;
    string text;
    getline(cin, text);
    char format[] = "%s %[^:]" ;
    char c[100] , k[100];
    sscanf(text.c_str(), format, c, k);
    command = c;
    key = k ;
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    int count = 0 ;
    for(unsigned int i = 0 ; i < names.size() ; i++ ){
        if(key == toUpperStr(names[i])){
            cout << "---------------------------------" << endl;
            cout << names[i] << "'s score = " << scores[i] << endl ;
            cout << names[i] << "'s grade = " << grades[i] << endl ;
            cout << "---------------------------------" << endl;
            count++;
        }
    }
    if(count == 0){
        cout << "---------------------------------" << endl;
        cout << "Cannot found." << endl;
        cout << "---------------------------------" << endl;
    }
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    cout << "---------------------------------" << endl;
    for(unsigned int j = 0 ; j < grades.size() ; j++){
        if(key[0] == (grades[j])){
            cout << names[j] << " (" << scores[j] << ")" << endl;
        }
    }
    cout << "---------------------------------" << endl;
}

int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
