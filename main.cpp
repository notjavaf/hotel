#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

//объявление классов

enum comfort {
		      lux = 500, 
			  semi_lux = 350, 
			  two_seat_sofa = 200, 
			  two_seat = 160, 
			  one_seat = 100
			 };

struct my_time {
    int hour;
    int day;
    my_time(int hour_, int day_);
};

class room{
    comfort comf;
    int cost;
    bool free;
public:
    room(comfort comf_, int cost_);
    int take_a_room();
    bool check_free();
    void set_free();
};

class hotel{
    int cur_revenue;
    int num_of_completed_requests;
    int num_of_unfulfilled_requests;
    map <comfort, int> num_of_completed_requests_by_rooms;
    map <comfort, vector <pair <pair <my_time, my_time>, room> > > rooms;
public:
    hotel(map <comfort, int> a);
    void book(comfort, my_time, my_time);
    void update_info(my_time time_);
    int get_num_of_completed_requests();
    int get_num_of_unfulfilled_requests();
    map <comfort, int> get_num_of_completed_requests_by_rooms();
    int get_cur_revenue();
};

class book_request {
    comfort comf;
    my_time time1;
    my_time time2;
public:
    book_request(comfort comf_, my_time time1_, my_time time2_);
    comfort get_comfort();
    my_time get_time1();
    my_time get_time2();
    void form(hotel&);
};

class experiment{
    hotel my_hotel;
    my_time cur_time;
    int M;
    int K;
    int random_variable;
public:
    experiment(int M_, int K_, map <comfort, int> a);
    my_time get_cur_time();
    void complete_one_step();
    void complete_all_steps();
    int get_num_of_completed_requests();
    int get_num_of_unfulfilled_requests();
    map <comfort, int> get_num_of_completed_requests_by_rooms();
    int get_cur_revenue();
};

//определение методов классов и функций
string comfort_to_string(comfort a){
    switch(a){
        case comfort::lux:
            return "lux";
            break;
        case comfort::semi_lux:
            return "semi_lux";
            break;
        case comfort::two_seat_sofa:
            return "two_seat_sofa";
            break;
        case comfort::two_seat:
            return "two_seat";
            break;
        default:
            return "one_seat";
            break;
    }
}

comfort get_comf(int i){
    switch (i)
    {
    case 1:
        return lux;
        break;
    case 2:
        return semi_lux;
        break;
    case 3:
        return two_seat_sofa;
        break;
    case 4:
        return two_seat;
        break;
    default:
        return one_seat;
        break;
    }
}

book_request::book_request(comfort comf_, my_time time1_, my_time time2_):
        comf(comf_),
        time1(time1_),
        time2(time2_){}

comfort book_request::get_comfort(){
        return comf;
}

my_time book_request::get_time1(){
        return time1;
}

my_time book_request::get_time2(){
        return time2;
}

void book_request::form(hotel& my_hotel){
    my_hotel.book(get_comfort(), get_time1(), get_time2());
}

my_time::my_time(int hour_, int day_): hour(hour_), day(day_) {}

bool operator< (my_time t1, my_time t2){
    if (t1.day < t2.day)
        return true;
    else if (t1.hour < t2.hour)
        return true;
    return false;
}

my_time operator++ (my_time t1){
    if (t1.hour > 17){
        t1.day++;
        t1.hour = (t1.hour + 6) % 24;
    } else {
        t1.hour += 6;
    }
    return t1;
}

bool operator== (my_time t1, my_time t2){
    if (t1.day == t2.day && t1.hour == t2.hour)
        return true;
    return false;
}

int operator- (my_time t1, my_time t2){
    return (t1.day - t2.day) * 24 + t1.hour - t2.hour; 
}

my_time operator+ (my_time t1, my_time t2){
    my_time res(t1.day + t2.day + (t1.hour + t2.hour) % 24, 
               (t1.hour + t2.hour) % 24);
    return res;
}

my_time operator+ (my_time t1, int h){
    my_time res(t1.day + h, t1.hour);
    return res;
}


