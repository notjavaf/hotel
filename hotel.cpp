#include "globals.h"
#include "room.h"
#include "hotel.h"

void hotel::update_info(my_time time_){
        for (auto time_room: rooms){
            for (auto my_rooms: time_room.second){
                if (!cross_time_interval(my_rooms.first, time_, time_))
                    my_rooms.second.set_free();
                else
                    my_rooms.second.take_a_room();
            }
        }
}

void hotel::book(comfort comf, my_time time1, my_time time2, type_of_req my_type){
        int k = -1;
        for (int i = 0; i < rooms[comf].size(); i++) {
            if (!cross_time_interval(rooms[comf][i].first,
                                     time1,
                                     time2)){
                k = i;
                break;
            }
        }
        if (k != -1){
            /*cout << rooms;
            cout << "prinyatoe = " << comfort_to_string(comf)  << time1.day << ":" 
                                                                 << time1.hour<< " - " 
                                                                 << time2.day << ":" 
                                                                 << time1.hour<< endl;*/

            cur_revenue += rooms[comf][k].second.take_a_room() *
                (time2 - time1) / 24;
		if (my_type == type_of_req::book)
            num_of_completed_requests_book++;
		else
			num_of_completed_requests_check_in++;
            num_of_completed_requests_by_rooms[comf]++;
            pair<my_time, my_time> t_time = {time1, time2};
            rooms[comf][k].first.push_back(t_time);
        } else if (comf != comfort::one_seat){
            comf = get_prev_comfort(comf);
            for (int i = 0; i < rooms[comf].size(); i++) {
                if (!cross_time_interval(rooms[comf][i].first,
                                         time1,
                                         time2)){
                    k = i;
                    break;
                }
            }
            if (k != -1){
                cur_revenue += rooms[comf][k].second.take_a_room() *
                    (time2 - time1) / 24 * 70 / 100;
        	if (my_type == type_of_req::book)
        		num_of_completed_requests_book++;
			else
				num_of_completed_requests_check_in++;
            num_of_completed_requests_by_rooms[comf]++;
            pair<my_time, my_time> t_time = {time1, time2};
            rooms[comf][k].first.push_back(t_time);
            }
        }
        if (k == -1){
            /*cout << rooms;
            cout << "neprinyatoe = " << comfort_to_string(comf)  << time1.day << ":" 
                                                                 << time1.hour<< " - " 
                                                                 << time2.day << ":" 
                                                                 << time1.hour<< endl;*/
            num_of_unfulfilled_requests++;

        }
}

hotel::hotel(map <comfort, int> a){
    cur_revenue = 0;
    num_of_completed_requests_book = 0;
	num_of_completed_requests_check_in = 0;
    num_of_unfulfilled_requests = 0;
    for (int i = 1; i < 6; i++){
        num_of_completed_requests_by_rooms[get_comf(i)] = 0;
    }
    for (auto g: a){
        for (int i = 0; i < g.second; i++){
            vector <pair <my_time, my_time> > a;
            room b = room(g.first, g.first);
            pair<vector <pair <my_time, my_time> >, room> c = {a, b};
            rooms[g.first].push_back(c);
        }
    }
}

hotel::hotel(){
    cur_revenue = 0;
    num_of_completed_requests_book = 0;
	num_of_completed_requests_check_in = 0;
    num_of_unfulfilled_requests = 0;
    for (int i = 1; i < 6; i++){
        num_of_completed_requests_by_rooms[get_comf(i)] = 0;
    }
}

int hotel::get_num_of_completed_requests_book() const{
    return num_of_completed_requests_book;
}

int hotel::get_num_of_completed_requests_check_in() const{
    return num_of_completed_requests_check_in;
}
    
int hotel::get_num_of_unfulfilled_requests() const{
    return num_of_unfulfilled_requests;
}
    
map <comfort, int> hotel::get_num_of_completed_requests_by_rooms() const{
    return num_of_completed_requests_by_rooms;
}
int hotel::get_cur_revenue() const{
    return cur_revenue;
}

map <comfort, pair<int, int>> hotel::get_stats(my_time time_) const{
    map <comfort, pair<int, int>> a;
    for (auto time_room: rooms){
        a[time_room.first] = {0, rooms.at(time_room.first).size()};
        bool f = false;
        for (auto my_rooms: time_room.second)
            if (cross_time_interval(my_rooms.first, time_, time_))
                    a[time_room.first].first++;
    }
    return a;
}

