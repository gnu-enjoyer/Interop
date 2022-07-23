#include <dlfcn.h>
#include <iostream>
#include <stdexcept>

class Loader {

  void *handle;

public:
  explicit Loader(const char *fd) { handle = dlopen(fd, RTLD_LAZY); };

  ~Loader() { dlclose(handle); };

  Loader(const Loader &) = delete;

  Loader(Loader &&) = delete;

  struct FFI {
    void *addr;

    template <typename T, typename TT> T Invoke(TT &&v) {
      return ((T(*)(TT))addr)(v);
    };
  };

  FFI GetFn(const char *name) { return {dlsym(handle, name)}; }
};

int main() {

  auto FFI = Loader("lib/dyn.so");

  auto Fn = FFI.GetFn("add3");

  try {
    std::cout << Fn.Invoke<int, int>(1234) << std::endl;

    if (Fn.Invoke<int>(1337) != 1340)
      throw std::runtime_error("Bad invocation");
  } catch (...) {}

  return 0;
}