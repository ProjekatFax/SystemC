#include <systemc>
#include <iostream>

using namespace sc_core;
typedef enum {Idle,Step1,Step2,Step3} State;


SC_MODULE(Proc){
    public:
        SC_HAS_PROCESS(Proc);
        Proc(sc_module_name);
        State state;
        int a_or_b;
    protected:
        sc_event clk,a,b;
        void clk_thread();
        void ab_thread();   
        void automat_method();


};

Proc::Proc(sc_module_name name) : sc_module(name){
    SC_THREAD(clk_thread);
    SC_THREAD(ab_thread);
    SC_METHOD(automat_method);
    sensitive<<a<<b<<clk;

    state = Idle;
}

void Proc::clk_thread(){
    while(1){
        wait(10,SC_NS);
        clk.notify();
    }
}

void Proc::ab_thread(){
    while(1){
        wait(15,SC_NS);
        a.notify();
        wait(15,SC_NS);
        b.notify();
    }
}

void Proc::automat_method(){
    switch(state){
    case Idle:
        std::cout<<"idle "<<std::endl;
        next_trigger(clk);
        state = Step1;
        break;
    case Step1:
        std::cout<<"step1 "<<std::endl;
        a_or_b = rand()%2;
        if(a_or_b == 0){
            next_trigger(a);
            state = Step2;
            break;
        }
        next_trigger(b);
        state = Step3;
        break;
    case Step2:
        std::cout<<"step2 "<<std::endl;
        next_trigger(clk);
        state = Idle;
        break;
    case Step3:
        std::cout<<"step3 "<<std::endl;
        next_trigger(clk);
        state = Idle;
        break;
    }
}

int sc_main(int argc,char* argv[]){
    Proc uut("UUT");
    sc_start(1000,SC_NS);

    return 0;
}
