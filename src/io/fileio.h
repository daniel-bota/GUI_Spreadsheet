#ifndef FILEIO_H
#define FILEIO_H

#include <QObject>
#include <QUrl>
#include <nlohmann/json.hpp>

class FileIO : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl activeFilePath READ activeFilePath WRITE setActiveFilePath NOTIFY activeFilePathChanged)
    Q_PROPERTY(nlohmann::json activeFile READ activeFile WRITE setActiveFile NOTIFY activeFileChanged)

public:
    explicit FileIO(QObject *parent = nullptr);

    Q_INVOKABLE bool read();
    Q_INVOKABLE bool write(nlohmann::json output);

    QUrl activeFilePath() const;
    void setActiveFilePath(const QUrl &newFilePath);

    nlohmann::json activeFile() const;
    void setActiveFile(nlohmann::json newActiveFile);

signals:

    void activeFilePathChanged();

    void activeFileChanged();

private:

    QUrl m_activeFilePath = QUrl();
    nlohmann::json m_activeFile;

    std::string pathToString();
};

#endif // FILEIO_H
