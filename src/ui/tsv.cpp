#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QDesktopServices>
#include <QUrl>
#include <QSettings>

class TSVWindow : public QWidget {
public:
    TSVWindow() {
        setWindowTitle("Enter TSV URLs...");

        QVBoxLayout *mainLayout = new QVBoxLayout;

        auto addRow = [this, mainLayout](const QString &labelText, QLineEdit *&lineEdit) {
            QHBoxLayout *rowLayout = new QHBoxLayout;
            QLabel *label = new QLabel(labelText);
            lineEdit = new QLineEdit;
            rowLayout->addWidget(label);
            rowLayout->addWidget(lineEdit);
            mainLayout->addLayout(rowLayout);
        };

        mainLayout->addWidget(new QLabel("Enter TSV URLs..."));

        QLabel *urlLabel = new QLabel("TSV Urls can be found at: <a href=\"https://nopaystation.com\">https://nopaystation.com</a>");
        urlLabel->setTextFormat(Qt::RichText);
        urlLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
        urlLabel->setOpenExternalLinks(true);
        mainLayout->addWidget(urlLabel);

        addRow("PS3_GAMES.TSV URL:", ps3GamesLineEdit);
        addRow("PS3_DLCS.TSV URL:", ps3DlcsLineEdit);
        addRow("PS3_DEMOS.TSV URL:", ps3DemosLineEdit);

        QPushButton *button = new QPushButton("Save", this);
        connect(button, &QPushButton::clicked, this, &TSVWindow::saveSettings);
        mainLayout->addWidget(button);

        setLayout(mainLayout);
    }

private slots:
    void saveSettings() {
        QSettings settings(configPath(), QSettings::IniFormat);
        settings.setValue("TSVs/PS3_GAMES", ps3GamesLineEdit->text());
        settings.setValue("TSVs/PS3_DLCS", ps3DlcsLineEdit->text());
        settings.setValue("TSVs/PS3_DEMOS", ps3DemosLineEdit->text());
        close();
    }

private:
    QLineEdit *ps3GamesLineEdit;
    QLineEdit *ps3DlcsLineEdit;
    QLineEdit *ps3DemosLineEdit;
};