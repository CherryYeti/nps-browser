#include <QAbstractTableModel>
#include <QTableView>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QApplication>
#include <QMainWindow>
#include <vector>
#include <string>
#include <algorithm>

// Assuming the `TSVRecord` struct and `parseTSV` function are defined as previously shown

std::string formatFileSize(const std::string &sizeStr) {
    if (sizeStr.empty()) {
        return "0 B";
    }
    double size = std::stod(sizeStr);
    const char *units[] = {"B", "KB", "MB", "GB"};
    int unitIndex = 0;

    while (size >= 1024 && unitIndex < 3) {
        size /= 1024;
        ++unitIndex;
    }

    char formattedSize[50];
    snprintf(formattedSize, sizeof(formattedSize), "%.2f %s", size, units[unitIndex]);
    return std::string(formattedSize);
}

class TSVTableModel : public QAbstractTableModel {

public:
    TSVTableModel(const std::vector<TSVRecord> &records, QObject *parent = nullptr)
        : QAbstractTableModel(parent), records(records) {}

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return records.size();
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return 5; // Number of fields in TSVRecord
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole) {
            const TSVRecord &record = records[index.row()];
            switch (index.column()) {
                case 0: return QString::fromStdString(record.titleID);
                case 1: return QString::fromStdString(record.region);
                case 2: return QString::fromStdString(record.name);
                case 3: return QString::fromStdString(record.lastModificationDate);
                case 4: return QString::fromStdString(formatFileSize(record.fileSize));
            }
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole) {
            if (orientation == Qt::Horizontal) {
                switch (section) {
                    case 0: return "Title ID";
                    case 1: return "Region";
                    case 2: return "Name";
                    case 3: return "Last Modification Date";
                    case 4: return "File Size";
                }
            }
        }
        return QVariant();
    }

    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override {
        std::sort(records.begin(), records.end(), [column, order](const TSVRecord &a, const TSVRecord &b) {
            switch (column) {
                case 0: return order == Qt::AscendingOrder ? a.titleID < b.titleID : a.titleID > b.titleID;
                case 1: return order == Qt::AscendingOrder ? a.region < b.region : a.region > b.region;
                case 2: return order == Qt::AscendingOrder ? a.name < b.name : a.name > b.name;
                case 3: return order == Qt::AscendingOrder ? a.lastModificationDate < b.lastModificationDate : a.lastModificationDate > b.lastModificationDate;
                case 4: return order == Qt::AscendingOrder ? a.fileSize < b.fileSize : a.fileSize > b.fileSize;
                default: return false;
            }
        });
        emit layoutChanged();
    }

private:
    std::vector<TSVRecord> records;
};

class TSVTableView : public QTableView {

public:
    TSVTableView(QWidget *parent = nullptr) : QTableView(parent) {
        setSortingEnabled(true);
        horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
};