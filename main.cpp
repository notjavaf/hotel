#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <random>
#include <locale>
#include <SFML/System/String.hpp>
#include <SFML/System/Utf.hpp>

using namespace std;

//объявление классов

enum comfort {
		      lux = 500, 
			  semi_lux = 350, 
			  two_seat_sofa = 200, 
			  two_seat = 160, 
			  one_seat = 100
			 };
    
enum type_of_req {
            book,
            check_in
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
    bool check_free() const;
    void set_free();
};

class hotel{
    int cur_revenue;
    int num_of_completed_requests;
    int num_of_unfulfilled_requests;
    map <comfort, int> num_of_completed_requests_by_rooms;
    map <comfort, vector <pair <vector <pair <my_time, my_time> >, room> > > rooms;
public:
	hotel();
    hotel(map <comfort, int> a);
    void book(comfort, my_time, my_time);
    void update_info(my_time time_);
    int get_num_of_completed_requests() const;
    int get_num_of_unfulfilled_requests() const;
    map <comfort, int> get_num_of_completed_requests_by_rooms() const;
    int get_cur_revenue() const;
    map <comfort, pair<int, int>> get_stats(my_time) const;
};

class book_request {
    type_of_req type_;
    comfort comf;
    my_time time1;
    my_time time2;
public:
    book_request(type_of_req _type, comfort comf_, my_time time1_, my_time time2_);
    comfort get_comfort() const;
    my_time get_time1() const;
    my_time get_time2() const;
    type_of_req get_type() const;
    void form(hotel&);
};

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

string comfort_to_string1(comfort a){
    switch(a){
        case comfort::lux:
            return "люкс";
            break;
        case comfort::semi_lux:
            return "полулюкс";
            break;
        case comfort::two_seat_sofa:
            return "2-мест. с див.";
            break;
        case comfort::two_seat:
            return "прост. 2-мест.";
            break;
        default:
            return "1-местный";
            break;
    }
}

string print_bool(bool c){
    if (c)
        return "true";
    else
        return "false";
}

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

book_request::book_request(type_of_req _type, comfort comf_, my_time time1_, my_time time2_):
        type_(_type),
        comf(comf_),
        time1(time1_),
        time2(time2_){}

comfort book_request::get_comfort() const{
        return comf;
}

my_time book_request::get_time1() const{
        return time1;
}

my_time book_request::get_time2() const{
        return time2;
}

