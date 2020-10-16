//
// Copyright [2020] <scorpy2013>
//

#include "experiment.hpp"
int Experiment::number_of_experiments = 0;
size_t Experiment::get_number() const { return number_of_elements; }
const Time &Experiment::get_time() const { return time; }
int Experiment::RETURN(int x) { return x; }
double Experiment::buffer_passing() {
  // фиксируем начальное время
  auto start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < ROUNDS; ++i) {
    for (size_t j = 0; j < number_of_elements; ++j) {
      RETURN(arr[j]);
    }
  }
  // фиксируем конечное время
  auto end = std::chrono::high_resolution_clock::now();
  // разница конечной и начальной позиции - время, требуемое для одного
  // иссследования
  return std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
      .count();
}
void Experiment::start() {
  direct_travel();
  reverse_travel();
  random_travel();
}
void Experiment::warming_up() {
  for (const size_t &i : indexes) {
    RETURN(arr[i]);
  }
}
void Experiment::direct_travel() {
  warming_up();
  time.direct_time = buffer_passing();
  std::cout << "Direct travel time: " << time.direct_time << " ms" << std::endl;
}
void Experiment::reverse_travel() {
  // подготовили наши индексы для обратного обхода
  std::reverse(indexes.begin(), indexes.end());
  warming_up();
  time.reverse_time = buffer_passing();
  std::cout << "Reverse travel time: " << time.reverse_time << " ms"
            << std::endl;
}
void Experiment::random_travel() {
  std::mt19937 g(clock());
  // перемешиваем наши индексы
  std::shuffle(indexes.begin(), indexes.end(), g);
  warming_up();
  time.random_time = buffer_passing();
  std::cout << "Random travel time: " << time.random_time << " ms" << std::endl;
}

Experiment::Experiment(const size_t &kol) {
  // подготавливаемся к проведению исследования
  number_of_elements = kol;
  number_of_experiments++;
  // std::cout << "_____________________________________" << std::endl;
  // std::cout << "Experiment № " << number_of_experiments << std::endl;
  // std::cout << "Numbers of elements: " << number_of_elements << std::endl;
  // создаем массив для прогрева и обходов
  arr = new int[number_of_elements];
  std::mt19937 randomiser(clock());
  for (size_t i = 0; i < number_of_elements; ++i) {
    // создаем случайные элементы в масссиве
    arr[i] = randomiser();
  }

  for (size_t i = 0; i < number_of_elements; i += 16) {
    indexes.push_back(i);
  }


}



Experiment::~Experiment() { delete[] arr; }
