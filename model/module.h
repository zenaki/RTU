#ifndef MODULE_H
#define MODULE_H

#include "util/utama.h"

#include <QFileDialog>
#include <QList>
#include <QString>
#include <QStringList>
#include <unistd.h>

class module
{
public:
    module();

    void write_module(struct t_module *tmodule);
    void update_setting(struct t_module *tmodule, QString addressModule);
    void update_module(struct t_module *tmodule, QString addressModule);
    void update_communication(struct t_module *tmodule, QString addressModule);
    void read_module(struct t_module *tmodule, QString addressModule);
    void save_as_module(struct t_module *tmodule, QString address);
};

#endif // MODULE_H
