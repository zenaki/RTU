#include "formmodule.h"
#include "ui_formmodule.h"

#include <QtGui>

formModule::formModule(QWidget *parent, QString address, QSerialPort *SerialPort) :
    QDialog(parent),
    ui(new Ui::formModule)
{
    ui->setupUi(this);
    this->ui->tabWidget->setCurrentIndex(0);

    Address_Module = address;
    struct t_module tModule;
    module mod;
    mod.read_module(&tModule, Address_Module);
    NoSeri.sprintf("%s", tModule.serial_number);

    Serial_Com = new QSerialPort(this);
    Serial_Com = SerialPort;

    Main = new MainWindow(this);
    Serial = new serial();
    Setting = new setting();
//    busyForm = new QLightBoxWidget(parent);

    this->setInterface(address);
    this->ui->tab_alarm->setEnabled(false);
    this->ui->pbEdit->setHidden(true);
    this->ui->pbAddRow->setHidden(true);
    this->ui->pbDeleteRows->setHidden(true);
    this->ui->pbRefresh->setHidden(true);

    this->ui->pbSet->setText("Set All Input Settings");
    this->ui->pbSetChk->setText("Set Checked Input Settings");
    this->ui->pbGet->setText("Get All Input Settings");

    this->ui->tab_alarm->setHidden(true);

    progress_dialog = new ProgressDialog(this);
    progress_dialog->setModal(true);
}

formModule::~formModule()
{
    delete ui;
}

void formModule::setInterface(QString address)
{
    this->setInterface_Input(address);
    this->setInterface_Output(address);
    this->setInterface_Communication(address);
    this->setInterface_Environtment(address);
    this->setInterface_Sumber(address);
    this->setInterface_Alarm(address);
    this->setInterface_Data_Settings(address);
    this->setInterface_Data_Monitoring(address);
}

void formModule::setInterface_Input(QString address)
{
    struct t_module tModule;
    module mod;
    Address_Module = address;
    mod.read_module(&tModule, Address_Module);
    QStringList data = tModule.data;

    int rowInputDigital = tModule.jml_input_digital;
    int rowInputAnalog = tModule.jml_input_analog;

    this->ui->tabel_input->verticalHeader()->setHidden(true);
    this->ui->tabel_input->setColumnCount(8);
    this->ui->tabel_input->setColumnWidth(0, 25);
//    this->ui->tabel_input->setColumnWidth(1, 50);
    this->ui->tabel_input->setColumnWidth(2, 100);
    this->ui->tabel_input->setColumnWidth(3, 150);
//    this->ui->tabel_input->setColumnWidth(4, 100);
//    this->ui->tabel_input->setColumnWidth(5, 100);
//    this->ui->tabel_input->setColumnWidth(6, 100);
    this->ui->tabel_input->setColumnWidth(7, 125);
    this->ui->tabel_input->setRowCount(rowInputDigital + rowInputAnalog);

    SigMapReg_input = new QSignalMapper(this);
    SigMapState_input = new QSignalMapper(this);
    for (int i = 0; i < rowInputDigital + rowInputAnalog; i++) {
        check_input[i] = new QCheckBox(this);

        name_input[i] = new QLineEdit(this);
        name_input[i]->setValidator(new QRegExpValidator(QRegExp("^\\S{1,10}$"),this));

        type_input[i] = new QComboBox(this);
        type_input[i]->installEventFilter(this);
        if (i >= rowInputDigital) {
            type_input[i]->addItem("Analog Monita",250);
            type_input[i]->addItem("Analog Running Hours",230);
        } else
        {
            type_input[i]->addItem("RPM",1);
            type_input[i]->addItem("ON / OFF",2);
//            type_input[i]->addItem("Push Button",3);
            type_input[i]->addItem("Flow - X",6);
            type_input[i]->addItem("RPM - RH",7);
//            type_input[i]->addItem("Running Hours",8);
            type_input[i]->addItem("ON / OFF - RH",9);
        }

        calib_m[i] = new QDoubleSpinBox(this);
        calib_m[i]->installEventFilter(this);
        calib_m[i]->setAlignment(Qt::AlignRight);
        calib_m[i]->setRange(-99999,99999);

        calib_x[i] = new QDoubleSpinBox(this);
        calib_x[i]->installEventFilter(this);
        calib_x[i]->setAlignment(Qt::AlignRight);
        calib_x[i]->setRange(-99999,99999);

        reg_input[i] = new QComboBox(this);
        reg_input[i]->installEventFilter(this);
        SigMapReg_input->setMapping(reg_input[i], i);
        connect(reg_input[i],SIGNAL(currentIndexChanged(int)),SigMapReg_input,SLOT(map()));
        if (i < rowInputDigital) {
            for (int j = 0; j < PIN_DIGITAL; j++) {
                tmp = tModule.data.at(j); list = tmp.split(';');
                reg_input[i]->addItem(list.at(1));
            }
        } else {
            for (int j = PIN_DIGITAL; j < PIN_DIGITAL + PIN_ANALOG; j++) {
                tmp = tModule.data.at(j); list = tmp.split(';');
                reg_input[i]->addItem(list.at(1));
            }
        }

        state_input[i] = new QComboBox(this);
        state_input[i]->installEventFilter(this);
        state_input[i]->addItem("NOT ACTIVE",0);
        state_input[i]->addItem("ACTIVE",1);
        SigMapState_input->setMapping(state_input[i], i);
        connect(state_input[i], SIGNAL(currentIndexChanged(int)), SigMapState_input, SLOT(map()));
    }
    connect(SigMapReg_input,SIGNAL(mapped(int)),this,SLOT(reg_kanal_changed()));
    connect(SigMapState_input,SIGNAL(mapped(int)),this,SLOT(state_kanal_change(int)));

    tModule.data.clear();
    for (int i = 0; i < rowInputDigital + rowInputAnalog; i++) {
        for (int j = 0; j < data.length(); j++) {
            str = data.at(j);
            str2 = tModule.Input.at(i);
            list = str.split(';');
            list2 = str2.split(';');
            if (list.at(0) == list2.at(1)) {
                tModule.data.append(str);
            }
        }
    }

    str.clear();
    for (int i = 0; i < tModule.Input.length(); i++) {
        str.append(tModule.InputName.at(i)).append(";").append(tModule.Input.at(i)).append(";");
        tmp = tModule.data.at(i); list = tmp.split(';');
        str.append(list.at(1)).append(";").append(list.at(11)).append(";");
    }

    list = str.split(';');
    tModule.data = data;

    for(int i = 0; i < rowInputDigital + rowInputAnalog; i++){
        if (i >= rowInputDigital) {
            type = " - Analog";
        } else {
            type = " - Digital";
        }

        type.prepend(QString::number(i+1));

        name_input[i]->setText(list[i*8]);
        if (list.at((i*8)+3).toInt() == Analog_Monita) {indx = 0;}
        if (list.at((i*8)+3).toInt() == Analog_Running_Hours) {indx = 1;}
        if (list.at((i*8)+3).toInt() == RPM) {indx = 0;}
        if (list.at((i*8)+3).toInt() == ON_OFF) {indx = 1;}
        if (list.at((i*8)+3).toInt() == FLOW_X) {indx = 2;}
        if (list.at((i*8)+3).toInt() == RPM_RH) {indx = 3;}
        if (list.at((i*8)+3).toInt() == ON_OFF_RH) {indx = 4;}
        type_input[i]->setCurrentIndex(indx);
        calib_m[i]->setValue(list.at((i*8)+4).toFloat());
        calib_x[i]->setValue(list.at((i*8)+5).toFloat());
        if (i < rowInputDigital) {reg_input[i]->setCurrentText(list.at((i*8)+6));}
        else {reg_input[i]->setCurrentText(list.at((i*8)+6));}
        state_input[i]->setCurrentIndex(list.at((i*8)+7).toInt());

        this->ui->tabel_input->setCellWidget(i,0, check_input[i]);
        this->ui->tabel_input->setItem(i,1, new QTableWidgetItem(type));
        this->ui->tabel_input->setCellWidget(i,2, name_input[i]);
        this->ui->tabel_input->setCellWidget(i,3, type_input[i]);
        this->ui->tabel_input->setCellWidget(i,4, calib_m[i]);
        this->ui->tabel_input->setCellWidget(i,5, calib_x[i]);
        this->ui->tabel_input->setCellWidget(i,6, reg_input[i]);
        this->ui->tabel_input->setCellWidget(i,7, state_input[i]);
    }

    this->ui->tabel_input->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for (int i = 0; i < tModule.jml_input_digital; i++) {
        for (int j = 0; j < tModule.jml_input_digital; j++) {
            qobject_cast<QStandardItemModel *>(reg_input[i]->model())
                    ->item(reg_input[i]->findText(reg_input[j]->currentText()))
                    ->setEnabled(false);
        }
    }
    for (int i = tModule.jml_input_digital; i < tModule.jml_input_digital + tModule.jml_input_analog; i++) {
        for (int j = tModule.jml_input_digital; j < tModule.jml_input_digital + tModule.jml_input_analog; j++) {
            tmp = reg_input[j]->currentText();
            type = QString::number(reg_input[i]->findText(reg_input[j]->currentText()));
            qobject_cast<QStandardItemModel *>(reg_input[i]->model())
                    ->item(reg_input[i]->findText(reg_input[j]->currentText()))
                    ->setEnabled(false);
        }
    }
}

