#include <iostream>
#include <iomanip>
#include <complex>
#include <vector>
using namespace std;

// Клас для представлення часу
class Time {
    int hour;     // Години
    int minute;   // Хвилини
    int second;   // Секунди

public:
    // Конструктор за замовчуванням
    Time() : hour(0), minute(0), second(0) {}

    // Конструктор з параметрами
    Time(int h, int m, int s) {
        setTime(h, m, s);
    }

    // Функція встановлення годин, хвилин та секунд
    void setTime(int h, int m, int s) {
        if (h >= 0 && h < 24)
            hour = h;
        else
            hour = 0;

        if (m >= 0 && m < 60)
            minute = m;
        else
            minute = 0;

        if (s >= 0 && s < 60)
            second = s;
        else
            second = 0;
    }

    // Функції отримання годин, хвилин та секунд
    int getHour() const {
        return hour;
    }

    int getMinute() const {
        return minute;
    }

    int getSecond() const {
        return second;
    }

    // Функція друку часу
    void printTime(bool is12HourFormat = false) const {
        if (is12HourFormat) {
            cout << ((hour == 0 || hour == 12) ? 12 : hour % 12) << " " << (hour < 12 ? "a.m." : "p.m.") << " "
                << setfill('0') << setw(2) << minute << " хвилин " << setw(2) << second << " секунд" << endl;
        }
        else {
            cout << setfill('0') << setw(2) << hour << " годин " << setw(2) << minute << " хвилин " << setw(2) << second << " секунд" << endl;
        }
    }
};

typedef complex<float> ComplexFloat;

// Клас для роботи з комплексними векторами
class ComplexVector {

    ComplexFloat* v;  // Масив комплексних чисел
    int num;          // Кількість елементів у векторі
    int state;        // Стан вектора

public:
    ComplexVector() : v(nullptr), num(0), state(0) {}  // Конструктор за замовчуванням
    ComplexVector(int n);                              // Конструктор з параметром
    ComplexVector(int n, ComplexFloat&);               // Конструктор з параметрами
    ComplexVector(int n, ComplexFloat*);               // Конструктор з параметрами
    ComplexVector(const ComplexVector& s);             // Конструктор копіювання
    ComplexVector& operator=(const ComplexVector& s);  // Оператор присвоєння
    ~ComplexVector() {                                 // Деструктор
        cout << " Deleting vector";
        if (v) delete[] v;
    }
    void Output();                                     // Вивід вектора
    void Input();                                      // Введення вектора
    ComplexVector Add(ComplexVector& b);               // Додавання векторів
    void SetElement(int index, const ComplexFloat& value = ComplexFloat(0, 0));  // Встановлення елементу вектора
    ComplexFloat GetElement(int index);                // Отримання елементу вектора
    ComplexVector Subtract(ComplexVector& b);          // Віднімання векторів
    ComplexVector Multiply(float scalar);              // Множення вектора на скаляр
};

// Конструктор з параметром для ініціалізації вектора з n елементів
ComplexVector::ComplexVector(int n) : v(nullptr), num(0), state(0) {
    if (n <= 0) {
        cout << " Vector size is invalid ";
        return;
    }
    num = n;
    v = new ComplexFloat[n];
    for (int i = 0; i < n; i++) {
        v[i] = 0.0;
    }
}

// Конструктор з параметром для ініціалізації вектора з n елементів, кожний з яких має значення b
ComplexVector::ComplexVector(int n, ComplexFloat& b) : v(nullptr), num(0), state(0) {
    if (n <= 0) {
        cout << " Vector size is invalid ";
        return;
    }
    num = n;
    v = new ComplexFloat[n];
    for (int i = 0; i < n; i++) {
        v[i] = b;
    }
}

// Конструктор з параметром для ініціалізації вектора з n елементів, які копіюються з масиву p
ComplexVector::ComplexVector(int n, ComplexFloat* p) : v(nullptr), num(0), state(0) {
    if (n <= 0 || p == nullptr) {
        cout << " Vector size or input array is invalid ";
        return;
    }
    num = n;
    v = new ComplexFloat[n];
    for (int i = 0; i < n; i++) {
        v[i] = p[i];
    }
}

// Конструктор копіювання
ComplexVector::ComplexVector(const ComplexVector& s) : v(nullptr), num(s.num), state(0) {
    if (num > 0) {
        v = new ComplexFloat[num];
        for (int i = 0; i < num; i++) {
            v[i] = s.v[i];
        }
    }
}

// Оператор присвоєння
ComplexVector& ComplexVector::operator=(const ComplexVector& s) {
    if (this != &s) {
        if (num != s.num) {
            if (v) delete[] v;
            num = s.num;
            v = new ComplexFloat[num];
        }
        for (int i = 0; i < num; i++) {
            v[i] = s.v[i];
        }
    }
    return *this;
}

