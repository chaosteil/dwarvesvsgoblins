#ifndef DVG_SRC_PYTHON_EXAMPLE_C_H_
#define DVG_SRC_PYTHON_EXAMPLE_C_H_

char const *GetString() {
  return "String";
}

int GetInt() {
  return 0;
}

class Example {
 public:
  Example() : int_(0) {}
  ~Example() {}

  int GetInt() const { return int_; }
  void IncInt() { int_++; }
  void DecInt() { int_--; }

 private:
  int int_;
};

#endif  // DVG_SRC_PYTHON_EXAMPLE_C_H_
