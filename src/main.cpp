#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include "fs/config.cpp"
#include "fs/tsv.cpp"
#include "ui/tsv.cpp"
#include "ui/components.cpp"
int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  // Main window
  QWidget mainWindow;
  mainWindow.resize(1280, 700);
  QVBoxLayout *layout = new QVBoxLayout;
  mainWindow.setLayout(layout);
  if (!configExists()) {
    createConfig();
  }
  mainWindow.setWindowTitle("NPS Browser");
  mainWindow.show();

  TSVWindow *tsvWindow = nullptr;
  if (!validTSV()) {
    tsvWindow = new TSVWindow();
    tsvWindow->show();
  } else {
    delete tsvWindow;
    tsvWindow = nullptr;
  }
  std::vector<TSVRecord> records = parseTSV("/home/jason/Downloads/PS3_GAMES.tsv");
  std::cout << "First game name: " << records[0].region << std::endl;

  // Create table model and view
  TSVTableModel *model = new TSVTableModel(records);
  TSVTableView *view = new TSVTableView();
  view->setModel(model);
  layout->addWidget(view);




  return app.exec();
}