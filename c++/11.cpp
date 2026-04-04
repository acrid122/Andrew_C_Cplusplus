#include <iostream>
#include <string>

using namespace std;

class Person
{
public:
    Person(string name, unsigned age)
    {
        this->name = name;
        this->age = age;
    }
    void print() const{
        cout << "Name: " << name << "\tAge " << age << endl;
    }
protected:
    string name; //доступно из производных классов, но недоступно извне
private: //закрытые переменные - доступ из производного класса недоступен
    unsigned age;
};

class Employee: public Person //private Person
{
public:
    Employee(string name, unsigned age, string company): Person(name, age)
    {
        this->company = company;
    }
    //using Person::print
    /*
    устанавливаем доступ к функции print базового класса как public
    но если переменные и функции определены в базовом классе как приватные, то сделать их публичными не получится
    */
    void printEmployee() const
    {
        //print() функция prine внутри класса Employee доступна при private спецификаторе
        cout << name << " works in " << company << endl; //Ошибка
    }
private:
    string company;
};

class Person1
{
public:
    Person1(string name, unsigned age): name(name), age(age)
    {}
    void print() const{
        cout << "Name: " << name << "\tAge " << age << endl;
    }
private:
    string name;
    unsigned age;
};

class Employee1: public Person1
{
public:
    Employee1(string name, unsigned age, string company): Person1(name, age), company(company)
    {}
    void print() const
    {
        Person1::print(); //вызываем функцию print из базового класса
        cout << "Works in " << company << endl;
    }
private:
    string company;
};


class Integer
{
public: 
    Integer(unsigned value): value(value)
    {}
    void printInteger() const
    {
        cout << value << endl;
    }
protected:
    unsigned value;
};

class Decimal: public Integer
{
public:
    Decimal (unsigned i_value, unsigned d_value): Integer(i_value), value(d_value)
    {}
    void printDecimal() const
    {
        cout << Integer::value << "." << value << endl; //чтобы обратиться к value из Integer, надо использовать ::.
    }
protected:
    unsigned value;
};


class Camera //класс камеры
{
public:
    void makePhoto()
    {
        cout << "making photo" << endl;
    }
};



class Phone //класс телефона
{
public:
    void makeCall()
    {
        cout << "making call" << endl;
    }
};

//класс смартфона

class Smartphone : public Phone, public Camera
{};

class Book //класс книги
{
public:
    Book (unsigned pages): pages(pages)
    {
        cout << "Book created" << endl;
    }
    ~Book()
    {
        cout << "Book deleted" << endl;
    }
    void printPageCount()
    {
        cout << pages << " pages" << endl;
    }
    void print()
    {
        cout << pages << " pages" << endl;
    }
private:
    unsigned pages; //количество страниц
};

class File //класс электронного файла
{
public:
    File (unsigned size): size(size)
    {
        cout << "File created" << endl;
    }
    ~File()
    {
        cout << "File deleted" << endl;
    }
    void printSize()
    {
        cout << size << " Mb" << endl;
    }
    void print()
    {
        cout << size << " Mb" << endl;
    }
private:
    double size; //количество страниц
};

//класс электронной книги

class Ebook : public Book, public File
{
public:
    Ebook(string title, unsigned pages, double size): Book{pages}, File{size}, title{title}
    //В определении класса Ebook первым базовым классом указан класс Book, поэтому сначала вызываем конструктор класса Book и только потом - конструктор класса File
    {
        cout << "Ebook created" << endl;
    }
    ~Ebook()
    {
        cout << "Ebook deleted" << endl;
    }
    void printTitle()
    {
        cout << "Title: " << endl;
    }
private:
    string title;
};


class Person2
{
public:
    Person2(string name): name(name)
    {
        cout << "Person created" << endl;
    }
    ~Person2()
    {
        cout << "Person deleted" << endl;
    }
    void print() const{
        cout << "Person " << name << endl;
    }
private:
    string name;
};


class Student : public virtual Person2//class Student : public Person2
{
public:
    Student(string name): Person2(name){}
};


class Employee2 : public virtual Person2//class Employee2 : public Person2
{
public:
    Employee2(string name): Person2(name){}
};


//работающий студент
class StudentEmployee: public Student, public Employee2
{
public:
    StudentEmployee(string name): Person2{name}, Student{name}, Employee2{name} {}
};


class Person3
{
public:
    Person3(string name): name{name}
    {}
    void print() const
    {
        cout << "Name: " << name << endl;
    }
private:
    string name; //имя
};

class Employee3: public Person3
{
public: 
    Employee3(string name, string company): Person3{name}, company{company}
    {}
    void print() const
    {
        Person3::print();
        cout << "Works in" << company << endl;
    }
private:
    string company;
};


