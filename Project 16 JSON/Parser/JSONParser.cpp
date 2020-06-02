#include "JSONParser.h"

//Additional functions to be called leter in startParser
void Parser::inputSave()
{
    std::string fileToSave;
    std::getline(std::cin, fileToSave);

    save(fileToSave.c_str());
}
void Parser::inputSet()
{
    std::string path;
    std::cin >> path;

    std::string toBeChanged;
    std::cin >> toBeChanged;

    if (path.length() == 0 || toBeChanged.length() == 0)
    {
        std::cout << std::endl
                  << "Invalid input, please make sure both the path and the new data were input correctly!\n";
    }
    else
    {
        create(path.c_str(), toBeChanged.c_str());
    }
}
void Parser::inputCreate()
{
    std::string path;
    std::cin >> path;

    std::string toBeCreated;
    std::cin >> toBeCreated;

    if (path.length() == 0 || toBeCreated.length() == 0)
    {
        std::cout << std::endl
                  << "Invalid input, please make sure both the path and the new data were input correctly!\n";
    }
    else
    {
        create(path, toBeCreated);
    }
}
void Parser::inputDelete()
{
    std::string path;
    std::cin >> path;

    if (path.length() == 0)
    {
        std::cout << std::endl
                  << "Invalid input, please make suw both the path was input correctly!\n";
    }
    else
    {
        deleteData(path);
    }
}
void Parser::InputMove()
{
    std::string pathFrom;
    std::cin >> pathFrom;

    std::string pathTo;
    std::cin >> pathTo;

    if (pathFrom.length() == 0 || pathTo.length() == 0)
    {
        std::cout << std::endl
                  << "Invalid input, please make sure both the path and the new data were input correctly!\n";
    }
    else
    {
        create(pathFrom, pathTo);
    }
}
//Functions to validate the file

bool Parser::isLeftSeparator(const char &symbol) const
{
    return ((symbol == '{') || (symbol == '['));
}
bool Parser::isRightSeparator(const char &symbol) const
{
    return ((symbol == '}') || (symbol == ']'));
}
bool Parser::isSeparator(const char &symbol) const
{
    switch (symbol)
    {
    case '{':
        return 1;
        break;
    case '}':
        return 1;
        break;
    case '[':
        return 1;
        break;
    case ']':
        return 1;
        break;
    case ':':
        return 1;
        break;
    case '"':
        return 1;
        break;

    default:
        return 0;
        break;
    }
}
void Parser::validateBraceCount(const std::string &data, std::vector<std::string> &errors) const
{

    size_t left = 0;
    size_t right = 0;

    for (int i = 0; i < data.length(); ++i)
    {
        if (data[i] == '{')
        {
            ++left;
        }
        else if (data[i] == '}')
        {
            ++right;
        }
    }

    if (left != right)
    {
        std::string error = "There are ";
        error.push_back('0' + std::max(left, right) - std::min(left, right));
        error += " unclosed braces!";

        errors.push_back(error);
    }
}
void Parser::validateCrochetCount(const std::string &data, std::vector<std::string> &errors) const
{
    size_t left = 0;
    size_t right = 0;

    for (int i = 0; i < data.length(); ++i)
    {
        if (data[i] == '[')
        {
            ++left;
        }
        else if (data[i] == ']')
        {
            ++right;
        }
    }

    if (left != right)
    {
        std::string error = "There are ";
        error.push_back('0' + std::max(left, right) - std::min(left, right));
        error += " unclosed crochets!";

        errors.push_back(error);
    }
}
void Parser::validateSeparators(const size_t &index, const std::string &data, std::vector<std::string> &errors) const
{
    if (data[index] == ':' && (isRightSeparator(data[index + 1]) || data[index + 1] == ':'))
    {
        std::string error = "Expected data and comma between ";
        error.push_back(data[index]);
        error += " and ";
        error.push_back(data[index + 1]);

        errors.push_back(error);
    }
    else if (isRightSeparator(data[index]) && data[index + 1] == ':')
    {
        std::string error = "Expected comma and key value between ";
        error.push_back(data[index]);
        error += " and ";
        error.push_back(data[index + 1]);
        errors.push_back(error);
    }
    else if (data[index] == '"' && (isLeftSeparator(data[index + 1]) || data[index + 1] == '"'))
    {
        std::string error = "Expected data or : between ";
        error.push_back(data[index]);
        error += " and ";
        error.push_back(data[index + 1]);
        errors.push_back(error);
    }
    else if (data[index] == ',' && (isRightSeparator(data[index + 1]) || data[index + 1] == ',' || fileData[index + 1] == ':'))
    {
        std::string error = "Excessive us of , between ";
        error.push_back(data[index]);
        error += " and ";
        error.push_back(data[index + 1]);
        errors.push_back(error);
    }
}

