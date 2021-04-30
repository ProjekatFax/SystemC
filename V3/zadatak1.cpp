// Моделовати модул коjи садржи два процеса. Први процес ствара кружну секвенцу 
// првих 64 Фибоначиjевих броjева у случаjнимв ременским интервалима. 
// Нови броj се ствара у интервалу од 10ns до 100 ns.  Други процес исписуjе 
// поруку 5 ns након што jеб роj створен. 
// За комуникациjу међу процесима користити догађаj.
// Порука треба да садржи броj и тренутно време симулациjе.

#include <systemc>
#include <iostream>
#include <cstdlib>
#include <deque>

SC_MODULE(Module01)
{	
	protected:
		std::deque<int> ints;
	public:
		sc_core::sc_event s0;
		
  		SC_CTOR(Module01)
    		{
  			SC_THREAD(rand_fib)
    			SC_THREAD(write)
    		}
		void rand_fib(void)
        	{
        		int first = 0, second = 1, sum = 0;
    			sum = first + second;
			
			for(;;)        		
			{
        			first = second;
        			second = sum;
        	      	
				int T1 = rand() % 100 + 10;
	        	      	wait(T1, sc_core::SC_NS);
				
				s0.notify();				

	        		sum = first + second;
				ints.push_back(sum);
				
				if(sum >= 2178309)
				{
					sum = 0;
					first = 0;
					second = 1;
				}
	    		}
        	}
  
  		void write(void)
        	{
			while(true)
			{
				wait(s0);
				wait(5, sc_core::SC_NS);
				int num = ints.front();
				ints.pop_front();
				
				std::cout << "Numbers sent: " << num <<" at time: " << sc_core::sc_time_stamp() << ".\n";
			}
        	}
};

int sc_main(int argc, char* argv [])
{
	Module01 uut("UUT");
	sc_start(0.1, sc_core::SC_SEC);
	
	return 0;
}