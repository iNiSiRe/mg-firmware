#ifndef FIRMWARE_UNIT_H
#define FIRMWARE_UNIT_H


class Unit {

private:
    const bool registration = false;

protected:
    const int id;
    void register_on_server();

public:
    Unit(int id, bool registration = true);
};


#endif //FIRMWARE_UNIT_H
