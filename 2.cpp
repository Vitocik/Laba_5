//Гаражная стоянка имеет одну стояночную полосу, причем въезд и выезд находятся в одном конце полосы. 
//Если владелец автомашины приходит забрать свой автомобиль, который не является ближайшим к выходу, то все автомашины, загораживающие проезд, удаляются, машина данного владельца выводится со стоянки,
//а другие машины возвращаются на стоянку в исходном порядке. Написать программу, которая моделирует процесс прибытия и отъезда машин. Прибытие или отъезд автомашины задается командной строкой, которая содержит признак прибытия или отъезда и номер машины. 
//Программа должна выводить сообщение при прибытии или выезде любой машины. При выезде автомашины со стоянки сообщение должно содержать число раз, которое машина удалялась со стоянки для обеспечения выезда других автомобилей. 
#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Car {
public:
    int number;
    string model; // Добавить информацию о модели автомобиля

    Car(int num, const string& mod = "") : number(num), model(mod) {}
};

class ParkingLot {
private:
    stack<Car> cars;
    int capacity; // Добавить ограничение вместимости для парковки

public:
    ParkingLot(int maxCars = 0) : capacity(maxCars) {} // Конструктор с вместимостью

    // Проверить, присутствует ли автомобиль с заданным номером на парковке
    bool isCarPresent(int carNumber) const {
        stack<Car> temp = cars; // Создать временную копию, чтобы избежать изменения оригинала
        while (!temp.empty()) {
            if (temp.top().number == carNumber) {
                return true;
            }
            temp.pop();
        }
        return false;
    }

    void arrival(int carNumber, const std::string& model = "") {
        if (capacity > 0 && cars.size() >= capacity) {
            cout << "Парковка заполнена. Автомобиль " << carNumber << " не может прибыть." << endl;
            return;
        }
        cars.push(Car(carNumber, model));
        cout << "Автомобиль " << carNumber << (model.empty() ? "" : " (" + model + ")") << " прибыл." << endl;
    }

    void departure(int carNumber) {
        if (!isCarPresent(carNumber)) {
            cout << "Автомобиль " << carNumber << " не находится на парковке." << endl;
            return;
        }

        int moves = 0;
        stack<Car> temp;
        while (!cars.empty()) {
            if (cars.top().number == carNumber) {
                cout << "Автомобиль " << carNumber << " покинул парковку после " << moves << " перемещений." << endl;
                break;
            }
            else {
                temp.push(cars.top());
                cars.pop();
                moves++;
            }
        }
        while (!temp.empty()) {
            cars.push(temp.top());
            temp.pop();
        }
    }

    //Функция для отображения текущего состояния парковки
    void displayStatus() const {
        if (cars.empty()) {
            cout << "Парковка пуста." << endl;
            return;
        }
        cout << "Текущее состояние парковки (сверху вниз):" << endl;
        stack<Car> temp = cars; // Создать временную копию, чтобы избежать изменения оригинала
        while (!temp.empty()) {
            cout << "  - Автомобиль " << temp.top().number << (temp.top().model.empty() ? "" : " (" + temp.top().model + ")") << endl;
            temp.pop();
        }
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    // Установить вместимость парковки
    int capacity = 5;

    ParkingLot parkingLot(capacity);

    parkingLot.arrival(1, "Honda Civic");
    parkingLot.arrival(2, "Ford Mustang");
    parkingLot.arrival(3, "Toyota Camry");
    parkingLot.departure(2); // Автомобиль 2 уезжает (может потребоваться перемещение автомобиля 1)
    parkingLot.departure(5); // Симитировать недопустимый выезд (не присутствует)
    parkingLot.arrival(4, "Tesla Model S");
    parkingLot.displayStatus(); // Опционально: Отобразить текущее состояние парковки

    return 0;
}
