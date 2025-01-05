namespace hypercpu {
  template<typename T>
  constexpr bool subtraction_will_underflow(T& a, T& b) {
    return b > a;
  }
}