int main(){
    Person person {"Tom", 38};
    person.print(); 

    Employee employee {"Bob", 42, "Microsoft"};
    employee.printEmployee(); //Bob works in Microsoft

    //employee.print() при private наследовании использовать не получится

    //Что делать если для класса Employee мы все-таки хотим вызвать функцию print()
    //используем using
    /*
    Уровень доступа и спецификатор protected.
    Если переменные или функции в базовом классе являются закрытыми, то есть объявлены со спецификатором private, то производный лкасс хотя и наследует эти переменные и функции, но
    не может к ним обращаться. К примеру, попробуем определить в производном классе функцию, которая выводит значения приватных
    переменных базового класса.
    */
   //Уровень доступа членов базового класса
   /*
   Спецификатор доступа базового класса, которые применяется при установке наследования.

   Если спецификатор базового класса явным образом не указан: class Employee: Person, то по умолчанию применяется спецификатор private. 

   Class person:
   public: name
   protected: name
   private: name

   -> Class Employee: public Person
   public -> public
   protected -> protected
   private -> наследует, но недоступна

   -> Class Employee: protected Person

   public -> protected
   protected -> protected
   private -> наследует, но недоступна

   -> Class Employee: private Person
   public -> private
   protected -> private
   private -> наследует, но недоступна
   */

   //Скрытие функционала базового класса
   /*
   С++ позволяет определять в производном классе переменные и функции с теми же именами, что имеют перменные и функции в базовом классе.
   В этом случае переменные и функции производного класса будут скрывать одноименные переменные и функции базового класса.

   Скрытие функций

   Производный класс может определить функцию с тем же именем, что и функция в базовом классе, с тем же или другим списком параметров.
   Для компилятора такая функция будет существовать независимо от базового класса. И подобное определение функции в проивзодном классе не будет переопределением
   функции из базового класса
   */
  Employee1 bob {"Bob", 22, "Google"};
  bob.print();
  /*
  Функция print в Employee скрывает функцию print класса Person. Однако иногда может потребовать возможность вызвать реализацию функции, которая определена
  именно в базовом классе. В этом случае просто используется оператор: ::.
  */
 //Скрытие перменных
 /*
 Производный класс может иметь переменные с тем же именем, что и базовый класс. Такие варианты реализации приводят к путанице, поэтому лучше так не делать.
 */

 //Множественное наследование
 /*
 Производные класс может иметь несколько прямых базовых классов. Подобный тип наследования называется множественным наследолванием, в отличие от одиночного
 наследования, при котором используется один базовый класс. 
 */

 Smartphone iphone;
 iphone.makeCall();
 iphone.makePhoto();
 //При установке наследование для каждого базового класса указывается спецификатор доступа

 //Конструкторы и деструкторы при множественном наследовании
 /*
 При множественном наследовании также необходимо вызывать конструкторы базовых классов, если они имеют параметры.
 */
Ebook cppbook("About C++", 320, 5.6);
cppbook.printSize();
cppbook.printPageCount();
cppbook.printTitle();

//cppbook.print() ошибка из-за двойственности, так как классы Book и File имеют метод с одинаковым названием
//Чтобы исправить проблему двойственности, можно использовать преобразования типов

static_cast<Book&>(cppbook).print();
static_cast<File&>(cppbook).print();

//двойственное наследование и виртуальные базовые классы

/*
Еще одной формой двойственности при наследовании может быть наследование от нескольких классов, которые косвенно или напрямую наследуются от одного и того
же класса.
*/
StudentEmployee bob_student{"bob"};
bob.print();
/*
Person created
Person Bob
Person deleted*/
/*
Person created
Person created
Person deleted
Person deleted
*/

/*
Для решения проблемы, связанной с тем, что у нас дважды вызывается конструктор и деструктор, а также, что bob.print() не компиируется, следует использовать
виртуальные базовые классы - при установке наследования перед именем базового класса указывается ключевое слово virtual
*/

/*
При вызове функции программа должна определять, с какой именно реализацией функции соотносить этот вызов, то есть связать вызов функции с самой функцией.
В С++ есть два типа связывания - статическое и динамическое.

Когда вызов функций фиксируется до выполнения программы на эатпе компиляции, это называется статическим связыванием (static binding), либо ранним
связыванием (early binding). При это вызов функции через указатель определяется исключительно типом указателя, а не объектом, на который он указывает.
*/

Person3 anna {"Anna"};
Person3* pers = &anna;
pers->print();

Employee3 oleg{"Oleg", "Microsoft"};
pers = &oleg;
pers->print();
}