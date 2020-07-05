#pragma GCC target("avx2")
#include <iostream>
#include "Viewer.h"

void Start() {
  std::cout << "--------------------lab8: Rubik's Cube--------------------\n";
  std::cout << "- Type \"1\" on your keyboard to read cube's state from a file;\n";
  std::cout << "- Type \"2\" on your keyboard to write cube's state to a file;\n";
  std::cout << "- Press \"G\" on your keyboard to generate random cube's state;\n";
  std::cout << "- Press \"S\" on your keyboard to solve cube.\n";
  Cube c = Cube();
  auto viewer = createOpenglViewer();
  viewer->init();
  viewer->setRotateDuration(0.5);
  viewer->setCube(c);
  std::cout << std::endl;
  viewer->run();
}

int main() {
  Start();
  return 0;
}