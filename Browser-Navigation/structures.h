#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
#include <ctime>
#include <stack>
#include <vector>
using namespace std;

struct Page {
    string url, title;
    time_t timestamp;
    Page() {}
    Page(string u, string t) : url(u), title(t), timestamp(time(nullptr)) {}

};

struct HistoryNode {
    Page page;
    HistoryNode* next;
    HistoryNode(Page p) : page(p), next(nullptr) {}
};

struct Tab {
    int id;
    Page currentPage;
    stack<Page> backStack, forwardStack;
    Tab(int tabId) : id(tabId) {}
};


struct SessionSnapshot {
    time_t timestamp;
    string description;
    vector<pair<int, string>> tabData;
    SessionSnapshot() : timestamp(time(nullptr)) {}
    SessionSnapshot(string desc) : timestamp(time(nullptr)), description(desc) {}
};

#endif