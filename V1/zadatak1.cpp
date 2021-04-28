//Celi brojevi ogranicene sirine, model racuna vrednost za sve brojeve < 64.
//Ograniciti minimalan br. bita za predstavljanje brojeva

#include <iostream>

int main()
{
	int n, t1 = 0, t2 = 1, nextT = 0;

	std::cout << "Enter base number, it must be < 64: " << "\n";
	std::cin >> n;
	
	while ( n > 63 )
	{
		std::cout << "Number cant be > 63, please try again: " << "\n";
		std::cin >> n;	
	}
	
	std::cout << "Fibonacci series: " << "\n";
	
	if (n == 0) 
	{
		nextT = 0;
	}
	else if (n == 1) 
	{
		nextT = 1;
	}
	else 
	{
		for (int i = 1; i <= n; ++i) 
		{
	       	// Prints the first two terms.
	       		if(i == 1) {
           			std::cout << t1 << ", ";
           			continue;
	       		}
	       		else if(i == 2) {
           			std::cout << t2 << ", ";
            			continue;
        		}
        		nextT = t1 + t2;
        		t1 = t2;
        		t2 = nextT;
        	
        	std::cout << nextT << ", ";
		
		}
	}
	
	std::cout << "\n";	

	return 0;
}