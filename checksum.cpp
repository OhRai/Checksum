#include <climits>
#include <iostream>

#ifndef MARMOSET_TESTING
int main();
#endif

unsigned int add_checksum();
bool verify_checksum();
unsigned int remove_checksum();

// Adding the checksum for ONE NUMBER
unsigned int add_checksum(unsigned int n) {
  if (n > 99999999) {
    return UINT_MAX;
  }

  unsigned int array[8]{};
  unsigned int temp{n};
  int i{0};
  int r{};
  int sum{0};

  // Splits up the number into singular digits and puts them into an array
  while (n != 0) {

    r = n % 10;

    array[i] = r;
    ++i;

    n /= 10;
  }

  for (i = 0; i < 8; i += 2) {
    array[i] *= 2;

    if (array[i] > 9) {
      array[i] = (array[i] / 10) + (array[i] % 10);
    }
  }

  for (int i = 0; i < 8; ++i) {
    sum += array[i];
  }

  unsigned int product = sum * 9;

  unsigned int checksum = product % 10;

  std::string s1 = std::to_string(temp);
  std::string s2 = std::to_string(checksum);

  std::string s = s1 + s2;

  unsigned int new_n = std::stoi(s);

  return new_n;
}

// Adding the checksum to a SERIES OF NUMBERS
void add_checksum(unsigned int array[], std::size_t capacity) {

  // Add checksum to each element in the array
  for (int i = 0; i < capacity; ++i) {
    array[i] = add_checksum(array[i]);
  }
}

bool verify_checksum(unsigned int n) {
  if (n % 10 == add_checksum(n / 10) % 10) {
    return true;
  }
  return false;
}

unsigned int remove_checksum(unsigned int n) {
  if (n > 999999999 || verify_checksum(n) == false) {
    return UINT_MAX;
  }

  return n / 10;
}

void remove_checksum( unsigned int array[], std::size_t capacity ) {
  for (int i = 0; i < capacity; ++i) {
    array[i] = remove_checksum(array[i]);
  }
}

#ifndef MARMOSET_TESTING
int main() {
  unsigned int value_to_protect{21352411};
  unsigned int temp_value{value_to_protect};
  unsigned int protected_value = add_checksum(value_to_protect);
  std::cout << "The value " << value_to_protect << " with the checksum added is " << protected_value << "." << std::endl;

  if (verify_checksum(protected_value) {
    std::cout << "The checksum is valid." << std::endl;
  } else {
    std::cout << "The checksum is invalid." << std::endl;
  }
  const std::size_t QTY_VALUES{3};
  unsigned int value_series[QTY_VALUES]{20201122, 20209913, 20224012};

  add_checksum(value_series, QTY_VALUES);

  std::cout << "Series with checksums added: ";
  for (std::size_t series_index{0}; series_index < QTY_VALUES; series_index++) {
    std::cout << value_series[series_index] << " ";
  }

  std::cout << std::endl;

  return 0;
}
#endif