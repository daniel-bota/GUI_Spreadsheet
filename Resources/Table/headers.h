#ifndef HEADERS_H
#define HEADERS_H

#include "qabstractitemmodel.h"
#include <QObject>

class HeadersModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int visibleHeaders READ visibleHeaders WRITE setVisibleHeaders NOTIFY visibleHeadersChanged)
    Q_PROPERTY(int lastRetrievedIndex READ lastRetrievedIndex CONSTANT)
public:
    explicit HeadersModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    enum CustomRole
    {
        Columns = Qt::UserRole + 1,
        Rows = Qt::UserRole + 2
    };

    QHash<int, QByteArray> roleNames() const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE bool insertRows();
    Q_INVOKABLE bool removeRows();
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    int visibleHeaders() const;

    Q_INVOKABLE int headerBuffer() const;

    void setVisibleHeaders(int newVisibleHeaders);

    Q_INVOKABLE void triggered(QString message);

    int lastRetrievedIndex() const;

signals:

    void visibleHeadersChanged();

private:
    const int m_headerBuffer = 26;
    int anything;
    int m_visibleHeaders = 26;
    QString columnTitle(int index) const;
    QString rowTitle(int index) const;
    mutable int m_lastRetrievedIndex;
};

#endif // HEADERS_H
