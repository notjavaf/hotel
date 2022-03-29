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
#include "globals.h"
#include "room.h"
#include "hotel.h"
#include "book_request.h"
#include "experiment.h"


using namespace std;

int main()
{
    srand(time(0));
    map <comfort, int> a = {{comfort::lux, 5},
                            {comfort::semi_lux, 5},
                            {comfort::two_seat_sofa, 5},
                            {comfort::two_seat, 5},
                            {comfort::one_seat, 5}};
    int M = 10, K = 25, inp = 0;
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
    text49, text50, text51, text52, text53, text54, text55,
	text56, text57, text58, text59, text60, text61, text62,
	text63, text64, text65, text66, text67, text68, text69,
	text70;
	sf::Vertex line[2], line1[2], line2[2], line3[2], line4[2], line5[2], line6[2], line7[2], line8[2];
    set_param_to_text1(text1, "Текущие дата и время", font, 600, 20, 16, sf::Color::Black);
	set_param_to_text1(text7, "Поступило заявок", font, 615, 80, 16, sf::Color::Black);
	set_param_to_text1(text59, "бронь/засел./всего", font, 610, 98, 16, sf::Color::Black);
	set_param_to_text1(text3, "Всего выполнено заявок", font, 595, 160, 16, sf::Color::Black);
	set_param_to_text1(text4, "Невыполнено заявок", font, 610, 230, 16, sf::Color::Black);
	set_param_to_text1(text5, "Выполнено заявок", font, 620, 300, 16, sf::Color::Black);
	set_param_to_text1(text6, "по номерам", font, 650, 322, 16, sf::Color::Black);
	set_param_to_text1(text16, "Текущая выручка", font, 620, 465, 16, sf::Color::Black);
	set_param_to_text1(text18, "люкс", font, 90, 65, 16, sf::Color::Black);
	set_param_to_text1(text19, "полулюкс", font, 76, 112, 16, sf::Color::Black);
	set_param_to_text1(text20, "двухместные с", font, 55, 159, 16, sf::Color::Black);
	set_param_to_text1(text21, "простые двухместные", font, 25, 206, 16, sf::Color::Black);
	set_param_to_text1(text22, "одноместные", font, 60, 253, 16, sf::Color::Black);
	set_param_to_text1(text60, "все номера", font, 63, 293, 16, sf::Color::Black);
	set_param_to_text1(text23, "раскладным диваном", font, 30, 173, 16, sf::Color::Black);
	set_param_to_text1(text24, "комфорт", font, 76, 20, 16, sf::Color::Black);
	set_param_to_text1(text25, "общее число", font, 217, 10, 16, sf::Color::Black);
	set_param_to_text1(text26, "занято в", font, 355, 10, 16, sf::Color::Black);
	set_param_to_text1(text27, "номеров", font, 232, 30, 16, sf::Color::Black);
	set_param_to_text1(text28, "данный момент", font, 340, 30, 16, sf::Color::Black);
	set_param_to_text1(text63, "процент", font, 490, 10, 16, sf::Color::Black);
	set_param_to_text1(text64, "занятости", font, 487, 30, 16, sf::Color::Black);
	set_param_to_line(line, 190, 20, 190, 310);
	set_param_to_line(line1, 330, 20, 330, 310);
	set_param_to_line(line2, 50, 50, 550, 50);
	set_param_to_line(line3, 30, 380, 520, 380);
	set_param_to_line(line4, 390, 350, 390, 550);
	set_param_to_line(line5, 270, 350, 270, 550);
	set_param_to_line(line6, 150, 350, 150, 550);
	set_param_to_line(line7, 50, 280, 550, 280);
	set_param_to_line(line8, 470, 20, 470, 310);
    set_param_to_text1(text39, "тип заявки", font, 50, 355, 16, sf::Color::Black);
	set_param_to_text1(text40, "время заселен.", font, 275, 355, 16, sf::Color::Black);
	set_param_to_text1(text41, "время выселения", font, 395, 355, 16, sf::Color::Black);
    set_param_to_text1(text42, "комфорт", font, 170, 355, 16, sf::Color::Black);
	sf::RectangleShape f1(sf::Vector2f(100, 20));
	sf::RectangleShape f2(sf::Vector2f(100, 20));
	sf::RectangleShape f3(sf::Vector2f(100, 20));
	sf::RectangleShape f4(sf::Vector2f(100, 20));
	sf::RectangleShape f5(sf::Vector2f(100, 20));
	sf::RectangleShape f6(sf::Vector2f(100, 20));
	f1.setPosition(250, 150);
	f2.setPosition(250, 250);
	f3.setPosition(250, 300);
	f4.setPosition(250, 350);
	f5.setPosition(250, 400);
	f6.setPosition(250, 450);
    set_param_to_text(text43, font, 252, 152, 16, sf::Color::Black);
	set_param_to_text(text44, font, 252, 252, 16, sf::Color::Black);
	set_param_to_text(text45, font, 252, 302, 16, sf::Color::Black);
    set_param_to_text(text46, font, 252, 352, 16, sf::Color::Black);
    set_param_to_text(text47, font, 252, 402, 16, sf::Color::Black);
	set_param_to_text(text48, font, 252, 452, 16, sf::Color::Black);
    string s43, s44, s45, s46, s47, s48;
	set_param_to_text1(text58, "Введите номерной фонд гостиницы", font, 100, 202, 18, sf::Color::Black);
	set_param_to_text1(text49, "люкс", font, 201, 252, 16, sf::Color::Black);
	set_param_to_text1(text50, "полулюкс", font, 167, 302, 16, sf::Color::Black);
	set_param_to_text1(text51, "двухместные с", font, 127, 342, 16, sf::Color::Black);
	set_param_to_text1(text52, "раскладным диваном", font, 78, 362, 16, sf::Color::Black);
	set_param_to_text1(text53, "простые двухместные", font, 70, 402, 16, sf::Color::Black);
	set_param_to_text1(text54, "одноместные", font, 140, 452, 16, sf::Color::Black);
	set_param_to_text1(text55, "число дней моделир.", font, 83, 152, 16, sf::Color::Black);
	set_param_to_text1(text56, "Введите поочередно числа, нажимая Enter", font, 50, 50, 20, sf::Color::Black);
	set_param_to_text1(text57, "(предварительно никуда нажимать не нужно)", font, 50, 80, 18, sf::Color::Black);
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
				switch(inp){
				case 6:
					start_pr = false;
					f = true;
					M = my_stoi(s43);
					a = {{comfort::lux, my_stoi(s44)},
                         {comfort::semi_lux, my_stoi(s45)},
                         {comfort::two_seat_sofa, my_stoi(s46)},
                         {comfort::two_seat, my_stoi(s47)},
                         {comfort::one_seat, my_stoi(s48)}};
					K = my_stoi(s44) + 
						my_stoi(s45) +
						my_stoi(s46) +
						my_stoi(s47) +
						my_stoi(s48);
					exp = experiment(M, K, a);
					break;
				case 5: 
					if (s47.size() == 0)
						s47 = "5";
					break;
				case 4: 
					if (s46.size() == 0)
						s46 = "5";
					break;
				case 3: 
					if (s45.size() == 0)
						s45 = "5";
					break;
				case 2: 
					if (s44.size() == 0)
						s44 = "5";
					break;
				case 1: 
					if (s43.size() == 0)
						s43 = "5";
					break;
				default: 
					break;
				} 
                if (event.key.code != sf::Keyboard::Return) {
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
					if (keycode >= sf::Keyboard::Num0 && keycode <= sf::Keyboard::Num9 && s44.size() < 10 && inp == 1){
                        char chr = static_cast<char>(keycode - sf::Keyboard::Num0 + '0');
                        s44.push_back(chr);
                    }
					if (keycode >= sf::Keyboard::Num0 && keycode <= sf::Keyboard::Num9 && s45.size() < 10 && inp == 2){
                        char chr = static_cast<char>(keycode - sf::Keyboard::Num0 + '0');
                        s45.push_back(chr);
                    }
					if (keycode >= sf::Keyboard::Num0 && keycode <= sf::Keyboard::Num9 && s46.size() < 10 && inp == 3){
                        char chr = static_cast<char>(keycode - sf::Keyboard::Num0 + '0');
                        s46.push_back(chr);
                    }
					if (keycode >= sf::Keyboard::Num0 && keycode <= sf::Keyboard::Num9 && s47.size() < 10 && inp == 4){
                        char chr = static_cast<char>(keycode - sf::Keyboard::Num0 + '0');
                        s47.push_back(chr);
                    }
					if (keycode >= sf::Keyboard::Num0 && keycode <= sf::Keyboard::Num9 && s48.size() < 10 && inp == 5){
                        char chr = static_cast<char>(keycode - sf::Keyboard::Num0 + '0');
                        s48.push_back(chr);
                    }
                }
				text43.setString(sf::String::fromUtf8(s43.begin(), s43.end()));
	            text44.setString(sf::String::fromUtf8(s44.begin(), s44.end()));
				text45.setString(sf::String::fromUtf8(s45.begin(), s45.end()));
				text46.setString(sf::String::fromUtf8(s46.begin(), s46.end()));
				text47.setString(sf::String::fromUtf8(s47.begin(), s47.end()));
				text48.setString(sf::String::fromUtf8(s48.begin(), s48.end()));
            } 
        }   
		set_param_to_text1(text2, time_to_string(exp.get_cur_time()), font, 650, 45, 16, sf::Color::Black);
		set_param_to_text1(text8, to_string(exp.get_num_of_completed_requests_book())+"/"+
								  to_string(exp.get_num_of_completed_requests_check_in())+"/"+
								  to_string(exp.get_num_of_completed_requests_book()+
											exp.get_num_of_completed_requests_check_in()+
											exp.get_num_of_unfulfilled_requests()), font, 650, 120, 16, sf::Color::Black);
		set_param_to_text1(text9, to_string(exp.get_num_of_completed_requests_book()+
											exp.get_num_of_completed_requests_check_in()), font, 675, 185, 16, sf::Color::Black);
		set_param_to_text1(text10, to_string(exp.get_num_of_unfulfilled_requests()), font, 675, 255, 16, sf::Color::Black);
		map<comfort, int> star_c_r = exp.get_num_of_completed_requests_by_rooms();
		set_param_to_text1(text11, "люкс: " + to_string(star_c_r[comfort::lux]), font, 670, 350, 16, sf::Color::Black);;
		set_param_to_text1(text12, "полулюкс: " + to_string(star_c_r[comfort::semi_lux]), font, 636, 370, 16, sf::Color::Black);
		set_param_to_text1(text13, "2-мест. с див.: " + to_string(star_c_r[comfort::two_seat_sofa]), font, 604, 390, 16, sf::Color::Black);
		set_param_to_text1(text14, "прост. 2-мест.: " + to_string(star_c_r[comfort::two_seat]), font, 600, 410, 16, sf::Color::Black);
		set_param_to_text1(text15, "1-мест: " + to_string(star_c_r[comfort::one_seat]), font, 655, 430, 16, sf::Color::Black);
		set_param_to_text1(text17, to_string(exp.get_cur_revenue()), font, 660, 490, 16, sf::Color::Black);
		map <comfort, pair<int, int> > stat_rooms = exp.get_stats();
		set_param_to_text1(text29, to_string(stat_rooms[comfort::lux].second), font, 255, 65, 16, sf::Color::Black);
		set_param_to_text1(text30, to_string(stat_rooms[comfort::semi_lux].second), font, 255, 112, 16, sf::Color::Black);
		set_param_to_text1(text31, to_string(stat_rooms[comfort::two_seat_sofa].second), font, 255, 159, 16, sf::Color::Black);
		set_param_to_text1(text32, to_string(stat_rooms[comfort::two_seat].second), font, 255, 206, 16, sf::Color::Black);
		set_param_to_text1(text33, to_string(stat_rooms[comfort::one_seat].second), font, 255, 253, 16, sf::Color::Black);
		set_param_to_text1(text61, to_string(stat_rooms[comfort::one_seat].second+
											 stat_rooms[comfort::two_seat].second+
											 stat_rooms[comfort::two_seat_sofa].second+
											 stat_rooms[comfort::semi_lux].second+
											 stat_rooms[comfort::lux].second), font, 255, 293, 16, sf::Color::Black);
		set_param_to_text1(text34, to_string(stat_rooms[comfort::lux].first), font, 395, 65, 16, sf::Color::Black);
		set_param_to_text1(text35, to_string(stat_rooms[comfort::semi_lux].first), font, 395, 112, 16, sf::Color::Black);
		set_param_to_text1(text36, to_string(stat_rooms[comfort::two_seat_sofa].first), font, 395, 159, 16, sf::Color::Black);
		set_param_to_text1(text37, to_string(stat_rooms[comfort::two_seat].first), font, 395, 206, 16, sf::Color::Black);
		set_param_to_text1(text38, to_string(stat_rooms[comfort::one_seat].first), font, 395, 253, 16, sf::Color::Black);
		set_param_to_text1(text62, to_string(stat_rooms[comfort::one_seat].first+
											 stat_rooms[comfort::two_seat].first+
											 stat_rooms[comfort::two_seat_sofa].first+
											 stat_rooms[comfort::semi_lux].first+
											 stat_rooms[comfort::lux].first), font, 395, 293, 16, sf::Color::Black);
		if (stat_rooms[comfort::lux].second != 0)
		set_param_to_text1(text65, to_string(100*stat_rooms[comfort::lux].first/
												 stat_rooms[comfort::lux].second)+"%", font, 500, 65, 16, sf::Color::Black);
		if (stat_rooms[comfort::semi_lux].second != 0)
		set_param_to_text1(text66, to_string(100*stat_rooms[comfort::semi_lux].first/
												 stat_rooms[comfort::semi_lux].second)+"%", font, 500, 112, 16, sf::Color::Black);
		if (stat_rooms[comfort::two_seat_sofa].second != 0)
		set_param_to_text1(text67, to_string(100*stat_rooms[comfort::two_seat_sofa].first/
												 stat_rooms[comfort::two_seat_sofa].second)+"%", font, 500, 159, 16, sf::Color::Black);
		if (stat_rooms[comfort::two_seat].second != 0)
		set_param_to_text1(text68, to_string(100*stat_rooms[comfort::two_seat].first/
												 stat_rooms[comfort::two_seat].second)+"%", font, 500, 206, 16, sf::Color::Black);
		if (stat_rooms[comfort::one_seat].second != 0)
		set_param_to_text1(text69, to_string(100*stat_rooms[comfort::one_seat].first/
												 stat_rooms[comfort::one_seat].second)+"%", font, 500, 253, 16, sf::Color::Black);
		if (stat_rooms[comfort::one_seat].second != 0)
		set_param_to_text1(text70, to_string(100*(stat_rooms[comfort::one_seat].first+
											 stat_rooms[comfort::two_seat].first+
											 stat_rooms[comfort::two_seat_sofa].first+
											 stat_rooms[comfort::semi_lux].first+
											 stat_rooms[comfort::lux].first)/(stat_rooms[comfort::one_seat].second+
											 stat_rooms[comfort::two_seat].second+
											 stat_rooms[comfort::two_seat_sofa].second+
											 stat_rooms[comfort::semi_lux].second+
											 stat_rooms[comfort::lux].second))+"%", font, 500, 293, 16, sf::Color::Black);
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
			print_objects(window, {f1, f2, f3, f4, f5, f6});
			print_objects(window, {text43, text44, text45, text46, text47, 
								   text48, text49, text50, text51, text52,
								   text53, text54, text55, text56, text57,
								   text58});
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
		    print_objects(window, {text1, text2, text3, text4, text5, 
							       text6, text7, text8, text9, text10,
							       text11, text12, text13, text14, text15,
							       text16, text17, text18, text19, text20,
							       text21, text22, text23, text24, text25,
							       text26, text27, text28, text29, text30,
							       text31, text32, text33, text34, text35,
							       text36, text37, text38, text39, text40,
							       text41, text42, text59, text60, text61,
								   text62, text63, text64, text65, text66,
								   text67, text68, text69, text70});
		    print_objects1(window, {line, line1, line2, line3, line4, line5, line6, line7, line8});
        }
        window.display();
    }
    return 0;
}
