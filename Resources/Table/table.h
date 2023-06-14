#ifndef TABLE_H
#define TABLE_H

#include <QAbstractTableModel>
#include <QtSql/QSqlQueryModel>
#include <QAbstractItemModel>
#include <QtQml/qqmlregistration.h>
#include "qpoint.h"
#include "qtmetamacros.h"
#include <QObject>
#include "../Sheet/Sheet.h"

class CustomTableModel : public QAbstractTableModel
{
    Q_OBJECT

    Q_PROPERTY(int rowCount READ rowCount WRITE setRowCount NOTIFY rowCountChanged)
    Q_PROPERTY(int columnCount READ columnCount WRITE setColumnCount NOTIFY columnCountChanged)

    Q_PROPERTY(QPoint lastRetrievedAddress READ lastRetrievedAddress CONSTANT)
    Q_PROPERTY(QVariant lastRetrievedValue READ lastRetrievedValue CONSTANT)

    Q_PROPERTY(Sheet sheet READ sheet WRITE setSheet NOTIFY sheetChanged)

public:
    explicit CustomTableModel(QObject* parent = nullptr);

    enum CustomRoles
    {
        Value = Qt::UserRole + 1
    };

    QHash<int, QByteArray> roleNames() const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    Q_INVOKABLE bool insertRows();
    Q_INVOKABLE bool removeRows();
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    Q_INVOKABLE bool insertColumns();
    Q_INVOKABLE bool removeColumns();

    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    QPoint lastRetrievedAddress() const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    void setRowCount(int newRowCount);

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    void setColumnCount(int newColumnCount);

    Q_INVOKABLE void triggered(QString message);

    Q_INVOKABLE QVariant cellValue(const QModelIndex& index = QModelIndex()) const;

    Sheet sheet() const;
    void setSheet(const Sheet &newSheet);

    Q_INVOKABLE nlohmann::json serialize();
    Q_INVOKABLE bool deserialize(const nlohmann::json& source);

    Q_INVOKABLE void clear();

    QVariant lastRetrievedValue() const;

signals:

    void rowCountChanged();

    void columnCountChanged();

    void sheetChanged();

private:
    mutable QPoint m_lastRetrievedAddress = {0, 0};
    mutable QVariant m_lastRetrievedValue;

    int m_rowCount = 52;
    int m_columnCount = 26;

    QString columnTitle(int index) const;
    QString rowTitle(int index) const;

    Sheet m_sheet;

    void RefreshChangedCells(const Address& initialAddress, const std::vector<Address>& changedAddresses);
};

#endif // TABLE_H
