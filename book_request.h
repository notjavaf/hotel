#pragma once

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
    void form(hotel& my_hotel);
};
