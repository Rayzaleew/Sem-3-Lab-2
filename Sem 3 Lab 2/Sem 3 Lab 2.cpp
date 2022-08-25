#include <iostream>

//=======================================================================
//	Лабораторная работа №2 по дисциплине «Программирование»
//	Группа: АБ-021
//	Студент: Шуваев В. А.
//	Преподаватель: Архипова А. Б.
//=======================================================================

using namespace std;

#define part1
#ifdef part1
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

class Time {
 private:
  int hour;
  int minute;
  int second;
  int msecond;

 public:
  Time(int a, int b, int c, int d) {
    hour = ((d / 1000 + c) / 60 + b) / 60 + a;
    minute = ((d / 1000 + c) / 60 + b) % 60;
    second = (d / 1000 + c) % 60;
    msecond = (d % 1000);
  }

  Time() {}
  void AddHour(int h) {
    hour += h;
    hour %= 24;
  }
  void AddMin(int m) {
    minute += m;
    AddHour(minute / 60);
    minute %= 60;
  }
  void AddSec(int s) {
    second += s;
    AddMin(second / 60);
    second %= 60;
  }
  void AddMSec(int s) {
    msecond += s;
    AddSec(msecond / 1000);
    msecond %= 1000;
  }
  void Print() {
    cout << hour << ' ' << minute << ' ' << second << ' ' << msecond << endl;
  }

  friend Time operator+(const Time& t1, const Time& t2);

  friend Time operator-(Time& time_a, Time& time_b);

  friend ostream& operator<<(ostream& os, const Time& t);

  friend istream& operator>>(istream& is, Time& t);

  friend istringstream& operator>>(istringstream& iss, Time& t);
};

Time operator+(const Time& time_a,
               const Time& time_b) {  //Перегрузка оператора вывода
  Time time3(time_a.hour + time_b.hour, time_a.minute + time_b.minute,
             time_a.second + time_b.second, time_a.msecond + time_b.msecond);

  return time3;
}

Time operator-(Time& time_a, Time& time_b) {  //Перегрузка оператора вычитания

  long long t1_all_in_mc = (time_a.hour * (60 * 60 * 1000)) +
                           (time_a.minute * (60 * 1000)) +
                           (time_a.second * 1000) + time_a.msecond;
  long long t2_all_in_mc = (time_b.hour * (60 * 60 * 1000)) +
                           (time_b.minute * (60 * 1000)) +
                           (time_b.second * 1000) + time_b.msecond;
  long long t3_all_in_mc = (t1_all_in_mc > t2_all_in_mc)
                               ? (t1_all_in_mc - t2_all_in_mc)
                               : (t2_all_in_mc - t1_all_in_mc);

  time_a.hour = t3_all_in_mc / (60 * 60 * 1000);
  t3_all_in_mc = t3_all_in_mc % (60 * 60 * 1000);

  time_a.minute = t3_all_in_mc / (60 * 1000);
  t3_all_in_mc = t3_all_in_mc % (60 * 1000);

  time_a.second = t3_all_in_mc / (1000);
  t3_all_in_mc = t3_all_in_mc % (1000);

  time_a.msecond = t3_all_in_mc;

  Time t3(time_a.hour, time_a.minute, time_a.second, time_a.msecond);

  return t3;
}

ostream& operator<<(ostream& os, const Time& t) {  //Перегрузка оператора вывода
  os << t.hour << ":" << t.minute << ":" << t.second << ":" << t.msecond;

  return os;
}

istream& operator>>(istream& is, Time& t) {  //Перегрузка оператора ввода
  if (&is == &cin) cout << "Часы: ";
  is >> t.hour;

  if (&is == &cin) cout << "Минуты: ";
  is >> t.minute;

  if (&is == &cin) cout << "Секунды: ";
  is >> t.second;

  if (&is == &cin) cout << "Миллисекунды: ";
  is >> t.msecond;

  if (&is == &cin) cout << endl;

  return is;
}

istringstream& operator>>(istringstream& iss, Time& t) {
  iss >> t.hour >> t.minute >> t.second >> t.msecond;

  return iss;
}

