#include "table.h"
#include <QDebug>
#include <fstream>
#include "../Sheet/Cell/FormulaCell.h"

CustomTableModel::CustomTableModel(QObject* parent) : QAbstractTableModel(parent)
{
    qDebug() << "table created";
}

QHash<int, QByteArray> CustomTableModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "display";
    roles[CustomTableModel::Value] = "value";
    return roles;
}

QVariant CustomTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    setLastRetrievedAddress(QPoint(index.column(), index.row()));

    int colIndex = index.column();
    int rowIndex = index.row();

    Address requested(colIndex, rowIndex);

    if (!m_sheet.Values().contains(requested))
    {
        return QString();
    }

    auto& cell = m_sheet.Values().at(requested);
    auto formulaCell = std::dynamic_pointer_cast<FormulaCell>(cell);
    if (formulaCell)
    {
        formulaCell->Update();
    }

    if (role == Qt::DisplayRole)
    {
        return QString::fromStdString(cell->ValueString());
    }

    if (role == CustomTableModel::Value)
    {
        return QVariant::fromStdVariant(cell->Value());
    }

    return QVariant();
}

QVariant CustomTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        switch (orientation)
        {
        case Qt::Orientation::Horizontal:
        {
            return columnTitle(section);
            break;
        }
        case Qt::Orientation::Vertical:
        {
            return rowTitle(section);
            break;
        }
        }
    }

    return QVariant();
}

bool CustomTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    auto input = value.toString().toStdString();
    Address currentAddress(index.column(), index.row());
    std::shared_ptr<Cell> currentCell = nullptr;
    if (m_sheet.Values().contains(currentAddress))
    {
        currentCell = m_sheet.Values().at(currentAddress);
    }

    m_sheet.AddCell(currentAddress, input);
    emit dataChanged(index, index);

    if (currentCell == nullptr)
    {
        return true;
    }

    RefreshChangedCells(currentCell->GetAddress(), currentCell->Referencing());

    return true;
}

Qt::ItemFlags CustomTableModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

bool CustomTableModel::insertRows()
{
    return insertRows(m_rowCount, 26);
}

bool CustomTableModel::removeRows()
{
    return removeRows(m_rowCount - 26, 26);
}

bool CustomTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if (row < 0 || row > m_rowCount || count == 0)
    {
        return false;
    }

    beginInsertRows(parent, row, row + count - 1);
    setRowCount(m_rowCount + count);
    endInsertRows();

    return true;
}

bool CustomTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (row < 0 || row > m_rowCount || count == 0)
    {
        return false;
    }

    beginRemoveRows(parent, row, row + count - 1);
    setRowCount(m_rowCount - count);
    endRemoveRows();

    return true;
}

bool CustomTableModel::insertColumns()
{
    return insertColumns(m_columnCount, 26);
}

bool CustomTableModel::removeColumns()
{
    return removeColumns(m_columnCount - 26, 26);
}

bool CustomTableModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    if (column < 0 || column > m_columnCount || count == 0)
    {
        return false;
    }

    beginInsertColumns(parent, column, column + count - 1);
    setColumnCount(m_columnCount + count);
    endInsertColumns();

    return true;
}

bool CustomTableModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    if (column < 0 || column > m_columnCount || count == 0)
    {
        return false;
    }

    beginRemoveColumns(parent, column, column + count - 1);
    setColumnCount(m_columnCount - count);
    endRemoveColumns();

    return true;
}

QPoint CustomTableModel::lastRetrievedAddress() const
{
    return m_lastRetrievedAddress;
}

void CustomTableModel::setLastRetrievedAddress(QPoint newLastRetrievedAddress) const
{
    if (m_lastRetrievedAddress == newLastRetrievedAddress)
        return;
    m_lastRetrievedAddress = newLastRetrievedAddress;
}

int CustomTableModel::rowCount(const QModelIndex &parent) const
{
    return m_rowCount;
}

void CustomTableModel::setRowCount(int newRowCount)
{
    if (m_rowCount == newRowCount)
        return;
    m_rowCount = newRowCount;
    emit rowCountChanged();
}

int CustomTableModel::columnCount(const QModelIndex &parent) const
{
    return m_columnCount;
}

void CustomTableModel::setColumnCount(int newColumnCount)
{
    if (m_columnCount == newColumnCount)
        return;
    m_columnCount = newColumnCount;
    emit columnCountChanged();
}

