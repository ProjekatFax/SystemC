//modul sadrzi 2 procesa. 
//rand_fib stvara kruznu sekvencu prvih 64(uradjeno za prvih 32) fib brojeva u rand(10ns-100ns)intervalima
//write ispisuje br stvorenih brojeva svake sekunde
//Sim traje 20s, komunikacija medju procesa koristi red v vektor

#include <systemc>
#include <iostream>
#include <cstdlib>
#include <deque>

SC_MODULE(Module01)
{	
	protected:
		std::deque<int> ints;
	public:
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
        	      	
				int T1 = rand() % 10 + 1;
	        	      	wait(T1, sc_core::SC_NS);
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
			int cnt = 0;
			for(;;)
			{	

				cnt = 0;
				wait(0.01, sc_core::SC_SEC);
				int out;

				while(ints.size() != 0)
				{
					//cnt = 0;
					cnt++;
					int num = ints.front();
					ints.pop_front();
					//Check sent numbers
					//std::cout << "Sent number " << num <<" at time: " << sc_core::sc_time_stamp() << ".\n";
					out = cnt;
				}
				std::cout << "Numbers sent " << out <<" at time: " << sc_core::sc_time_stamp() << ".\n";
			}
        	}
};

int sc_main(int argc, char* argv [])
{
	Module01 uut("UUT");
	sc_start(0.2, sc_core::SC_SEC);
	
	return 0;
}