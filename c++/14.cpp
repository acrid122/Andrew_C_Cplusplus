#include <iostream>
#include <string>
#include <memory>
using namespace std;

/* class MyClass
{
public:
    operator OtherType const; //оператор преобразования типа MyClass в тип OtherType
    //Причем тип возвращаемого значения у функции оператора не указывается, поскольку целевой тип всегда подразумевается в имени функции, поэтому
    //здесь функция должна возвращать объект OtherType.
    
    В отличие от большинства операторов, операторы преобразования должны быть определены только как функции-члены класса. Их нельзя определить
    как обычные функции. Они также являются единственными операторами, в которых ключеоввму слову оператора не предшествует тип возвращаемого значения
    (вместо этого возвращаемый тип идет после ключевого слова operator).
} */
class Counter
{
public:
    Counter(int number)
    {
        value = number;
    }
    operator int() const {return value;} //оператор преобразования типа Counter в тип int
    explicit operator double() const {return value;} //оператор преобразования типа Counter в тип double. Ключевое слово explicit отключает неявные преобразования типа Counter в тип double
private:
    int value;
};

//электронная книга
class Printbook;

class Ebook
{
public: 
    Ebook(string book_title)
    {
        title = book_title;
    }
    operator Printbook() const;
    string getTitle() const {return title;}
private:
    string title;
};

class Printbook
{
public:
    Printbook(string book_title)
    {
        title = book_title;
    }
    operator Ebook() const;
    string getTitle() const {return title;}
private:
    string title;
};

Ebook::operator Printbook() const
{
    return Printbook{title};
}

Printbook::operator Ebook() const
{
    return Ebook{title};
}


class Person
{
public:
    Person(string p_name, int p_age, string p_company)
    {
        name = p_name;
        company = p_company;
        age = p_age;
    }
    string operator[] (unsigned index) const
    {
        switch (index)
        {
            case 0: return name;
            case 1: return to_string(age);
            case 2: return company;
            default: return "Bad index";
        }
    }
private:
    string name;
    int age;
    string company;
};

class Person2
{
public:
    Person2(string p_name, int p_age, string p_company)
    {
        name = p_name;
        company = p_company;
        age = p_age;
    }
    string operator[] (const string& prop) const
    {
        if (prop == "name") return name;
        else if (prop == "age") return to_string(age);
        else if (prop == "company") return company;
        else return "Bad Index";
    }
private:
    string name;
    int age;
    string company;
};

class Counter2
{
public:
    Counter2 (int val)
    {
        value = val;
    }
    void print() const
    {
        cout << "Value: " << value << endl; 
    }
    void setValue(int val){ value = val;}

private:
    int value;
};

class Counter3
{
public:
    Counter3 (int val)
    {
        value = val;
    }
    void print() const
    {
        cout << "Value: " << value << endl; 
    }
    Counter3& operator= (const Counter3& counter)
    {
        if (&counter != this)
        {
            value = counter.value; //counter1 = counter1
        }
        return *this;
    }
    
private:
    int value;
};



namespace hello //определяем пространство имен hello
{
    const string message {"hello world"};
    void print(const string& text)
    {
        cout << text << endl;
    }
}

namespace console
{
    namespace messages
    {
        const string hello {"hello"};
        const string welcome {"welcome"};
        const string goodbye {"good bye"};
    }
    void print(const string &text)
    {
        cout << text << endl;
    }
    void print_default()
    {
        cout << messages::hello << endl;
    }
}

//using namespace hello - подключаю все компоненты пространства hello
//using console::print - подключить только какие-то определенные функции, чтобы избежать конфликта переменных
//Псевдонимы пространств

class Person3
{
private:
    string name;
    class Account // вложенный класс
    {
    public:
        Account(const string& p_email, const string& p_password)
        {
            email = p_email;
            password = p_password;
        }
        string email;
        string password;
    };
    Account account {"", ""}; //переменная вложенного класа
public:
    Person3(const string& p_name, const string& p_email, const string& p_password)
    {
        name = p_name;
        account = Account(p_email, p_password);
    }
    void print()
    {
        cout << "Name: " << name << "\n" << "Email: " << account.email << "\n" << "Password: " << account.password << endl;
    }
};

struct Person4
{
    string name;
    int age;
};

struct Product{
    string name;
    double price;
    double min_discount;
    double max_discount;

