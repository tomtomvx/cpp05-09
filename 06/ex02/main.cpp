
#include "Base.hpp"
#include <cstddef>

Base *generate() { return NULL; }
void identify(Base *p) { (void)p; }
void identify(Base &p) { (void)p; }

int main() { return 0; }
