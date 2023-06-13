#include "fileio.h"
#include <fstream>
#include <nlohmann/json.hpp>

FileIO::FileIO(QObject *parent)
    : QObject{parent}
{

}

bool FileIO::read()
{
    std::ifstream saveFile(pathToString());

    if (!saveFile.is_open())
    {
        return false;
    }

    nlohmann::json input;
    saveFile >> input;

    if (!saveFile.good())
    {
        return false;
    }

    setActiveFile(input);
    return true;
}

bool FileIO::write(nlohmann::json output)
{
    setActiveFile(output);

    std::ofstream saveFile(pathToString(), std::ios::trunc);

    if (!saveFile.is_open())
    {
        return false;
    }

    saveFile << m_activeFile;
    return true;
}

std::string FileIO::pathToString()
{
    auto source = m_activeFilePath;
    std::string stringPath = source.toString().toStdString();
    stringPath = stringPath.substr(stringPath.find_first_not_of("file:///"), stringPath.length());
    return stringPath;
}
QUrl FileIO::activeFilePath() const
{
    return m_activeFilePath;
}

void FileIO::setActiveFilePath(const QUrl &newFilePath)
{
    if (m_activeFilePath == newFilePath)
        return;
    m_activeFilePath = newFilePath;
    emit activeFilePathChanged();
}

nlohmann::json FileIO::activeFile() const
{
    return m_activeFile;
}

void FileIO::setActiveFile(nlohmann::json newActiveFile)
{
    if (m_activeFile == newActiveFile)
        return;
    m_activeFile = newActiveFile;
    emit activeFileChanged();
}
