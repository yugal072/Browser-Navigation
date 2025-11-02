#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "structures.h"
#include <unordered_map>
#include <fstream>

class FileManager {
public:
    static void saveHistory(HistoryNode* head);
    static HistoryNode* loadHistory();
    static void saveBookmarks(unordered_map<string, Page>& bookmarks);
    static void loadBookmarks(unordered_map<string, Page>& bookmarks);
    static void saveVisitCount(unordered_map<string, int>& visitCount);
    static void loadVisitCount(unordered_map<string, int>& visitCount);
    static void saveTabs(vector<Tab*>& tabs, int currentIndex, int nextId);
    static void loadTabs(vector<Tab*>& tabs, int& currentIndex, int& nextId);
    static void saveSessionHistory(vector<SessionSnapshot>& sessions);
    static void loadSessionHistory(vector<SessionSnapshot>& sessions);
};

void FileManager::saveHistory(HistoryNode* head) {
    ofstream file("history.txt");
    while (head) {
        file << head->page.url << "," << head->page.title << "\n";
        head = head->next;
    }
}

HistoryNode* FileManager::loadHistory() {
    ifstream file("history.txt");
    if (!file) return nullptr;
    HistoryNode *head = nullptr, *tail = nullptr;
    string line;
    while (getline(file, line)) {
        size_t comma = line.find(',');
        if (comma != string::npos) {
            HistoryNode* node = new HistoryNode(Page(line.substr(0, comma), line.substr(comma + 1)));
            if (!head) head = tail = node;
            else tail = tail->next = node;
        }
    }
    return head;
}

void FileManager::saveBookmarks(unordered_map<string, Page>& bookmarks) {
    ofstream file("bookmarks.txt");
    for (auto& b : bookmarks)
        file << b.second.url << "," << b.second.title << "\n";
}

void FileManager::loadBookmarks(unordered_map<string, Page>& bookmarks) {
    ifstream file("bookmarks.txt");
    if (!file) return;
    string line;
    while (getline(file, line)) {
        size_t comma = line.find(',');
        if (comma != string::npos)
            bookmarks[line.substr(0, comma)] = Page(line.substr(0, comma), line.substr(comma + 1));
    }
}

void FileManager::saveVisitCount(unordered_map<string, int>& visitCount) {
    ofstream file("visitCount.txt");
    for (auto& v : visitCount)
        file << v.first << "," << v.second << "\n";
}

void FileManager::loadVisitCount(unordered_map<string, int>& visitCount) {
    ifstream file("visitCount.txt");
    if (!file) return;
    string line;
    while (getline(file, line)) {
        size_t comma = line.find(',');
        if (comma != string::npos)
            visitCount[line.substr(0, comma)] = stoi(line.substr(comma + 1));
    }
}

void FileManager::saveTabs(vector<Tab*>& tabs, int currentIndex, int nextId) {
    ofstream file("tabs.txt");
    file << currentIndex << "\n" << nextId << "\n";
    for (auto tab : tabs) {
        file << "TAB:" << tab->id << "\n";
        if (!tab->currentPage.url.empty())
            file << "CURRENT:" << tab->currentPage.url << "," << tab->currentPage.title << "\n";
    }
}

void FileManager::loadTabs(vector<Tab*>& tabs, int& currentIndex, int& nextId) {
    ifstream file("tabs.txt");
    if (!file) return;
    string line;
    if (getline(file, line)) currentIndex = stoi(line);
    if (getline(file, line)) nextId = stoi(line);
    Tab* currentTab = nullptr;
    while (getline(file, line)) {
        if (line.find("TAB:") == 0) {
            currentTab = new Tab(stoi(line.substr(4)));
            tabs.push_back(currentTab);
        } else if (line.find("CURRENT:") == 0 && currentTab) {
            size_t comma = line.find(',', 8);
            if (comma != string::npos)
                currentTab->currentPage = Page(line.substr(8, comma - 8), line.substr(comma + 1));
        }
    }
}

void FileManager::saveSessionHistory(vector<SessionSnapshot>& sessions) {
    ofstream file("sessionHistory.txt");
    for (auto& s : sessions) {
        file << "SNAPSHOT:" << s.timestamp << "," << s.description << "\n";
        for (auto& td : s.tabData)
            file << "TAB:" << td.first << "," << td.second << "\n";
        file << "END\n";
    }
}

void FileManager::loadSessionHistory(vector<SessionSnapshot>& sessions) {
    ifstream file("sessionHistory.txt");
    if (!file) return;
    string line;
    SessionSnapshot* current = nullptr;
    while (getline(file, line)) {
        if (line.find("SNAPSHOT:") == 0) {
            size_t comma = line.find(',', 9);
            if (comma != string::npos) {
                sessions.push_back(SessionSnapshot(line.substr(comma + 1)));
                current = &sessions.back();
                current->timestamp = stoll(line.substr(9, comma - 9));
            }
        } else if (line.find("TAB:") == 0 && current) {
            size_t comma = line.find(',', 4);
            if (comma != string::npos)
                current->tabData.push_back({stoi(line.substr(4, comma - 4)), line.substr(comma + 1)});
        } else if (line == "END") current = nullptr;
    }
}

#endif