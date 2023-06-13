#include "headers.h"
#include <iostream>
#include <QDebug>

HeadersModel::HeadersModel(QObject *parent): QAbstractListModel(parent) {}

int HeadersModel::rowCount(const QModelIndex &parent) const
{
    return m_visibleHeaders;
}

QHash<int, QByteArray> HeadersModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "display";
    roles[HeadersModel::Columns] = "columns";
    roles[HeadersModel::Rows] = "rows";
    return roles;
}

QVariant HeadersModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }
    
    if (role == HeadersModel::Columns)
    {
        return columnTitle(index.row());
    }
    
    if (role == HeadersModel::Rows)
    {
        return rowTitle(index.row());
    }

    return QVariant();
}

bool HeadersModel::insertRows()
{
    return insertRows(0, 0);
}

bool HeadersModel::removeRows()
{
    return removeRows(0, 0);
}

bool HeadersModel::insertRows(int row, int count, const QModelIndex &parent)
{
    qDebug() << "insertRows method called";

    int currentVisible = m_visibleHeaders;
    beginInsertRows(parent, currentVisible, currentVisible + m_headerBuffer - 1);
    currentVisible += m_headerBuffer;
    setVisibleHeaders(currentVisible);
    endInsertRows();

    return true;
}

bool HeadersModel::removeRows(int row, int count, const QModelIndex &parent)
{
    qDebug() << "removeRows method called";

    int currentVisible = m_visibleHeaders;
    int last = currentVisible - 1;
    int first = currentVisible - 26;
    beginRemoveRows(parent, first, last);
    currentVisible -= m_headerBuffer;
    setVisibleHeaders(currentVisible);
    endRemoveRows();

    return true;
}

QString HeadersModel::columnTitle(int index) const
{
    setLastRetrievedIndex(index);
    if (index == 0)
    {
        return "A";
    }

    QString title = "";
    int base = 26;
    int position = index;

    while (position >= 0)
    {
        int charPosition = position % base;
        title.prepend(QChar('A' + charPosition));
        position -= charPosition;
        position = position / base - 1;
    }

    return title;
}

QString HeadersModel::rowTitle(int index) const
{
    setLastRetrievedIndex(index);
    std::string title = std::to_string(index + 1);
    return QString::fromStdString(title);
}

int HeadersModel::visibleHeaders() const
{
    return m_visibleHeaders;
}

int HeadersModel::headerBuffer() const
{
    return m_headerBuffer;
}

void HeadersModel::setVisibleHeaders(int newVisibleHeaders)
{
    if (m_visibleHeaders == newVisibleHeaders)
        return;
    m_visibleHeaders = newVisibleHeaders;
    emit visibleHeadersChanged();
}

void HeadersModel::triggered(QString message)
{
    QString output = QString("triggered") + ' ' + message;
    qDebug() << output;
}

int HeadersModel::lastRetrievedIndex() const
{
    return m_lastRetrievedIndex;
}

void HeadersModel::setLastRetrievedIndex(int newLastRetrievedIndex) const
{
    if (m_lastRetrievedIndex == newLastRetrievedIndex)
        return;
    m_lastRetrievedIndex = newLastRetrievedIndex;
}