type_of_req book_request::get_type() const{
    return type_;
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

my_time& operator++ (my_time& t1){
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

int operator- (int i, my_time t2){
    return (i - t2.day) * 4 - t2.hour/6; 
}

my_time operator+ (my_time t1, my_time t2){
    my_time res((t1.hour + t2.hour) % 24, t1.day + t2.day + (t1.hour + t2.hour) % 24);
    return res;
}

my_time operator+ (my_time t1, int h){
    my_time res(t1.hour, t1.day + h);
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

bool room::check_free() const{
        return free;
}

bool cross_time_interval(const vector <pair <my_time, my_time> >& a, 
                         my_time st_t2, my_time f_t2){
    for (const auto& g: a)
        if (g.first < st_t2 && st_t2 < g.second || g.first < f_t2 && f_t2 < g.second)
            return true;
    return false; 
}


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

void hotel::book(comfort comf, my_time time1, my_time time2){
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
            num_of_completed_requests++;
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
                num_of_completed_requests++;
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
    num_of_completed_requests = 0;
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
    num_of_completed_requests = 0;
    num_of_unfulfilled_requests = 0;
    for (int i = 1; i < 6; i++){
        num_of_completed_requests_by_rooms[get_comf(i)] = 0;
    }
}

int hotel::get_num_of_completed_requests() const{
    return num_of_completed_requests;
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
    random_variable(K_ / 6)
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

ostream& operator<< (ostream& o, const map<comfort, int> &a){
    for (const auto& g: a){
        o << comfort_to_string(g.first) << ": " << g.second << endl; 
    }
    return o;
}

ostream& operator<< (ostream& o, const map<comfort, pair <int, int> > &a){
    for (const auto& g: a){
        o << comfort_to_string(g.first) << ": " << g.second.first << " из " <<  g.second.second << endl; 
    }
    return o;
}

void print_cur_res(experiment& exp){
    cout << exp.get_num_of_completed_requests() << " " 
         << exp.get_num_of_unfulfilled_requests() << endl;
    cout << exp.get_num_of_completed_requests_by_rooms();
    cout << "revenue = " << exp.get_cur_revenue() << endl;
    cout << exp.get_stats();
}

void set_param_to_text(sf::Text& text, sf::Font& font, int x, int y, int size, sf::Color col){
    text.setFont(font);
    text.setPosition(x, y);
    text.setCharacterSize(size);
    text.setColor(col);
}

string time_to_string(my_time t){ 
    return to_string(t.day + 1) + " д., " + to_string(t.hour) + " ч.";
}

string type_of_req_to_string(type_of_req a){
    if (a == type_of_req::book)
        return "бронирование";
    else   
        return "заселение";
}


int main()
{
    srand(time(0));
    map <comfort, int> a = {{comfort::lux, 5},
                            {comfort::semi_lux, 5},
                            {comfort::two_seat_sofa, 5},
                            {comfort::two_seat, 5},
                            {comfort::one_seat, 5}};
    int M = 10, K = 25;
    bool f = false, start_pr = true;
    experiment exp(M, K, a);
    setlocale(LC_CTYPE, "rus");
    sf::RenderWindow window(sf::VideoMode(800, 600), "Hotel");
    sf::Texture TextureExitButton, TextureOneStepButton, TextureAllStepsButton;
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text1, text2, text3, text4, text5, text6,
	text7, text8, text9, text10, text11, text12, text13,
	text14, text15, text16, text17, text18, text19, text20,
	text21, text22, text23, text24, text25, text26, text27,
	text28, text29, text30, text31, text32, text33, text34,
	text35, text36, text37, text38, text39, text40, text41,
	text42, text43, text44, text45, text46, text47, text48,
    text49, text50, text51, text52, text53, text54, text55;	
    string s  = "Текущие дата и время"; 
	string s1 = "Всего выполнено заявок";
	string s2 = "Невыполнено заявок";
	string s3 = "Выполнено заявок";
	string s4 = "по номерам";
	string s5 = "Всего поступило заявок";
	string s6 = "Текущая выручка";
    text1.setString(sf::String::fromUtf8(s.begin(), s.end()));
	text3.setString(sf::String::fromUtf8(s1.begin(), s1.end()));
	text4.setString(sf::String::fromUtf8(s2.begin(), s2.end()));
	text5.setString(sf::String::fromUtf8(s3.begin(), s3.end()));
	text6.setString(sf::String::fromUtf8(s4.begin(), s4.end()));
	text7.setString(sf::String::fromUtf8(s5.begin(), s5.end()));
	text16.setString(sf::String::fromUtf8(s6.begin(), s6.end()));
    set_param_to_text(text1, font, 600, 20, 16, sf::Color::Black);
	set_param_to_text(text7, font, 595, 90, 16, sf::Color::Black);
	set_param_to_text(text3, font, 595, 160, 16, sf::Color::Black);
	set_param_to_text(text4, font, 610, 230, 16, sf::Color::Black);
	set_param_to_text(text5, font, 620, 300, 16, sf::Color::Black);
	set_param_to_text(text6, font, 650, 322, 16, sf::Color::Black);
	set_param_to_text(text16, font, 620, 465, 16, sf::Color::Black);
	sf::Vertex line[] =
	{
    	sf::Vertex(sf::Vector2f(200, 20)),
    	sf::Vertex(sf::Vector2f(200, 300))
	};
	line[0].color = sf::Color::Black;
    line[1].color = sf::Color::Black;
	sf::Vertex line1[] =
    {
    	sf::Vertex(sf::Vector2f(350, 20)),
    	sf::Vertex(sf::Vector2f(350, 300))
	};
	line1[0].color = sf::Color::Black;
    line1[1].color = sf::Color::Black;
	sf::Vertex line2[] =
	{
    	sf::Vertex(sf::Vector2f(50, 50)),
    	sf::Vertex(sf::Vector2f(500, 50))
	};
	line2[0].color = sf::Color::Black;
    line2[1].color = sf::Color::Black;
	string s11 = "люкс";
	string s12 = "полулюкс";
	string s13 = "двухместные с";
	string s10 = "раскладным диваном";
	string s14 = "простые двухместные";
	string s15 = "одноместные";
	text18.setString(sf::String::fromUtf8(s11.begin(), s11.end()));
	text19.setString(sf::String::fromUtf8(s12.begin(), s12.end()));
	text20.setString(sf::String::fromUtf8(s13.begin(), s13.end()));
	text21.setString(sf::String::fromUtf8(s14.begin(), s14.end()));
	text22.setString(sf::String::fromUtf8(s15.begin(), s15.end()));
	text23.setString(sf::String::fromUtf8(s10.begin(), s10.end()));
	set_param_to_text(text18, font, 90, 65, 16, sf::Color::Black);
	set_param_to_text(text19, font, 76, 112, 16, sf::Color::Black);
	set_param_to_text(text20, font, 55, 159, 16, sf::Color::Black);
	set_param_to_text(text21, font, 30, 206, 16, sf::Color::Black);
	set_param_to_text(text22, font, 60, 253, 16, sf::Color::Black);
	set_param_to_text(text23, font, 37, 173, 16, sf::Color::Black);
	string s16 = "комфорт";
	string s17 = "общее число";
	string s18 = "занято в";
	string s19 = "номеров";
	string s20 = "данный момент";
	text24.setString(sf::String::fromUtf8(s16.begin(), s16.end()));
	text25.setString(sf::String::fromUtf8(s17.begin(), s17.end()));
	text26.setString(sf::String::fromUtf8(s18.begin(), s18.end()));
	text27.setString(sf::String::fromUtf8(s19.begin(), s19.end()));
	text28.setString(sf::String::fromUtf8(s20.begin(), s20.end()));
	set_param_to_text(text24, font, 76, 20, 16, sf::Color::Black);
	set_param_to_text(text25, font, 227, 10, 16, sf::Color::Black);
	set_param_to_text(text26, font, 390, 10, 16, sf::Color::Black);
	set_param_to_text(text27, font, 242, 30, 16, sf::Color::Black);
	set_param_to_text(text28, font, 370, 30, 16, sf::Color::Black);

    sf::Vertex line3[] =
	{
    	sf::Vertex(sf::Vector2f(30, 380)),
    	sf::Vertex(sf::Vector2f(520, 380))
	};
	line3[0].color = sf::Color::Black;
    line3[1].color = sf::Color::Black;
	sf::Vertex line4[] =
	{
    	sf::Vertex(sf::Vector2f(390, 350)),
    	sf::Vertex(sf::Vector2f(390, 550))
	};
	line4[0].color = sf::Color::Black;
    line4[1].color = sf::Color::Black;
	sf::Vertex line5[] =
	{
    	sf::Vertex(sf::Vector2f(270, 350)),
    	sf::Vertex(sf::Vector2f(270, 550))
	};
	line5[0].color = sf::Color::Black;
    line5[1].color = sf::Color::Black;
    sf::Vertex line6[] =
	{
    	sf::Vertex(sf::Vector2f(150, 350)),
    	sf::Vertex(sf::Vector2f(150, 550))
	};
	line6[0].color = sf::Color::Black;
    line6[1].color = sf::Color::Black;
    string s21 = "тип заявки";
	string s22 = "время заселен.";
	string s23 = "время выселения";
    string s24 = "комфорт";
    text39.setString(sf::String::fromUtf8(s21.begin(), s21.end()));
	text40.setString(sf::String::fromUtf8(s22.begin(), s22.end()));
	text41.setString(sf::String::fromUtf8(s23.begin(), s23.end()));
    text42.setString(sf::String::fromUtf8(s24.begin(), s24.end()));
    set_param_to_text(text39, font, 50, 355, 16, sf::Color::Black);
	set_param_to_text(text40, font, 275, 355, 16, sf::Color::Black);
	set_param_to_text(text41, font, 395, 355, 16, sf::Color::Black);
    set_param_to_text(text42, font, 170, 355, 16, sf::Color::Black);

	sf::RectangleShape f1(sf::Vector2f(100, 20));
	sf::RectangleShape f2(sf::Vector2f(100, 20));
	sf::RectangleShape f3(sf::Vector2f(100, 20));
	sf::RectangleShape f4(sf::Vector2f(100, 20));
	sf::RectangleShape f5(sf::Vector2f(100, 20));
	sf::RectangleShape f6(sf::Vector2f(100, 20));
	f1.setPosition(250, 150);
	f2.setPosition(250, 200);
	f3.setPosition(250, 250);
	f4.setPosition(250, 300);
	f5.setPosition(250, 350);
	f6.setPosition(250, 400);
    set_param_to_text(text43, font, 252, 152, 16, sf::Color::Black);
	set_param_to_text(text44, font, 252, 202, 16, sf::Color::Black);
	set_param_to_text(text45, font, 252, 252, 16, sf::Color::Black);
    set_param_to_text(text46, font, 252, 302, 16, sf::Color::Black);
    set_param_to_text(text47, font, 252, 352, 16, sf::Color::Black);
	set_param_to_text(text48, font, 252, 402, 16, sf::Color::Black);
    string s43, s44, s45, s46, s47, s48;
	int inp = 0;

	string s49 = "люкс";
	string s50 = "полулюкс";
	string s51 = "двухместные с";
	string s52 = "раскладным диваном";
	string s53 = "простые двухместные";
	string s54 = "одноместные";
	string s55 = "число дней моделир.";
	text49.setString(sf::String::fromUtf8(s49.begin(), s49.end()));
	text50.setString(sf::String::fromUtf8(s50.begin(), s50.end()));
	text51.setString(sf::String::fromUtf8(s51.begin(), s51.end()));
	text52.setString(sf::String::fromUtf8(s52.begin(), s52.end()));
	text53.setString(sf::String::fromUtf8(s53.begin(), s53.end()));
	text54.setString(sf::String::fromUtf8(s54.begin(), s54.end()));
	text55.setString(sf::String::fromUtf8(s55.begin(), s55.end()));
	set_param_to_text(text49, font, 201, 202, 16, sf::Color::Black);
	set_param_to_text(text50, font, 167, 252, 16, sf::Color::Black);
	set_param_to_text(text51, font, 127, 292, 16, sf::Color::Black);
	set_param_to_text(text52, font, 83, 312, 16, sf::Color::Black);
	set_param_to_text(text53, font, 75, 352, 16, sf::Color::Black);
	set_param_to_text(text54, font, 140, 402, 16, sf::Color::Black);
	set_param_to_text(text55, font, 83, 152, 16, sf::Color::Black);
	string s56 = "Вводите";
	text56.setString(sf::String::fromUtf8(s56.begin(), s56.end()));
	set_param_to_text(text56, font, 83, 152, 16, sf::Color::Black);

    TextureExitButton.loadFromFile("exit.png");
    TextureOneStepButton.loadFromFile("one_step.png");
    TextureAllStepsButton.loadFromFile("n_steps.png");
    sf::Sprite ExitButton(TextureExitButton), 
    OneStepButton(TextureOneStepButton), 
    AllStepsButton(TextureAllStepsButton);
    ExitButton.setPosition(130, 560);
    OneStepButton.setPosition(330, 560);
    AllStepsButton.setPosition(530, 560);   

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left){
                    
                    if (sf::IntRect(130, 560, 100, 32).contains(sf::Mouse::getPosition(window))){ 
                        window.close(); 
                    }
                    if (f){
                        if (sf::IntRect(330, 560, 100, 32).contains(sf::Mouse::getPosition(window))){ 
                            exp.complete_one_step();  
                            //print_cur_res(exp); 
                            my_time cur_time = exp.get_cur_time();
                            if (cur_time.day >= M)
                                f = false;
                        }
                        if (sf::IntRect(530, 560, 180, 32).contains(sf::Mouse::getPosition(window))){ 
                            exp.complete_all_steps();  
                            //print_cur_res(exp); 
                            f = false;
                        }
                    }
                }
            } else if (event.type == sf::Event::KeyReleased){
                if (event.key.code == sf::Keyboard::Return){
                	inp++;
                }
				if (inp == 6){
					start_pr = false;
					f = true;
					M = stoi(s43);
					a = {{comfort::lux, stoi(s44)},
                         {comfort::semi_lux, stoi(s45)},
                         {comfort::two_seat_sofa, stoi(s46)},
                         {comfort::two_seat, stoi(s47)},
                         {comfort::one_seat, stoi(s48)}};
					K = stoi(s44) + 
						stoi(s45) +
						stoi(s46) +
						stoi(s47) +
						stoi(s48);
					exp = experiment(M, K, a);
				}
                else {
                    sf::Keyboard::Key keycode = event.key.code;
					if (keycode == sf::Keyboard::BackSpace){
						switch (inp){
							case 0:
								if (s43.size() > 0)
									s43 = s43.substr(0, s43.size() - 1);
								break;
							case 1:
								if (s44.size() > 0)
									s44 = s44.substr(0, s44.size() - 1);
								break;
							case 2:
								if (s45.size() > 0)
									s45 = s45.substr(0, s45.size() - 1);
								break;
							case 3:
								if (s46.size() > 0)
									s46 = s46.substr(0, s46.size() - 1);
								break;
							case 4:
								if (s47.size() > 0)
									s47 = s47.substr(0, s47.size() - 1);
								break;
							default:
								if (s48.size() > 0)
									s48 = s48.substr(0, s48.size() - 1);
								break;
						}
					}
                    if (keycode >= sf::Keyboard::Num0 && keycode <= sf::Keyboard::Num9 && s43.size() < 10 && inp == 0){
                        char chr = static_cast<char>(keycode - sf::Keyboard::Num0 + '0');
                        s43.push_back(chr);
                    }
                    text43.setString(sf::String::fromUtf8(s43.begin(), s43.end()));
					if (keycode >= sf::Keyboard::Num0 && keycode <= sf::Keyboard::Num9 && s44.size() < 10 && inp == 1){
                        char chr = static_cast<char>(keycode - sf::Keyboard::Num0 + '0');
                        s44.push_back(chr);
                    }
                    text44.setString(sf::String::fromUtf8(s44.begin(), s44.end()));
					if (keycode >= sf::Keyboard::Num0 && keycode <= sf::Keyboard::Num9 && s45.size() < 10 && inp == 2){
                        char chr = static_cast<char>(keycode - sf::Keyboard::Num0 + '0');
                        s45.push_back(chr);
                    }
                    text45.setString(sf::String::fromUtf8(s45.begin(), s45.end()));
					if (keycode >= sf::Keyboard::Num0 && keycode <= sf::Keyboard::Num9 && s46.size() < 10 && inp == 3){
                        char chr = static_cast<char>(keycode - sf::Keyboard::Num0 + '0');
                        s46.push_back(chr);
                    }
                    text46.setString(sf::String::fromUtf8(s46.begin(), s46.end()));
					if (keycode >= sf::Keyboard::Num0 && keycode <= sf::Keyboard::Num9 && s47.size() < 10 && inp == 4){
                        char chr = static_cast<char>(keycode - sf::Keyboard::Num0 + '0');
                        s47.push_back(chr);
                    }
                    text47.setString(sf::String::fromUtf8(s47.begin(), s47.end()));
					if (keycode >= sf::Keyboard::Num0 && keycode <= sf::Keyboard::Num9 && s48.size() < 10 && inp == 5){
                        char chr = static_cast<char>(keycode - sf::Keyboard::Num0 + '0');
                        s48.push_back(chr);
                    }
                    text48.setString(sf::String::fromUtf8(s48.begin(), s48.end()));
                }
            } 
        }   
		string s_cur_time = time_to_string(exp.get_cur_time());
		text2.setString(sf::String::fromUtf8(s_cur_time.begin(), s_cur_time.end()));
		set_param_to_text(text2, font, 650, 45, 16, sf::Color::Black);
		string all_req = to_string(exp.get_num_of_completed_requests()+exp.get_num_of_unfulfilled_requests());
		text8.setString(sf::String::fromUtf8(all_req.begin(), all_req.end()));
		set_param_to_text(text8, font, 675, 115, 16, sf::Color::Black);
		string all_req1 = to_string(exp.get_num_of_completed_requests());
		text9.setString(sf::String::fromUtf8(all_req1.begin(), all_req1.end()));
		set_param_to_text(text9, font, 675, 185, 16, sf::Color::Black);
		string all_req2 = to_string(exp.get_num_of_unfulfilled_requests());
		text10.setString(sf::String::fromUtf8(all_req2.begin(), all_req2.end()));
		set_param_to_text(text10, font, 675, 255, 16, sf::Color::Black);

		map<comfort, int> star_c_r = exp.get_num_of_completed_requests_by_rooms();
		string r1 = "люкс: " + to_string(star_c_r[comfort::lux]);
		text11.setString(sf::String::fromUtf8(r1.begin(), r1.end()));
		set_param_to_text(text11, font, 670, 350, 16, sf::Color::Black);
		string r2 = "полулюкс: " + to_string(star_c_r[comfort::semi_lux]);
		text12.setString(sf::String::fromUtf8(r2.begin(), r2.end()));
		set_param_to_text(text12, font, 636, 370, 16, sf::Color::Black);
		string r3 = "2-мест. с див.: " + to_string(star_c_r[comfort::two_seat_sofa]);
		text13.setString(sf::String::fromUtf8(r3.begin(), r3.end()));
		set_param_to_text(text13, font, 604, 390, 16, sf::Color::Black);
		string r4 = "прост. 2-мест.: " + to_string(star_c_r[comfort::two_seat]);
		text14.setString(sf::String::fromUtf8(r4.begin(), r4.end()));
		set_param_to_text(text14, font, 600, 410, 16, sf::Color::Black);
		string r5 = "1-мест: " + to_string(star_c_r[comfort::one_seat]);
		text15.setString(sf::String::fromUtf8(r5.begin(), r5.end()));
		set_param_to_text(text15, font, 655, 430, 16, sf::Color::Black);
		string s_cur_rev = to_string(exp.get_cur_revenue());
		text17.setString(sf::String::fromUtf8(s_cur_rev.begin(), s_cur_rev.end()));
		set_param_to_text(text17, font, 660, 490, 16, sf::Color::Black);

		map <comfort, pair<int, int> > stat_rooms = exp.get_stats();
		string r11 = to_string(stat_rooms[comfort::lux].second);
		text29.setString(sf::String::fromUtf8(r11.begin(), r11.end()));
		set_param_to_text(text29, font, 265, 65, 16, sf::Color::Black);
		string r12 = to_string(stat_rooms[comfort::semi_lux].second);
		text30.setString(sf::String::fromUtf8(r12.begin(), r12.end()));
		set_param_to_text(text30, font, 265, 112, 16, sf::Color::Black);
		string r13 = to_string(stat_rooms[comfort::two_seat_sofa].second);
		text31.setString(sf::String::fromUtf8(r13.begin(), r13.end()));
		set_param_to_text(text31, font, 265, 159, 16, sf::Color::Black);
		string r14 = to_string(stat_rooms[comfort::two_seat].second);
		text32.setString(sf::String::fromUtf8(r14.begin(), r14.end()));
		set_param_to_text(text32, font, 265, 206, 16, sf::Color::Black);
		string r15 = to_string(stat_rooms[comfort::one_seat].second);
		text33.setString(sf::String::fromUtf8(r15.begin(), r15.end()));
		set_param_to_text(text33, font, 265, 253, 16, sf::Color::Black);
		string r16 = to_string(stat_rooms[comfort::lux].first);
		text34.setString(sf::String::fromUtf8(r16.begin(), r16.end()));
		set_param_to_text(text34, font, 415, 65, 16, sf::Color::Black);
		string r17 = to_string(stat_rooms[comfort::semi_lux].first);
		text35.setString(sf::String::fromUtf8(r17.begin(), r17.end()));
		set_param_to_text(text35, font, 415, 112, 16, sf::Color::Black);
		string r18 = to_string(stat_rooms[comfort::two_seat_sofa].first);
		text36.setString(sf::String::fromUtf8(r18.begin(), r18.end()));
		set_param_to_text(text36, font, 415, 159, 16, sf::Color::Black);
		string r19 = to_string(stat_rooms[comfort::two_seat].first);
		text37.setString(sf::String::fromUtf8(r19.begin(), r19.end()));
		set_param_to_text(text37, font, 415, 206, 16, sf::Color::Black);
		string r20 = to_string(stat_rooms[comfort::one_seat].first);
		text38.setString(sf::String::fromUtf8(r20.begin(), r20.end()));
		set_param_to_text(text38, font, 415, 253, 16, sf::Color::Black);

        vector<book_request> vec_b = exp.get_vec_of_book_requests();
        vector<vector <sf::Text> > vec_t;
        for (auto g: vec_b){
            vector <sf::Text> b;
            type_of_req a1 = g.get_type();
            comfort a2 = g.get_comfort();
            my_time a3 = g.get_time1();
            my_time a4 = g.get_time2();
            sf::Text text_1, text_2, text_3, text_4;
            string r_1 = type_of_req_to_string(a1);
            string r_2 = comfort_to_string1(a2);
            string r_3 = time_to_string(a3);
            string r_4 = time_to_string(a4);
            text_1.setString(sf::String::fromUtf8(r_1.begin(), r_1.end()));
            text_2.setString(sf::String::fromUtf8(r_2.begin(), r_2.end()));
            text_3.setString(sf::String::fromUtf8(r_3.begin(), r_3.end()));
            text_4.setString(sf::String::fromUtf8(r_4.begin(), r_4.end()));
            b.push_back(text_1);
            b.push_back(text_2);
            b.push_back(text_3);
            b.push_back(text_4);
            vec_t.push_back(b);
        }
        window.clear(sf::Color(220, 220, 220, 255));
		window.setFramerateLimit(60);
        int i = 380;
		window.draw(ExitButton);
        if (start_pr){
			window.draw(f1);
			window.draw(f2);
			window.draw(f3);
			window.draw(f4);
			window.draw(f5);
			window.draw(f6);
            window.draw(text43);
			window.draw(text44);
			window.draw(text45);
            window.draw(text46);
			window.draw(text47);
			window.draw(text48);
			window.draw(text49);
			window.draw(text50);
			window.draw(text51);
			window.draw(text52);
			window.draw(text53);
        	window.draw(text54);
			window.draw(text55);
			window.draw(text56);
            //start_pr = false;
        }
        else {
        if (f){
            window.draw(OneStepButton);
            window.draw(AllStepsButton);
        }
        for (auto g: vec_t){
            set_param_to_text(g[0], font, 40, i, 16, sf::Color::Black);
            set_param_to_text(g[1], font, 160, i, 16, sf::Color::Black);
            set_param_to_text(g[2], font, 290, i, 16, sf::Color::Black);
            set_param_to_text(g[3], font, 410, i, 16, sf::Color::Black);
            i += 20;
            window.draw(g[0]);
		    window.draw(g[1]);
		    window.draw(g[2]);
		    window.draw(g[3]);
        }
        window.draw(text1);
		window.draw(text2);
		window.draw(text3);
		window.draw(text4);
		window.draw(text5);
		window.draw(text6);
		window.draw(text7);
		window.draw(text8);
		window.draw(text9);
		window.draw(text10);
		window.draw(text11);
		window.draw(text12);
		window.draw(text13);
		window.draw(text14);
		window.draw(text15);
		window.draw(text16);
		window.draw(text17);
		window.draw(text18);
		window.draw(text19);
		window.draw(text20);
		window.draw(text21);
		window.draw(text22);
		window.draw(text23);
		window.draw(text24);
		window.draw(text25);
		window.draw(text26);
		window.draw(text27);
		window.draw(text28);
		window.draw(text29);
		window.draw(text30);
		window.draw(text31);
		window.draw(text32);
		window.draw(text33);
		window.draw(text34);
		window.draw(text35);
		window.draw(text36);
		window.draw(text37);
		window.draw(text38);
		window.draw(text39);
		window.draw(text40);
		window.draw(text41);
        window.draw(text42);
		window.draw(line, 2, sf::Lines);
		window.draw(line1, 2, sf::Lines);
		window.draw(line2, 2, sf::Lines);
		window.draw(line3, 2, sf::Lines);
		window.draw(line4, 2, sf::Lines);
		window.draw(line5, 2, sf::Lines);
        window.draw(line6, 2, sf::Lines);
        }
        window.display();
    }
	
 
    return 0;
}
