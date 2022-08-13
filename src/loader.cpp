#include <dlfcn.h>
#include <iostream>
#include <stdexcept>

class Loader {

  void *handle;

public:
  explicit Loader(const char *fd) { 
    handle = dlopen(fd, RTLD_LAZY); 

    if(!handle) throw std::runtime_error("obj not found");    
    };

  ~Loader() { dlclose(handle); };

  struct FFI {
    void *addr;

    template <typename T, typename TT> T Invoke(TT &&v) {
      return ((T(*)(TT))addr)(v);
    };
  };

  FFI GetFn(const char *name) { return {dlsym(handle, name)}; }
};

int main() {

  Loader FFILdr = Loader("lib/static.so");

  auto Fn = FFILdr.GetFn("add3");

  std::cout << Fn.Invoke<int, int>(1234l) << std::endl;

  if (Fn.Invoke<int>(1337) != 1340) throw std::runtime_error("Bad invocation");

  auto FnString = FFILdr.GetFn("strng");

  std::cout << FnString.Invoke<const char*>("helloNim") << std::endl;

  return 0;
}