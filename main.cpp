#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <random>
#include <fstream>
#include <iomanip>
#include <locale>
#include <SFML/System/String.hpp>
#include <SFML/System/Utf.hpp>
#include "globals.h"
#include "room.h"
#include "hotel.h"
#include "book_request.h"
#include "experiment.h"


using namespace std;

sf::Text text_cur_date_and_time_title, 
			 text_cur_date_and_time, 
			 text_num_of_completed_requests_title, 
			 text_num_of_unfulfilled_requests_title, 
			 text_num_of_completed_requests_by_rooms_title_1, 
			 text_num_of_completed_requests_by_rooms_title_2,
			 text_num_of_received_requests, 
			 text_num_of_requests_stats, 
			 text_num_of_completed_requests, 
			 text_num_of_unfulfilled_requests, 
			 text_num_of_completed_requests_lux, 
			 text_num_of_completed_requests_semi_lux, 
			 text_num_of_completed_requests_two_seat_sofa,
			 text_num_of_completed_requests_two_seat, 
			 text_num_of_completed_requests_one_seat, 
			 text_cur_revenue_title, 
			 text_cur_revenue, 
			 text_num_of_completed_requests_lux_title, 
			 text_num_of_completed_requests_semi_lux_title, 
			 text_num_of_completed_requests_two_seat_sofa_title, 
			 text_num_of_completed_requests_two_seat_title, 
			 text_num_of_completed_requests_one_seat_title, 
			 text_num_of_completed_requests_two_seat_sofa_title2, 
			 text_comfort_title, 
			 text_num_of_rooms_1, 
			 text_num_of_occ_rooms_1,  
			 text_num_of_rooms_2,
			 text_num_of_occ_rooms_2,  
			 text_num_of_occ_rooms_2_lux, 
			 text_num_of_occ_rooms_2_semi_lux,
			 text_num_of_occ_rooms_2_two_seat_sofa, 
			 text_num_of_occ_rooms_2_two_seat, 
			 text_num_of_occ_rooms_2_one_seat,   
			 text_num_of_occ_rooms_1_lux, 
			 text_num_of_occ_rooms_1_semi_lux,
			 text_num_of_occ_rooms_1_two_seat_sofa, 
			 text_num_of_occ_rooms_1_two_seat, 
			 text_num_of_occ_rooms_1_one_seat,   
			 text_type_of_req,  
			 text_type_of_comfort,  
			 text_time_in_title,
			 text_time_out_title,  
			 text_input_days,  
			 text_input_lux,  
			 text_input_semi_lux,  
			 text_input_two_seat_sofa,  
			 text_input_two_seat,  
			 text_input_one_seat,
			 text_input_lux_title,  
			 text_input_semi_lux_title,  
			 text_input_two_seat_sofa_title_1, 
			 text_input_two_seat_sofa_title_2, 
			 text_input_two_seat_title,  
			 text_input_one_seat_title,  
			 text_input_days_title, 
			 text_title_window_1,  
			 text_title_window_2,  
			 text_title_window_3,  
			 text_book_check_in_all_title,  
			 text_all_rooms_title,  
			 text_num_of_occ_rooms_all,  
			 text_num_of_occ_rooms_all_stat, 
			 text_percent_of_occ_title,  
			 text_percent_of_occ_title_2,  
			 text_percent_of_occ_lux,  
			 text_percent_of_occ_semi_lux,  
			 text_percent_of_occ_two_seat_sofa,  
			 text_percent_of_occ_two_seat,  
			 text_percent_of_occ_one_seat, 
			 text_percent_of_occ_all;

map <comfort, int> a = {{comfort::lux, 5},
                        {comfort::semi_lux, 5},
                        {comfort::two_seat_sofa, 5},
                        {comfort::two_seat, 5},
                        {comfort::one_seat, 5}};
vector<int> day_stat;
int M = 10, K = 25, inp = 0;
bool f = false, start_pr = true;
experiment experim(M, K, a);
sf::Vertex line[2], line1[2], line2[2], line3[2], line4[2], line5[2], line6[2], line7[2], line8[2];
sf::Texture TextureExitButton, 
	TextureOneStepButton, 
	TextureAllStepsButton;
