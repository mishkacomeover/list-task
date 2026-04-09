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
    if (!target) {
       cout << "target не существует" << endl;
       exit(0);
    }
    task* newTask = new task{id,value,nullptr,target -> next};
    target -> next = newTask;
    if (newTask -> next) {
        newTask -> next -> prev = newTask;
    }

    else {
        tail = newTask;
    }

    registery[id] = newTask;
}

void move_to_front (int id) {
    task* task = registery[id];
    if (!task || task == head) return;
    if (task -> prev) task -> prev -> next = task -> next;
    if (task -> next) task -> next -> prev = task -> prev;

    if (task == tail) tail = task -> prev;

    task -> prev = nullptr;
    task -> next = head;

    if (head) head -> prev = task; // по идее можно и без проверки, но пусть лучше будет

    head = task;
}

void splice_range (int id_from, int id_to) {

    task* task_start = registery[id_from];
    task* task_end = registery[id_to];

    if (!task_start || !task_end || id_from > id_to) return;

    if (task_start == task_end) {
        move_to_front(id_from);
        return;
    }

    

    if (task_start -> prev) task_start -> prev -> next = task_end -> next;
    if (task_end -> next) task_end -> next -> prev = task_start -> prev;

    if (task_end == tail) tail = task_end -> prev;

    task_start -> prev = nullptr;
    task_end -> next = head;

    if (head) head -> prev = task_start;

    head = task_start;
}

void get_value (int id) {
    if (registery[id]) cout << "Значение:" << registery[id] -> value << endl;
    else {
        cout << "Задачи не существует" << endl;
        return;
    }
}

void remove (int id) {
    task* task = registery[id];
    if (!task) return;

    if (task -> prev) task -> prev -> next = task -> next;
    if (task -> next) task -> next -> prev = task -> prev;

    if (task == head) head = task -> next;
    if (task == tail) tail = task -> prev;

    registery.erase(id);
    delete task;
}

int main(){
    int n;
    cout << "Введите количество операций (от 1 до 100000)" << endl;
    while (true) {
        cin >> n;
        if (n <= 0 || n > 100000) {
            cout << "Еблан блять по русски написано от 1 до 100000" << endl;
            n = 0;
        }

        else {
            for (int i = 0; i <= n; i++) {
                add(i, i*10);
                cout << "Added id:" << i << " value:" << i*10 << endl;
            }
            break;
        }
    }

    cout << "Выберите следующее действие:" << endl
         << "1 - add <id> <value> " << endl
         << "2 - insert_after <target_id> <new_id> <value>" << endl
         << "3 - move_to_front <id>" << endl
         << "4 - splice_range <id_from> <id_to>" << endl
         << "5 - get_value <id>" << endl
         << "6 - remove <id>" << endl
         << "7 - выход из программы" << endl;
    
    int choose = 0;
    while (true) {
        cin >> choose;
        switch (choose) {
        case 1: {
            int id, value = 0;
            cout << "Введите <id>: ";
            cin >> id;
            cout << "Введите <value>: ";
            cin >> value;

            if (!registery[id]) {
                add(id,value);
                cout << "Задача с id = " << id << " и value = " << value << " успешно добавлена!" << endl;
            }

            else cout << "Задача с таким id уже существует!" << endl;
            break;
        }

        case 2: {
            int target_id, new_id, value = 0;
            cout << "Введите <target_id>: ";
            cin >> target_id;
            cout << "Введите <new_id>: ";
            cin >> new_id;
            cout << "Введите <value>: ";
            cin >> value;

            insert_after(target_id,new_id,value);
            break;
        }

        case 3: {
            int id = 0;
            cout << "Введите <id>: ";
            cin >> id;

            move_to_front(id);
            break;
        }

        case 4: {
            int id_from, id_to = 0;
            cout << "Введите <id_from>: ";
            cin >> id_from;
            cout << "Введите <id_to>: ";
            cin >> id_to;

            splice_range(id_from,id_to);
            break;
        }

        case 5: {
            int id = 0;
            cout << "Введите <id>: ";
            cin >> id;
            get_value(id);
            break;
        }

        case 6: {
            int id = 0;
            cout << "Введите <id>: ";
            cin >> id;
            remove(id);
            break;
        }

        case 7:
            cout << "Программа завершена" << endl;
            break;

        case 8: {
            for (map x : registery) {
                
            }
        }

        default:
            cout << "Неверный ввод" << endl;
            break;
        }
    }
    return 0;
}