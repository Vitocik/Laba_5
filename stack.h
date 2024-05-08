//Создать шаблон класса «стек». Использовать его при решении задачи 8 из раздела «Динамические структуры данных»
#include <iostream>
#include <stack>

using namespace std;

template <typename T>
class Stack {
private:
    stack<T> elements;

public:
    // Добавление элемента в стек
    void push(T element) {
        elements.push(element);
    }
    // Удаление и возврат верхнего элемента из стека
    T pop() {
        T topElement = elements.top();
        elements.pop();
        return topElement;
    }
    // Получение верхнего элемента без его удаления
    T top() {
        return elements.top();
    }
    // Проверка, пуст ли стек
    bool isEmpty() {
        return elements.empty();
    }
    // Получение размера стека
    int size() {
        return elements.size();
    }
};
