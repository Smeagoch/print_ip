#include <iostream>
#include <list>
#include <string>
#include <vector>

template <typename T>
typename std::enable_if <
std::is_integral<std::remove_reference_t<T>>::value>::type
print_ip(T ip) {
  for (int i = sizeof(T) - 1; i >= 0; --i) {
    std::cout << ((ip >> (8 * i)) & 0xFF);
    if (i > 0)
      std::cout << ".";
  }
  std::cout << std::endl;
}

template <typename T>
typename std::enable_if<
    std::is_same<std::remove_reference_t<T>, std::string>::value>::type
print_ip(T ip) {
  std::cout << ip << "\n";
}

template <typename T> struct is_vector : std::false_type {};

template <typename... Args>
struct is_vector<std::vector<Args...>> : std::true_type {};

template <typename T> struct is_list : std::false_type {};

template <typename... Args>
struct is_list<std::list<Args...>> : std::true_type {};

template <typename T>
typename std::enable_if<is_vector<std::remove_reference_t<T>>::value ||
                        is_list<std::remove_reference_t<T>>::value>::type
print_ip(T ip) {
  auto it = ip.begin();
  const auto end = ip.end();

  while (it != end) {
    std::cout << *it;

    if (++it != end) {
      std::cout << ".";
    }
  }

  std::cout << std::endl;
}

int main()
{
    print_ip( int8_t{-1} ); // 255
    print_ip( int16_t{0} ); // 0.0
    print_ip( int32_t{2130706433} ); // 127.0.0.1
    print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
    print_ip( std::string{"Hello, World!"} ); // Hello, World!
    print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
    print_ip( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100

    return 0;
}