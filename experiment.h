#pragma once

class experiment{
    vector<book_request> vec;
    hotel my_hotel;
    my_time cur_time;
    int M;
    int K;
    int random_variable;
public:
	experiment();
    experiment(int M_, int K_, map <comfort, int> a);
    my_time get_cur_time() const;
    void complete_one_step();
    void complete_all_steps();
    int get_num_of_completed_requests() const;
    vector <book_request> get_vec_of_book_requests() const;
    int get_num_of_unfulfilled_requests() const;
    map <comfort, int> get_num_of_completed_requests_by_rooms();
    int get_cur_revenue() const;
    map <comfort, pair<int, int>> get_stats() const;
};
