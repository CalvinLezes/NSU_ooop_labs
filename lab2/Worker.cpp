#include "Worker.h"
#include <fstream>
#include <iostream>

ConveyorException::ConveyorException(const string& message) : error{ message } {}

const char* ConveyorException::error_message(){
    return error.c_str();
}

Parser::Parser(string workflow) : workflow{ workflow } {}

void Parser::Parse() {
    ifstream workflow_file;
    workflow_file.exceptions(ifstream::failbit | ifstream::badbit);
    workflow_file.open(workflow);
    string word;
    int id = 0;
    int start_id = 0;
    int end_id = 0;
    workflow_file >> word;

    if (word != "desc") {
        throw ConveyorException("Workflow blocks must begin with desc");
    }

    while (workflow_file >> word) {
        if (word == "csed"){
            break;
        }
        if (isdigit(word[0]) != 0) {
            id = stoi(word);
            continue;
        }
        if (word == "=") {
            continue;
        }
        if (word == "replace") {
            string word1;
            string word2;
            workflow_file >> word1;
            workflow_file >> word2;
            auto replace = make_shared<Replace>(word1, word2);
            block_map.insert({ id, replace });
            id = 0;
            continue;
        }
        if (word == "readfile") {
            string in_file_name;
            workflow_file >> in_file_name;
            auto read = make_shared<Readfile>(in_file_name);
            block_map.insert({ id, read });
            start_id = id;
            id = 0;
            continue;
        }
        if (word == "writefile") {
            string out_file_name;
            workflow_file >> out_file_name;
            auto write = make_shared<Writefile>(out_file_name);
            block_map.insert({ id, write });
            end_id = id;
            id = 0;
            continue;
        }
        if (word == "grep") {
            string word_to_find;
            workflow_file >> word_to_find;
            auto grep = make_shared<Grep>(word_to_find);
            block_map.insert({ id, grep });
            id = 0;
            continue;
        }
        if (word == "sort") {
            auto sort = make_shared<Sort>();
            block_map.insert({ id, sort });
            id = 0;
            continue;
        }
        if (word == "dump") {
            string file_name;
            workflow_file >> file_name;
            auto dump = make_shared<Dump>(file_name);
            block_map.insert({ id, dump });
            id = 0;
            continue;
        }
        if (workflow_file.eof()) {
            throw ConveyorException("Workflow blocks must end with csed");
        }
    }
    vector<int> conveyor;
    while (workflow_file >> word) {
        if (isdigit(word[0]) != 0) {
            id = stoi(word);
            conveyor.push_back(id);
            
        }
        if (word == "->") {
            continue;
        }
        if (workflow_file.eof()) {
            break;
        }
    }
    if (conveyor.empty())
    {
        throw ConveyorException("Conveyor is empty");
    }
    if (conveyor[0] != start_id)
    {
        throw ConveyorException("First operation must be ReadFile");
    }
    if (conveyor[conveyor.size() - 1] != end_id)
    {
        throw ConveyorException("Last operation must be WriteFile");
    }
    vector<string> text;
    for (size_t i = 0; i < conveyor.size(); i++)
    {
        text = block_map[conveyor[i]]->Execute(text);
    }
}

Readfile::Readfile(const string& in_file_name) : in_file_name{ in_file_name } {}

vector<string> Readfile::Execute(vector<string>& text){
    ifstream in_file(in_file_name);
    vector<string> in_text;
    string line;
    while (getline(in_file, line)){
        in_text.push_back(line);
    }
    return in_text;
}

Writefile::Writefile(const string& out_file_name): out_file_name{ out_file_name } {}

vector<string> Writefile::Execute(vector<string>& text){
    ofstream out_file(out_file_name);
    for (size_t i = 0; i < text.size(); i++){
        out_file << text[i] << endl;
    }
    return text;
}

Grep::Grep(const string& word) : word{ word } {}

vector<string> Grep::Execute(vector<string>& text){
    for (size_t i = 0; i < text.size(); i++){
        if (text[i].find(word) == string::npos){
            text.erase(text.begin() + i);
        }
    }
    return text;
}

Sort::Sort() {}

vector<string> Sort::Execute(vector<string>& text){
    sort(text.begin(), text.end());
    return text;
}

Replace::Replace(string word1, string word2) : word1{ word1 }, word2{ word2 } {}

vector<string> Replace::Execute(vector<string>& text){
    size_t pos_in_string = 0;
    for (size_t i = 0; i < text.size(); i++){
        pos_in_string = 0;
        while ((pos_in_string = text[i].find(word1, pos_in_string)) != string::npos){
            text[i].replace(pos_in_string, word1.length(), word2);
            pos_in_string += word2.length();
        }
    }
    return text;
}

Dump::Dump(const string& dump_file_name) : dump_file_name{ dump_file_name } {}

vector<string> Dump::Execute(vector<string>& text){
    ofstream dump_file(dump_file_name);
    for (size_t i = 0; i < text.size(); i++){
        dump_file << text[i] << endl;
        
    }
    return text;
}