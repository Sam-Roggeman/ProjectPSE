#ifndef VACCININTERFACE_H
#define VACCININTERFACE_H

#include "Simulation.h"
#include "simulationImporter.h"
#include <string>
#include <QWidget>
#include <QFileDialog>
#include <QDialog>
#include <QStackedWidget>


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

    void on_stackedWidget_currentChanged(int arg1);

private:
    Ui::VaccinInterface *ui;
};

#endif // VACCININTERFACE_H
