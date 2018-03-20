#ifndef FIRMWARE_UNIT_H
#define FIRMWARE_UNIT_H


class Unit {

protected:
    const int id;
    void register_on_server();

public:
    Unit(const int id);
};


#endif //FIRMWARE_UNIT_H
