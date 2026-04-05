#include <iostream>
#include <locale.h>
#include <map>
#include <list>
using namespace std;

struct task {
    int id;
    int value;
    task* prev;
    task* next;
};

task* head = nullptr;
task* tail = nullptr;

map <int, task*> registery;

void add (int id, int value) {
    task* newTask = new task{id, value, tail, nullptr};
    if (tail) tail -> next = newTask;
    else  {
        head = newTask;
        tail = newTask;
    }
    registery[id] = newTask;
}

void insert_after (int target_id, int id, int value) {
    auto target = registery[target_id];
    task* newTask = new task{id, value, target, target->next};
    
}

int main(){
    int n;
    cout << "Введите количество операций (от 0 до 100001)" << endl;
    while (true) {
        cin >> n;
        if (n <= 0 || n > 100000) {
            cout << "Еблан блять по русски написано от 0 до 100001" << endl;
            n = 0;
        }
        else break;
    }

    cout << "proverka" << endl;


    return 0;
}