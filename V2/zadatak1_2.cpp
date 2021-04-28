#include <systemc>
#include <iostream>

int sc_main(int argc, char* argv [])
{
  
  int T1 = rand() % 10 + 1;
  int T2 = rand() % 10 + 1;
  int T = T1 + T2;
  
  sc_start(T, sc_core::SC_NS);
  std::cout << "Trenutno simulaciono vreme je: " << sc_core::sc_time_stamp() << std::endl;
  std::cout << "Random vreme T1 je: " << T1 << ", random vreme T2 je: " << T2 << ", suma vremena je: " << T; 
  
}