int main() {
  //Задание к работе: Написать программу на языке С++, которая складывает и
  //вычитает время (часы, минуты, секунды и миллисекунды) с использованием
  //классов. Использовать конструкторы по умолчанию и параметризованные.
  //Перегрузить операторы сложения и вычитания, а также ввода и вывода на 3
  //потока (строковый, консоль, файловый).

  cout << "===================================================================="
          "===\n\tЛабораторная работа №2 по дисциплине "
          "\"Программирование\"\n\tГруппа: АБ-021\n\tСтудент: Шуваев. В. "
          "А.\n\tПреподаватель: Архипова А. "
          "Б.\n================================================================"
          "=======\n\n";

  Time time_a, time_b;

  int choise;
  cout << "Выберите тип ввода и вывода данных: " << endl
       << "1 - ввод с консоли и вывод в консоль" << endl
       << "2 - ввод с файла и вывод в файл" << endl
       << "3 - поток вывода" << endl
       << ": ";
  do {
    cin >> choise;
    cout << endl;
    if (choise < 1 || choise > 3)
      cout << "Вы неверно ввели номер варианта типа ввода и вывода данных. "
              "Попробуйте еще раз: ";
  } while (choise < 1 || choise > 3);

  switch (choise) {
    case 1: {
      //Вввод значений из консоли
      cin >> time_a;
      cin >> time_b;
      //Вывод значений в консоль
      cout << "Cумма времени: " << time_a + time_b << endl;
      cout << "Разность времени: " << time_a - time_b << endl;
      break;
    }
    case 2: {
      ifstream file1(
          "in.txt");  //Инициализация file1 в качестве объекта потока ввода
      ofstream file2(
          "out.txt");  //Инициализация file2 в качестве объекта потока вывода
      //Чтение значений из файла "in.txt"
      file1 >> time_a;
      file1 >> time_b;
      //Запись значений в файл "out.txt"
      file2 << time_a + time_b << endl;
      file2 << time_a - time_b << endl;
      break;
    }
    case 3: {
      ostringstream oss;  //Инициализация объекта строкового потока вывода
      //Чтение значений из консоли
      /*cin >> time_a;
      cin >> time_b;*/

      string str1 = "100 100 100 100", str2 = "100 100 100 101";
      /*cin.ignore(32767,'\n');
      getline(cin,str1);
      getline(cin, str2);*/

      istringstream iss1(str1), iss2(str2);
      iss1 >> time_a;
      iss2 >> time_b;
      //Запись результатов работы в объект строкового потока вывода
      oss << "Cумма времени time_a и time_b: " << time_a + time_b << endl;
      oss << "Разница во времени между time_a и time_b: " << time_a - time_b
          << endl;
      //Вывод данных, содержащихся в объекте строкового потока вывода, в виде
      //строки в консоль
      cout << oss.str();
      break;
    }
  }

  return 0;
}
#endif

//#define part2
#ifdef part2

#include <vector>

// y = f(x,z,t)

// y = x - (az  + b) + tc

struct Axis {
  double x;
  double z;
  double t;
};

struct Parametrs {
  double a;
  double b;
  double c;
};

class Term {  //Сложение/вычитание
 public:
  Term(char o, double p) {
    op = o;
    number = p;
  }
  double Done(double num) {
    if (op == '+') {
      num += number;
    }
    if (op == '-') {
      num -= number;
    }
    return num;
  }

 private:
  char op;
  double number;
};

class NumberOfTerm {
 public:
  void AddTerm(char op, double n) { terms.push_back({op, n}); }

  double Execute(double num) {
    for (Term term : terms) {
      num = term.Done(num);
    }
    return num;
  }

 private:
  vector<Term> terms;
};

NumberOfTerm MakeY(Parametrs p, Axis ax) {  //Вычисление значения y
  NumberOfTerm func;

  func.AddTerm('-', ax.z * p.a + p.b);  //Вычисление -(a*z+b)
  func.AddTerm('+', ax.t * p.c);        //Вычисление +(t*c)

  return func;
}

NumberOfTerm MakeX(Parametrs p, Axis ax) {  //Вычисление значения x
  NumberOfTerm func;

  func.AddTerm('+', ax.z * p.a + p.b);  //Вычисление +(a*z+b)
  func.AddTerm('-', ax.t * p.c);        //Вычисление -(t*c)

  return func;
}

double EvaluateY(Parametrs p, Axis a) {  //возврат значения y
  NumberOfTerm func = MakeY(p, a);

  return func.Execute(a.x);
}

double EvaluateX(Parametrs p, Axis a, double Y) {
  NumberOfTerm func = MakeX(p, a);

  return func.Execute(Y);
}

int main() {
  Axis A{15, 3, 4};      // x,z,t
  Parametrs p{1, 0, 1};  // a,b,c

  // y = x - (a*z + b) + t*c
  double Y = EvaluateY(p, A);
  cout << Y << endl;

  // x = y + (a*z + b) - t*c
  double X = EvaluateX(p, A, Y);
  cout << X << endl;

  return 0;
}

#endif