#include <systemc>
#include <iostream>
#include <list>
#include <string>
#include <sstream>

using namespace sc_core;
using namespace std;

int instance_count = -1;

SC_MODULE(Philosopher){
    public:
        SC_HAS_PROCESS(Philosopher);
        Philosopher(sc_module_name name, sc_mutex*,sc_mutex*);
    protected:
        sc_mutex* fork_left;
        sc_mutex* fork_right;
        int left_locked;
        int right_locked;

        void proc();

    
};

Philosopher::Philosopher(sc_module_name name,sc_mutex* fork_right, sc_mutex* fork_left){
    instance_count++;
    SC_THREAD(proc);
}

void Philosopher::proc(){
    while(1){
        wait(1,SC_SEC);
        left_locked = fork_left->trylock();
        right_locked = fork_right->trylock();
        if((left_locked == -1) && (right_locked == -1)){
            std::cout<<"philosopher"<<instance_count<<" eating"<<std::endl;
            wait(5,SC_SEC);
            std::cout<<"philosopher"<<instance_count<<" thinking"<<std::endl;
        }
        fork_left->unlock();
        fork_right->unlock();
    }
}

int sc_main(int argc, char* argv[]){
    
    sc_mutex fork_0;
    sc_mutex fork_1;
    sc_mutex fork_2;
    sc_mutex fork_3;
    sc_mutex fork_4;


    Philosopher* philosopher0 = new Philosopher("philosopher0",&fork_0,&fork_1);
    Philosopher* philosopher1 = new Philosopher("philosopher1",&fork_1,&fork_2);
    Philosopher* philosopher2 = new Philosopher("philosopher2",&fork_2,&fork_3);
    Philosopher* philosopher3 = new Philosopher("philosopher3",&fork_3,&fork_4);
    Philosopher* philosopher4 = new Philosopher("philosopher4",&fork_4,&fork_0);


    sc_start(20,SC_SEC);

    return 0;
}