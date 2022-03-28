#include "globals.h"
#include "room.h"
#include "hotel.h"
#include "book_request.h"
#include "experiment.h"

int experiment::get_num_of_completed_requests() const{
    return my_hotel.get_num_of_completed_requests();
}
    
int experiment::get_num_of_unfulfilled_requests() const{
    return my_hotel.get_num_of_unfulfilled_requests();
}
    
map <comfort, int> experiment::get_num_of_completed_requests_by_rooms(){
    return my_hotel.get_num_of_completed_requests_by_rooms();
}

int experiment::get_cur_revenue() const{
    return my_hotel.get_cur_revenue();
}

vector <book_request> experiment::get_vec_of_book_requests() const{
    return vec;
}

experiment::experiment(int M_, int K_, map <comfort, int> a):
    vec({}),
    my_hotel(a),
    M(M_),
    K(K_),
    cur_time(my_time(0, 0)),
    random_variable((K_ > 10 ? K_ / 5 : 2))
    {}

experiment::experiment():
    vec({}),
    cur_time(my_time(0, 0))
    {}

my_time experiment::get_cur_time() const{
    return cur_time;
}

void experiment::complete_one_step(){
    ++cur_time;
    vec.clear();
    my_hotel.update_info(cur_time);
    int rand_book_1 = rand() % random_variable;
    for (int i = 0; i < rand_book_1; i++){
        int rand_comf_1 = rand() % 5 + 1;
        int rand_days_1 = rand() % 3 + 1;
        book_request req(type_of_req::check_in,
                        get_comf(rand_comf_1), 
                         cur_time, 
                         cur_time + rand_days_1);
        vec.push_back(req);
        req.form(my_hotel);
    }
    int rand_book_2 = rand() % random_variable;
    for (int i = 0; i < rand_book_2; i++){
        int rand_comf_1 = rand() % 5 + 1;
        int rand_days_1 = rand() % 3 + 1;
        int rand_days_2 = rand() % 3 + 1;
        book_request req(type_of_req::book,
                         get_comf(rand_comf_1), 
                         cur_time + rand_days_1, 
                         cur_time + rand_days_1 + rand_days_2);
        vec.push_back(req);
        req.form(my_hotel);
    }
    my_hotel.update_info(cur_time);
    ///////////////////////
    //cout << cur_time.day << ":" << cur_time.hour << endl;
}
    
void experiment::complete_all_steps(){
    my_time start_time = cur_time;
    for (int i = 0; i < (M - start_time); i++)
        complete_one_step();
}

map <comfort, pair<int, int>> experiment::get_stats() const{
    return my_hotel.get_stats(cur_time);
}


