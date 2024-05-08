//Вариант 3
//Требуется создать шаблон некоторого целевого класса А, возможно, реализованный с применением некоторого серверного класса В. Это означает, что объект класса В используется как элемент класса А. Необходимо предусмотреть генерацию и обработку исключений для возможных ошибочных ситуаций.
//Показать в клиенте mainO использование созданного класса, включая ситуации, приводящие к генерации исключений. Показать инстанцирование шаблона для типов int, double, std::string. 
//Целевой шаблонный класс - Stack,   Реализация с применением - динамический массив

#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

template <typename T>
class Stack {
private:
    T* data;        // Динамический массив
    int vmestim;   // Емкость стека
    int size;       // Текущий размер стека

public:
    Stack(int vmestim) : vmestim(vmestim), size(0) {
        data = new T[vmestim];
    }

    ~Stack() {
        delete[] data;
    }

    // Помещает элемент на вершину стека
    void push(const T& item) {
        if (size >= vmestim) {
            throw overflow_error("Переполнение стека");
        }
        data[size++] = item;
    }

    // Удаляет элемент с вершины стека и возвращает его
    T pop() {
        if (size <= 0) {
            throw underflow_error("Стек пуст");
        }
        return data[--size];
    }
    // Показывает элемент на вершине стека
    T& top() {
        if (size <= 0) {
            throw underflow_error("Стек пуст");
        }
        return data[size - 1];
    }

    // Проверяет, пуст ли стек
    bool isEmpty() const {
        return size == 0;
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    try {
        // Использование шаблонного класса Stack для типа int
        Stack<int> intStack(5);
        intStack.push(1);
        intStack.push(2);
        cout << "Верхний элемент intStack: " << intStack.top() << endl;
        intStack.pop();
        cout << "После извлечения, верхний элемент intStack: " << intStack.top() << endl;

        // Использование шаблонного класса Stack для типа double
        Stack<double> doubleStack(3);
        doubleStack.push(3.14);
        cout << "Верхний элемент doubleStack: " << doubleStack.top() << endl;

        // Использование шаблонного класса Stack для типа string
        Stack<string> stringStack(2);
        stringStack.push("Привет");
        stringStack.push("Мир");
        cout << "Верхний элемент stringStack: " << stringStack.top() << endl;

        // Показ ситуации, приводящей к генерации исключения (стек переполнен)
        Stack<int> fullStack(2);
        fullStack.push(10);
        fullStack.push(20);
        fullStack.push(30);  // Здесь будет выброшено исключение
    }
    catch (const exception& e) {
        cerr << "Возникло исключение: " << e.what() << endl;
    }

    return 0;
}
