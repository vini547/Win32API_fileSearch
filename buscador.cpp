#include <windows.h>
#include <string>
#include <iostream>

using namespace std;

void TraverseDirectories(const std::wstring& path, const std::wstring& extension, const std::wstring& searchString)
{
    WIN32_FIND_DATAW findData;
    std::wstring searchPath = path + L"\\*";
    HANDLE hFind = FindFirstFileW(searchPath.c_str(), &findData);

    if (hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                if (wcscmp(findData.cFileName, L".") != 0 && wcscmp(findData.cFileName, L"..") != 0)
                {
                    std::wstring subDir = path + L"\\" + findData.cFileName;
                    TraverseDirectories(subDir, extension, searchString);
                }
            }
            else
            {
                std::wstring filename = findData.cFileName;
                if (filename.length() > extension.length() &&
                    filename.substr(filename.length() - extension.length()) == extension &&
                    filename.find(searchString) != std::wstring::npos)
                {
                    std::wstring filePath = path + L"\\" + filename;
                    std::wcout << filePath << std::endl;
                }
            }
        } while (FindNextFileW(hFind, &findData) != 0);

        FindClose(hFind);
    }
}

int main()
{
    std::wstring rootPath;
    std::wstring extension;
    std::wstring searchString;

    std::wcout << "Enter the root path: ";
    std::getline(std::wcin, rootPath);

    std::wcout << "Enter the file extension: ";
    std::getline(std::wcin, extension);

    std::wcout << "Enter the search string: ";
    std::getline(std::wcin, searchString);

    TraverseDirectories(rootPath, extension, searchString);
    cin.get();

    return 0;
}
