#ifndef VACCININTERFACE_H
#define VACCININTERFACE_H

#include "Simulation.h"
#include "simulationImporter.h"
#include <string>
#include <QWidget>
#include <QFileDialog>
#include <QDialog>

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
