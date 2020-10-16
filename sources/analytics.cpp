//
// Copyright [2020] <scorpy2013>
//
// 1/2 * cache_sizes['1'] < 2^x < 2^(x+1) < ... < 2^(x+n) < 3/2 *
// cache_sizes['max'] cache_size['1'] = 0,031 mb; cache_size['2'] = 0,25 mb;
// cache_size['3'] = 3 mb;
// 0,0155 mb < ... < 4,5 mb
// 16 kb < ... < 3072 kb
#include "analytics.hpp"
Analytics::Analytics() {
  buffer.min_size = 0.5 * cache_size_L1;
  buffer.current_size = buffer.min_size;
  buffer.max_size = 1.5 * cache_size_L3;
}
Analytics::Analytics(const size_t &min, const size_t &max) {
  buffer.min_size = 0.5 * min * 1024;
  buffer.current_size = buffer.min_size;
  buffer.max_size = 1.5 * max * 1024;
}
void Analytics::Start() {
  size_t kol = buffer.min_size / sizeof(int);
  size_t x = std::log2(buffer.min_size);  // степень двойки 2^x
  // 2^x < 2^(x+1) < ... < 2^(x+n) < 3/2 * cache_sizes['max']
  // пока выполняется условие, мы записываем результаты исследований
  while (buffer.current_size <= buffer.max_size) {
    auto *experiment = new Experiment(kol);
    experiment->start();  // начинаем делать обходы для кол-ва эл-тов kol
    results.push_back(experiment);
    x++;  // увеличиваем степень двойки
    buffer.current_size = pow(2, x);  // текущий размер меняется
    kol = buffer.current_size / sizeof(int);
  }
  if (buffer.current_size != buffer.max_size) {
    auto *experiment = new Experiment(buffer.max_size / sizeof(int));
    experiment->start();
    results.push_back(experiment);
  }
}
void Analytics::Report() {
  std::cout << "investigation:\n";
  std::cout << "\ttravel_variant: Direct\n";
  std::cout << "\texperiments:\n";
  for (size_t i = 0; i < results.size(); i++) {
    std::cout << "\t- experiment:\n";
    std::cout << "\t\tnumber: " << i + 1 << "\n";
    std::cout << "\t\tinput data:\n";
    std::cout << "\t\t\tbuffer size: \""
              << results[i]->get_number() * sizeof(int) / 1024 << " kB\"\n";
    std::cout << "\t\tresults:\n";
    std::cout << "\t\t\tduration: \"" << results[i]->get_time().direct_time
              << " ms\"\n";
  }
  std::cout << "\n";
  std::cout << "investigation:\n";
  std::cout << "\ttravel_variant: Reverse\n";
  std::cout << "\texperiments:\n";
  for (size_t i = 0; i < results.size(); i++) {
    std::cout << "\t- experiment:\n";
    std::cout << "\t\tnumber: " << i + 1 << "\n";
    std::cout << "\t\tinput data:\n";
    std::cout << "\t\t\tbuffer size: \""
              << results[i]->get_number() * sizeof(int) / 1024 << " kB\"\n";
    std::cout << "\t\tresults:\n";
    std::cout << "\t\t\tduration: \"" << results[i]->get_time().reverse_time
              << " ms\"\n";
  }
  std::cout << "\n";
  std::cout << "investigation:\n";
  std::cout << "\ttravel_variant: Random\n";
  std::cout << "\texperiments:\n";
  for (size_t i = 0; i < results.size(); i++) {
    std::cout << "\t- experiment:\n";
    std::cout << "\t\tnumber: " << i + 1 << "\n";
    std::cout << "\t\tinput data:\n";
    std::cout << "\t\t\tbuffer size: \""
              << results[i]->get_number() * sizeof(int) / 1024 << " kB\"\n";
    std::cout << "\t\tresults:\n";
    std::cout << "\t\t\tduration: \"" << results[i]->get_time().random_time
              << " ms\"\n";
  }
  std::cout << "\n";
}
Analytics::~Analytics() {
  for (auto element : results) {
    delete element;
  }
  results.clear();
}
