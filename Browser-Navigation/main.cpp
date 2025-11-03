#include "browser.h"

int main() {
    Browser browser;
    int choice;
    string url, title;

    while (true) {
        cout << "\n====== Smart Browser Navigation ======\n";
        cout << "1. Visit Page \n2. Back  \n3. Forward  \n4. Bookmark\n";
        cout << "5. View Bookmarks  \n6. History  \n7. Most Visited  \n8. Current\n";
        cout << "9. New Tab  \n10. View Tabs  \n11. Switch Tab  \n12. Close Tab\n";
        cout << "13. Save Session  \n14. Session History  \n15. Restore Session\n";
        cout << "0. Exit \nChoice: ";
        
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "URL: "; getline(cin, url);
                cout << "Title: "; getline(cin, title);
                browser.visitPage(url, title);
                break;

            case 2: browser.goBack(); break;
            case 3: browser.goForward(); break;
            case 4: browser.addBookmark(); break;
            case 5: browser.viewBookmarks(); break;
            case 6: browser.viewHistory(); break;
            case 7: browser.showMostVisited(); break;
            case 8: browser.showCurrent(); break;
            case 9: browser.createNewTab(); break;
            case 10: browser.viewAllTabs(); break;

            case 11: {
                int idx;
                cout << "Tab index: ";
                cin >> idx;
                browser.switchTab(idx);
                break;
            }

            case 12: browser.closeCurrentTab(); break;
            case 13: browser.saveCurrentSession(); break;
            case 14: browser.viewSessionHistory(); break;
            case 15: {
                int idx;
                cout << "Snapshot index: ";
                cin >> idx;
                browser.restoreSession(idx);
                break;
            }

            case 0:
                cout << "\n Saving data... Exiting safely!\n";
                return 0;

            default:
                cout << "\n Invalid choice!\n";
        }
    }

}