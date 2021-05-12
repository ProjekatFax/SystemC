#include <systemc>
#include <iostream>
#include <cstdlib>

#define DEACTIVATED 0
#define ACTIVATED 1
#define EXPLODED 2

int number_of_particles = 0; 
int nth_particle = 0;
int number_of_exploded = 0;
int helloka = 0;
sc_core::sc_event explode_event;


SC_MODULE(Particle){
    private:
        int state;
        int explosion_time;
    public:

        SC_CTOR(Particle){
            state = DEACTIVATED;
            if(number_of_particles == 999){
                state = ACTIVATED;
            }

            number_of_particles++;
            std::cout<< "number of particles" <<number_of_particles<<std::endl;
            SC_THREAD(activate)
        }

        void activate(){
            if(state == ACTIVATED){
                explode();
            }else if(state == DEACTIVATED){
                while(true){
                    wait(explode_event);
                    int activation_chance = rand()%100+1;
                    if(activation_chance == 1){
                        state = ACTIVATED;
                        explode();
                        break;
                    }
                }
            }   
        }

        void explode(){
            explosion_time = rand()%10+1;
            wait(explosion_time,sc_core::SC_NS);
            state = EXPLODED;
            number_of_exploded++;
            explode_event.notify();
            print_status();
        }

        void print_status(){
            std::cout<< "number of exploded particles: "<< number_of_exploded;
            std::cout<< " time: "<<sc_core::sc_time_stamp()<< std::endl;
        }
             
};

SC_MODULE(Many_particles)
{
  sc_core::sc_vector<Particle> m; 
  SC_CTOR(Many_particles)
    : m("particles", 1000) // constructor
  {}
}; 

int sc_main(int argc, char* argv[]){
    Many_particles uut("UUT");
    sc_core::sc_start();
    return 0;
}

