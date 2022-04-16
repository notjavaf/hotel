#pragma once

class room{
    comfort comf;
    int cost;
    bool free;
    vector <pair <my_time, my_time> > timetable;
public:
	vector <pair <my_time, my_time> > get_timetable();
    room(comfort comf_, int cost_);
    int take_a_room();
    bool check_free() const;
    void set_free();
	void add_time_interval(pair<my_time, my_time> t_time);
};

ostream& operator<< (ostream& o, const map <comfort, vector <pair <vector <pair <my_time, my_time> >, room> > > &rooms);
