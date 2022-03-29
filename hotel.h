#pragma once

class hotel{
    int cur_revenue;
    int num_of_completed_requests_book;
	int num_of_completed_requests_check_in;
    int num_of_unfulfilled_requests;
    map <comfort, int> num_of_completed_requests_by_rooms;
    map <comfort, vector <pair <vector <pair <my_time, my_time> >, room> > > rooms;
public:
	hotel();
    hotel(map <comfort, int> a);
    void book(comfort, my_time, my_time, type_of_req);
    void update_info(my_time time_);
    int get_num_of_completed_requests_book() const;
	int get_num_of_completed_requests_check_in() const;
    int get_num_of_unfulfilled_requests() const;
    map <comfort, int> get_num_of_completed_requests_by_rooms() const;
    int get_cur_revenue() const;
    map <comfort, pair<int, int>> get_stats(my_time) const;
};
