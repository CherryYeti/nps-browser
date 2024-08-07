#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

struct TSVRecord {
  std::string titleID;
  std::string region;
  std::string name;
  std::string pkgDirectLink;
  std::string rap;
  std::string contentID;
  std::string lastModificationDate;
  std::string downloadRapFile;
  std::string fileSize;
  std::string sha256;
};

std::vector<TSVRecord> parseTSV(const std::string &filePath) {
  std::vector<TSVRecord> records;
  std::ifstream file(filePath);
  std::string line;

  // Skip the header line
  std::getline(file, line);

  while (std::getline(file, line)) {
    std::istringstream ss(line);
    std::string field;
    TSVRecord record;

    std::getline(ss, record.titleID, '\t');
    std::getline(ss, record.region, '\t');
    std::getline(ss, record.name, '\t');
    std::getline(ss, record.pkgDirectLink, '\t');
    std::getline(ss, record.rap, '\t');
    std::getline(ss, record.contentID, '\t');
    std::getline(ss, record.lastModificationDate, '\t');
    std::getline(ss, record.downloadRapFile, '\t');
    std::getline(ss, record.fileSize, '\t');
    std::getline(ss, record.sha256, '\t');

    records.push_back(record);
  }

  return records;
}