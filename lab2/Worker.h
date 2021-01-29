#ifndef WORKER_H
#define WORKER_H
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>

using namespace std;

    class ConveyorException : exception 
    {
        string error;

    public:
        ConveyorException(const string& message);
        const char* error_message();
    };

    class Worker
    {
    public:
        virtual vector<string> Execute(vector<string>& text) = 0;
    };

    class Parser
    {
        string workflow;
        map<int, shared_ptr<Worker>> block_map;

    public:
        Parser(string workflow);
        void Parse();
    };

    class Readfile : public Worker
    {
        const string in_file_name;

    public:
        Readfile(const string& in_file_name);
        virtual vector<string> Execute(vector<string>& text) override;
    };

    class Writefile : public Worker
    {
        const string out_file_name;

    public:
        Writefile(const string& out_file_name);
        virtual vector<string> Execute(vector<string>& text) override;
    };

    class Grep : public Worker
    {
        const string word;

    public:
        Grep(const string& word);
        virtual vector<string> Execute(vector<string>& text) override;
    };

    class Sort : public Worker
    {
    public:
        Sort();
        virtual vector<string> Execute(vector<string>& text) override;
    };

    class Replace : public Worker
    {
        string word1;
        string word2;

    public:
        Replace(string word1, string word2);
        virtual vector<string> Execute(vector<string>& text) override;
    };

    class Dump : public Worker
    {
        const string dump_file_name;

    public:
        Dump(const string& dump_file_name);
        virtual vector<string> Execute(vector<string>& text) override;
    };
#endif 