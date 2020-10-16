//
// Copyright [2020] <scorpy2013>
//

#ifndef INCLUDE_ANALYTICS_HPP_
#define INCLUDE_ANALYTICS_HPP_

#include <fstream>
#include <vector>

#include "experiment.hpp"
// размер кэшов процессора моего компьютера в байтах
const size_t cache_size_L1 = 32 * 1024;
const size_t cache_size_L2 = 256 * 1024;
const size_t cache_size_L3 = 3072 * 1024;
// размеры массивов для прогрева и обходов из формулы
// 1/2 * cache_sizes['1'] < 2^x < 2^(x+1) < ... < 2^(x+n) < 3/2 *
// cache_sizes['max']
struct buffer_size {
  double min_size;      // начальный размер массива
  double current_size;  // текущий размер массива
  double max_size;      // максимальный размер массива
};
// класс для исследования зависимости времени
// чтения одного элемента массива от размера массива
class Analytics {
 public:
  Analytics();
  Analytics(const size_t &min, const size_t &max);
  // функция, запускающая исследования
  void Start();
  // функция, выводящая результат на экран
  void Report();
  virtual ~Analytics();

 private:
  // размеры массива для эксперимента
  buffer_size buffer{};
  // результаты исследования
  std::vector<Experiment *> results;
};
#endif  // INCLUDE_ANALYTICS_HPP_