void CustomTableModel::triggered(QString message)
{
    QString output = QString("triggered") + ' ' + message;
    qDebug() << output;
}

QVariant CustomTableModel::cellValue(const QModelIndex &index) const
{
    return QVariant();
}

QString CustomTableModel::columnTitle(int index) const
{
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

QString CustomTableModel::rowTitle(int index) const
{
    std::string title = std::to_string(index + 1);
    return QString::fromStdString(title);
}

void CustomTableModel::RefreshChangedCells(const Address& initialAddress, const std::vector<Address>& changedAddresses)
{
    if (changedAddresses.empty())
    {
        return;
    }

    for (const Address& address : changedAddresses)
    {
        if (address == initialAddress)
        {
            continue;
        }

        auto changedIndex = this->index(address.Row(), address.Col());
        emit dataChanged(changedIndex, changedIndex);

        auto& cell = m_sheet.Values().at(address);
        RefreshChangedCells(initialAddress, cell->Referencing());
    }
}

void CustomTableModel::clear()
{
    qDebug() << "table cleared";\

    setSheet(Sheet());
}

Sheet CustomTableModel::sheet() const
{
    return m_sheet;
}

void CustomTableModel::setSheet(const Sheet &newSheet)
{
    beginResetModel();
    m_sheet = newSheet;
    emit sheetChanged();
    endResetModel();
}

nlohmann::json CustomTableModel::serialize()
{
    return m_sheet.Serialize();
}

bool CustomTableModel::deserialize(const nlohmann::json& source)
{
    if (!m_sheet.Deserialize(source))
    {
        return false;
    }

    beginResetModel();
    emit sheetChanged();
    endResetModel();
    return true;
}

QVariant CustomTableModel::lastRetrievedValue() const
{
    return m_lastRetrievedValue;
}

void CustomTableModel::setLastRetrievedValue(const QVariant &newLastRetrievedValue) const
{
    if (m_lastRetrievedValue == newLastRetrievedValue)
        return;
    m_lastRetrievedValue = newLastRetrievedValue;
}







//void CustomTableModel::update()
//{
//    qDebug() << "table updated";

//    if (m_columnHeaders == nullptr || m_rowHeaders == nullptr)
//    {
//        return;
//    }

//    auto deltaColumns = std::abs(m_columnHeaders->rowCount() - m_columnCount);
//    auto deltaRows = std::abs(m_rowHeaders->rowCount() - m_rowCount);

//    if (m_columnCount < m_columnHeaders->rowCount())
//    {
//        int startIndex = m_columnCount;
//        insertColumns(startIndex, deltaColumns);

//        setColumnCount(m_columnHeaders->rowCount());

//        return;
//    }

//    if (m_columnCount > m_columnHeaders->rowCount())
//    {
//        int startIndex = m_columnHeaders->rowCount();
//        removeColumns(startIndex, deltaColumns);

//        setColumnCount(m_columnHeaders->rowCount());

//        return;
//    }

//    if (m_rowCount < m_rowHeaders->rowCount())
//    {
//        int startIndex = m_rowCount;
//        insertRows(startIndex, deltaRows);

//        setRowCount(m_rowHeaders->rowCount());

//        return;
//    }

//    if (m_rowCount > m_rowHeaders->rowCount())
//    {
//        int startIndex = m_rowHeaders->rowCount();
//        removeRows(startIndex, deltaRows);

//        setRowCount(m_rowHeaders->rowCount());
//    }
//}


//HeadersModel *CustomTableModel::columnHeaders() const
//{
//    return m_columnHeaders;
//}

//void CustomTableModel::setColumnHeaders(HeadersModel *newColumnHeaders)
//{
//    qDebug() << "table columns property set";

//    if (m_columnHeaders == newColumnHeaders)
//        return;
//    m_columnHeaders = newColumnHeaders;
//    emit columnHeadersChanged();

//    if (m_rowHeaders == nullptr)
//    {
//        return;
//    }
//    Initialize();
//}

//HeadersModel *CustomTableModel::rowHeaders() const
//{
//    return m_rowHeaders;
//}

//void CustomTableModel::setRowHeaders(HeadersModel *newRowHeaders)
//{
//    qDebug() << "table rows property set";

//    if (m_rowHeaders == newRowHeaders)
//        return;
//    m_rowHeaders = newRowHeaders;
//    emit rowHeadersChanged();

//    if (m_columnHeaders == nullptr)
//    {
//        return;
//    }
//    Initialize();
//}