void formModule::setInterface_Output(QString address)
{
    struct t_module tModule;
    module mod;
    Address_Module = address;
    mod.read_module(&tModule, Address_Module);
    QString modules;

    int rowOutput = tModule.jml_output;
    QString type;

    this->ui->tabel_output->verticalHeader()->setHidden(true);
    this->ui->tabel_output->setColumnCount(5);
        this->ui->tabel_output->setColumnWidth(0, 25);
        this->ui->tabel_output->setColumnWidth(1, 100);
        this->ui->tabel_output->setColumnWidth(2, 125);
    //    this->ui->tabel_output->setColumnWidth(3, 100);
    //    this->ui->tabel_output->setColumnWidth(4, 75);
    this->ui->tabel_output->setRowCount(rowOutput);

    for (int i = 0; i < rowOutput; i++){
        check_output[i] = new QCheckBox(this);

//        name_output[i] = new QLineEdit(this);
//        name_output[i]->setValidator(new QRegExpValidator(QRegExp("^\\S{1,10}$"),this));

        state_output[i] = new QComboBox(this);
        state_output[i]->installEventFilter(this);
        state_output[i]->addItem("NOT ACTIVE");
        state_output[i]->addItem("ACTIVE");

        control[i] = new QComboBox(this);
        control[i]->installEventFilter(this);
        control[i]->addItem("LATCH");
        control[i]->addItem("LOGIC");
        control[i]->addItem("SCHEDULER");

        reg_output[i] = new QSpinBox(this);
        reg_output[i]->installEventFilter(this);
        reg_output[i]->setAlignment(Qt::AlignCenter);
        reg_output[i]->setRange(0,99999);
    }

    QString str;
    QString tmp;
    QStringList list;
    for (int i = 0; i < tModule.Output.length(); i++) {
        str.append(tModule.OutputName.at(i)).append(";")
                .append(tModule.Output.at(i)).append(";");
    }
    list = str.split(';');

    for(int i = 0; i < rowOutput; i++){
//        name_output[i]->setText(list[i*6]);
        state_output[i]->setCurrentIndex(list.at((i*6)+3).toInt());
        control[i]->setCurrentIndex(list.at((i*6)+4).toInt());
        reg_output[i]->setValue(list.at((i*6)+5).toInt());
//        reg_output[i]->setText(QString::number(i+1) + QString::number(i+1) + QString::number(i+1));

        type = " - Relay";
        type.prepend(list.at((i*6)+2));
        this->ui->tabel_output->setCellWidget(i,0, check_output[i]);
        this->ui->tabel_output->setItem(i,1, new QTableWidgetItem(type));
//        this->ui->tabel_output->setCellWidget(i,2, name_output[i]);
        this->ui->tabel_output->setCellWidget(i,2, state_output[i]);
        this->ui->tabel_output->setCellWidget(i,3, control[i]);
        this->ui->tabel_output->setCellWidget(i,4, reg_output[i]);
    }

    this->ui->tabel_output->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void formModule::setInterface_Communication(QString address)
{
    struct t_module tModule;
    module mod;
    Address_Module = address;
    mod.read_module(&tModule, Address_Module);
    QString modules;

    modules.sprintf("%s", tModule.name_gsm_1);
    this->ui->opt_1->setText(modules);
    modules.sprintf("%s", tModule.name_gsm_2);
    this->ui->opt_2->setText(modules);
    modules.sprintf("%s", tModule.device_name_gsm_1);
    this->ui->device_1->setText(modules);
    modules.sprintf("%s", tModule.device_name_gsm_2);
    this->ui->device_2->setText(modules);
    modules.sprintf("%s", tModule.status_gsm_1);
    this->ui->status_1->setText(modules);
    modules.sprintf("%s", tModule.status_gsm_2);
    this->ui->status_2->setText(modules);
    modules.sprintf("%s", tModule.com_gsm_1);
    this->ui->com_1->setText(modules);
    modules.sprintf("%s", tModule.com_gsm_2);
    this->ui->com_2->setText(modules);
    modules.sprintf("%s", tModule.number_gsm_1);
    this->ui->number_1->setText(modules);
    modules.sprintf("%s", tModule.number_gsm_2);
    this->ui->number_2->setText(modules);

    modules.sprintf("%s", tModule.user_gsm_1);
    this->ui->user_1->setText(modules);
    modules.sprintf("%s", tModule.apn_gsm_1);
    this->ui->apn_1->setText(modules);
    modules.sprintf("%s", tModule.passwd_gsm_1);
    this->ui->passwd_1->setText(modules);

    modules.sprintf("%s", tModule.user_gsm_2);
    this->ui->user_2->setText(modules);
    modules.sprintf("%s", tModule.apn_gsm_2);
    this->ui->apn_2->setText(modules);
    modules.sprintf("%s", tModule.passwd_gsm_2);
    this->ui->passwd_2->setText(modules);
}

void formModule::setInterface_Environtment(QString address)
{
    struct t_module tModule;
    module mod;
    Address_Module = address;
    mod.read_module(&tModule, Address_Module);
    QString modules;

    modules.sprintf("%s", tModule.module_name);
    this->ui->module_name->setText(modules);
    modules.sprintf("%s", tModule.serial_number);
    this->ui->serial_number->setText(modules);

//    modules.sprintf("%s", tModule.ip_address);
//    this->ui->ip_address->setText(modules);
    modules.sprintf("%s", tModule.server_address);
    this->ui->server_address->setText(modules);
    modules.sprintf("%s", tModule.file_address);
    this->ui->file_address->setText(modules);
    modules.sprintf("%s", tModule.status_webclient);
    this->ui->web_client->setText(modules);
    int s = 0; int m = 0; int h = 0; int d = 0;
    if (tModule.interval_relay <= 60) {
        this->ui->interval_relay->setText(QString::number(tModule.interval_relay) + " s");
    } else {
        s = tModule.interval_relay;
        m = s / 60;
        for (int i = 0; i < m; i++) s = s - 60;
        if (m > 60) {
            h = m / 60;
            for (int i = 0; i < h; i++) m = m - 60;
            if (h > 24) {
                d = h / 24;
                for (int i = 0; i < d; i++) h = h - 24;
                this->ui->interval_relay->setText(QString::number(d) + " d " + QString::number(h) + " h " + QString::number(m) + " m " + QString::number(s) + " s");
            } else {
                this->ui->interval_relay->setText(QString::number(h) + " h " + QString::number(m) + " m " + QString::number(s) + " s");
            }
        } else {
            this->ui->interval_relay->setText(QString::number(m) + " m " + QString::number(s) + " s");
        }
    }
    s = 0; m = 0; h = 0; d = 0;
    if (tModule.interval_data <= 60) {
        this->ui->interval_data->setText(QString::number(tModule.interval_data) + " s");
    } else {
        s = tModule.interval_data;
        m = s / 60;
        for (int i = 0; i < m; i++) s = s - 60;
        if (m > 60) {
            h = m / 60;
            for (int i = 0; i < h; i++) m = m - 60;
            if (h > 24) {
                d = h / 24;
                for (int i = 0; i < d; i++) h = h - 24;
                this->ui->interval_data->setText(QString::number(d) + " d " + QString::number(h) + " h " + QString::number(m) + " m " + QString::number(s) + " s");
            } else {
                this->ui->interval_data->setText(QString::number(h) + " h " + QString::number(m) + " m " + QString::number(s) + " s");
            }
        } else {
            this->ui->interval_data->setText(QString::number(m) + " m " + QString::number(s) + " s");
        }
    }
    modules.sprintf("%s", tModule.mode_http);
    this->ui->mode_http->setText(modules);
    this->ui->port->setText(QString::number(tModule.port));
    this->ui->utc->setText(QString::number(tModule.utc));
}

void formModule::setInterface_Sumber(QString address)
{
    struct t_module tModule;
    module mod;
    Address_Module = address;
    mod.read_module(&tModule, Address_Module);
    QString modules;

    QString str;
    QString tmp;
    QStringList list;

    int rowSource = tModule.jml_sumber;
    QString type;

    this->ui->tabel_sources->verticalHeader()->setHidden(true);
    this->ui->tabel_sources->setColumnCount(16);
    this->ui->tabel_sources->setColumnWidth(0, 25);
    this->ui->tabel_sources->setColumnWidth(1, 25);
    this->ui->tabel_sources->setColumnWidth(2, 75);
    this->ui->tabel_sources->setColumnWidth(3, 100);
    this->ui->tabel_sources->setColumnWidth(4, 125);
    this->ui->tabel_sources->setColumnWidth(5, 75);
    this->ui->tabel_sources->setColumnWidth(6, 125);
    this->ui->tabel_sources->setColumnWidth(7, 75);
    this->ui->tabel_sources->setColumnWidth(8, 75);
    this->ui->tabel_sources->setColumnWidth(9, 150);
    this->ui->tabel_sources->setColumnWidth(10, 125);
    this->ui->tabel_sources->setColumnWidth(11, 125);
    this->ui->tabel_sources->setColumnWidth(12, 75);
    this->ui->tabel_sources->setColumnWidth(13, 75);
    this->ui->tabel_sources->setColumnWidth(14, 75);
    this->ui->tabel_sources->setColumnWidth(15, 75);
    this->ui->tabel_sources->setRowCount(rowSource);

    SigMapDel_Source = new QSignalMapper(this);
    SigMap_length_source = new QSignalMapper(this);
    SigMap_tReg_source = new QSignalMapper(this);
    for (int i = 0; i < rowSource; i++){
        check_source[i] = new QCheckBox(this);
        delete_source[i] = new QPushButton("Del", this);
        SigMapDel_Source->setMapping(delete_source[i], i);
        connect(delete_source[i],SIGNAL(clicked()),SigMapDel_Source,SLOT(map()));

        name_source[i] = new QLineEdit(this);
        name_source[i]->setValidator(new QRegExpValidator(QRegExp("^\\S{1,10}$"),this));

        ip_source[i] = new QLineEdit(this);
        ip_source[i]->setAlignment(Qt::AlignCenter);
        ip_source[i]->setInputMask("000.000.000.000");

        port_source[i] = new QSpinBox(this);
        port_source[i]->installEventFilter(this);
        port_source[i]->setAlignment(Qt::AlignCenter);
        port_source[i]->setRange(0,99999);

        state_source[i] = new QComboBox(this);
        state_source[i]->installEventFilter(this);
        state_source[i]->addItem("NOT ACTIVE",0);
        state_source[i]->addItem("ACTIVE",1);

        type_source[i] = new QComboBox(this);
        type_source[i]->installEventFilter(this);
        type_source[i]->addItem("",0);
        type_source[i]->addItem("Native",1);
        type_source[i]->addItem("PM810",2);
        type_source[i]->addItem("Santer",3);
        type_source[i]->addItem("GWR",4);
        type_source[i]->addItem("PM5560",5);

        id_source[i] = new QSpinBox(this);
        id_source[i]->installEventFilter(this);
        id_source[i]->setAlignment(Qt::AlignCenter);
        id_source[i]->setRange(0,999);

        sensor_reg_source[i] = new QSpinBox(this);
        sensor_reg_source[i]->installEventFilter(this);
        sensor_reg_source[i]->setAlignment(Qt::AlignCenter);
        sensor_reg_source[i]->setRange(0,99999);

//        OffsetBase_source[i] = new QComboBox(this);
//        OffsetBase_source[i]->addItem("Offset",0);
//        OffsetBase_source[i]->addItem("Base",1);

        command_source[i] = new QComboBox(this);
        command_source[i]->installEventFilter(this);
        command_source[i]->addItem("Read Holding Register",0);
        command_source[i]->addItem("Write Holding Register",1);

        length_source[i] = new QComboBox(this);
        length_source[i]->installEventFilter(this);
        for (int j = 0; j <= tModule.data.length()+(DATA_PERIOD*2); j+=2) {
            length_source[i]->addItem(QString::number(j));
        }

        target_reg_source[i] = new QComboBox(this);
        target_reg_source[i]->installEventFilter(this);
        target_reg_source[i]->addItem("");
        for (int j = tModule.data.length()-(tModule.data.length()-(DATA_PERIOD*2)); j < tModule.data.length(); j++) {
            str = tModule.data.at(j); list = str.split(';');
            target_reg_source[i]->addItem(list.at(1));
        }

        swap_source[i] = new QComboBox(this);
        swap_source[i]->installEventFilter(this);
        swap_source[i]->addItem("Normal", 0);
        swap_source[i]->addItem("Swap Byte", 1);
        swap_source[i]->addItem("Swap Word", 2);
        swap_source[i]->addItem("Swap Byte & Word", 3);

        data_type_source[i] = new QComboBox(this);
        data_type_source[i]->installEventFilter(this);
        data_type_source[i]->addItem("Float", 0);
        data_type_source[i]->addItem("Integer", 1);

        data_bits_source[i] = new QComboBox(this);
        data_bits_source[i]->installEventFilter(this);
        data_bits_source[i]->addItem("16 bit", 0);
        data_bits_source[i]->addItem("32 bit", 1);
    }
    connect(SigMapDel_Source,SIGNAL(mapped(int)),this,SLOT(del_src_clicked(int)));

    for (int i = 0; i < rowSource; i++){
        type = "Source - ";
        type.append(QString::number(i+1));

        if (i <= tModule.sumber.length()) {
            if (this->checkFormula(tModule.sumber.at(i))) {
                str = tModule.sumber.at(i);
                list = str.split(';');
                name_source[i]->setText(list.at(1));
                ip_source[i]->setText(list.at(2));
                port_source[i]->setValue(list.at(3).toInt());
                state_source[i]->setCurrentIndex(list.at(4).toInt());
                type_source[i]->setCurrentIndex(list.at(5).toInt());
                id_source[i]->setValue(list.at(6).toInt());
                sensor_reg_source[i]->setValue(list.at(7).toInt());
//                OffsetBase_source[i]->setCurrentIndex(list.at(8).toInt());
                command_source[i]->setCurrentIndex(list.at(9).toInt());
                length_source[i]->setCurrentText(list.at(10));
                if (list[11] != "") {
                    target_reg_source[i]->setCurrentText(list.at(11));
                } else {
                    target_reg_source[i]->setCurrentIndex(0);
                }
                swap_source[i]->setCurrentIndex(list.at(12).toInt());
                data_type_source[i]->setCurrentIndex(list.at(13).toInt());
                data_bits_source[i]->setCurrentIndex(list.at(14).toInt());
            } else {
                str = tModule.sumber.at(i);
                list = str.split(';');
                name_source[i]->setText(list.at(1));
                ip_source[i]->setText(list.at(2));
                port_source[i]->setValue(list.at(3).toInt());
                state_source[i]->setCurrentIndex(list.at(4).toInt());
            }
        }
        SigMap_length_source->setMapping(length_source[i], i);
        connect(length_source[i],SIGNAL(currentIndexChanged(int)),SigMap_length_source,SLOT(map()));
        SigMap_tReg_source->setMapping(target_reg_source[i], i);
        connect(target_reg_source[i],SIGNAL(currentIndexChanged(int)),SigMap_tReg_source,SLOT(map()));

        this->ui->tabel_sources->setCellWidget(i,0, check_source[i]);
        this->ui->tabel_sources->setCellWidget(i,1, delete_source[i]);
        this->ui->tabel_sources->setItem(i,2, new QTableWidgetItem(type));
        this->ui->tabel_sources->setCellWidget(i,3, name_source[i]);
        this->ui->tabel_sources->setCellWidget(i,4, ip_source[i]);
        this->ui->tabel_sources->setCellWidget(i,5, port_source[i]);
        this->ui->tabel_sources->setCellWidget(i,6, state_source[i]);
        this->ui->tabel_sources->setCellWidget(i,7, type_source[i]);
        this->ui->tabel_sources->setCellWidget(i,8, id_source[i]);
        this->ui->tabel_sources->setCellWidget(i,9, command_source[i]);
        this->ui->tabel_sources->setCellWidget(i,10, sensor_reg_source[i]);
        this->ui->tabel_sources->setCellWidget(i,11, target_reg_source[i]);
        this->ui->tabel_sources->setCellWidget(i,12, length_source[i]);
        this->ui->tabel_sources->setCellWidget(i,13, swap_source[i]);
        this->ui->tabel_sources->setCellWidget(i,14, data_type_source[i]);
        this->ui->tabel_sources->setCellWidget(i,15, data_bits_source[i]);
    }
    connect(SigMap_length_source,SIGNAL(mapped(int)),this,SLOT(length_src_changed()));
    connect(SigMap_tReg_source,SIGNAL(mapped(int)),this,SLOT(tReg_src_changed()));
    this->ui->tabel_sources->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int val;
    for (int i = 0; i < tModule.jml_sumber; i++) {
        for (int j = 0; j < tModule.jml_sumber; j++) {
            for (int k = 0; k < length_source[i]->currentIndex(); k++) {
                qobject_cast<QStandardItemModel *>(target_reg_source[j]->model())
                        ->item(target_reg_source[i]->currentIndex()+k)
                        ->setEnabled(false);
            }
            if (target_reg_source[i]->currentIndex() == 0) {
                for (int k = 0; k <= tModule.data.length()+(DATA_PERIOD*2); k+=2) {
                    qobject_cast<QStandardItemModel *>(length_source[i]->model())
                            ->item(length_source[i]->findText(QString::number(k)))
                            ->setEnabled(false);
                }
            } else {
                val = 0;
                for (int k = 0; k < tModule.jml_sumber; k++) {
                    val = val + length_source[k]->currentIndex();
                }
                for (int k = 0; k < val; k++) {
                    qobject_cast<QStandardItemModel *>(length_source[j]->model())
                            ->item((tModule.data.length()+(DATA_PERIOD*2))/2-k)
                            ->setEnabled(false);
                }
            }
        }
    }
}

void formModule::setInterface_Alarm(QString address)
{
    struct t_module tModule;
    module mod;
    Address_Module = address;
    mod.read_module(&tModule, Address_Module);
    QString modules;
    QString type;
    QString str;
    QString tmp;
    QStringList list;
    QStringList data = tModule.data;
    QStringList temp = tModule.data;
    tModule.data.clear();
    for (int i = 0; i < this->ui->tabel_input->rowCount(); i++) {
        for (int j = 0; j < data.length(); j++) {
            str = data.at(j);
            str2 = tModule.Input.at(i);
            list = str.split(';');
            list2 = str2.split(';');
            if (list.at(0) == list2.at(1)) {
                tModule.data.append(str);
            }
        }
    }
    data = tModule.data;
    tModule.data = temp;
    mod.read_module(&tModule, Address_Module);
    int rowAlarm = tModule.jml_alarm;

    this->ui->tabel_alarm->verticalHeader()->setHidden(true);
    this->ui->tabel_alarm->setColumnCount(13);
    this->ui->tabel_alarm->setColumnWidth(0, 25);
    this->ui->tabel_alarm->setColumnWidth(1, 25);
//    this->ui->tabel_alarm->setColumnWidth(2, 75);
    this->ui->tabel_alarm->setColumnWidth(3, 100);
    this->ui->tabel_alarm->setColumnWidth(4, 175);
//    this->ui->tabel_alarm->setColumnWidth(5, 75);
    this->ui->tabel_alarm->setColumnWidth(6, 100);
//    this->ui->tabel_alarm->setColumnWidth(7, 50);
//    this->ui->tabel_alarm->setColumnWidth(8, 75);
//    this->ui->tabel_alarm->setColumnWidth(9, 75);
//    this->ui->tabel_alarm->setColumnWidth(10, 75);
//    this->ui->tabel_alarm->setColumnWidth(11, 75);
//    this->ui->tabel_alarm->setColumnWidth(12, 75);
    this->ui->tabel_alarm->setRowCount(rowAlarm);

    SigMapDel_alarm = new QSignalMapper(this);
    SigMapInput_alarm = new QSignalMapper(this);
    for (int i = 0; i < rowAlarm; i++){
        check_alarm[i] = new QCheckBox(this);
        delete_alarm[i] = new QPushButton("Del", this);
        SigMapDel_alarm->setMapping(delete_alarm[i], i);
        connect(delete_alarm[i],SIGNAL(clicked()),SigMapDel_alarm,SLOT(map()));

        name_alarm[i] = new QLineEdit(this);
        name_alarm[i]->setValidator(new QRegExpValidator(QRegExp("^\\S{1,10}$"),this));

        state_alarm[i] = new QComboBox(this);
        state_alarm[i]->addItem("NOT ACTIVE",0);
        state_alarm[i]->addItem("ACTIVE",1);

        input_alarm[i] = new QComboBox(this);
        input_alarm[i]->addItem("");
        for (int j = 0; j < tModule.jml_input_digital + tModule.jml_input_analog; j++) {
            if (j < tModule.jml_input_digital) {
                str = data.at(j); list = str.split(';');
                type = "Kanal " + list.at(0) + " - Digital - REG: " + list.at(1);
                input_alarm[i]->addItem(type);
                type.clear();
            } else {
                str = data.at(j); list = str.split(';');
                type = "Kanal " + list.at(0) + " - Analog - REG: " + list.at(1);
                input_alarm[i]->addItem(type);
                type.clear();
            }
        }

        output_alarm[i] = new QComboBox(this);
        for (int j = 0; j < tModule.jml_output; j++) {
            str = tModule.Output.at(j); list = str.split(';');
            type = "Relay " + list.at(1);
            output_alarm[i]->addItem(type);
            type.clear();
        }

        range_l[i] = new QLineEdit(this);
        range_l[i]->setAlignment(Qt::AlignCenter);
        range_l[i]->setValidator(new QDoubleValidator(-9999.999,9999.999,1,this));

        batas_ll[i] = new QLineEdit(this);
        batas_ll[i]->setAlignment(Qt::AlignCenter);
        batas_ll[i]->setValidator(new QDoubleValidator(-9999.999,9999.999,1,this));

        batas_l[i] = new QLineEdit(this);
        batas_l[i]->setAlignment(Qt::AlignCenter);
        batas_l[i]->setValidator(new QDoubleValidator(-9999.999,9999.999,1,this));

        batas_h[i] = new QLineEdit(this);
        batas_h[i]->setAlignment(Qt::AlignCenter);
        batas_h[i]->setValidator(new QDoubleValidator(-9999.999,9999.999,1,this));

        batas_hh[i] = new QLineEdit(this);
        batas_hh[i]->setAlignment(Qt::AlignCenter);
        batas_hh[i]->setValidator(new QDoubleValidator(-9999.999,9999.999,1,this));

        range_h[i] = new QLineEdit(this);
        range_h[i]->setAlignment(Qt::AlignCenter);
        range_h[i]->setValidator(new QDoubleValidator(-9999.999,9999.999,1,this));
    }
    connect(SigMapDel_alarm,SIGNAL(mapped(int)),this,SLOT(del_alrm_clicked(int)));

    for (int i = 0; i < rowAlarm; i++){
        type = "Alarm - ";
        if (i <= tModule.alarm.length()) {
            str = tModule.alarm.at(i);
            list = str.split(';');
            type.append(list[0]);
            name_alarm[i]->setText(list.at(1));
            input_alarm[i]->setCurrentIndex(list.at(2).toInt());
            output_alarm[i]->setCurrentIndex(list.at(3).toInt());
            state_alarm[i]->setCurrentIndex(list.at(4).toInt());
            range_l[i]->setText(list.at(5));
            batas_ll[i]->setText(list.at(6));
            batas_l[i]->setText(list.at(7));
            batas_h[i]->setText(list.at(8));
            batas_hh[i]->setText(list.at(9));
            range_h[i]->setText(list.at(10));
        }
        SigMapInput_alarm->setMapping(input_alarm[i], i);
        connect(input_alarm[i],SIGNAL(currentIndexChanged(int)),SigMapInput_alarm,SLOT(map()));

        this->ui->tabel_alarm->setCellWidget(i,0, check_alarm[i]);
        this->ui->tabel_alarm->setCellWidget(i,1, delete_alarm[i]);
        this->ui->tabel_alarm->setItem(i,2, new QTableWidgetItem(type));
        this->ui->tabel_alarm->setCellWidget(i,3, name_alarm[i]);
        this->ui->tabel_alarm->setCellWidget(i,4, input_alarm[i]);
        this->ui->tabel_alarm->setCellWidget(i,5, output_alarm[i]);
        this->ui->tabel_alarm->setCellWidget(i,6, state_alarm[i]);
        this->ui->tabel_alarm->setCellWidget(i,7, range_l[i]);
        this->ui->tabel_alarm->setCellWidget(i,8, batas_ll[i]);
        this->ui->tabel_alarm->setCellWidget(i,9, batas_l[i]);
        this->ui->tabel_alarm->setCellWidget(i,10, batas_h[i]);
        this->ui->tabel_alarm->setCellWidget(i,11, batas_hh[i]);
        this->ui->tabel_alarm->setCellWidget(i,12, range_h[i]);
    }
    connect(SigMapInput_alarm,SIGNAL(mapped(int)),this,SLOT(input_alrm_changed(int)));

    this->ui->tabel_alarm->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->ui->tabel_alarm->hideColumn(5);
    this->ui->tabel_alarm->hideColumn(5);

    for (int i = 0; i < tModule.jml_alarm; i++) {
        for (int j = 0; j < tModule.jml_alarm; j++) {
            qobject_cast<QStandardItemModel *>(input_alarm[i]->model())->item(input_alarm[i]->findText(input_alarm[j]->currentText()))->setEnabled(false);
        }
    }
}

void formModule::setInterface_Data_Settings(QString address)
{
    struct t_module tModule;
    module mod;
    Address_Module = address;
    mod.read_module(&tModule, Address_Module);
    QString modules;

    QString str;
    QString tmp;
    QStringList list;

    int rowData = tModule.jml_data;
    QString type;

    this->ui->tabel_data_s->verticalHeader()->setHidden(true);
    this->ui->tabel_data_s->setColumnCount(12);
    this->ui->tabel_data_s->setColumnWidth(0, 25);
    this->ui->tabel_data_s->setColumnWidth(1, 25);
    this->ui->tabel_data_s->setColumnWidth(2, 75);
    this->ui->tabel_data_s->setColumnWidth(3, 75);
//    this->ui->tabel_data_s->setColumnWidth(4, 75);
    this->ui->tabel_data_s->setColumnWidth(4, 75);
    this->ui->tabel_data_s->setColumnWidth(5, 100);
    this->ui->tabel_data_s->setColumnWidth(6, 100);
    this->ui->tabel_data_s->setColumnWidth(7, 100);
    this->ui->tabel_data_s->setColumnWidth(8, 100);
    this->ui->tabel_data_s->setColumnWidth(9, 100);
    this->ui->tabel_data_s->setColumnWidth(10, 100);
    this->ui->tabel_data_s->setColumnWidth(11, 125);
    this->ui->tabel_data_s->setRowCount(rowData);

    SigMapState_data_s = new QSignalMapper(this);
    for (int i = 0; i < rowData; i++){
        check_data_s[i] = new QCheckBox(this);

        id_data_s[i] = new QSpinBox(this);
        id_data_s[i]->installEventFilter(this);
        id_data_s[i]->setAlignment(Qt::AlignHCenter);
        id_data_s[i]->setRange(0,9999);

        name_data_s[i] = new QLineEdit(this);
        name_data_s[i]->setAlignment(Qt::AlignHCenter);
        name_data_s[i]->setValidator(new QRegExpValidator(QRegExp("^\\S{1,10}$"),this));

//        value_data_s[i] = new QDoubleSpinBox(this);
//        value_data_s[i]->setAlignment(Qt::AlignHCenter);
//        value_data_s[i]->setEnabled(false);
//        value_data_s[i]->setRange(-999999,999999);

        unit_data_s[i] = new QLineEdit(this);
        unit_data_s[i]->setAlignment(Qt::AlignHCenter);
        unit_data_s[i]->setValidator(new QRegExpValidator(QRegExp("^\\S{1,10}$"),this));

        range_l_data_s[i] = new QDoubleSpinBox(this);
        range_l_data_s[i]->installEventFilter(this);
        range_l_data_s[i]->setAlignment(Qt::AlignHCenter);
        range_l_data_s[i]->setRange(-999999,999999);

        border_ll_data_s[i] = new QDoubleSpinBox(this);
        border_ll_data_s[i]->installEventFilter(this);
        border_ll_data_s[i]->setAlignment(Qt::AlignHCenter);
        border_ll_data_s[i]->setRange(-999999,999999);

        border_l_data_s[i] = new QDoubleSpinBox(this);
        border_l_data_s[i]->installEventFilter(this);
        border_l_data_s[i]->setAlignment(Qt::AlignHCenter);
        border_l_data_s[i]->setRange(-999999,999999);

        border_h_data_s[i] = new QDoubleSpinBox(this);
        border_h_data_s[i]->installEventFilter(this);
        border_h_data_s[i]->setAlignment(Qt::AlignHCenter);
        border_h_data_s[i]->setRange(-999999,999999);

        border_hh_data_s[i] = new QDoubleSpinBox(this);
        border_hh_data_s[i]->installEventFilter(this);
        border_hh_data_s[i]->setAlignment(Qt::AlignHCenter);
        border_hh_data_s[i]->setRange(-999999,999999);

        range_h_data_s[i] = new QDoubleSpinBox(this);
        range_h_data_s[i]->installEventFilter(this);
        range_h_data_s[i]->setAlignment(Qt::AlignHCenter);
        range_h_data_s[i]->setRange(-999999,999999);

        state_data_s[i] = new QComboBox(this);
        state_data_s[i]->installEventFilter(this);
        state_data_s[i]->addItem("NOT ACTIVE");
        state_data_s[i]->addItem("ACTIVE");
        SigMapState_data_s->setMapping(state_data_s[i], i);
        connect(state_data_s[i], SIGNAL(currentIndexChanged(int)), SigMapState_data_s, SLOT(map()));
    }
    connect(SigMapState_data_s,SIGNAL(mapped(int)),this,SLOT(state_data_change(int)));

    for (int i = 0; i < rowData; i++){
        str = tModule.data.at(i);
        list = str.split(';');
        type = list[0];

        id_data_s[i]->setValue(list.at(1).toInt());
        name_data_s[i]->setText(list.at(2));
//        value_data_s[i]->setValue(list.at(3).toInt());
        unit_data_s[i]->setText(list.at(4));
        range_l_data_s[i]->setValue(list.at(5).toInt());
        border_ll_data_s[i]->setValue(list.at(6).toInt());
        border_l_data_s[i]->setValue(list.at(7).toInt());
        border_h_data_s[i]->setValue(list.at(8).toInt());
        border_hh_data_s[i]->setValue(list.at(9).toInt());
        range_h_data_s[i]->setValue(list.at(10).toInt());
        state_data_s[i]->setCurrentIndex(list.at(11).toInt());

        this->ui->tabel_data_s->setCellWidget(i,0, check_data_s[i]);
        this->ui->tabel_data_s->setItem(i,1, new QTableWidgetItem(type));
        this->ui->tabel_data_s->setCellWidget(i,2, id_data_s[i]);
        this->ui->tabel_data_s->setCellWidget(i,3, name_data_s[i]);
//        this->ui->tabel_data_s->setCellWidget(i,4, value_data_s[i]);
        this->ui->tabel_data_s->setCellWidget(i,4, unit_data_s[i]);
        this->ui->tabel_data_s->setCellWidget(i,5, range_l_data_s[i]);
        this->ui->tabel_data_s->setCellWidget(i,6, border_ll_data_s[i]);
        this->ui->tabel_data_s->setCellWidget(i,7, border_l_data_s[i]);
        this->ui->tabel_data_s->setCellWidget(i,8, border_h_data_s[i]);
        this->ui->tabel_data_s->setCellWidget(i,9, border_hh_data_s[i]);
        this->ui->tabel_data_s->setCellWidget(i,10, range_h_data_s[i]);
        this->ui->tabel_data_s->setCellWidget(i,11, state_data_s[i]);
    }

    this->ui->tabel_data_s->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void formModule::setInterface_Data_Monitoring(QString address)
{
    struct t_module tModule;
    module mod;
    Address_Module = address;
    mod.read_module(&tModule, Address_Module);
    QString modules;

    QString str;
    QString tmp;
    QStringList list;
    QStringList data = tModule.data;
    QStringList temp = tModule.data;
    tModule.data.clear();
    for (int i = 0; i < data.length(); i++) {
        str = data.at(i);
        list =str.split(';');
        if (list.at(11) == "1") {
            tModule.data.append(str);
        }
    }

    int rowData = tModule.data.length();
    QString type;

    this->ui->tabel_data_m->verticalHeader()->setHidden(true);
    this->ui->tabel_data_m->setColumnCount(5);
    this->ui->tabel_data_m->setColumnWidth(0, 25);
//    this->ui->tabel_data_m->setColumnWidth(1, 75);
    this->ui->tabel_data_m->setColumnWidth(2, 100);
    this->ui->tabel_data_m->setColumnWidth(3, 100);
    this->ui->tabel_data_m->setColumnWidth(4, 50);
    this->ui->tabel_data_m->setRowCount(rowData);

    for (int i = 0; i < rowData; i++){
        reg_data[i] = new QLabel(this);
        reg_data[i]->setAlignment(Qt::AlignCenter);

        name_data[i] = new QLabel(this);
        name_data[i]->setAlignment(Qt::AlignCenter);

        value_data[i] = new QLabel(this);
        value_data[i]->setAlignment(Qt::AlignCenter);

        unit_data[i] = new QLabel(this);
        unit_data[i]->setAlignment(Qt::AlignCenter);
    }

    for (int i = 0; i < rowData; i++){
        str = tModule.data.at(i);
        list = str.split(';');
        type = list[0];
        reg_data[i]->setText(list[1]);
        name_data[i]->setText(list[2]);
        value_data[i]->setText(list[3]);
        unit_data[i]->setText(list[4]);

        this->ui->tabel_data_m->setItem(i,0, new QTableWidgetItem(type));
        this->ui->tabel_data_m->setCellWidget(i,1, reg_data[i]);
        this->ui->tabel_data_m->setCellWidget(i,2, name_data[i]);
        this->ui->tabel_data_m->setCellWidget(i,3, value_data[i]);
        this->ui->tabel_data_m->setCellWidget(i,4, unit_data[i]);
    }

    this->ui->tabel_data_m->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tModule.data = temp;
}

bool formModule::checkFormula(QString data)
{
    QStringList list = data.split(';');
    if (list.length() > 6) {
        return true;
    } else {
        return false;
    }
}

void formModule::data_monitoring()
{
    struct t_module tModule;
    struct t_serial_settings tSerial;
    QStringList val_data;
    module mod;
    Address_Module = ".RTUdata/module/m_" + this->windowTitle() + ".dbe";
    mod.read_module(&tModule, Address_Module);

    QString str;
    QString tmp;
    QStringList list;

    if (Serial_Com->isOpen()) {
        QString Request = "0005\r\n";
        bool timeout = false;
//        while (!this->ui->tabWidget->currentIndex() == 6) {
//            Serial_Com->write(Request.toUtf8().data());
            Request.remove("\r\n");
            for (int i = 0; i < Request.length(); i++) {
                tmp = QChar(Request.at(i));
                Serial_Com->write(tmp.toUtf8().data());
                progress_dialog->delay(WAIT_WRITE);
            }
            Serial_Com->write("\r\n");

            QTime dieTime = QTime::currentTime().addMSecs(TIMEOUT);
            while (!progress_dialog->read_FinishRead()) {
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
                if (QTime::currentTime() >= dieTime && !timeout) {
                    timeout = true;
                    break;
                }
            }
//            work->delay(1000);
            if (!timeout) {
                Serial->read_parsing(&tSerial);
                val_data = tSerial.str_data_dat.split("*");
                progress_dialog->Get_Data(&tModule, val_data);

                QStringList data = tModule.data;
                QStringList temp = tModule.data;
                int data_count = 0;
                tModule.data.clear();
                for (int i = 0; i < data.length(); i++) {
                    str = data.at(i);
                    list =str.split(';');
                    if (list.length() == 12) {
                        if (list.at(11) == "1") {
                            tModule.data.append(str);
                            data_count++;
                        }
                    }
                }

                for (int i = 0; i < data_count; i++){
                    str = tModule.data.at(i);
                    list = str.split(';');
                    str = list[0];
                    reg_data[i]->setText(list[1]);
                    name_data[i]->setText(list[2]);
                    value_data[i]->setText(list[3]);
                    unit_data[i]->setText(list[4]);

                    this->ui->tabel_data_m->setItem(i,0, new QTableWidgetItem(str));
                    this->ui->tabel_data_m->setCellWidget(i,1, reg_data[i]);
                    this->ui->tabel_data_m->setCellWidget(i,2, name_data[i]);
                    this->ui->tabel_data_m->setCellWidget(i,3, value_data[i]);
                    this->ui->tabel_data_m->setCellWidget(i,4, unit_data[i]);
                }
                tModule.data = temp;
                mod.write_module(&tModule);
                cryp code; code.encryp(Address_Module);

            } else {
                timeout = false;
            }
//        }
    }
}

void formModule::on_tabWidget_tabBarClicked(int index)
{
    if (index == 2 || index == 3) {
        this->ui->pbSet->setHidden(true);
        this->ui->pbSetChk->setHidden(true);
        this->ui->pbGet->setHidden(true);
        this->ui->pbEdit->setHidden(false);
        this->ui->pbAddRow->setHidden(true);
        this->ui->pbDeleteRows->setHidden(true);
        this->ui->pbRefresh->setHidden(true);
    } else {
        this->ui->pbSet->setHidden(false);
        this->ui->pbSetChk->setHidden(false);
        this->ui->pbGet->setHidden(false);
        this->ui->pbEdit->setHidden(true);
        this->ui->pbRefresh->setHidden(true);
        if (index == 4 || index == 5) {
            this->ui->pbAddRow->setHidden(false);
            this->ui->pbDeleteRows->setHidden(false);
        } else {
            this->ui->pbAddRow->setHidden(true);
            this->ui->pbDeleteRows->setHidden(true);
        }
    }
    if (index == 7) {
        this->ui->pbSet->setHidden(true);
        this->ui->pbSetChk->setHidden(true);
        this->ui->pbSetAll->setHidden(true);
        this->ui->pbGet->setHidden(true);
        this->ui->pbGetAll->setHidden(true);
        this->ui->pbRefresh->setHidden(false);
    } else {
        this->ui->pbSetAll->setHidden(false);
        this->ui->pbGetAll->setHidden(false);
        this->ui->pbRefresh->setHidden(true);
    }
    this->ui->tabWidget->setCurrentIndex(index);

    if (index == 0) {
        this->ui->pbSet->setText("Set All Input Settings");
        this->ui->pbSetChk->setText("Set Checked Input Settings");
        this->ui->pbGet->setText("Get All Input Settings");
    } else if (index == 1) {
        this->ui->pbSet->setText("Set All Output Settings");
        this->ui->pbSetChk->setText("Set Checked Output Settings");
        this->ui->pbGet->setText("Get All Output Settings");
    } else if (index == 2) {
        this->ui->pbEdit->setText("Edit Communication");
    } else if (index == 3) {
        this->ui->pbEdit->setText("Edit Environtment");
    } else if (index == 4) {
        this->ui->pbSet->setText("Set Sources Settings");
        this->ui->pbSetChk->setText("Set Checked Sources Settings");
        this->ui->pbGet->setText("Get Sources Settings");
    } else if (index == 5) {
        this->ui->pbSet->setText("Set Alarm Settings");
        this->ui->pbSetChk->setText("Set Checked Alarm Settings");
        this->ui->pbGet->setText("Get Alarm Settings");
        this->setInterface_Alarm(".RTUdata/module/m_" + this->windowTitle() + ".dbe");
    } else if (index == 6) {
        this->ui->pbSet->setText("Set Data Settings");
        this->ui->pbSetChk->setText("Set Checked Data Settings");
        this->ui->pbGet->setText("Get Data Settings");
    }
}

void formModule::on_pbSetAll_clicked()
{
    struct t_module tModule;
    QString data[60];
    indx = 0;
    diff = 0;
    timeout = false;
    fail = false;
    cancel = false;

    module mod;
    mod.read_module(&tModule, Address_Module);

    /** ON MODULE FILE **/
    /** SET KANAL **/
    for (int i = 0; i < ui->tabel_input->rowCount(); i++)
    {
//        tModule.d_port[i].status_input = state_input[i]->currentIndex();
        tModule.d_port[i].calib_m = calib_m[i]->value();
        tModule.d_port[i].calib_x = calib_x[i]->value();

        if (i >= 6) {
            if (type_input[i]->currentIndex() == 0) {indx = 250;}
            if (type_input[i]->currentIndex() == 1) {indx = 230;}
            tModule.d_port[i].type_input = indx;

            data[i].sprintf("A;%d;%d;%.3f;%.3f", i+1
                            , indx
                            , tModule.d_port[i].calib_m
                            , tModule.d_port[i].calib_x);
        } else {
            if (type_input[i]->currentIndex() == 0) {indx = 1;}
            if (type_input[i]->currentIndex() == 1) {indx = 2;}
            if (type_input[i]->currentIndex() == 2) {indx = 6;}
            if (type_input[i]->currentIndex() == 3) {indx = 7;}
            if (type_input[i]->currentIndex() == 4) {indx = 9;}
            tModule.d_port[i].type_input = indx;

            data[i].sprintf("D;%d;%d;%.3f;%.3f", i+1
                            , indx
                            , tModule.d_port[i].calib_m
                            , tModule.d_port[i].calib_x);
        }
        tModule.Input[i] = data[i];
        tModule.InputName[i] = name_input[i]->text();

        data[i] = tModule.data.at(i);
        list = data[i].split(';');
        list[1] = reg_input[i]->currentText();
        list[2] = name_input[i]->text();
        list[11] = QString::number(state_input[i]->currentIndex());
        data[i].clear();
        data[i] = list[0];
        for (int j = 1; j < 12; j++) {
            data[i].append(";").append(list[j]);
        }
        tModule.data[i] = data[i];
    }

    /** SET RELAY **/
    for (int i = 0; i < ui->tabel_output->rowCount(); i++)
    {
        tModule.d_port[i].status_output = state_output[i]->currentIndex();
        tModule.d_port[i].control = control[i]->currentIndex();
        tModule.d_port[i].reg_output = reg_output[i]->value();

        data[i].sprintf("R;%d;%d;%d;%d", i+1
                     , tModule.d_port[i].status_output
                     , tModule.d_port[i].control
                     , tModule.d_port[i].reg_output);

        tModule.Output[i] = data[i];
//        tModule.OutputName[i] = name_output[i]->text();
    }

    /** SET SUMBER **/
    for (int i = 0; i < ui->tabel_sources->rowCount(); i++) {
        data[i] = QString::number(i+1) + ";" +
                  name_source[i]->text() + ";" +
                  ip_source[i]->text() + ";" +
                  QString::number(port_source[i]->value()) + ";" +
                  QString::number(state_source[i]->currentIndex()) + ";" +
                  QString::number(type_source[i]->currentIndex()) + ";" +
                  QString::number(id_source[i]->value()) + ";" +
                  QString::number(sensor_reg_source[i]->value()) + ";" +
//                  QString::number(OffsetBase_source[i]->currentIndex()) + ";" +
                  "0;" +
                  QString::number(command_source[i]->currentIndex()) + ";" +
                  length_source[i]->currentText() + ";" +
                  target_reg_source[i]->currentText() + ";" +
                  QString::number(swap_source[i]->currentIndex()) + ";" +
                  QString::number(data_type_source[i]->currentIndex()) + ";" +
                  QString::number(data_bits_source[i]->currentIndex());

        tModule.sumber[i] = data[i];
    }

    /** SET ALARM **/
    for (int i = 0; i < ui->tabel_alarm->rowCount(); i++) {
        data[i] = QString::number(i+1) + ";" +
                  name_alarm[i]->text() + ";" +
                  QString::number(input_alarm[i]->currentIndex()) + ";" +
                  QString::number(output_alarm[i]->currentIndex()) + ";" +
                  QString::number(state_alarm[i]->currentIndex()) + ";" +
                  range_l[i]->text() + ";" +
                  batas_ll[i]->text() + ";" +
                  batas_l[i]->text() + ";" +
                  batas_h[i]->text() + ";" +
                  batas_hh[i]->text() + ";" +
                  range_h[i]->text();

        tModule.alarm[i] = data[i];
        for (int j = 0; j < tModule.jml_data; j++) {
            str = tModule.data.at(j);
            list = str.split(';');
            if (input_alarm[i]->currentIndex() > 0 &&
                    input_alarm[i]->currentIndex() < tModule.jml_input_digital) {
                if (QString::number(input_alarm[i]->currentIndex()) == list.at(0)) {
                    str = list.at(0) + ";" +
                          list.at(1) + ";" +
                          name_alarm[i]->text() + ";" +
                          list.at(3) + ";" +
                          list.at(4) + ";" +
                          range_l[i]->text() + ";" +
                          batas_ll[i]->text() + ";" +
                          batas_l[i]->text() + ";" +
                          batas_h[i]->text() + ";" +
                          batas_hh[i]->text() + ";" +
                          range_h[i]->text() + ";" +
                          list.at(11); //QString::number(state_alarm[i]->currentIndex());

                    tModule.data[j] = str;
                }
            } else if (input_alarm[i]->currentIndex() > tModule.jml_input_digital &&
                       input_alarm[i]->currentIndex() < tModule.jml_input_digital + tModule.jml_input_analog) {
                if (QString::number(input_alarm[i]->currentIndex()+4) == list.at(0)) {
                    str = list.at(0) + ";" +
                          list.at(1) + ";" +
                          name_alarm[i]->text() + ";" +
                          list.at(3) + ";" +
                          list.at(4) + ";" +
                          range_l[i]->text() + ";" +
                          batas_ll[i]->text() + ";" +
                          batas_l[i]->text() + ";" +
                          batas_h[i]->text() + ";" +
                          batas_hh[i]->text() + ";" +
                          range_h[i]->text() + ";" +
                          list.at(11); //QString::number(state_alarm[i]->currentIndex());

                    tModule.data[j] = str;
                }
            }
        }
    }

    /** SET DATA **/
    for (int i = 0; i < ui->tabel_data_s->rowCount(); i++) {
        data[i] = QString::number(i+1) + ";" +
                  QString::number(id_data_s[i]->value()) + ";" +
                  name_data_s[i]->text() + ";" +
                  "0;" +
                  unit_data_s[i]->text() + ";" +
                  QString::number(range_l_data_s[i]->value()) + ";" +
                  QString::number(border_ll_data_s[i]->value()) + ";" +
                  QString::number(border_l_data_s[i]->value()) + ";" +
                  QString::number(border_h_data_s[i]->value()) + ";" +
                  QString::number(border_hh_data_s[i]->value()) + ";" +
                  QString::number(range_h_data_s[i]->value()) + ";" +
                  QString::number(state_data_s[i]->currentIndex());

        tModule.data[i] = data[i];
    }

    mod.write_module(&tModule);
    cryp code; code.encryp(Address_Module);

    /** ON BOARD **/
    if (Serial_Com->isOpen()) {
        this->writeLogFile();
        this->EnableButton(false);

        struct t_serial_settings tSerial;
        QStringList val_data;

        timeout = work->Request_ENV(Serial_Com, false);
        if (timeout) {fail = true;} else {
            Serial->read_parsing(&tSerial);
            val_data = tSerial.str_data_env.split(";");
            if (NoSeri == val_data.at(1)) {
                if (!fail) {
                    progress_dialog->show();
                    progress_dialog->setWindowTitle("Set All Configuration to board ..");
                    progress_dialog->Processing(Serial_Com, Address_Module, "0102;0103;0101;0104;0105;0005;0002;0001;0004");
                    cancel = progress_dialog->cancel;
                    progress_dialog->close();
                    mod.read_module(&tModule, Address_Module);
                }

                Message = "On-Board";

            } else {
                Message = "On-Local";
                if (val_data.at(1) != "") {
                    diff = 1;
                } else {
                    diff = 2;
                }
            }
        }
    } else {
        Message = "On-Local";
    }

//    if (reset == 1) {
//        Request = "reset\r\n";
//        Serial->write_data(Serial_Com, Request);
//        work->delay(jeda*5);
//    }

    mod.write_module(&tModule);
    code.encryp(Address_Module);

    this->setInterface(Address_Module);

    if (diff == 0 && !fail) {
        if (cancel) {
            Message.prepend("Setting ").append(" Canceled");
            QMessageBox::information(this, "Cancel!!", Message, 0, 0);
        } else {
            Message.prepend("Setting ").append(" Saved");
            QMessageBox::information(this, "Success!!", Message, 0, 0);
        }
    } else if (diff == 1 && !fail) {
        Message.prepend("Setting ").append(" Error !!");
        Message.append("\n\n Different Serial Number !!!");
        QMessageBox::information(this, "Error!!", Message, 0, 0);
    } else if (diff == 2 && !fail) {
        Message.prepend("Setting ").append(" Error !!");
        Message.append("\nBoard Serial Number is not exist ..");
        QMessageBox::information(this, "Error!!", Message, 0, 0);
    }

    if (fail) {
        QMessageBox::information(this, "Serial Communication", STR_TIMEOUT, 0, 0);
    }

    this->EnableButton(true);
}

void formModule::on_pbSet_clicked()
{
    struct t_module tModule;
    QString data[60];
    indx = 0;
    diff = 0;
    reset = 0;
    timeout = false;
    fail = false;

    module mod;
    mod.read_module(&tModule, Address_Module);

    /** ON MODULE FILE **/
    if (this->ui->tabWidget->currentIndex() == 0) {
        /** SET INPUT **/
        for (int i = 0; i < ui->tabel_input->rowCount(); i++)
        {
            tModule.d_port[i].calib_m = calib_m[i]->value();
            tModule.d_port[i].calib_x = calib_x[i]->value();

            if (i >= 6) {
                if (type_input[i]->currentIndex() == 0) {indx = 250;}
                if (type_input[i]->currentIndex() == 1) {indx = 230;}
                tModule.d_port[i].type_input = indx;

                data[i].sprintf("A;%d;%d;%.3f;%.3f", i+1
                                , indx
                                , tModule.d_port[i].calib_m
                                , tModule.d_port[i].calib_x);
            } else {
                if (type_input[i]->currentIndex() == 0) {indx = 1;}
                if (type_input[i]->currentIndex() == 1) {indx = 2;}
                if (type_input[i]->currentIndex() == 2) {indx = 6;}
                if (type_input[i]->currentIndex() == 3) {indx = 7;}
                if (type_input[i]->currentIndex() == 4) {indx = 9;}
                tModule.d_port[i].type_input = indx;

                data[i].sprintf("D;%d;%d;%.3f;%.3f", i+1
                                , indx
                                , tModule.d_port[i].calib_m
                                , tModule.d_port[i].calib_x);
            }
            tModule.Input[i] = data[i];
            tModule.InputName[i] = name_input[i]->text();

            data[i] = tModule.data.at(i);
            list = data[i].split(';');
            list[1] = reg_input[i]->currentText();
            list[2] = name_input[i]->text();
            list[11] = QString::number(state_input[i]->currentIndex());
            data[i].clear();
            data[i] = list[0];
            for (int j = 1; j < 12; j++) {
                data[i].append(";").append(list[j]);
            }
            tModule.data[i] = data[i];
        }
    } else if (this->ui->tabWidget->currentIndex() == 1) {
        /** SET OUTPUT **/
        for (int i = 0; i < ui->tabel_output->rowCount(); i++)
        {
            tModule.d_port[i].status_output = state_output[i]->currentIndex();
            tModule.d_port[i].control = control[i]->currentIndex();
            tModule.d_port[i].reg_output = reg_output[i]->value();

            data[i].sprintf("R;%d;%d;%d;%d", i+1
                         , tModule.d_port[i].status_output
                         , tModule.d_port[i].control
                         , tModule.d_port[i].reg_output);

            tModule.Output[i] = data[i];
//            tModule.OutputName[i] = name_output[i]->text();
        }
    } else if (this->ui->tabWidget->currentIndex() == 4) {
        /** SET SUMBER **/
        for (int i = 0; i < ui->tabel_sources->rowCount(); i++) {
            data[i] = QString::number(i+1) + ";" +
                      name_source[i]->text() + ";" +
                      ip_source[i]->text() + ";" +
                      QString::number(port_source[i]->value()) + ";" +
                      QString::number(state_source[i]->currentIndex()) + ";" +
                      QString::number(type_source[i]->currentIndex()) + ";" +
                      QString::number(id_source[i]->value()) + ";" +
                      QString::number(sensor_reg_source[i]->value()) + ";" +
//                      QString::number(OffsetBase_source[i]->currentIndex()) + ";" +
                      "0;" +
                      QString::number(command_source[i]->currentIndex()) + ";" +
                      length_source[i]->currentText() + ";" +
                      target_reg_source[i]->currentText() + ";" +
                      QString::number(swap_source[i]->currentIndex()) + ";" +
                      QString::number(data_type_source[i]->currentIndex()) + ";" +
                      QString::number(data_bits_source[i]->currentIndex());

            tModule.sumber[i] = data[i];
        }
    } else if (this->ui->tabWidget->currentIndex() == 5) {
        /** SET ALARM **/
        for (int i = 0; i < ui->tabel_alarm->rowCount(); i++) {
            data[i] = QString::number(i+1) + ";" +
                      name_alarm[i]->text() + ";" +
                      QString::number(input_alarm[i]->currentIndex()) + ";" +
                      QString::number(output_alarm[i]->currentIndex()) + ";" +
                      QString::number(state_alarm[i]->currentIndex()) + ";" +
                      range_l[i]->text() + ";" +
                      batas_ll[i]->text() + ";" +
                      batas_l[i]->text() + ";" +
                      batas_h[i]->text() + ";" +
                      batas_hh[i]->text() + ";" +
                      range_h[i]->text();

            tModule.alarm[i] = data[i];
            for (int j = 0; j < tModule.jml_data; j++) {
                str = tModule.data.at(j);
                list = str.split(';');
                if (input_alarm[i]->currentIndex() > 0 &&
                        input_alarm[i]->currentIndex() <= tModule.jml_input_digital) {
                    if (QString::number(input_alarm[i]->currentIndex()) == list.at(0)) {
                        str = list.at(0) + ";" +
                              list.at(1) + ";" +
                              name_alarm[i]->text() + ";" +
                              list.at(3) + ";" +
                              list.at(4) + ";" +
                              range_l[i]->text() + ";" +
                              batas_ll[i]->text() + ";" +
                              batas_l[i]->text() + ";" +
                              batas_h[i]->text() + ";" +
                              batas_hh[i]->text() + ";" +
                              range_h[i]->text() + ";" +
                              list.at(11); //QString::number(state_alarm[i]->currentIndex());

                        tModule.data[j] = str;
                    }
                } else if (input_alarm[i]->currentIndex() > tModule.jml_input_digital &&
                           input_alarm[i]->currentIndex() <= tModule.jml_input_digital + tModule.jml_input_analog) {
                    if (QString::number(input_alarm[i]->currentIndex()+4) == list.at(0)) {
                        str = list.at(0) + ";" +
                              list.at(1) + ";" +
                              name_alarm[i]->text() + ";" +
                              list.at(3) + ";" +
                              list.at(4) + ";" +
                              range_l[i]->text() + ";" +
                              batas_ll[i]->text() + ";" +
                              batas_l[i]->text() + ";" +
                              batas_h[i]->text() + ";" +
                              batas_hh[i]->text() + ";" +
                              range_h[i]->text() + ";" +
                              list.at(11); //QString::number(state_alarm[i]->currentIndex());

                        tModule.data[j] = str;
                    }
                }
            }
        }
    } else if (this->ui->tabWidget->currentIndex() == 6) {
        /** SET DATA **/
        for (int i = 0; i < ui->tabel_data_s->rowCount(); i++) {
            data[i] = QString::number(i+1) + ";" +
                      QString::number(id_data_s[i]->value()) + ";" +
                      name_data_s[i]->text() + ";" +
                      "0;" +
                      unit_data_s[i]->text() + ";" +
                      QString::number(range_l_data_s[i]->value()) + ";" +
                      QString::number(border_ll_data_s[i]->value()) + ";" +
                      QString::number(border_l_data_s[i]->value()) + ";" +
                      QString::number(border_h_data_s[i]->value()) + ";" +
                      QString::number(border_hh_data_s[i]->value()) + ";" +
                      QString::number(range_h_data_s[i]->value()) + ";" +
                      QString::number(state_data_s[i]->currentIndex());

            tModule.data[i] = data[i];
        }
    }

    mod.write_module(&tModule);
    cryp code; code.encryp(Address_Module);

    /** ON BOARD **/
    if (Serial_Com->isOpen()) {
        this->writeLogFile();
        this->EnableButton(false);

        struct t_serial_settings tSerial;
        QString Request; QStringList val_data;

        timeout = work->Request_ENV(Serial_Com, false);
        if (timeout) {fail = true;} else {
            Serial->read_parsing(&tSerial);
            val_data = tSerial.str_data_env.split(";");
            if (NoSeri == val_data.at(1)) {
                if (this->ui->tabWidget->currentIndex() == 0) {
                    Request = "0102";
                } else if (this->ui->tabWidget->currentIndex() == 1) {
                    Request = "0103";
                } else if (this->ui->tabWidget->currentIndex() == 2) {
                    Request = "0101";
                } else if (this->ui->tabWidget->currentIndex() == 3) {
                    Request = "0100";
                } else if (this->ui->tabWidget->currentIndex() == 4) {
                    Request = "0104";
                } else if (this->ui->tabWidget->currentIndex() == 5) {

                } else if (this->ui->tabWidget->currentIndex() == 6) {
                    Request = "0105";
                }
//                work->Reset_Board(busyForm, "Reset Board ...", Serial_Com);
                if (this->ui->tabWidget->currentIndex() <= 1) {
                    Request = Request + ";0005;0002";
                } else if (this->ui->tabWidget->currentIndex() == 2) {
                    Request = Request + ";0001";
                } else if (this->ui->tabWidget->currentIndex() == 3) {
                    Request = Request + ";0000";
                } else if (this->ui->tabWidget->currentIndex() == 4) {
                    Request = Request + ";0004;0005";
                } else if (this->ui->tabWidget->currentIndex() == 5) {

                } else if (this->ui->tabWidget->currentIndex() == 6) {
                    Request = Request + ";0005";
                }

                progress_dialog->show();
                progress_dialog->setWindowTitle("Set " + Message + "to board");
                progress_dialog->Processing(Serial_Com, Address_Module, Request);
                progress_dialog->close();
                mod.read_module(&tModule, Address_Module);

                Message = "On-Board";

            } else {
                Message = "On-Local";
                if (val_data.at(1) != "") {
                    diff = 1;
                } else {
                    diff = 2;
                }
            }
        }
    } else {
        Message = "On-Local";
    }

    if (reset == 1) {
//        Request = "reset\r\n";
//        Serial->write_data(Serial_Com, Request);
//        work->delay(jeda*5);
    }

    mod.write_module(&tModule);
    code.encryp(Address_Module);

    this->setInterface(Address_Module);

    if (diff == 0 && !fail) {
        if (this->ui->tabWidget->currentIndex() == 0) {
            Message.prepend("Input Channel ");
        } else if (this->ui->tabWidget->currentIndex() == 1) {
            Message.prepend("Output Channel ");
        } else if (this->ui->tabWidget->currentIndex() == 2) {
            Message.prepend("SIM Configuration ");
        } else if (this->ui->tabWidget->currentIndex() == 3) {
            Message.prepend("Environtment ");
        } else if (this->ui->tabWidget->currentIndex() == 4) {
            Message.prepend("Sources ");
        } else if (this->ui->tabWidget->currentIndex() == 5) {
            Message.prepend("Alarm ");
        } else if (this->ui->tabWidget->currentIndex() == 6) {
            Message.prepend("Data ");
        }
        Message.prepend("Setting ").append(" Saved");
        QMessageBox::information(this, "Success!!", Message, 0, 0);
    } else if (diff == 1 && !fail) {
        Message.prepend("Setting ").append(" Saved");
        Message.append("\n\n Different Serial Number !!!");
        QMessageBox::information(this, "Success!!", Message, 0, 0);
    } else if (diff == 2 && !fail) {
        Message.prepend("Setting ").append(" Saved");
        Message.append("\nBoard is not have Serial Number ..");
        QMessageBox::information(this, "Success!!", Message, 0, 0);
    }

    if (fail) {
        QMessageBox::information(this, "Serial Communication", STR_TIMEOUT, 0, 0);
    }

    this->EnableButton(true);
}

void formModule::on_pbSetChk_clicked()
{
    struct t_module tModule;
    QString data[60];
    indx = 0;
    diff = 0;
    reset = 0;
    timeout = false;
    fail = false;
    int checked = 0;
    Request.clear();

    module mod;
    mod.read_module(&tModule, Address_Module);

    /** ON MODULE FILE **/
    if (this->ui->tabWidget->currentIndex() == 0) {
        /** SET INPUT **/
        for (int i = 0; i < ui->tabel_input->rowCount(); i++) {
            if (check_input[i]->isChecked()) {
                checked++;
                tModule.d_port[i].calib_m = calib_m[i]->value();
                tModule.d_port[i].calib_x = calib_x[i]->value();

                if (i >= 6) {
                    if (type_input[i]->currentIndex() == 0) {indx = 250;}
                    if (type_input[i]->currentIndex() == 1) {indx = 230;}
                    tModule.d_port[i].type_input = indx;

                    data[i].sprintf("A;%d;%d;%.3f;%.3f", i+1
                                    , indx
                                    , tModule.d_port[i].calib_m
                                    , tModule.d_port[i].calib_x);
                } else {
                    if (type_input[i]->currentIndex() == 0) {indx = 1;}
                    if (type_input[i]->currentIndex() == 1) {indx = 2;}
                    if (type_input[i]->currentIndex() == 2) {indx = 6;}
                    if (type_input[i]->currentIndex() == 3) {indx = 7;}
                    if (type_input[i]->currentIndex() == 4) {indx = 9;}
                    tModule.d_port[i].type_input = indx;

                    data[i].sprintf("D;%d;%d;%.3f;%.3f", i+1
                                    , indx
                                    , tModule.d_port[i].calib_m
                                    , tModule.d_port[i].calib_x);
                }
                tModule.Input[i] = data[i];
                tModule.InputName[i] = name_input[i]->text();

                data[i] = tModule.data.at(i);
                list = data[i].split(';');
                list[1] = reg_input[i]->currentText();
                list[2] = name_input[i]->text();
                list[11] = QString::number(state_input[i]->currentIndex());
                data[i].clear();
                data[i] = list[0];
                for (int j = 1; j < 12; j++) {
                    data[i].append(";").append(list[j]);
                }
                tModule.data[i] = data[i];
            }
        }
    } else if (this->ui->tabWidget->currentIndex() == 1) {
        /** SET OUTPUT **/
        for (int i = 0; i < ui->tabel_output->rowCount(); i++) {
            if (check_output[i]->isChecked()) {
                checked++;
                tModule.d_port[i].status_output = state_output[i]->currentIndex();
                tModule.d_port[i].control = control[i]->currentIndex();
                tModule.d_port[i].reg_output = reg_output[i]->value();

                data[i].sprintf("R;%d;%d;%d;%d", i+1
                             , tModule.d_port[i].status_output
                             , tModule.d_port[i].control
                             , tModule.d_port[i].reg_output);

                tModule.Output[i] = data[i];
//                tModule.OutputName[i] = name_output[i]->text();
            }
        }
    } else if (this->ui->tabWidget->currentIndex() == 4) {
        /** SET SUMBER **/
        for (int i = 0; i < ui->tabel_sources->rowCount(); i++) {
            if (check_source[i]->isChecked()) {
                checked++;
                data[i] = QString::number(i+1) + ";" +
                          name_source[i]->text() + ";" +
                          ip_source[i]->text() + ";" +
                          QString::number(port_source[i]->value()) + ";" +
                          QString::number(state_source[i]->currentIndex()) + ";" +
                          QString::number(type_source[i]->currentIndex()) + ";" +
                          QString::number(id_source[i]->value()) + ";" +
                          QString::number(sensor_reg_source[i]->value()) + ";" +
//                          QString::number(OffsetBase_source[i]->currentIndex()) + ";" +
                          "0;" +
                          QString::number(command_source[i]->currentIndex()) + ";" +
                          length_source[i]->currentText() + ";" +
                          target_reg_source[i]->currentText() + ";" +
                          QString::number(swap_source[i]->currentIndex()) + ";" +
                          QString::number(data_type_source[i]->currentIndex()) + ";" +
                          QString::number(data_bits_source[i]->currentIndex());

                tModule.sumber[i] = data[i];
            }
        }
    } else if (this->ui->tabWidget->currentIndex() == 5) {
        /** SET ALARM **/
        for (int i = 0; i < ui->tabel_alarm->rowCount(); i++) {
            if (check_alarm[i]->isChecked()) {
                checked++;
                data[i] = QString::number(i+1) + ";" +
                          name_alarm[i]->text() + ";" +
                          QString::number(input_alarm[i]->currentIndex()) + ";" +
                          QString::number(output_alarm[i]->currentIndex()) + ";" +
                          QString::number(state_alarm[i]->currentIndex()) + ";" +
                          range_l[i]->text() + ";" +
                          batas_ll[i]->text() + ";" +
                          batas_l[i]->text() + ";" +
                          batas_h[i]->text() + ";" +
                          batas_hh[i]->text() + ";" +
                          range_h[i]->text();

                tModule.alarm[i] = data[i];
                for (int j = 0; j < tModule.jml_data; j++) {
                    str = tModule.data.at(j);
                    list = str.split(';');
                    if (input_alarm[i]->currentIndex() > 0 &&
                        input_alarm[i]->currentIndex() <= tModule.jml_input_digital) {
                       if (QString::number(input_alarm[i]->currentIndex()) == list.at(0)) {
                            str = list.at(0) + ";" +
                                  list.at(1) + ";" +
                                  name_alarm[i]->text() + ";" +
                                  list.at(3) + ";" +
                                  list.at(4) + ";" +
                                  range_l[i]->text() + ";" +
                                  batas_ll[i]->text() + ";" +
                                  batas_l[i]->text() + ";" +
                                  batas_h[i]->text() + ";" +
                                  batas_hh[i]->text() + ";" +
                                  range_h[i]->text() + ";" +
                                  list.at(11); //QString::number(state_alarm[i]->currentIndex());

                            tModule.data[j] = str;
                        }
                    } else if (input_alarm[i]->currentIndex() > tModule.jml_input_digital &&
                               input_alarm[i]->currentIndex() <= tModule.jml_input_digital + tModule.jml_input_analog) {
                        if (QString::number(input_alarm[i]->currentIndex()+4) == list.at(0)) {
                            str = list.at(0) + ";" +
                                  list.at(1) + ";" +
                                  name_alarm[i]->text() + ";" +
                                  list.at(3) + ";" +
                                  list.at(4) + ";" +
                                  range_l[i]->text() + ";" +
                                  batas_ll[i]->text() + ";" +
                                  batas_l[i]->text() + ";" +
                                  batas_h[i]->text() + ";" +
                                  batas_hh[i]->text() + ";" +
                                  range_h[i]->text() + ";" +
                                  list.at(11); //QString::number(state_alarm[i]->currentIndex());

                            tModule.data[j] = str;
                        }
                    }
                }
            }
        }
    } else if (this->ui->tabWidget->currentIndex() == 6) {
        /** SET DATA **/
        for (int i = 0; i < ui->tabel_data_s->rowCount(); i++) {
            if (check_data_s[i]->isChecked()) {
                checked++;
                data[i] = QString::number(i+1) + ";" +
                          QString::number(id_data_s[i]->value()) + ";" +
                          name_data_s[i]->text() + ";" +
                          "0;" +
                          unit_data_s[i]->text() + ";" +
                          QString::number(range_l_data_s[i]->value()) + ";" +
                          QString::number(border_ll_data_s[i]->value()) + ";" +
                          QString::number(border_l_data_s[i]->value()) + ";" +
                          QString::number(border_h_data_s[i]->value()) + ";" +
                          QString::number(border_hh_data_s[i]->value()) + ";" +
                          QString::number(range_h_data_s[i]->value()) + ";" +
                          QString::number(state_data_s[i]->currentIndex());

                tModule.data[i] = data[i];
            }
        }
    }

    mod.write_module(&tModule);
    cryp code; code.encryp(Address_Module);

    /** ON BOARD **/
    if (Serial_Com->isOpen()) {
        this->writeLogFile();
        this->EnableButton(false);

        struct t_serial_settings tSerial;
        QStringList val_data;

        timeout = work->Request_ENV(Serial_Com, false);
        if (timeout) {fail = true;} else {
            Serial->read_parsing(&tSerial);
            val_data = tSerial.str_data_env.split(";");
            if (NoSeri == val_data.at(1)) {
                if (this->ui->tabWidget->currentIndex() == 0) {
                    for (int i = 0; i < ui->tabel_input->rowCount(); i++) {
                        if (check_input[i]->isChecked()) {
                            checked++;
                            str = tModule.Input.at(i); list = str.split(';');
                            if (!progress_dialog->isActiveWindow()) progress_dialog->show();
                            progress_dialog->setWindowTitle("Set Input to board");
                            if (i < 6) {
                                progress_dialog->Processing(Serial_Com, Address_Module, "0102;0105", QString::number(i) + ";" + QString::number(i));
                            } else {
                                progress_dialog->Processing(Serial_Com, Address_Module, "0102;0105", QString::number(i) + ";" + QString::number(i));
                            }
                        }
                    }
                } else if (this->ui->tabWidget->currentIndex() == 1) {
                    for (int i = 0; i < ui->tabel_output->rowCount(); i++) {
                        if (check_output[i]->isChecked()) {
                            checked++;
                            if (!progress_dialog->isActiveWindow()) progress_dialog->show();
                            progress_dialog->setWindowTitle("Set Output to board");
                            progress_dialog->Processing(Serial_Com, Address_Module, "0103", QString::number(i));
                        }
                    }
                } else if (this->ui->tabWidget->currentIndex() == 4) {
                    for (int i = 0; i < ui->tabel_sources->rowCount(); i++) {
                        if (check_source[i]->isChecked()) {
                            checked++;
                            if (!progress_dialog->isActiveWindow()) progress_dialog->show();
                            progress_dialog->setWindowTitle("Set Sources to board");
                            progress_dialog->Processing(Serial_Com, Address_Module, "0104", QString::number(i));
                        }
                    }
                } else if (this->ui->tabWidget->currentIndex() == 5) {

                } else if (this->ui->tabWidget->currentIndex() == 6) {
                    for (int i = 0; i < ui->tabel_data_s->rowCount(); i++) {
                        if (check_data_s[i]->isChecked()) {
                            checked++;
                            if (!progress_dialog->isActiveWindow()) progress_dialog->show();
                            progress_dialog->setWindowTitle("Set Data to board");
                            progress_dialog->Processing(Serial_Com, Address_Module, "0105", QString::number(i));
                        }
                    }
                }

                if (checked != 0) {
//                    progress_dialog->close();
                    if (this->ui->tabWidget->currentIndex() <= 1) {
                        Message = "I/O ";
                        Request = "0005;0002";
                    } else if (this->ui->tabWidget->currentIndex() == 2) {
                        Message = "SIM Configuration ";
                        Request = "0001";
                    } else if (this->ui->tabWidget->currentIndex() == 3) {
                        Message = "Environtment ";
                        Request = "0000";
                    } else if (this->ui->tabWidget->currentIndex() == 4) {
                        Message = "Sources ";
                        Request = "0005;0004";
                    } else if (this->ui->tabWidget->currentIndex() == 5) {
                        Message = "Alarm ";
                    } else if (this->ui->tabWidget->currentIndex() == 6) {
                        Message = "Data ";
                        Request = "0005";
                    }
//                    progress_dialog->show();
                    progress_dialog->setWindowTitle("Get " + Message + "from board");
                    progress_dialog->Processing(Serial_Com, Address_Module, Request);
                    progress_dialog->close();
                    mod.read_module(&tModule, Address_Module);
                }
                Message = "On-Board";

            } else {
                Message = "On-Local";
                if (val_data.at(1) != "") {
                    diff = 1;
                } else {
                    diff = 2;
                }
            }
        }
    } else {
        Message = "On-Local";
    }

    if (reset == 1) {
//        Request = "reset\r\n";
//        Serial->write_data(Serial_Com, Request);
//        work->delay(jeda*5);
    }

    mod.write_module(&tModule);
    code.encryp(Address_Module);

//    this->setInterface(Address_Module);
    if (checked != 0) {
        if (diff == 0 && !fail) {
            if (this->ui->tabWidget->currentIndex() == 0) {
                Message.prepend("Input Channel ");
            } else if (this->ui->tabWidget->currentIndex() == 1) {
                Message.prepend("Output Channel ");
            } else if (this->ui->tabWidget->currentIndex() == 2) {
                Message.prepend("SIM Configuration ");
            } else if (this->ui->tabWidget->currentIndex() == 3) {
                Message.prepend("Environtment ");
            } else if (this->ui->tabWidget->currentIndex() == 4) {
                Message.prepend("Sources ");
            } else if (this->ui->tabWidget->currentIndex() == 5) {
                Message.prepend("Alarm ");
            } else if (this->ui->tabWidget->currentIndex() == 6) {
                Message.prepend("Data ");
            }
            Message.prepend("Setting (with checked) ").append(" Saved");
            QMessageBox::information(this, "Success!!", Message, 0, 0);
        } else if (diff == 1 && !fail) {
            Message.prepend("Setting (with checked) ").append(" Saved");
            Message.append("\n\n Different Serial Number !!!");
            QMessageBox::information(this, "Success!!", Message, 0, 0);
        } else if (diff == 2 && !fail) {
            Message.prepend("Setting (with checked) ").append(" Saved");
            Message.append("\nBoard is not have Serial Number ..");
            QMessageBox::information(this, "Success!!", Message, 0, 0);
        }
        if (fail) {
            QMessageBox::information(this, "Serial Communication", STR_TIMEOUT, 0, 0);
        }
    } else {
        QMessageBox::critical(this, "Settings Critical", "Please Check List Before Setting ..", 0, 0);
    }

    this->EnableButton(true);
}

void formModule::on_pbGetAll_clicked()
{
    struct t_module tModule;
    struct t_serial_settings tSerial;
    QStringList val_data;
    bool timeout = false;
    bool fail = false;

    this->EnableButton(false);
    if (!Serial_Com->isOpen()) {
        QMessageBox::warning(this, "Serial Comunication", "Protocol is not open ..!!", 0, 0);
        this->EnableButton(true);
    } else {
        this->writeLogFile();
        timeout = work->Request_ENV(Serial_Com, false);
        if (timeout) {fail = true;} else {
            Serial->read_parsing(&tSerial);
            val_data = tSerial.str_data_env.split(";");
            if (NoSeri == val_data.at(1)) {
                module mod;
                mod.read_module(&tModule, Address_Module);

                progress_dialog->show();
                progress_dialog->setWindowTitle("Get All Configuration from board");
                progress_dialog->Processing(Serial_Com, Address_Module, "0005;0002;0001;0004");
                progress_dialog->close();
                mod.read_module(&tModule, Address_Module);

                this->setInterface(Address_Module);
                if (!fail) {
                    QMessageBox::information(this, "Syncronization Board", "All Setting is Syncronized ..", 0, 0);
                } else {
                    QMessageBox::information(this, "Serial Communication", STR_TIMEOUT, 0, 0);
                }
                this->EnableButton(true);
            } else {
                if (!fail) {
                    QMessageBox::warning(this, "Serial Comunication", "Serial Number is not syncronize ..!!", 0, 0);
                }
                this->EnableButton(true);
            }
        }
    }
}

void formModule::on_pbGet_clicked()
{
    struct t_module tModule;
    struct t_serial_settings tSerial;
    QStringList val_data;
    QString Message;
    bool timeout = false;
    bool fail = false;
    QString Request;

    this->EnableButton(false);
    if (!Serial_Com->isOpen()) {
        QMessageBox::warning(this, "Serial Comunication", "Protocol is not open ..!!", 0, 0);
        this->EnableButton(true);
    } else {
        this->writeLogFile();
        timeout = work->Request_ENV(Serial_Com, false);
        if (timeout) {fail = true;} else {
            Serial->read_parsing(&tSerial);
            val_data = tSerial.str_data_env.split(";");
            if (NoSeri == val_data.at(1)) {
                module mod;
                mod.read_module(&tModule, Address_Module);

                if (this->ui->tabWidget->currentIndex() <= 1) {
                    Message = "I/O ";
                    Request = "0005;0002";
                } else if (this->ui->tabWidget->currentIndex() == 2) {
                    Message = "SIM Configuration ";
                    Request = "0001";
                } else if (this->ui->tabWidget->currentIndex() == 3) {
                    Message = "Environtment ";
                    Request = "0000";
                } else if (this->ui->tabWidget->currentIndex() == 4) {
                    Message = "Sources ";
                    Request = "0004";
                } else if (this->ui->tabWidget->currentIndex() == 5) {

                    Message = "Alarm ";
                } else if (this->ui->tabWidget->currentIndex() == 6) {
                    Message = "Data ";
                    Request = "0005";
                }

                progress_dialog->show();
                progress_dialog->setWindowTitle("Get " + Message + "from board");
                progress_dialog->Processing(Serial_Com, Address_Module, Request);
                progress_dialog->close();
                mod.read_module(&tModule, Address_Module);

                this->setInterface(Address_Module);

                Message.append(" Setting is Syncronized ..");
                if (!fail) {
                    QMessageBox::information(this, "Syncronization Board", Message, 0, 0);
                } else {
                    QMessageBox::information(this, "Serial Communication", STR_TIMEOUT, 0, 0);
                }
                this->EnableButton(true);
            } else {
                if (!fail) {
                    QMessageBox::warning(this, "Serial Comunication", "Serial Number is not syncronize ..!!", 0, 0);
                }
                this->EnableButton(true);
            }
        }
    }
}

void formModule::on_pbEdit_clicked()
{
    bool fail = false; QString message;
    if (this->ui->tabWidget->currentIndex() == 2) {
        faddModule = new form_addModule(this, false, Address_Module, this->ui->tabWidget->currentIndex());
        faddModule->setWindowTitle("Edit Communications");
        faddModule->setModal(true);
        message = "SIM Configuration On-Local";
    } else if (this->ui->tabWidget->currentIndex() == 3) {
        faddModule = new form_addModule(this, false, Address_Module, this->ui->tabWidget->currentIndex());
        faddModule->setWindowTitle("Edit Environtments");
        faddModule->setModal(true);
        message = "Environtment On-Local";
    }
    faddModule->exec();

    if (faddModule->accept == 0) return;

    Address_Module = faddModule->currentFile;
    this->setInterface(Address_Module);
    this->setWindowTitle(
                Address_Module.mid(Address_Module.indexOf("m_")+2,
                                   Address_Module.indexOf(".dbe")).remove(".dbe"));
    struct t_module tModule;
    struct t_serial_settings tSerial;
    QStringList val_data;

    mod.read_module(&tModule, Address_Module);
    if (Serial_Com->isOpen()) {
        this->writeLogFile();
        this->EnableButton(false);

        if (this->ui->tabWidget->currentIndex() == 2) {
//            timeout = work->Set_SIM(this, busyForm, Serial_Com, &tModule, false);
//            if (timeout) {fail = true;} else {fail = false;}// return;};

//            timeout = work->Request_SIM(this, busyForm, Serial_Com, false);
//            if (timeout) {fail = true;} else {
//                Serial->read_parsing(&tSerial);
//                val_data = tSerial.str_data_sim.split("*");
//                work->Get_SIM(&tModule, val_data);
//            }

            progress_dialog->show();
            progress_dialog->setWindowTitle("Set SIM Configuration to board ..");
            progress_dialog->Processing(Serial_Com, Address_Module, "0101;0001");
            progress_dialog->close();
            mod.read_module(&tModule, Address_Module);

            this->setInterface_Communication(Address_Module);
            message = "SIM Configuration On-Board";
        } else if (this->ui->tabWidget->currentIndex() == 3) {
//            timeout = work->Set_ENV(this, busyForm, Serial_Com, &tModule, false);
//            if (timeout) {fail = true;} else {fail = false;}// return;};

//            timeout = work->Request_ENV(this, busyForm, Serial_Com, false);
//            if (timeout) {fail = true;} else {
//                Serial->read_parsing(&tSerial);
//                val_data = tSerial.str_data_env.split(";");
//                work->Get_ENV(&tModule, val_data);
//            }

            progress_dialog->show();
            progress_dialog->setWindowTitle("Set Environtment to board ..");
            progress_dialog->Processing(Serial_Com, Address_Module, "0100;0000");
            progress_dialog->close();
            mod.read_module(&tModule, Address_Module);

            this->setInterface_Environtment(Address_Module);
            message = "Environtment On-Board";
        }

        if (!fail) {
            message.prepend("Setting ").append(" Success ..");
            QMessageBox::information(this, "Syncronization Board !!", message, 0, 0);
        } else {
            QMessageBox::information(this, "Serial Communication", STR_TIMEOUT, 0, 0);
        }

        this->EnableButton(true);
    } else {
        message.prepend("Setting ").append(" Success ..");
        QMessageBox::information(this, "Syncronization Board !!", message, 0, 0);
    }

    NoSeri = tModule.serial_number;
}

void formModule::EnableButton(bool enab)
{
    this->ui->pbGetAll->setEnabled(enab);
    this->ui->pbSetAll->setEnabled(enab);
    this->ui->pbGet->setEnabled(enab);
    this->ui->pbSet->setEnabled(enab);
    this->ui->pbSetChk->setEnabled(enab);
    this->ui->pbEdit->setEnabled(enab);
}

void formModule::writeLogFile() {
    /* Try and open a file for output */
    QString outputFilename = PATH_LOG;
    QFile outputFile(outputFilename);
    outputFile.open(QIODevice::Append | QIODevice::Text);

    /* Check it opened OK */
    if(!outputFile.isOpen()){
        qDebug() << "- Error, unable to open" << outputFilename << "for output";
    } else {

        /* Point a QTextStream object at the file */
        QTextStream outStream(&outputFile);

        /* Write the line to the file */
        outStream << "----------" << "----------" <<
                     "----------" << "----------" <<
                     "----------" << "----------" <<
                     "----------" << "----------" <<
                     "----------" << "----------" <<
                     "----------" << "----------" <<
                     "----------" << "----------" <<
                     "----------" << "----------" <<
                     "\r\n";

        /* Close the file */
        outputFile.close();
    }
}

void formModule::on_pbAddRow_clicked()
{
    struct t_module tModule;
    module mod;
    Address_Module = ".RTUdata/module/m_" + this->windowTitle() + ".dbe";
    QString tmp;
    mod.read_module(&tModule, Address_Module);
    if (this->ui->tabWidget->currentIndex() == 4) {
        if (tModule.jml_sumber < 6) {
            tModule.jml_sumber++;
            tmp = QString::number(tModule.jml_sumber) + ";;;0;0;-";
            tModule.sumber.insert(tModule.jml_sumber-1, tmp);
            mod.write_module(&tModule);
            cryp code; code.encryp(Address_Module);
            this->setInterface_Sumber(Address_Module);
        } else {
            QMessageBox::information(this, "Sources Configuration", "Max 6 Rows ..", 0, 0);
        }
    } else if (this->ui->tabWidget->currentIndex() == 5) {
        tModule.jml_alarm++;
        tmp = QString::number(tModule.jml_alarm) + ";;0;0;0;0;0;0;0;0;0";
        tModule.alarm.insert(tModule.jml_alarm-1, tmp);
        mod.write_module(&tModule);
        cryp code; code.encryp(Address_Module);
        this->setInterface_Alarm(Address_Module);
    }
}

void formModule::del_src_clicked(int index)
{
    struct t_module tModule; module mod;
    Address_Module = ".RTUdata/module/m_" + this->windowTitle() + ".dbe";
    QString tmp; QStringList list1; QStringList list2;
    mod.read_module(&tModule, Address_Module);
    list1 = tModule.sumber;
    list1[index] = "";
    tModule.sumber.clear(); tModule.jml_sumber = 0;
    for (int i = 0; i < list1.length(); i++) {
        if (list1.at(i) != "") {
            tmp = list1.at(i);
            list2 = tmp.split(';');
            tmp = QString::number(tModule.jml_sumber+1) + ";" +
                    list2.at(1) + ";" +
                    list2.at(2) + ";" +
                    list2.at(3) + ";" +
                    list2.at(4) + ";" +
                    list2.at(5);
            tModule.sumber.insert(tModule.jml_sumber,tmp);
            tModule.jml_sumber++;
        }
    }
    mod.write_module(&tModule);
    cryp code; code.encryp(Address_Module);
    for (int i = 0; i <= this->ui->tabel_sources->rowCount(); i++) {
        this->ui->tabel_sources->removeRow(i);
    }
    this->setInterface_Sumber(Address_Module);
}

void formModule::length_src_changed()
{
    struct t_module tModule; module mod;
    Address_Module = ".RTUdata/module/m_" + this->windowTitle() + ".dbe";
    QString tmp; int val;
    mod.read_module(&tModule, Address_Module);

    for (int i = 0; i < tModule.jml_sumber; i++) {
        for (int j = 0; j <= 30; j++) {
            qobject_cast<QStandardItemModel *>(length_source[i]->model())->item(j)->setEnabled(true);
        }
        for (int j = 0; j <= 30; j++) {
            qobject_cast<QStandardItemModel *>(target_reg_source[i]->model())->item(j)->setEnabled(true);
        }
    }
    for (int i = 0; i < tModule.jml_sumber; i++) {
        for (int j = 0; j < tModule.jml_sumber; j++) {
            for (int k = 0; k < length_source[i]->currentIndex(); k++) {
                qobject_cast<QStandardItemModel *>(target_reg_source[j]->model())
                        ->item(target_reg_source[i]->currentIndex()+k)
                        ->setEnabled(false);
            }
            if (target_reg_source[i]->currentIndex() == 0) {
                for (int k = 0; k <= tModule.data.length()+(DATA_PERIOD*2); k+=2) {
                    qobject_cast<QStandardItemModel *>(length_source[i]->model())
                            ->item(length_source[i]->findText(QString::number(k)))
                            ->setEnabled(false);
                }
            } else {
                val = 0;
                for (int k = 0; k < tModule.jml_sumber; k++) {
                    val = val + length_source[k]->currentIndex();
                }
                for (int k = 0; k < val; k++) {
                    qobject_cast<QStandardItemModel *>(length_source[j]->model())
                            ->item((tModule.data.length()+(DATA_PERIOD*2))/2-k)
                            ->setEnabled(false);
                }
            }
        }
    }
}

void formModule::tReg_src_changed()
{
    struct t_module tModule; module mod;
    Address_Module = ".RTUdata/module/m_" + this->windowTitle() + ".dbe";
    QString tmp; int val;
    mod.read_module(&tModule, Address_Module);

    for (int i = 0; i < tModule.jml_sumber; i++) {
        for (int j = 0; j <= 30; j++) {
            qobject_cast<QStandardItemModel *>(length_source[i]->model())->item(j)->setEnabled(true);
        }
        for (int j = 0; j <= 30; j++) {
            qobject_cast<QStandardItemModel *>(target_reg_source[i]->model())->item(j)->setEnabled(true);
        }
    }
    for (int i = 0; i < tModule.jml_sumber; i++) {
        for (int j = 0; j < tModule.jml_sumber; j++) {
            for (int k = 0; k < length_source[i]->currentIndex(); k++) {
                qobject_cast<QStandardItemModel *>(target_reg_source[j]->model())
                        ->item(target_reg_source[i]->currentIndex()+k)
                        ->setEnabled(false);
            }
            if (target_reg_source[i]->currentIndex() == 0) {
                for (int k = 0; k <= tModule.data.length()+(DATA_PERIOD*2); k+=2) {
                    qobject_cast<QStandardItemModel *>(length_source[i]->model())
                            ->item(length_source[i]->findText(QString::number(k)))
                            ->setEnabled(false);
                }
            } else {
                val = 0;
                for (int k = 0; k < tModule.jml_sumber; k++) {
                    val = val + length_source[k]->currentIndex();
                }
                for (int k = 0; k < val; k++) {
                    qobject_cast<QStandardItemModel *>(length_source[j]->model())
                            ->item((tModule.data.length()+(DATA_PERIOD*2))/2-k)
                            ->setEnabled(false);
                }
            }
        }
    }
}

void formModule::del_alrm_clicked(int index)
{
    struct t_module tModule; module mod;
    Address_Module = ".RTUdata/module/m_" + this->windowTitle() + ".dbe";
    QString tmp; QStringList list1; QStringList list2;
    mod.read_module(&tModule, Address_Module);
    list1 = tModule.alarm;
    list1[index] = "";
    tModule.alarm.clear(); tModule.jml_alarm = 0;
    for (int i = 0; i < list1.length(); i++) {
        if (list1.at(i) != "") {
            tmp = list1.at(i);
            list2 = tmp.split(';');
            tmp = QString::number(tModule.jml_alarm+1) + ";" +
                    list2.at(1) + ";" +
                    list2.at(2) + ";" +
                    list2.at(3) + ";" +
                    list2.at(4) + ";" +
                    list2.at(5) + ";" +
                    list2.at(6) + ";" +
                    list2.at(7) + ";" +
                    list2.at(8) + ";" +
                    list2.at(9) + ";" +
                    list2.at(10);
            tModule.alarm.insert(tModule.jml_alarm,tmp);
            tModule.jml_alarm++;
        }
    }
    mod.write_module(&tModule);
    cryp code; code.encryp(Address_Module);
    for (int i = 0; i <= this->ui->tabel_alarm->rowCount(); i++) {
        this->ui->tabel_alarm->removeRow(i);
    }
    this->setInterface_Alarm(Address_Module);
}

void formModule::input_alrm_changed(int index)
{
    struct t_module tModule; module mod;
    Address_Module = ".RTUdata/module/m_" + this->windowTitle() + ".dbe";
    QString tmp; QString str; QStringList list;
    mod.read_module(&tModule, Address_Module);

    for (int i = 0; i < tModule.jml_alarm; i++) {
        for (int j = 0; j <= tModule.jml_input_digital + tModule.jml_input_analog; j++) {
            qobject_cast<QStandardItemModel *>(input_alarm[i]->model())->item(j)->setEnabled(true);
        }
    }
    for (int i = 0; i < tModule.jml_alarm; i++) {
        for (int j = 0; j < tModule.jml_alarm; j++) {
            tmp = input_alarm[j]->currentText();
            qobject_cast<QStandardItemModel *>(input_alarm[i]->model())->item(input_alarm[i]->findText(tmp))->setEnabled(false);
        }
    }

    if (input_alarm[index]->currentIndex() - 1 >= 0) {
        str = tModule.data.at(input_alarm[index]->currentIndex() - 1);
        list = str.split(';');
        name_alarm[index]->setText(list[2]);
        state_alarm[index]->setCurrentIndex(list[11].toInt());
        range_l[index]->setText(list[5]);
        batas_ll[index]->setText(list[6]);
        batas_l[index]->setText(list[7]);
        batas_h[index]->setText(list[8]);
        batas_hh[index]->setText(list[9]);
        range_h[index]->setText(list[10]);
    } else {
        name_alarm[index]->setText("");
        state_alarm[index]->setCurrentIndex(0);
        range_l[index]->setText("0");
        batas_ll[index]->setText("0");
        batas_l[index]->setText("0");
        batas_h[index]->setText("0");
        batas_hh[index]->setText("0");
        range_h[index]->setText("0");
    }
}

void formModule::on_pbDeleteRows_clicked()
{
    struct t_module tModule; module mod;
    Address_Module = ".RTUdata/module/m_" + this->windowTitle() + ".dbe";
    QString tmp; QStringList list1; QStringList list2;
    mod.read_module(&tModule, Address_Module);
    if (this->ui->tabWidget->currentIndex() == 4) {
        list1 = tModule.sumber;
        for (int i = 0; i < tModule.jml_sumber; i++) {
            if (check_source[i]->isChecked()) {
                list1[i] = "";
            }
        }
        tModule.sumber.clear(); tModule.jml_sumber = 0;
        for (int i = 0; i < list1.length(); i++) {
            if (list1.at(i) != "") {
              tmp = list1.at(i);
                list2 = tmp.split(';');
                tmp = QString::number(tModule.jml_sumber+1) + ";" +
                        list2.at(1) + ";" +
                        list2.at(2) + ";" +
                        list2.at(3) + ";" +
                        list2.at(4) + ";" +
                        list2.at(5);
                tModule.sumber.insert(tModule.jml_sumber,tmp);
                tModule.jml_sumber++;
            }
        }
        mod.write_module(&tModule);
        cryp code; code.encryp(Address_Module);
        for (int i = 0; i <= this->ui->tabel_sources->rowCount(); i++) {
            this->ui->tabel_sources->removeRow(i);
        }
        this->setInterface_Sumber(Address_Module);
    } else if (this->ui->tabWidget->currentIndex() == 5) {
        list1 = tModule.alarm;
        for (int i = 0; i < tModule.jml_alarm; i++) {
            if (check_alarm[i]->isChecked()) {
                list1[i] = "";
            }
        }
        tModule.alarm.clear(); tModule.jml_alarm = 0;
        for (int i = 0; i < list1.length(); i++) {
            if (list1.at(i) != "") {
                tmp = list1.at(i);
                list2 = tmp.split(';');
                tmp = QString::number(tModule.jml_alarm+1) + ";" +
                        list2.at(1) + ";" +
                        list2.at(2) + ";" +
                        list2.at(3) + ";" +
                        list2.at(4) + ";" +
                        list2.at(5) + ";" +
                        list2.at(6) + ";" +
                        list2.at(7) + ";" +
                        list2.at(8) + ";" +
                        list2.at(9) + ";" +
                        list2.at(10);
                tModule.alarm.insert(tModule.jml_alarm,tmp);
                tModule.jml_alarm++;
            }
        }
        mod.write_module(&tModule);
        cryp code; code.encryp(Address_Module);
        for (int i = 0; i <= this->ui->tabel_alarm->rowCount(); i++) {
            this->ui->tabel_alarm->removeRow(i);
        }
        this->setInterface_Alarm(Address_Module);
    }
}

void formModule::on_pbRefresh_clicked()
{
    this->ui->pbRefresh->setEnabled(false);
    this->data_monitoring();
    this->ui->pbRefresh->setEnabled(true);
}

//void formModule::state_kanal_change(int index)
//{
////    state_data_s[index]->setCurrentIndex(state_input[index]->currentIndex());
//}

//void formModule::state_data_change(int index)
//{
////    state_input[index]->setCurrentIndex(state_data_s[index]->currentIndex());
//}

void formModule::reg_kanal_changed()
{
    struct t_module tModule; module mod;
    Address_Module = ".RTUdata/module/m_" + this->windowTitle() + ".dbe";
    QString tmp;
    mod.read_module(&tModule, Address_Module);

    for (int i = 0; i < tModule.jml_input_digital; i++) {
        for (int j = 0; j < PIN_DIGITAL; j++) {
            qobject_cast<QStandardItemModel *>(reg_input[i]->model())->item(j)->setEnabled(true);
        }
    }
    for (int i = tModule.jml_input_digital; i < tModule.jml_input_digital + tModule.jml_input_analog; i++) {
        for (int j = 0; j < PIN_ANALOG; j++) {
            qobject_cast<QStandardItemModel *>(reg_input[i]->model())->item(j)->setEnabled(true);
        }
    }
    for (int i = 0; i < tModule.jml_input_digital; i++) {
        for (int j = 0; j < tModule.jml_input_digital; j++) {
            tmp = reg_input[j]->currentText();
            qobject_cast<QStandardItemModel *>(reg_input[i]->model())->item(reg_input[i]->findText(tmp))->setEnabled(false);
        }
    }
    for (int i = tModule.jml_input_digital; i < tModule.jml_input_digital + tModule.jml_input_analog; i++) {
        for (int j = tModule.jml_input_digital; j < tModule.jml_input_digital + tModule.jml_input_analog; j++) {
            tmp = reg_input[j]->currentText();
            qobject_cast<QStandardItemModel *>(reg_input[i]->model())->item(reg_input[i]->findText(tmp))->setEnabled(false);
        }
    }
}

bool formModule::eventFilter(/*QObject *obj, */QEvent *event)
{
    if(event->type() == QEvent::Wheel/* && obj == m_combo*/)
    {
//        qDebug() << "Wheel event blocked";
        return true;
    }
    return false;
}
