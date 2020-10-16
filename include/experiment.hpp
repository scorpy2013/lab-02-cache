//
// Copyright [2020] <scorpy2013>
//

#ifndef INCLUDE_EXPERIMENT_HPP_
#define INCLUDE_EXPERIMENT_HPP_
#include <algorithm>
#include <chrono>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <utility>
#include <vector>
// кол-во обходов
const size_t ROUNDS = 1000;
// время, требуемое для различных видов обходов
struct Time {
  double direct_time;
  double reverse_time;
  double random_time;
};
// класс, помогающий проводить исследование
class Experiment {
 public:
  static int number_of_experiments;
  // конструктор, принимающий кол-во элементов в массиве
  explicit Experiment(const size_t &kol);
  // функция, проводящая исследования
  void start();
  ~Experiment();
  [[nodiscard]] size_t get_number() const;  // получаем кол-во элементов
  [[nodiscard]] const Time &get_time()
      const;  // получаем время выполнения обхода
 private:
  Time time;
  int *arr;                   // наш массив
  size_t number_of_elements;  // размер массива
  std::vector<size_t> indexes;
  int RETURN(int x);
  double buffer_passing();
  void warming_up();      // прогрев
  void direct_travel();   // прямой обход
  void reverse_travel();  // обратный обход
  void random_travel();   // случайный обход
};
#endif  // INCLUDE_EXPERIMENT_HPP_