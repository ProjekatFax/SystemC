#include <systemc>
#include <iostream>

int sc_main(int argc, char* argv [])
{
  
  int T = rand() % 100 + 10;
  sc_start(T, sc_core::SC_NS);
  std::cout << "Trenutno simulaciono vreme je: " << sc_core::sc_time_stamp() << std::endl;
  std::cout << "Random vreme je: " << T; 
  
}