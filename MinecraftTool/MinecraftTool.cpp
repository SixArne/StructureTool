#include <iostream>

#include <fstream>
#include <string>
#define NOMINMAX
#include <iomanip>
#include <Windows.h>

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

#include <locale>
#include <vector>
#include <typeindex>

#include "StructureLoader.h"

std::string ReadFile(const char* source)
{
    std::string contents{};

    std::ifstream file{source};

    contents.assign(
        std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>()
    );

    return contents;
}

struct OBJ
{
	std::vector<float> vertices{};
    std::vector<float> normals{};
    std::vector<const char*> faces{};
};

template <typename T>
void GetData(rapidjson::Document& jsonDoc, std::string key, std::vector<T>& container)
{
    const rapidjson::Value& vField = jsonDoc[key.c_str()];
    for (rapidjson::Value::ConstValueIterator itr = vField.Begin(); itr != vField.End(); itr++)
    {
        container.emplace_back(itr->Get<T>());
    }
}

void ReadFileAsOBJ(const wchar_t* source, OBJ& obj)
{
    auto is = std::ifstream{ source };
    if (is)
    {
        rapidjson::IStreamWrapper isw{ is };
        rapidjson::Document jsonDoc{};
        jsonDoc.ParseStream(isw);

        GetData<float>(jsonDoc, "vertices", obj.vertices);
        GetData<float>(jsonDoc, "normals", obj.normals);
        GetData<const char*>(jsonDoc, "faces", obj.faces);
    }
}


void LoadProgramArguments(int argc, wchar_t* argv[], std::vector<std::wstring>& args)
{
    for (int i{}; i < argc; i++)
    {
        args.emplace_back(argv[i]);
    }
}

bool HasOutputArguments(int argc, wchar_t* argv[], std::wstring& output)
{
	for (int i{}; i < argc; i++)
	{
        const auto hasOutputFlag = std::wstring(argv[i]) == L"-o";
		if (hasOutputFlag) // 0 => contains
		{
            if (i + 1 <= argc)
            {
                output = argv[i + 1];
                return true;
            }

            throw std::runtime_error("-o provided but no output path found behind it.");
		}
	}

    return false;
}

void HasInputArguments(int argc, wchar_t* argv[], std::wstring& output)
{
    for (int i{}; i < argc; i++)
    {
        const bool hasInputFlag = std::wstring(argv[i]) == L"-i";
        if (hasInputFlag) // 0 => contains
        {
            if (i + 1 <= argc)
            {
                output = argv[i + 1];

                // argument found so stop looking
                return;
            }
            else
            {
                throw std::runtime_error("-i provided but no input path found behind it.");
            }
        }
    }
    throw std::runtime_error("-i flag not provided.");
}

int wmain(int argc, wchar_t* argv[], wchar_t* envp[])
{
    // Set console code page to UTF-8 so console knows how to interpret string data
    SetConsoleOutputCP(CP_UTF8);

    // Enable buffering to prevent VS from chopping up UTF-8
    setvbuf(stdout, nullptr, _IOFBF, 1000);

    Structure outStructure{};
    StructureLoader::LoadStructureFromJSON("Data/structure.json", outStructure);
    //if (argc >= 3)
    //{
    //    // Check for custom input path
    //    std::wstring inputLocation{};
    //    HasInputArguments(argc, argv, inputLocation);

    //    // Check for custom output path
    //    std::wstring outputLocation{};
    //    const bool hasOutput = HasOutputArguments(argc, argv, outputLocation);

    //    OBJ obj{};
    //    ReadFileAsOBJ(argv[2], obj);


    //    if (hasOutput)
    //    {
    //        std::wcout << "Writing to specified file";
    //    }
    //    else
    //    {
    //        std::wcout << "Writing to default file";
    //    }

    //    //__debugbreak();
    //}
}
