#include "globals.h"
#include "room.h"

ostream& operator<< (ostream& o, const map <comfort, vector <pair <vector <pair <my_time, my_time> >, room> > > &rooms){
    for (const auto& g: rooms){
        for (const auto &gg: g.second){
            o << comfort_to_string(g.first) << "- "; 
            for (const auto &ggg: gg.first)
            o << ggg.first.day << ":"
              << ggg.first.hour << " to " 
              << ggg.second.day << ":" 
              << ggg.second.hour << " ";
            o << print_bool(gg.second.check_free()) << endl; 
        }
    }
    return o;
}

void room::set_free(){
        free = true;
}

room::room(comfort comf_, int cost_): comf(comf_),  
                                    cost(cost_),
                                    free(true){}

int room::take_a_room(){
        free = false;
        return cost;
}

bool room::check_free() const{
        return free;
}