//Constructors and Destructor
Parser::Parser() : numberOfObjects{0}, objectsInFile{nullptr} {};
Parser::Parser(const Parser &other) : fileData{other.fileData}, numberOfObjects{other.numberOfObjects}, objectsInFile{new JsonPair[numberOfObjects]}
{
    for (int i = 0; i < other.numberOfObjects; ++i)
    {
        this->objectsInFile[i] = other.objectsInFile[i];
    }
}
Parser::~Parser()
{
    numberOfObjects = 0;

    if (this->objectsInFile != nullptr)
    {
        delete[] objectsInFile;
    }
};

//Operators
Parser &Parser::operator=(const Parser &other)
{
    if (this != &other)
    {
        this->fileData = other.fileData;
        this->numberOfObjects = other.numberOfObjects;
        this->objectsInFile = new JsonPair[numberOfObjects];

        for (int i = 0; i < numberOfObjects; ++i)
        {
            this->objectsInFile[i] = other.objectsInFile[i];
        }
    }

    return *this;
};

//Functions from the task guidelines
void Parser::help() const
{
    std::cout << "\n------List of commands------\n";

    std::cout << "\nCommand one:\n";
    std::cout << "Command syntax: open <filename>\n";
    std::cout << "Does: Opens the designated file!\n";

    std::cout << "\nCommand two:\n";
    std::cout << "Command syntax: close\n";
    std::cout << "Does: Closes the current file, without saving the changes!\n";

    std::cout << "\nCommand three:\n";
    std::cout << "Command syntax: save [<path>]\n";
    std::cout << "Does: Save only the chosen JsonValue in the file. If path is not input, then saves all changes in the file!\n";

    std::cout << "\nCommand four:\n";
    std::cout << "Command syntax: saveas <filename> [<path>]\n";
    std::cout << "Does: Saves only the chosen JsonValue in the new file.\nIf path is not input, then saves all data in the new file!\n";

    std::cout << "\nCommand five:\n";
    std::cout << "Command syntax: validate\n";
    std::cout << "Does: Checks if the open file is valid according to the JSON syntax.\nIf there are any erros, prints them out!\n";

    std::cout << "\nCommand six:\n";
    std::cout << "Command syntax: print\n";
    std::cout << "Does: Prints the file data!\n";

    std::cout << "\nCommand seven:\n";
    std::cout << "Command syntax: search<key>\n";
    std::cout << "Does: Prints all values, saved under <key>!\n";

    std::cout << "\nCommand eight:\n";
    std::cout << "Command syntax: set <path> <string>\n";
    std::cout << "Does: Changes the value of the element from <path> with <string>.\nIf <path> or <string> are invalid, prints out the errors!\n";

    std::cout << "\nCommand nine:\n";
    std::cout << "Command syntax: create <path> <string>\n";
    std::cout << "Does: Creates the value of the element from <path> with <string>.\nIf some elements of <path> do not exist, creates them as well.\n If the values already exist,does not change them and announces of their existence.\nIf<path> or <string> are invalid, prints out the errors !\n ";

    std::cout << "\nCommand ten:\n";
    std::cout << "Command syntax: delete <path>\n";
    std::cout << "Does: Deletes the value of the element from <path>.\nIf <path> is invalid, prints out the errors!\n";

    std::cout << "\nCommand eleven:\n";
    std::cout << "Command syntax: move <path_from> <path_to>\n";
    std::cout << "Does: Moves the designated objects from <path_from> to <path_to>.\n If <path_*> is invalid, prints out the errors!\n";

    std::cout << "\n------End of List------\n";
}
void Parser::validate() const
{
    std::vector<std::string> errors;

    validateBraceCount(fileData, errors);

    validateCrochetCount(fileData, errors);

    for (int i = 0; i < fileData.size() - 2; ++i)
    {
        validateSeparators(i, fileData, errors);
    }

    if (errors.empty())
    {
        std::cout << "\nValid!\n";
    }
    else
    {
        for (int i = 0; i < errors.size(); ++i)
        {
            std::cout << std::endl
                      << errors[i]
                      << std::endl;
        }
    }
};

