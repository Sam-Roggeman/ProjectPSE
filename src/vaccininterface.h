#ifndef VACCININTERFACE_H
#define VACCININTERFACE_H

#include "Simulation.h"
#include "simulationImporter.h"
#include "iostream"
#include <string>
#include <QWidget>
#include <QFileDialog>
#include <QDialog>
#include <QStackedWidget>
#include "Simulation.h"



namespace Ui {
class VaccinInterface;
}

class VaccinInterface : public QDialog
{
    Q_OBJECT
    variable Simulation * simulatie;

public:
    explicit VaccinInterface(QWidget *parent = nullptr);
    ~VaccinInterface();

private slots:
    void on_pushButton_clicked();

    void on_stackedWidget_currentChanged(int arg1);

    void on_Start_clicked();

    void on_Stop_clicked();

    void on_Vorige_dag_clicked();

    void on_Volgende_dag_clicked();

    void on_Grafische_impressie_clicked();

    void on_Normale_impressie_clicked();

private:
    Ui::VaccinInterface *ui;
};

#endif // VACCININTERFACE_H
