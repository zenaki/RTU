#ifndef MODULE_H
#define MODULE_H

#include "util/utama.h"

#include <QFileDialog>
#include <QList>
#include <QString>
#include <QStringList>
#include <unistd.h>

#include "model/cryp.h"
class cryp;

/**
 * @brief The module class
 */
class module
{
public:
    /**
     * @brief module
     */
    module();

    /**
     * @brief write_module
     * @param tmodule
     */
    void write_module(struct t_module *tmodule);
    /**
     * @brief read_module
     * @param tmodule
     * @param addressModule
     */
    void read_module(struct t_module *tmodule, QString addressModule);
    /**
     * @brief save_as_module
     * @param tmodule
     * @param address
     */
    void save_as_module(struct t_module *tmodule, QString address);
    /**
     * @brief validate_module
     * @param tmodule
     * @return
     */
    bool validate_module(t_module *tmodule);
};

#endif // MODULE_H