void Parser::print() const
{
    /*std::cout << "{\n";

    for (int i = 0; i < numberOfObjects; ++i)
    {
        std::cout << '    ';
        objectsInFile[i].print();
    }

    std::cout << '}';*/
    size_t wideSpaceCounter = 0;

    for (int i = 0; i < fileData.length(); ++i)
    {
        if (fileData[i] == ',')
        {
            std::cout << fileData[i] << std::endl;
            for (int i = wideSpaceCounter; i > 0; --i)
            {
                std::cout << "    ";
            }
        }
        else if (isLeftSeparator(fileData[i]))
        {
            wideSpaceCounter++;
            std::cout << fileData[i] << std::endl;
            for (int i = wideSpaceCounter; i > 0; --i)
            {
                std::cout << "    ";
            }
        }
        else if (isRightSeparator(fileData[i + 1]))
        {
            wideSpaceCounter--;

            std::cout << fileData[i] << std::endl;
            for (int i = wideSpaceCounter; i > 0; --i)
            {
                std::cout << "    ";
            }
        }
        else
        {
            std::cout << fileData[i];
        }
    }

    std::cout << std::endl;
};
void Parser::search(const std::string &key) const
{
    std::vector<const JsonValue *> listOfObjects;

    for (int i = 0; i < numberOfObjects; ++i)
    {
        if (objectsInFile[i].compareName(key))
        {
            listOfObjects.push_back(objectsInFile[i].getData());
        }

        objectsInFile[i].findByKey(key, listOfObjects);
    }
};
void Parser::set(const std ::string &path, const std::string &newValue)
{
    JsonPath currPath(path);
    std::vector<size_t> elementIndex;

    for (int i = 0; i < numberOfObjects; ++i)
    {
        if (objectsInFile[i].compareName(currPath.getPathPairAt(0).name))
        {
            elementIndex.push_back(i);
        }
    }

    elementIndex.shrink_to_fit();

    if (!elementIndex.size()) ///If we have no elements with the required name, then the path is not valid
    {
        std::cout << "Error! There is no element named " << currPath.getPathPairAt(0).name << "!\n";
        return;
    }
    else if (elementIndex.size() > 1) ///If we have more than one element with the required name, then the path is not valid
    {
        std::cout << "Error! There are more than one elements named " << currPath.getPathPairAt(0).name << "!\n";
        return;
    }
    else if (currPath.getPathPairAt(0).index > -1 && objectsInFile[elementIndex[0]].getType() != JsonValueType::Array) ///If the desired element is not an array and we have an index in the path, then invalid
    {

        std::cout << "Error! The desired element(" << currPath.getPathPairAt(0).name << ") is not an array. No index expected!";

        return;
    }
    else //If the desired element is valid, then we proceed with tracing the path to the desired element
    {
        if (currPath.getPathLength() == 1 && currPath.getPathPairAt(0).index == -1) //If the path stops here, then we proceed to change the value
        {                                                                           //If the pair previously contained an array, but we want to change all of its content we change it here
            objectsInFile[elementIndex[0]].setData(newValue);
        }
        else
        { //If the path is longer or we want to change an element of the found pair's array, we continue here
            objectsInFile[elementIndex[0]].setFind(path, 1, newValue);
        }
    }
}
void Parser::create(const std::string &path, const std::string &toBeCreated) {}
void Parser::deleteData(const std::string &path) {}
void Parser::move(const std ::string &pathFrom, const std::string &pathTo) {}
//File manipulation functions
bool Parser::loadData(std::fstream &input)
{
    char a;

    while (input)
    {
        input >> a;
        fileData.push_back(a);
    }

    fileData.pop_back();

    return 1;
};
bool Parser::seedData(std::fstream &output)
{
    for (int i = 0; i < fileData.size(); ++i)
    {
        output << fileData[i];
    }

    return 1;
};
void Parser::open(const char *fileName)
{
    std::fstream input;
    input.open(fileName, std::ios::in);

    if (input.is_open())
    {
        if (loadData(input))
        {
            std::cout << "Data successfully loaded!\n";
        }
    }
    else
    {
        std::cout << "Will create a new file named "
                  << fileName
                  << "!\n";

        std::fstream output;
        output.open(fileName, std::ios::in);
        output.close();
    }

    input.close();

    validate();
};
void Parser::save(const char *fileName)
{
    std::fstream output;
    output.open(fileName, std::ios::out);

    std::cout << std::endl
              << "Saving data in "
              << fileName
              << "...\n";

    if (output.is_open())
    {
        if (seedData(output))
        {
            std::cout << "Data saved successfully!\n";
        }
        else
        {
            std::cout << "An error has occured, while saving the data!\n";
        }
    }

    output.close();
};
void Parser::close()
{
    std::cout << "\nClosing file!";

    while (fileData.size())
    {
        fileData.pop_back();
    }

    delete[] objectsInFile;
    numberOfObjects = 0;
}

