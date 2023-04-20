#include <iomanip>
#include <iostream>

using namespace std;

// A templated linked list class
template <typename T>
struct List {
    T value;
    const List<T>* next;
};

// templated function that adds a new element to a single linked list of type T
template <typename T>
List<T>* add_new_element(const List<T>* head, const T value) {
    List<T>* new_elem = new List<T>();
    new_elem->value = value;
    new_elem->next = head;
    return (new_elem);
}

// templated function that prints the element of a linked list
template <typename T>
void print_list(const List<T>* head) {
    const List<T>* tmp = head;
    while (tmp) {
        cout << tmp->value;
        if (tmp->next)
            cout << ", ";
        tmp = tmp->next;
    }
    cout << endl;
    return;
}

// main entry point of the program
int main(void) {
    // instantiate the list with type <int>
    List<int>* i_list = NULL;
    // instantiate the list with type <double>
    List<double>* d_list = NULL;

    for (auto i = 0; i < 100; i++) {
        d_list = add_new_element(d_list, 1.0 / (double)(i + 1));
        i_list = add_new_element(i_list, i + 1);
    }

    cout << "Double List" << endl
         << "-----------" << endl;
    print_list(d_list);
    cout << endl
         << "Int List" << endl
         << "--------" << endl;
    print_list(i_list);
    return (0);
}