comfort get_prev_comfort(comfort a){
    switch(a){
        case lux:
            return semi_lux;
            break;
        case semi_lux:
            return two_seat_sofa;
            break;
        case two_seat_sofa:
            return two_seat;
            break;
        default:
            return one_seat;
            break;
    }
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
bool room::check_free(){
        return free;
}

bool cross_time_interval(my_time st_t1, my_time f_t1, 
                         my_time st_t2, my_time f_t2){
    if (st_t1 < st_t2 && st_t2 < f_t1 || st_t1 < f_t2 && f_t2 < f_t1)
        return true;
    else return false; 
}


void hotel::update_info(my_time time_){
        for (auto time_room: rooms){
            for (auto my_rooms: time_room.second){
                if (my_rooms.first.second < time_ || 
                    time_ < my_rooms.first.first)
                    my_rooms.second.set_free();
                else
                    my_rooms.second.take_a_room();
            }
        }
}

void hotel::book(comfort comf, my_time time1, my_time time2){
        int k = -1;
        for (int i = 0; i < rooms[comf].size(); i++) {
            if (!cross_time_interval(rooms[comf][i].first.first,
                                     rooms[comf][i].first.second,
                                     time1,
                                     time2)){
                k = i;
                break;
            }
        }
        if (k != -1){
            cur_revenue += rooms[comf][k].second.take_a_room() *
                (time2 - time1) / 24;
            num_of_completed_requests++;
            num_of_completed_requests_by_rooms[comf]++;
            rooms[comf][k].first.first = time1;
            rooms[comf][k].first.second = time2;
        } else if (comf != comfort::one_seat){
            comf = get_prev_comfort(comf);
            for (int i = 0; i < rooms[comf].size(); i++) {
                if (!cross_time_interval(rooms[comf][i].first.first,
                                         rooms[comf][i].first.second,
                                         time1,
                                         time2)){
                    k = i;
                    break;
                }
            }
            if (k != -1){
                cur_revenue += rooms[comf][k].second.take_a_room() *
                    (time2 - time1) / 24 * 70 / 100;
                num_of_completed_requests++;
                num_of_completed_requests_by_rooms[comf]++;
                rooms[comf][k].first.first = time1;
                rooms[comf][k].first.second = time2;
            }
        }
        if (k == -1){
            num_of_unfulfilled_requests++;
        }
}

hotel::hotel(map <comfort, int> a){
    cur_revenue = 0;
    num_of_completed_requests = 0;
    num_of_unfulfilled_requests = 0;
    for (int i = 1; i < 6; i++){
        num_of_completed_requests_by_rooms[get_comf(i)] = 0;
    }
    for (auto g: a){
        rooms[g.first].push_back(pair<pair<my_time, my_time>, room>
                                (pair<my_time, my_time>
                                (my_time(-1, -1), my_time(-1, -1)),
                                 room(g.first, g.first)));
    }
}

int hotel::get_num_of_completed_requests(){
    return num_of_completed_requests;
}
    
int hotel::get_num_of_unfulfilled_requests(){
    return num_of_unfulfilled_requests;
}
    
map <comfort, int> hotel::get_num_of_completed_requests_by_rooms(){
    return num_of_completed_requests_by_rooms;
}
int hotel::get_cur_revenue(){
    return cur_revenue;
}

int experiment::get_num_of_completed_requests(){
    return my_hotel.get_num_of_completed_requests();
}
    
int experiment::get_num_of_unfulfilled_requests(){
    return my_hotel.get_num_of_unfulfilled_requests();
}
    
map <comfort, int> experiment::get_num_of_completed_requests_by_rooms(){
    return my_hotel.get_num_of_completed_requests_by_rooms();
}

int experiment::get_cur_revenue(){
    return my_hotel.get_cur_revenue();
}

experiment::experiment(int M_, int K_, map <comfort, int> a):
    my_hotel(a),
    M(M_),
    K(K_),
    cur_time(my_time(0, 0)),
    random_variable(K_ / 6)
    {}

my_time experiment::get_cur_time(){
    return cur_time;
}

void experiment::complete_one_step(){
    ++cur_time;
    my_hotel.update_info(cur_time);
    int rand_book_1 = rand() % random_variable;
    for (int i = 0; i < rand_book_1; i++){
        int rand_comf_1 = rand() % 5 + 1;
        int rand_days_1 = rand() % 3 + 1;
        book_request req(get_comf(rand_comf_1), 
                         cur_time, 
                         cur_time + rand_days_1);
        req.form(my_hotel);
    }
    for (int i = 0; i < rand_book_1; i++){
        int rand_comf_1 = rand() % 5 + 1;
        int rand_days_1 = rand() % 3 + 1;
        int rand_days_2 = rand() % 3 + 1;
        book_request req(get_comf(rand_comf_1), 
                         cur_time + rand_days_1, 
                         cur_time + rand_days_1 + rand_days_2);
        req.form(my_hotel);
    }
    my_hotel.update_info(cur_time);
}
    
void experiment::complete_all_steps(){
    my_time start_time = cur_time;
    my_time end_time = my_time(0, M);
    for (my_time cur_time = start_time;
        cur_time < end_time;)
        complete_one_step();
}

ostream& operator<< (ostream& o, const map<comfort, int> &a){
    for (const auto& g: a){
        cout << comfort_to_string(g.first) << ": " << g.second << endl; 
    }
}

//дополнительные классы для sfml 

int main()
{
    srand(time(0));
    map <comfort, int> a = {{comfort::lux, 5},
                            {comfort::semi_lux, 5},
                            {comfort::two_seat_sofa, 5},
                            {comfort::two_seat, 5},
                            {comfort::one_seat, 5}};
    int M = 15, K = 25;
    experiment exp(M, K, a);
    for (int i = 0; i < M; i++){
        exp.complete_one_step();
    }
    cout << exp.get_num_of_completed_requests() << " " 
         << exp.get_num_of_unfulfilled_requests() << endl;
    cout << exp.get_num_of_completed_requests_by_rooms();
    cout << "revenue = " << exp.get_cur_revenue() << endl;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Hotel");
    sf::Texture TextureExitButton, TextureOneStepButton, TextureAllStepsButton;
    TextureExitButton.loadFromFile("exit.png");
    TextureOneStepButton.loadFromFile("one_step.png");
    TextureAllStepsButton.loadFromFile("n_steps.png");
    sf::Sprite ExitButton(TextureExitButton), 
               OneStepButton(TextureOneStepButton), 
               AllStepsButton(TextureAllStepsButton);
    ExitButton.setPosition(10, 10);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }   
        window.clear(sf::Color(220, 220, 220, 255));
        window.display();
    }
	
 
    return 0;
}
