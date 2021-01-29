#include "Worker.h"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2)
        {
            cout << "Wrong input, please include [workflow] file" << std::endl;
        }
        Parser parse(argv[1]);
        Parser parse("workflow.txt");
        parse.Parse();
    }
    catch (ifstream::failure& error)
    {
        cerr << "Exception opening/reading/closing file\n";
    }
    catch (ConveyorException& error)
    {
        cerr << error.error_message();
    }
    return 0;
}
