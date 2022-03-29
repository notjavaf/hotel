#include "globals.h"

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

my_time::my_time(int hour_, int day_): hour(hour_), day(day_) {}

bool operator< (my_time t1, my_time t2){
    if (t1.day < t2.day)
        return true;
    else if (t1.hour < t2.hour)
        return true;
    return false;
}

bool operator<= (my_time t1, my_time t2){
    if (t1.day <= t2.day)
    	if (t1.hour <= t2.hour)
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

bool cross_time_interval(const vector <pair <my_time, my_time> >& a, 
                         my_time st_t2, my_time f_t2){
    for (const auto& g: a)
        if (g.first <= st_t2 && st_t2 < g.second || g.first <= f_t2 && f_t2 < g.second)
            return true;
    return false; 
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

void set_param_to_text(sf::Text& text, sf::Font& font, int x, int y, int size, sf::Color col){
    text.setFont(font);
    text.setPosition(x, y);
    text.setCharacterSize(size);
    text.setColor(col);
}

void set_param_to_text1(sf::Text& text, string s, sf::Font& font, int x, int y, int size, sf::Color col){
	text.setString(sf::String::fromUtf8(s.begin(), s.end()));
    text.setFont(font);
    text.setPosition(x, y);
    text.setCharacterSize(size);
    text.setColor(col);
}

void set_param_to_line(sf::Vertex line[2], int x1, int y1, int x2, int y2){
    line[0] = sf::Vertex(sf::Vector2f(x1, y1));
    line[1] = sf::Vertex(sf::Vector2f(x2, y2));
	line[0].color = sf::Color::Black;
    line[1].color = sf::Color::Black;
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

void print_objects (sf::RenderWindow& w, const vector<sf::Text> &a){
	for (const auto& g: a){
		w.draw(g);
	}
}

void print_objects (sf::RenderWindow& w, const vector<sf::RectangleShape> &a){
	for (const auto& g: a){
		w.draw(g);
	}
}

void print_objects1 (sf::RenderWindow& w, const vector<sf::Vertex *> &a){
	for (const auto& g: a){
		w.draw(g, 2, sf::Lines);
	}
}

int my_stoi(const string& s){
	if (s.size() == 0)
		return 5;
	else
		return stoi(s);
}
