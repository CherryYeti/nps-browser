#include <QDir>
#include <QFile>

#include <QSettings>
#include <QString>
#include <QStringList>

QString configPath() {
  QDir dir(QDir::homePath() + "/.config/nps");
  if (!dir.exists()) {
    dir.mkpath(".");
  }
  return QDir::homePath() + "/.config/nps/config.ini";
}
bool configExists() {
  QDir dir(QDir::homePath() + "/.config/nps");
  QFile file(dir.absolutePath() + "/config.ini");
  return file.exists();
}

void createConfig() {
  QSettings settings(configPath(), QSettings::IniFormat);
  const QStringList regions = {"ASIA", "EU", "JP", "US"};
  for (const auto &region : regions) {
    settings.setValue("Regions/" + region, true);
  }
  settings.setValue("downloadDirectory", QDir::homePath() + "/Downloads/nps");
  const QStringList tsvs = {"PS3_GAMES", "PS3_DLCS", "PS3_DEMOS"};
  for (const auto &tsv : tsvs) {
    settings.setValue("TSVs/" + tsv, "");
  }
}
bool validTSV() {
    QSettings settings(configPath(), QSettings::IniFormat);
    const QStringList tsvs = {"PS3_GAMES", "PS3_DLCS", "PS3_DEMOS"};
    for (const auto &tsv : tsvs) {
        qWarning() << settings.value("TSVs/" + tsv, "").toString();
        if (settings.value("TSVs/" + tsv, "").toString() == "") {
            return false;
        }
    }
    return true;
}