sf::Font font;
sf::RectangleShape f_input_field_1(sf::Vector2f(100, 20));
sf::RectangleShape f_input_field_2(sf::Vector2f(100, 20));
sf::RectangleShape f_input_field_3(sf::Vector2f(100, 20));
sf::RectangleShape f_input_field_4(sf::Vector2f(100, 20));
sf::RectangleShape f_input_field_5(sf::Vector2f(100, 20));
sf::RectangleShape f_input_field_6(sf::Vector2f(100, 20));
sf::RenderWindow window(sf::VideoMode(800, 600), "Hotel");
string s_days = "5", s_lux = "5", s_semi_lux = "5", s_two_seat_sofa = "5", s_two_seat = "5", s_one_seat = "5"; 

void set_param_to_static_gr_objects(){
    set_param_to_text1(text_cur_date_and_time_title, "Текущие дата и время", font, 600, 20, 16, sf::Color::Black);
	set_param_to_text1(text_num_of_received_requests, "Поступило заявок", font, 615, 80, 16, sf::Color::Black);
	set_param_to_text1(text_book_check_in_all_title, "бронь/засел./всего", font, 610, 98, 16, sf::Color::Black);
	set_param_to_text1(text_num_of_completed_requests_title, "Всего выполнено заявок", font, 595, 160, 16, sf::Color::Black);
	set_param_to_text1(text_num_of_unfulfilled_requests_title, "Невыполнено заявок", font, 610, 230, 16, sf::Color::Black);
	set_param_to_text1(text_num_of_completed_requests_by_rooms_title_1, "Выполнено заявок", font, 620, 300, 16, sf::Color::Black);
	set_param_to_text1(text_num_of_completed_requests_by_rooms_title_2, "по номерам", font, 650, 322, 16, sf::Color::Black);
	set_param_to_text1(text_cur_revenue_title, "Текущая выручка", font, 620, 465, 16, sf::Color::Black);
	set_param_to_text1(text_num_of_completed_requests_lux_title, "люкс", font, 90, 65, 16, sf::Color::Black);
	set_param_to_text1(text_num_of_completed_requests_semi_lux_title, "полулюкс", font, 76, 112, 16, sf::Color::Black);
	set_param_to_text1(text_num_of_completed_requests_two_seat_sofa_title, "двухместные с", font, 55, 159, 16, sf::Color::Black);
	set_param_to_text1(text_num_of_completed_requests_two_seat_title, "простые двухместные", font, 25, 206, 16, sf::Color::Black);
	set_param_to_text1(text_num_of_completed_requests_one_seat_title, "одноместные", font, 60, 253, 16, sf::Color::Black);
	set_param_to_text1(text_all_rooms_title, "все номера", font, 63, 293, 16, sf::Color::Black);
	set_param_to_text1(text_num_of_completed_requests_two_seat_sofa_title2, "раскладным диваном", font, 30, 173, 16, sf::Color::Black);
	set_param_to_text1(text_comfort_title, "комфорт", font, 76, 20, 16, sf::Color::Black);
	set_param_to_text1(text_num_of_rooms_1, "общее число", font, 217, 10, 16, sf::Color::Black);
	set_param_to_text1(text_num_of_occ_rooms_1, "занято в", font, 355, 10, 16, sf::Color::Black);
	set_param_to_text1(text_num_of_rooms_2, "номеров", font, 232, 30, 16, sf::Color::Black);
	set_param_to_text1(text_num_of_occ_rooms_2, "данный момент", font, 340, 30, 16, sf::Color::Black);
	set_param_to_text1(text_percent_of_occ_title, "процент", font, 490, 10, 16, sf::Color::Black);
	set_param_to_text1(text_percent_of_occ_title_2, "занятости", font, 487, 30, 16, sf::Color::Black);
	set_param_to_line(line, 190, 20, 190, 310);
	set_param_to_line(line1, 330, 20, 330, 310);
	set_param_to_line(line2, 50, 50, 550, 50);
	set_param_to_line(line3, 30, 380, 520, 380);
	set_param_to_line(line4, 390, 350, 390, 550);
	set_param_to_line(line5, 270, 350, 270, 550);
	set_param_to_line(line6, 150, 350, 150, 550);
	set_param_to_line(line7, 50, 280, 550, 280);
	set_param_to_line(line8, 470, 20, 470, 310);
    set_param_to_text1(text_type_of_req, "тип заявки", font, 50, 355, 16, sf::Color::Black);
	set_param_to_text1(text_type_of_comfort, "время заселен.", font, 275, 355, 16, sf::Color::Black);
	set_param_to_text1(text_time_in_title, "время выселения", font, 395, 355, 16, sf::Color::Black);
    set_param_to_text1(text_time_out_title, "комфорт", font, 170, 355, 16, sf::Color::Black);
	f_input_field_1.setPosition(250, 150);
	f_input_field_2.setPosition(250, 250);
	f_input_field_3.setPosition(250, 300);
	f_input_field_4.setPosition(250, 350);
	f_input_field_5.setPosition(250, 400);
	f_input_field_6.setPosition(250, 450);
    set_param_to_text(text_input_days, font, 252, 152, 16, sf::Color::Black);
	set_param_to_text(text_input_lux, font, 252, 252, 16, sf::Color::Black);
	set_param_to_text(text_input_semi_lux, font, 252, 302, 16, sf::Color::Black);
    set_param_to_text(text_input_two_seat_sofa, font, 252, 352, 16, sf::Color::Black);
    set_param_to_text(text_input_two_seat, font, 252, 402, 16, sf::Color::Black);
	set_param_to_text(text_input_one_seat, font, 252, 452, 16, sf::Color::Black);
	set_param_to_text1(text_title_window_3, "Введите номерной фонд гостиницы", font, 100, 202, 18, sf::Color::Black);
	set_param_to_text1(text_input_lux_title, "люкс", font, 201, 252, 16, sf::Color::Black);
	set_param_to_text1(text_input_semi_lux_title, "полулюкс", font, 167, 302, 16, sf::Color::Black);
	set_param_to_text1(text_input_two_seat_sofa_title_1, "двухместные с", font, 127, 342, 16, sf::Color::Black);
	set_param_to_text1(text_input_two_seat_sofa_title_2, "раскладным диваном", font, 78, 362, 16, sf::Color::Black);
	set_param_to_text1(text_input_two_seat_title, "простые двухместные", font, 70, 402, 16, sf::Color::Black);
	set_param_to_text1(text_input_one_seat_title, "одноместные", font, 140, 452, 16, sf::Color::Black);
	set_param_to_text1(text_input_days_title, "число дней моделир.", font, 83, 152, 16, sf::Color::Black);
	set_param_to_text1(text_title_window_1, "Введите поочередно числа, нажимая Enter", font, 50, 50, 20, sf::Color::Black);
	set_param_to_text1(text_title_window_2, "(предварительно никуда нажимать не нужно)", font, 50, 80, 18, sf::Color::Black);
	text_input_days.setString(sf::String::fromUtf8(s_days.begin(), s_days.end()));
	text_input_lux.setString(sf::String::fromUtf8(s_lux.begin(), s_lux.end()));
	text_input_semi_lux.setString(sf::String::fromUtf8(s_semi_lux.begin(), s_semi_lux.end()));
	text_input_two_seat_sofa.setString(sf::String::fromUtf8(s_two_seat_sofa.begin(), s_two_seat_sofa.end()));
	text_input_two_seat.setString(sf::String::fromUtf8(s_two_seat.begin(), s_two_seat.end()));
	text_input_one_seat.setString(sf::String::fromUtf8(s_one_seat.begin(), s_one_seat.end()));
}

