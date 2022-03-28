#pragma once

class room{
    comfort comf;
    int cost;
    bool free;
public:
    room(comfort comf_, int cost_);
    int take_a_room();
    bool check_free() const;
    void set_free();
};

ostream& operator<< (ostream& o, const map <comfort, vector <pair <vector <pair <my_time, my_time> >, room> > > &rooms);
