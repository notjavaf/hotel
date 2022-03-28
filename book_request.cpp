#include "globals.h"
#include "room.h"
#include "hotel.h"
#include "book_request.h"

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