//Main input function

void Parser::startParser()
{
    //The longst function name is 16 characters - lowestattendance
    std::string openedFileName; //If a file has been opned via the open function, we will keep it's name here. No other actions will be allowed while there is no opened file

    std::cout << "Parser successfully started!\n";

    std::string userInput;

    do
    {
        std::cin >> userInput;

        if (!userInput.compare("open"))
        {
            if (openedFileName.size())
            {
                close();
            }

            std::getline(std::cin, openedFileName);
            open(openedFileName.c_str() + 1);
            continue;
        }
        else if (!userInput.compare("help"))
        {
            help();
            continue;
        }
        else if (openedFileName.empty())
        {
            std::cout << "\nYou have not opened a file yet, please use 'open' in order to be able to use additional commands!/n";
        }
        else if (!userInput.compare("close") && !openedFileName.empty())
        {
            std::cout << "\nClosing program!";
            return;
        }
        else if (!userInput.compare("save") && !openedFileName.empty())
        {
            save(openedFileName.c_str() + 1);
            continue;
        }
        else if (!userInput.compare("saveas") && !openedFileName.empty())
        {
            inputSave();
            continue;
        }
        else if (!userInput.compare("exit"))
        {
            std::cout << std::endl
                      << "Exiting the program!\n";
            return;
        }
        else if (!userInput.compare("validate") && !openedFileName.empty())
        {
            validate();
            continue;
        }
        else if (!userInput.compare("print") && !openedFileName.empty())
        {
            print();
            continue;
        }
        else if (!userInput.compare("set") && !openedFileName.empty())
        {
            inputSet();
            continue;
        }
        else if (!userInput.compare("create") && !openedFileName.empty())
        {
            inputCreate();
            continue;
        }
        else if (!userInput.compare("delete") && !openedFileName.empty())
        {
            inputDelete();
            continue;
        }
    } while (true);
}
