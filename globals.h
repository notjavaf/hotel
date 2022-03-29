#pragma once

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

string comfort_to_string(comfort a);

string comfort_to_string1(comfort a);

string print_bool(bool c);

comfort get_comf(int i);

bool operator< (my_time t1, my_time t2);

bool operator<= (my_time t1, my_time t2);

my_time& operator++ (my_time& t1);

bool operator== (my_time t1, my_time t2);

int operator- (my_time t1, my_time t2);

int operator- (int i, my_time t2);

my_time operator+ (my_time t1, my_time t2);

my_time operator+ (my_time t1, int h);

comfort get_prev_comfort(comfort a);

bool cross_time_interval(const vector <pair <my_time, my_time> >& a, 
                         my_time st_t2, my_time f_t2);

ostream& operator<< (ostream& o, const map<comfort, int> &a);

void set_param_to_text(sf::Text& text, sf::Font& font, int x, int y, int size, sf::Color col);

ostream& operator<< (ostream& o, const map<comfort, pair <int, int> > &a);

void set_param_to_text1(sf::Text& text, string s, sf::Font& font, int x, int y, int size, sf::Color col);

void set_param_to_line(sf::Vertex line[2], int x1, int y1, int x2, int y2);

string time_to_string(my_time t);

string type_of_req_to_string(type_of_req a);

void print_objects (sf::RenderWindow& w, const vector<sf::Text> &a);

void print_objects (sf::RenderWindow& w, const vector<sf::RectangleShape> &a);

void print_objects1 (sf::RenderWindow& w, const vector<sf::Vertex *> &a);

int my_stoi(const string& s);
