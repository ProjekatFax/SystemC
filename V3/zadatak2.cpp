#include <systemc>
#include <iostream>
#include <cstdlib>

#define DEACTIVATED 0
#define ACTIVATED 1
#define EXPLODED 2


SC_MODULE(Particle){
    private:
        int state;
        static int number_of_particles = 0;
        static int number_of_exploded_particles = 0;
        int explosion_time;

    public:
        sc_core::sc_event explode_event;

        SC_CTOR(Particle){
            SC_THREAD(activate)
        }

        void activate(){
            state = DEACTIVATED;
            if(number_of_particles == 0){
                state = ACTIVATED;
                explode();
            }
            while(true){
                wait(explode_event);
                int activation_chance = rand()%100+1;
                
                if(activation_chance == 1){
                    state = ACTIVATED;
                    explode();
                }
                
            }
        }

        void explode(){
            explosion_time = rand()%10+1;
            wait(explosion_time,sc_core::SC_NS);
            state = EXPLODED;
            number_of_exploded_particles++;
            explode_event.notify();
            print_status();
        }

        void print_status(){
            std::cout<< "number of exploded particles: "<< number_of_exploded_particles;
            std::cout<< " time: "<<sc_core::sc_time_stamp()<< endl;
        }
        
             
};

SC_MODULE(Many_particles)
{
  sc_vector<Particle> m; 
  SC_CTOR(Many_particles)
    : m("particles", 1000) // constructor
  {}
}; 

int sc_main(int argc, char* argv[]){
    Many_particles uut("UUT");
    sc_core::sc_start();

}

