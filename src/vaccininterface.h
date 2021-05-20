#ifndef VACCININTERFACE_H
#define VACCININTERFACE_H

#include <QDialog>
#include "Simulation.h"
#include "QWidget"
#include "QFileDialog"

namespace Ui {
class VaccinInterface;
}

class VaccinInterface : public QDialog
{
    Q_OBJECT

public:
    explicit VaccinInterface(QWidget *parent = nullptr);
    ~VaccinInterface();

private slots:
    void on_pushButton_clicked();

private:
    Ui::VaccinInterface *ui;
};

#endif // VACCININTERFACE_H
