#ifndef SERIAL_H
#define SERIAL_H

#include "util/utama.h"

class serial
{
public:
    serial();

    void write_data(struct t_module *tmodule);
    void read_data(struct t_module *tmodule, bool serial_set);
};

#endif // SERIAL_H