void press_step_buttons(){
	if (sf::IntRect(330, 560, 100, 32).contains(sf::Mouse::getPosition(window))){ 
                            experim.complete_one_step();  
                            my_time cur_time = experim.get_cur_time();
                            if (cur_time.day >= M)
                                f = false;
                        }
                        if (sf::IntRect(530, 560, 180, 32).contains(sf::Mouse::getPosition(window))){ 
                            experim.complete_all_steps();  
                            f = false;
                        }
}

int main()
{	
    srand(time(0));
    setlocale(LC_CTYPE, "rus");
    font.loadFromFile("arial.ttf");
    set_param_to_static_gr_objects();
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
                        press_step_buttons();
                    }
                }
            } else if (event.type == sf::Event::KeyReleased){
                if (event.key.code == sf::Keyboard::Return){
                	inp++;
                }
				switch(inp){
				case 6:
					start_pr = false;
					f = true;
					M = my_stoi(s_days);
					a = {{comfort::lux, my_stoi(s_lux)},
                         {comfort::semi_lux, my_stoi(s_semi_lux)},
                         {comfort::two_seat_sofa, my_stoi(s_two_seat_sofa)},
                         {comfort::two_seat, my_stoi(s_two_seat)},
                         {comfort::one_seat, my_stoi(s_one_seat)}};
					K = my_stoi(s_lux) + 
						my_stoi(s_semi_lux) +
						my_stoi(s_two_seat_sofa) +
						my_stoi(s_two_seat) +
						my_stoi(s_one_seat);
					experim = experiment(M, K, a);
					break;
				case 5: 
					if (s_two_seat.size() == 0)
						s_two_seat = "5";
					break;
				case 4: 
					if (s_two_seat_sofa.size() == 0)
						s_two_seat_sofa = "5";
					break;
				case 3: 
					if (s_semi_lux.size() == 0)
						s_semi_lux = "5";
					break;
				case 2: 
					if (s_lux.size() == 0)
						s_lux = "5";
					break;
				case 1: 
					if (s_days.size() == 0)
						s_days = "5";
					break;
				default: 
					break;
				} 
                if (event.key.code != sf::Keyboard::Return) {
                    sf::Keyboard::Key keycode = event.key.code;
					if (keycode == sf::Keyboard::BackSpace){
						switch (inp){
							case 0:
								if (s_days.size() > 0)
									s_days = s_days.substr(0, s_days.size() - 1);
								break;
							case 1:
								if (s_lux.size() > 0)
									s_lux = s_lux.substr(0, s_lux.size() - 1);
								break;
							case 2:
								if (s_semi_lux.size() > 0)
									s_semi_lux = s_semi_lux.substr(0, s_semi_lux.size() - 1);
								break;
							case 3:
								if (s_two_seat_sofa.size() > 0)
									s_two_seat_sofa = s_two_seat_sofa.substr(0, s_two_seat_sofa.size() - 1);
								break;
							case 4:
								if (s_two_seat.size() > 0)
									s_two_seat = s_two_seat.substr(0, s_two_seat.size() - 1);
								break;
							default:
								if (s_one_seat.size() > 0)
									s_one_seat = s_one_seat.substr(0, s_one_seat.size() - 1);
								break;
						}
					}
                    if (keycode >= sf::Keyboard::Num0 && keycode <= sf::Keyboard::Num9 && s_days.size() < 10 && inp == 0){
                        char chr = static_cast<char>(keycode - sf::Keyboard::Num0 + '0');
                        s_days.push_back(chr);
                    }
					if (keycode >= sf::Keyboard::Num0 && keycode <= sf::Keyboard::Num9 && s_lux.size() < 10 && inp == 1){
                        char chr = static_cast<char>(keycode - sf::Keyboard::Num0 + '0');
                        s_lux.push_back(chr);
                    }
					if (keycode >= sf::Keyboard::Num0 && keycode <= sf::Keyboard::Num9 && s_semi_lux.size() < 10 && inp == 2){
                        char chr = static_cast<char>(keycode - sf::Keyboard::Num0 + '0');
                        s_semi_lux.push_back(chr);
                    }
					if (keycode >= sf::Keyboard::Num0 && keycode <= sf::Keyboard::Num9 && s_two_seat_sofa.size() < 10 && inp == 3){
                        char chr = static_cast<char>(keycode - sf::Keyboard::Num0 + '0');
                        s_two_seat_sofa.push_back(chr);
                    }
					if (keycode >= sf::Keyboard::Num0 && keycode <= sf::Keyboard::Num9 && s_two_seat.size() < 10 && inp == 4){
                        char chr = static_cast<char>(keycode - sf::Keyboard::Num0 + '0');
                        s_two_seat.push_back(chr);
                    }
					if (keycode >= sf::Keyboard::Num0 && keycode <= sf::Keyboard::Num9 && s_one_seat.size() < 10 && inp == 5){
                        char chr = static_cast<char>(keycode - sf::Keyboard::Num0 + '0');
                        s_one_seat.push_back(chr);
                    }
                }
				text_input_days.setString(sf::String::fromUtf8(s_days.begin(), s_days.end()));
	            text_input_lux.setString(sf::String::fromUtf8(s_lux.begin(), s_lux.end()));
				text_input_semi_lux.setString(sf::String::fromUtf8(s_semi_lux.begin(), s_semi_lux.end()));
				text_input_two_seat_sofa.setString(sf::String::fromUtf8(s_two_seat_sofa.begin(), s_two_seat_sofa.end()));
				text_input_two_seat.setString(sf::String::fromUtf8(s_two_seat.begin(), s_two_seat.end()));
				text_input_one_seat.setString(sf::String::fromUtf8(s_one_seat.begin(), s_one_seat.end()));
            } 
        }   
		set_param_to_text1(text_cur_date_and_time, time_to_string(experim.get_cur_time()), font, 650, 45, 16, sf::Color::Black);
		set_param_to_text1(text_num_of_requests_stats, to_string(experim.get_num_of_completed_requests_book())+"/"+
								  to_string(experim.get_num_of_completed_requests_check_in())+"/"+
								  to_string(experim.get_num_of_completed_requests_book()+
											experim.get_num_of_completed_requests_check_in()+
											experim.get_num_of_unfulfilled_requests()), font, 650, 120, 16, sf::Color::Black);
		set_param_to_text1(text_num_of_completed_requests, to_string(experim.get_num_of_completed_requests_book()+
											experim.get_num_of_completed_requests_check_in()), font, 675, 185, 16, sf::Color::Black);
		set_param_to_text1(text_num_of_unfulfilled_requests, to_string(experim.get_num_of_unfulfilled_requests()), font, 675, 255, 16, sf::Color::Black);
		map<comfort, int> star_c_r = experim.get_num_of_completed_requests_by_rooms();
		set_param_to_text1(text_num_of_completed_requests_lux, "люкс: " + to_string(star_c_r[comfort::lux]), font, 670, 350, 16, sf::Color::Black);;
		set_param_to_text1(text_num_of_completed_requests_semi_lux, "полулюкс: " + to_string(star_c_r[comfort::semi_lux]), font, 636, 370, 16, sf::Color::Black);
		set_param_to_text1(text_num_of_completed_requests_two_seat_sofa, "2-мест. с див.: " + to_string(star_c_r[comfort::two_seat_sofa]), font, 604, 390, 16, sf::Color::Black);
		set_param_to_text1(text_num_of_completed_requests_two_seat, "прост. 2-мест.: " + to_string(star_c_r[comfort::two_seat]), font, 600, 410, 16, sf::Color::Black);
		set_param_to_text1(text_num_of_completed_requests_one_seat, "1-мест: " + to_string(star_c_r[comfort::one_seat]), font, 655, 430, 16, sf::Color::Black);
		set_param_to_text1(text_cur_revenue, to_string(experim.get_cur_revenue()), font, 660, 490, 16, sf::Color::Black);
		map <comfort, pair<int, int> > stat_rooms = experim.get_stats();
		set_param_to_text1(text_num_of_occ_rooms_2_lux, to_string(stat_rooms[comfort::lux].second), font, 255, 65, 16, sf::Color::Black);
		set_param_to_text1(text_num_of_occ_rooms_2_semi_lux, to_string(stat_rooms[comfort::semi_lux].second), font, 255, 112, 16, sf::Color::Black);
		set_param_to_text1(text_num_of_occ_rooms_2_two_seat_sofa, to_string(stat_rooms[comfort::two_seat_sofa].second), font, 255, 159, 16, sf::Color::Black);
		set_param_to_text1(text_num_of_occ_rooms_2_two_seat, to_string(stat_rooms[comfort::two_seat].second), font, 255, 206, 16, sf::Color::Black);
		set_param_to_text1(text_num_of_occ_rooms_2_one_seat, to_string(stat_rooms[comfort::one_seat].second), font, 255, 253, 16, sf::Color::Black);
		set_param_to_text1(text_num_of_occ_rooms_all, to_string(stat_rooms[comfort::one_seat].second+
											 stat_rooms[comfort::two_seat].second+
											 stat_rooms[comfort::two_seat_sofa].second+
											 stat_rooms[comfort::semi_lux].second+
											 stat_rooms[comfort::lux].second), font, 255, 293, 16, sf::Color::Black);
		set_param_to_text1(text_num_of_occ_rooms_1_lux, to_string(stat_rooms[comfort::lux].first), font, 395, 65, 16, sf::Color::Black);
		set_param_to_text1(text_num_of_occ_rooms_1_semi_lux, to_string(stat_rooms[comfort::semi_lux].first), font, 395, 112, 16, sf::Color::Black);
		set_param_to_text1(text_num_of_occ_rooms_1_two_seat_sofa, to_string(stat_rooms[comfort::two_seat_sofa].first), font, 395, 159, 16, sf::Color::Black);
		set_param_to_text1(text_num_of_occ_rooms_1_two_seat, to_string(stat_rooms[comfort::two_seat].first), font, 395, 206, 16, sf::Color::Black);
		set_param_to_text1(text_num_of_occ_rooms_1_one_seat, to_string(stat_rooms[comfort::one_seat].first), font, 395, 253, 16, sf::Color::Black);
		set_param_to_text1(text_num_of_occ_rooms_all_stat, to_string(stat_rooms[comfort::one_seat].first+
											 stat_rooms[comfort::two_seat].first+
											 stat_rooms[comfort::two_seat_sofa].first+
											 stat_rooms[comfort::semi_lux].first+
											 stat_rooms[comfort::lux].first), font, 395, 293, 16, sf::Color::Black);
		if (stat_rooms[comfort::lux].second != 0)
		set_param_to_text1(text_percent_of_occ_lux, to_string(100*stat_rooms[comfort::lux].first/
												 stat_rooms[comfort::lux].second)+"%", font, 500, 65, 16, sf::Color::Black);
		if (stat_rooms[comfort::semi_lux].second != 0)
		set_param_to_text1(text_percent_of_occ_semi_lux, to_string(100*stat_rooms[comfort::semi_lux].first/
												 stat_rooms[comfort::semi_lux].second)+"%", font, 500, 112, 16, sf::Color::Black);
		if (stat_rooms[comfort::two_seat_sofa].second != 0)
		set_param_to_text1(text_percent_of_occ_two_seat_sofa, to_string(100*stat_rooms[comfort::two_seat_sofa].first/
												 stat_rooms[comfort::two_seat_sofa].second)+"%", font, 500, 159, 16, sf::Color::Black);
		if (stat_rooms[comfort::two_seat].second != 0)
		set_param_to_text1(text_percent_of_occ_two_seat, to_string(100*stat_rooms[comfort::two_seat].first/
												 stat_rooms[comfort::two_seat].second)+"%", font, 500, 206, 16, sf::Color::Black);
		if (stat_rooms[comfort::one_seat].second != 0)
		set_param_to_text1(text_percent_of_occ_one_seat, to_string(100*stat_rooms[comfort::one_seat].first/
												 stat_rooms[comfort::one_seat].second)+"%", font, 500, 253, 16, sf::Color::Black);
		if (stat_rooms[comfort::one_seat].second != 0)
		set_param_to_text1(text_percent_of_occ_all, to_string(100*(stat_rooms[comfort::one_seat].first+
											 stat_rooms[comfort::two_seat].first+
											 stat_rooms[comfort::two_seat_sofa].first+
											 stat_rooms[comfort::semi_lux].first+
											 stat_rooms[comfort::lux].first)/(stat_rooms[comfort::one_seat].second+
											 stat_rooms[comfort::two_seat].second+
											 stat_rooms[comfort::two_seat_sofa].second+
											 stat_rooms[comfort::semi_lux].second+
											 stat_rooms[comfort::lux].second))+"%", font, 500, 293, 16, sf::Color::Black);
        vector<book_request> vec_b = experim.get_vec_of_book_requests();
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
			//fout << r_1 << " в " << r_2 << " с " << r_3 << " до " << r_4 << endl;
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
			print_objects(window, {f_input_field_1, 
								   f_input_field_2, 
								   f_input_field_3, 
								   f_input_field_4, 
								   f_input_field_5, 
								   f_input_field_6});
			print_objects(window, {text_input_days,  
			 					text_input_lux,  
			 					text_input_semi_lux,  
			 					text_input_two_seat_sofa,  
			 					text_input_two_seat,  
			 					text_input_one_seat, 
								text_input_lux_title,  
			 					text_input_semi_lux_title,  
			 					text_input_two_seat_sofa_title_1, 
			 					text_input_two_seat_sofa_title_2, 
			 					text_input_two_seat_title,  
			 					text_input_one_seat_title,  
								text_input_days_title, 
								text_title_window_1, 
								text_title_window_2,
								text_title_window_3});
        }
        else {
            if (f){
                window.draw(OneStepButton);
                window.draw(AllStepsButton);
            }
		    int gr = 8;
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
			    gr--;
			    if (gr == 0)
				    break;
            }
		    print_objects(window, {text_cur_date_and_time_title, 
								   text_cur_date_and_time, 
								   text_num_of_completed_requests_title, 
								   text_num_of_unfulfilled_requests_title, 
								   text_num_of_completed_requests_by_rooms_title_1, 
							       text_num_of_completed_requests_by_rooms_title_2, 
								   text_num_of_received_requests, 
								   text_num_of_requests_stats, 
								   text_num_of_completed_requests, 
								   text_num_of_unfulfilled_requests,
							       text_num_of_completed_requests_lux, 
								   text_num_of_completed_requests_semi_lux, 
								   text_num_of_completed_requests_two_seat_sofa, 
								   text_num_of_completed_requests_two_seat, 
								   text_num_of_completed_requests_one_seat,
							       text_cur_revenue_title, 
								   text_cur_revenue, 
								   text_num_of_completed_requests_lux_title, 
								   text_num_of_completed_requests_semi_lux_title, 
								   text_num_of_completed_requests_two_seat_sofa_title, 
								   text_num_of_completed_requests_two_seat_title, 
								   text_num_of_completed_requests_one_seat_title, 
								   text_num_of_completed_requests_two_seat_sofa_title2, 
								   text_comfort_title, 								   
								   text_num_of_rooms_1,
							       text_num_of_occ_rooms_1, 								   
								   text_num_of_rooms_2, 
								   text_num_of_occ_rooms_2, 								   
								   text_num_of_occ_rooms_2_lux, 
								   text_num_of_occ_rooms_2_semi_lux,
							       text_num_of_occ_rooms_2_two_seat_sofa, 
								   text_num_of_occ_rooms_2_two_seat, 
								   text_num_of_occ_rooms_2_one_seat, 
								   text_num_of_occ_rooms_1_lux, 
								   text_num_of_occ_rooms_1_semi_lux,
							       text_num_of_occ_rooms_1_two_seat_sofa, 
								   text_num_of_occ_rooms_1_two_seat, 
								   text_num_of_occ_rooms_1_one_seat,  
								   text_type_of_req,  
			 					   text_type_of_comfort,  
			 					   text_time_in_title,
			 					   text_time_out_title,
								   text_book_check_in_all_title, 
								   text_all_rooms_title, 
								   text_num_of_occ_rooms_all,
								   text_num_of_occ_rooms_all_stat, 
								   text_percent_of_occ_title, 
								   text_percent_of_occ_title_2, 
								   text_percent_of_occ_lux,  
			 					   text_percent_of_occ_semi_lux,  
			 					   text_percent_of_occ_two_seat_sofa,  
			 					   text_percent_of_occ_two_seat,  
			 					   text_percent_of_occ_one_seat, 
			 					   text_percent_of_occ_all});
		    print_objects1(window, {line, line1, line2, line3, line4, line5, line6, line7, line8});
        }
        window.display();
    }
    return 0;
}
