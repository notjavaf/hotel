#include "globals.h"
#include "room.h"
#include "hotel.h"

void hotel::change_cur_revenue(int i, my_time time2, my_time time1, bool f){
if (f)
	cur_revenue += i * (time2 - time1) / hours_in_day;
else
	// 70/100 - скидка, это нельзя написать в виде константы,
	// так как в вычислениях участвуют только int,
	// а 70/100 в виде константы просто будет равно 0
	cur_revenue += i * (time2 - time1) / hours_in_day * 70 / 100;
}

void hotel::update_info(my_time time_){
        for (auto time_room: rooms){
            for (auto my_rooms: time_room.second){
                if (!cross_time_interval(my_rooms.get_timetable(), time_, time_))
                    my_rooms.set_free();
                else
                    my_rooms.take_a_room();
            }
        }
}

void hotel::book(comfort comf, my_time time1, my_time time2, type_of_req my_type){
        int k = -1;
        for (int i = 0; i < rooms[comf].size(); i++) {
            if (!cross_time_interval(rooms[comf][i].get_timetable(),
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
			change_cur_revenue(rooms[comf][k].take_a_room(), time2, time1, true);
		if (my_type == type_of_req::book)
            num_of_completed_requests_book++;
		else
			num_of_completed_requests_check_in++;
            num_of_completed_requests_by_rooms[comf]++;
            pair<my_time, my_time> t_time = {time1, time2};
            rooms[comf][k].add_time_interval(t_time);
        } else if (comf != comfort::one_seat){
            comf = get_prev_comfort(comf);
            for (int i = 0; i < rooms[comf].size(); i++) {
                if (!cross_time_interval(rooms[comf][i].get_timetable(),
                                         time1,
                                         time2)){
                    k = i;
                    break;
                }
            }
            if (k != -1){
                change_cur_revenue(rooms[comf][k].take_a_room(), time2, time1, false);
        	if (my_type == type_of_req::book)
        		num_of_completed_requests_book++;
			else
				num_of_completed_requests_check_in++;
            num_of_completed_requests_by_rooms[comf]++;
            pair<my_time, my_time> t_time = {time1, time2};
            rooms[comf][k].add_time_interval(t_time);
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
    for (int i = 0; i < num_of_types; i++){
        num_of_completed_requests_by_rooms[get_comf(i+1)] = 0;
    }
    for (auto g: a){
        for (int i = 0; i < g.second; i++){
            room b = room(g.first, g.first);
            rooms[g.first].push_back(b);
        }
    }
}

hotel::hotel(){
    cur_revenue = 0;
    num_of_completed_requests_book = 0;
	num_of_completed_requests_check_in = 0;
    num_of_unfulfilled_requests = 0;
    for (int i = 0; i < num_of_types; i++){
        num_of_completed_requests_by_rooms[get_comf(i+1)] = 0;
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
            if (cross_time_interval(my_rooms.get_timetable(), time_, time_))
                    a[time_room.first].first++;
    }
    return a;
}