// Введення елементів вектора
void ComplexVector::Input() {
    if (num == 0) {
        do {
            cout << "Input vector size: ";
            cin >> num;
        } while (num <= 0);
        v = new ComplexFloat[num];
    }
    float real_part, imag_part;
    for (int i = 0; i < num; i++) {
        cout << "Enter real and imaginary parts for v[" << i << "]: ";
        cin >> real_part >> imag_part;
        v[i] = ComplexFloat(real_part, imag_part);
    }
}

// Вивід елементів вектора
void ComplexVector::Output() {
    if (num > 0) {
        for (int i = 0; i < num; i++) {
            cout << "v[" << i << "]: " << v[i] << endl;
        }
    }
    else {
        cout << "Vector is empty." << endl;
    }
}

// Встановлення значення елемента вектора за індексом
void ComplexVector::SetElement(int index, const ComplexFloat& value) {
    if (index >= 0 && index < num) {
        v[index] = value;
    }
    else {
        cout << "Index out of bounds." << endl;
    }
}

// Отримання значення елемента вектора за індексом
ComplexFloat ComplexVector::GetElement(int index) {
    if (index >= 0 && index < num) {
        return v[index];
    }
    else {
        cout << "Index out of bounds. Returning default value." << endl;
        return ComplexFloat(0, 0);
    }
}

// Додавання векторів
ComplexVector ComplexVector::Add(ComplexVector& b) {
    int tnum = (num < b.num) ? num : b.num;
    ComplexVector tmp(tnum);
    for (int i = 0; i < tnum; i++) {
        tmp.v[i] = v[i] + b.v[i];
    }
    return tmp;
}

// Віднімання векторів
ComplexVector ComplexVector::Subtract(ComplexVector& b) {
    int tnum = (num < b.num) ? num : b.num;
    ComplexVector tmp(tnum);
    for (int i = 0; i < tnum; i++) {
        tmp.v[i] = v[i] - b.v[i];
    }
    return tmp;
}

// Множення вектора на скаляр
ComplexVector ComplexVector::Multiply(float scalar) {
    ComplexVector tmp(num);
    for (int i = 0; i < num; i++) {
        tmp.v[i] = v[i] * scalar;
    }
    return tmp;
}

// Основна функція програми
int main() {
    setlocale(LC_CTYPE, "ukr");
    int choice;
    cout << "Виберіть завдання для виконання:" << endl;
    cout << "1. Робота з класом Time" << endl;
    cout << "2. Робота з класом Vector" << endl;
    cout << "Введіть номер завдання: ";
    cin >> choice;

    switch (choice) {
    case 1: {
        // Приклад роботи з класом Time
        Time time1; // Конструктор за замовчуванням
        Time time2(16, 18, 3); // Конструктор з параметрами

        cout << "Час 1:" << endl;
        cout << "Година: " << time1.getHour() << endl;
        cout << "Хвилини: " << time1.getMinute() << endl;
        cout << "Секунди: " << time1.getSecond() << endl;
        time1.printTime();
        time1.printTime(true);

        cout << "\nЧас 2:" << endl;
        cout << "Година: " << time2.getHour() << endl;
        cout << "Хвилини: " << time2.getMinute() << endl;
        cout << "Секунди: " << time2.getSecond() << endl;
        time2.printTime();
        time2.printTime(true);
        break;
    }
    case 2: {
        // Приклад роботи з класом ComplexVector
        ComplexFloat a(1.0, 2), b, c;
        cout << a << endl;
        b.real(21.3);
        b.imag(22.3);
        cout << b << endl;
        c = a + b;
        cout << c << endl;
        cout << "Test" << endl;
        ComplexVector VecObj, VecObj1(10);
        cout << "VecObj: " << endl;
        VecObj.Output();
        cout << "VecObj1: " << endl;
        VecObj1.Output();
        cout << "Input a: " << endl;
        cin >> a;
        ComplexVector VecObj2(10, a);
        VecObj2.Output();
        VecObj.Input();
        cout << endl;
        VecObj.Output();
        VecObj1 = VecObj.Add(VecObj2);
        VecObj1.Output();

        // Додавання деяких даних та використання нових функцій
        VecObj.SetElement(0, ComplexFloat(3, 4)); // Встановлюємо значення для першого елемента
        cout << "Value of element 0: " << VecObj.GetElement(0) << endl; // Отримуємо значення першого елемента
        ComplexVector VecObj3 = VecObj.Subtract(VecObj1); // Віднімаємо VecObj1 від VecObj
        VecObj3.Output(); // Виводимо результат віднімання

        ComplexVector VecObj4 = VecObj.Multiply(2); // Помножимо всі елементи VecObj на 2
        VecObj4.Output(); // Виводимо результат множення

        return 0;
    }
    }

    return 0;
}
