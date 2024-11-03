#include <iostream>
#include <list>
#include <forward_list>
#include <vector>
#include <string>
#include <regex>
#include <algorithm>

struct Book {
    std::string title;
    std::string author;
    std::string id;
};

struct Borrower {
    std::string name;
    std::vector<std::string> borrowedBooks;
};

bool isValidId(const std::string& id) {
    std::regex idPattern("^[A-Za-z]\\d{4}$");
    return std::regex_match(id, idPattern);
}

void addBook(std::list<Book>& books) {
    Book book;
    std::cout << "輸入書名: ";
    std::getline(std::cin, book.title);
    std::cout << "輸入作者名稱: ";
    std::getline(std::cin, book.author);
    do {
        std::cout << "輸入圖書編號 (首位為英文字母 + 4位數字): ";
        std::getline(std::cin, book.id);
        if (!isValidId(book.id)) {
            std::cout << "不符合規定，請重新輸入\n";
        }
    } while (!isValidId(book.id));
    books.push_back(book);
    std::cout << "圖書已成功添加。\n";
}

void removeBook(std::list<Book>& books, std::forward_list<Borrower>& borrowers) {
    std::string id;
    std::cout << "輸入要刪除的圖書編號: ";
    std::getline(std::cin, id);
    books.remove_if([&id](const Book& book) { return book.id == id; });
    for (auto& borrower : borrowers) {
        borrower.borrowedBooks.erase(
            std::remove(borrower.borrowedBooks.begin(), borrower.borrowedBooks.end(), id),
            borrower.borrowedBooks.end()
        );
    }
    std::cout << "圖書及相關借閱記錄已成功刪除。\n";
}

void searchBook(const std::list<Book>& books) {
    std::string id;
    std::cout << "輸入要搜索的圖書編號: ";
    std::getline(std::cin, id);
    auto it = std::find_if(books.begin(), books.end(), [&id](const Book& book) { return book.id == id; });
    if (it != books.end()) {
        std::cout << "找到圖書 - 書名: " << it->title << ", 作者: " << it->author << ", 圖書編號: " << it->id << '\n';
    }
    else {
        std::cout << "未找到圖書。\n";
    }
}

void displayBooks(const std::list<Book>& books) {
    if (books.empty()) {
        std::cout << "圖書館中沒有圖書。\n";
        return;
    }
    for (const auto& book : books) {
        std::cout << "書名: " << book.title << ", 作者: " << book.author << ", 圖書編號: " << book.id << '\n';
    }
}

void sortBooks(std::list<Book>& books) {
    books.sort([](const Book& a, const Book& b) { return a.id < b.id; });
    std::cout << "圖書已按圖書編號排序。\n";
}

void addBorrower(std::forward_list<Borrower>& borrowers) {
    Borrower borrower;
    std::cout << "輸入借閱者姓名: ";
    std::getline(std::cin, borrower.name);
    borrowers.push_front(borrower);
    std::cout << "借閱者已成功添加。\n";
}

void removeBorrower(std::forward_list<Borrower>& borrowers) {
    std::string name;
    std::cout << "輸入要刪除的借閱者姓名: ";
    std::getline(std::cin, name);
    borrowers.remove_if([&name](const Borrower& borrower) { return borrower.name == name; });
    std::cout << "借閱者已成功刪除。\n";
}

void searchBorrower(const std::forward_list<Borrower>& borrowers) {
    std::string name;
    std::cout << "輸入要搜索的借閱者姓名: ";
    std::getline(std::cin, name);
    auto it = std::find_if(borrowers.begin(), borrowers.end(), [&name](const Borrower& borrower) { return borrower.name == name; });
    if (it != borrowers.end()) {
        std::cout << "找到借閱者 - 姓名: " << it->name << ", 借閱的圖書編號: ";
        for (const auto& bookId : it->borrowedBooks) {
            std::cout << bookId << " ";
        }
        std::cout << '\n';
    }
    else {
        std::cout << "未找到借閱者。\n";
    }
}

void displayBorrowers(const std::forward_list<Borrower>& borrowers) {
    if (borrowers.empty()) {
        std::cout << "沒有借閱者。\n";
        return;
    }
    for (const auto& borrower : borrowers) {
        std::cout << "姓名: " << borrower.name << ", 借閱的圖書編號: ";
        for (const auto& bookId : borrower.borrowedBooks) {
            std::cout << bookId << " ";
        }
        std::cout << '\n';
    }
}

int main() {
    std::list<Book> books = {
        {"紅樓夢", "曹雪芹", "A1234"},
        {"西遊記", "吳承恩", "B2345"},
        {"水滸傳", "施耐庵", "B3456"},
        {"三國演義", "羅貫中", "C4567"},
        {"金瓶梅", "蘭陵笑笑生", "C5678"},
        {"聊齋志異", "蒲松齡", "D6789"},
        {"儒林外史", "吳敬梓", "D7890"},
        {"封神演義", "許仲琳", "E8901"},
        {"鏡花緣", "李汝珍", "E9012"},
        {"老殘遊記", "劉鶚", "F0123"}
    };

    std::forward_list<Borrower> borrowers = {
        {"小明", {"A1234", "B2345"}},
        {"小華", {"C4567"}},
        {"小美", {"D6789", "E8901"}},
        {"小強", {"F0123"}},
        {"小麗", {"B3456", "C5678"}}
    };

    int choice;
    do {
        std::cout << "圖書館管理系統\n";
        std::cout << "1. 添加新圖書\n";
        std::cout << "2. 刪除圖書\n";
        std::cout << "3. 搜索圖書\n";
        std::cout << "4. 顯示所有圖書\n";
        std::cout << "5. 排序圖書\n";
        std::cout << "6. 添加新借閱者\n";
        std::cout << "7. 刪除借閱者\n";
        std::cout << "8. 搜索借閱者\n";
        std::cout << "9. 顯示所有借閱者\n";
        std::cout << "10. 退出\n";
        std::cout << "輸入你的選擇: ";
        std::cin >> choice;
        std::cin.ignore(); // 忽略緩衝區中的換行符
        switch (choice) {
        case 1:
            addBook(books);
            break;
        case 2:
            removeBook(books, borrowers);
            break;
        case 3:
            searchBook(books);
            break;
        case 4:
            displayBooks(books);
            break;
        case 5:
            sortBooks(books);
            break;
        case 6:
            addBorrower(borrowers);
            break;
        case 7:
            removeBorrower(borrowers);
            break;
        case 8:
            searchBorrower(borrowers);
            break;
        case 9:
            displayBorrowers(borrowers);
            break;
        case 10:
            std::cout << "退出...\n";
            break;
        default:
            std::cout << "無效的選擇，請重試。\n";
        }
    } while (choice != 10);
    return 0;
}