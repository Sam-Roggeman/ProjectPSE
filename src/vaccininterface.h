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
#include <stack>
#include <QMessageBox>
#include <QtCharts>




namespace Ui {
class VaccinInterface;
}

class VaccinInterface : public QDialog
{
    Q_OBJECT
    Simulation * simulatie;
    QFont* textFont;
    std::stack<Simulation> redoStack;
    std::stack<Simulation> undoStack;
    std::map<int , std::pair<QString,QString>> dayToString;
    Gegevens curr_gegevens;
    QBarSet *volledig_gevaccineerden = new QBarSet("volledig_gevaccineerden");
    QBarSet *gevaccineerden = new QBarSet("gevaccineerden");
    QBarSet *ongevaccineerden = new QBarSet("ongevaccineerden");
    std::map<std::string, QBarSet*> barsets;
    QValueAxis *axisY_types;



public:
    explicit VaccinInterface(QWidget *parent = nullptr);
    ~VaccinInterface();

private slots:
    void on_pushButton_clicked();

    void on_stackedWidget_currentChanged(int arg1);

    void on_Start_clicked();

    void on_Vorige_dag_clicked();

    void on_Volgende_dag_clicked();

    void on_Grafische_impressie_clicked();

    void on_Normale_impressie_clicked();

    void on_Exit_clicked();

    void on_Impressies_currentChanged(int arg1);

    void on_Confirm_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::VaccinInterface *ui;

    void doSimulation(int aantal_dagen);

    void replaceChart(const Gegevens *gegevens);
};

#endif // VACCININTERFACE_H