    void print_final_price(double Product::*discount)
    {
        //В качестве параметра в функцию передается указатель double Product::*discount. Он не хранит значение, а лишь "знает", как получить доступ  к полю
        //типа double внутри любого объекта Poduct.
        //Применяем укзаатель на член к this
        double final_price = this->price - (this->*discount);
        cout << "Final price for " << this->name << " is: " << final_price << endl;
    }
};


struct Product2{
    string name;
    double price;

    double get_fixed_discount(double amount)
    {
        return amount;
    }

    double get_percentage_discount (double percent)
    {
        return price * (percent / 100);
    }
};

namespace mes = console::messages;
int main(){
    //Операторы преобразования типов.
    /*
    С++ позволяет определить функцию оператора преобразования из типа текущего класса в другой тип. Тип, в который производится преобразование,
    может быть фундаментальным типом или типом класса. В общем случае оператор преобразования имеет следующую форму:
    */
    Counter counter{25};
    int n = counter; //вызов оператора преобразования типа Counter в тип int

    Counter counter2{30};
    int m = static_cast<int>(counter2); //вызов оператора преобразования типа Counter в тип int с помощью оператора static_cast
    cout << "n: " << n << endl; //n: 25'
    cout << "m: " << m << endl; //m: 30

    /*Неявные преобразования не всегда желательны. В данном случае их можно отключить, определив функцию оператора с помощью ключевого слова explicit. 
    В этом случае оператор преобразования будет вызываться только при явном указании типа, к которому выполняется преобразование, с помощью оператора 
    static_cast.
    */
   Counter counter3{40};
    //double d = counter3; //ошибка компиляции, так как оператор преобразования типа Counter в тип double определен с помощью ключевого слова explicit
    double d = static_cast<double>(counter3); //вызов оператора преобразования типа Counter в тип double с помощью оператора static_cast
    cout << "d: " << d << endl; //d: 40

    Printbook book("C++");
    Ebook ebook {book}; //вызов оператора преобразования типа Printbook в тип Ebook
    cout << "ebook title: " << ebook.getTitle() << endl; //ebook title
    Printbook print_book {ebook}; //вызов оператора преобразования типа Ebook в тип Printbook
    cout << "print book title: " << print_book.getTitle() << endl; //print book title

    //Оператора индексирования
    /*
    Оператор индексирования позволяет интепретировать объект как массив или как контейнер других объектов и позволяет выбирать из объекта отдельные элементы.
    Функция оператора [] должна принимать в качестве аргумента условный индекс, по которому в объекте-контейнере можно найти нужный элемент.
    */

    Person tom {"Tom", 50, "Microsoft"};
    cout << tom[0] << '\n' << tom[1] << '\n' << tom[2] << endl;

    Person2 tom2 {"Tom2", 50, "Microsoft"};
    cout << tom2["name"] << '\n' << tom2["age"] << '\n' << tom2["company"] << endl;

    //Переопределение оператора присваивания
    /*
    Компилятор по умолчанию компилирует для типов оператор присваивания, благодаря чему мы можем присваивать значения некоторого типа переменным/параметрам/
    константам этого типа. Создаваемый по умолчанию оператор присваивания просто копирует все переменные-члены класса одну за другой (в том порядке, в котором
    они объявлены в определении класса)
    */
   Counter2 c1{25};
   Counter2 c2 = c1; // c2 получается копию сосстояния c1
   c1.setValue(30); //изменения в c1 не влияют на c2
   c1.print(); //30
   c2.print(); //25
   /*
   Стоит отметить, что какие-либо изменения переменной value в одном объекте Counter, никак не затрагивает другой объект.
   Так работает создаваемый по умолчанию оператор присваивания. Но его можно переопределить. Стоит учитывать, что оператор присваивания можно определить только
   как функцию-член класса. Оператор присваивания должен возвращать ссылку на объект, а его параметр должен предствалять ссылку на константу. 
   */
    /*
   Counter3 counter1{25};
   Counter3 counter2{0};
   Counter3 counter3{0};
   counter3 = counter2 = counter1;
   counter3 = (counter2 = counter1);
   */
  Counter3 c4{25};
  Counter3 c5{30};
  c5  = c4;
  c5.print();

  //Пространства имен

  /*
  Пространство имен позволяет сгруппировать функционал в отедльные контейнеры. Пространтсво имен представляет блок кода, которые содержит набор компонентов
  (функций, классов и т.д.) и имеет некоторое имя, которое прикрепляется к каждому компоненту из этого пространства. Полное имя каждого компонента - 
  это имя пространства имен, за которым следует оператор :: (оператор области видимости) и имя компонента. Примером может служить оператор cout, который
  предназначен для вывода строки на конасоль и который определен в пространстве имен std.

  Если пространство имен не указано, то по умолчанию применяется глобальное пространство имен. все имена в глобальном пространтсве имен такие же, как вы
  их объявлете, без прикрепления имени пространства имен.
  */
 hello::print(hello::message);
 console::print(console::messages::hello);
    cout << mes::welcome << endl;
 //директива using позволяет ссылаться на любой компонент пространства имен без использования его имени

 //Вложенные классы
 /*
 Вложенный класс - класс, определение которого находится внутри другого класса. Обычно вложенные классы применяются для описания таких сущностей, которые могут
 существовать только в рамках объекта внешнего класса, особенно когда внешний класс работает с набором объектов вложенного класса.
 */
Person3 tom3 {"Tom", "tom@gmail.com", "1234"};
tom3.print();

/*
В С++ существуют не только обычные указатели, которые хранят адрес объекта в памяти. Есть и более специфический интсрумент - указатели на члены класса. Это особый
вид указателей, который "указывает" не на конкретный объект, а на само поле или метод внутри определения класса.

В отличие от обычного указателя, который хранит абсолютный адрес в памяти, указатель на член класса хранит, по сути, смещение поля данных или адрес функции-члена
относительно начала любого объекта этого класса. Сами по себе они бесполезны; их сила раскрывается только при применении к конкретному экземпляру класса.

Указатели на члены класса не часто используются, но в некоторых сценариях они незаменимы.
Некоторые ситуации применения. Реализация паттера "Стратегия" или "Команда": объект может хранить указатель на метод, который определяет его текущее поведение (стратегию)

Обработка данных по шаблону: можно создать массив указателей на поля и итерироваться по ним для выполнения однотипных операций (сериализация, валидация, вычисление суммы)

Диспетчеризация вызово: в событийных системах, управляемых событиями, можно составить карту.словарь, где ключом является некое событие, а значением - указатель на
метод-обработчик этого события.

Указатели на поля класса/структуры представляют простейший вид указателей на члены класса. Они позволяют выбрать, с каким поле объекта работать, уже во время
выполнения программы. Их формальный синтаксис вовлекает три компонента:

1. Объявление ->  тип_поля Класс::*имя_указателя;
2. Инициализация -> имя_указателя = &Класс::имя_поля;
3. Использование -> объект.*имя_указателя (оператор "точка-звездочка")
указатель_на_объект->*имя_указателя (оператора "стрелка-зведочка")
*/
//Объявляем указатель на член класса Person4 типа int

int Person4::*p_age;

//Инициализируем указатель - указываем на поле age

p_age = &Person4::age;

//Используем указатель

Person4 tom4 {"Tom", 33};
cout << "Person age: " << tom4.*p_age << endl;

Person4 bob4 {"Bob", 22};
Person4* p_bob = &bob4;
cout << "Person age: " << p_bob->*p_age << endl;

Product phone{"Iphone", 1000.0, 50.0, 200.0};

//В зависимости от условия, наш указатель будет "смотреть" на разные поля

cout << "Min discount: " << endl;
phone.print_final_price(&Product::min_discount);

cout << "Max discount: " << endl;
phone.print_final_price(&Product::max_discount);

phone.max_discount = 300.0;
cout << "Max discount: " << endl;
phone.print_final_price(&Product::max_discount);

/*
Указатели на функции-члены класса.

Указатели на функции позволяют динамически выбирать, какой метод объекта будет вызван.

1. Объявление -> возвращаемый_тип (Класс::*имя_указателя)(параметры);
2. Инициализаиция -> имя_указателя = &Класс::имя_метода;
3. Использования:
(объект.*имя_указателя)(аргументы);
(указатель_на_объект->*имя_указателя)(аргументы);
*/

//Объявляю указатель на метод класса Product2, который принимает double и возвращает double

double (Product2::*p_discount_calculator)(double);

Product2 tv{"LG", 2000.0};

bool holiday_season = true;

if (holiday_season){
    //указываю на метод, считающий скидку в процентах

    p_discount_calculator = &Product2::get_percentage_discount;
    double discount = (tv.*p_discount_calculator)(15.0); 
    cout << "Holiday discount: " << discount << endl;
    cout << "Final price: " << tv.price - discount << endl;
}
else{
    //Указываю не метод с фиксированной скидкой
    p_discount_calculator = &Product2::get_fixed_discount;
    double discount = (tv.*p_discount_calculator)(100); 
    cout << "Rergular discount: " << discount << endl;
    cout << "Final price: " << tv.price - discount << endl; 
}
}
