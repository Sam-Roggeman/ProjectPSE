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
#include "DesignByContract.h"
#include <QtCharts>

namespace Ui {
class VaccinInterface;
}

class VaccinInterface : public QDialog
{
    Q_OBJECT
    Simulation * simulatie;
    QFont* textFont;
    std::stack<Simulation*> redoStack;
    std::stack<Simulation*> undoStack;
    std::map<int , std::pair<QString,QString>> dayToString;
    QBarSet *volledig_gevaccineerden = new QBarSet("volledig_gevaccineerden");
    QBarSet *gevaccineerden = new QBarSet("gevaccineerden");
    QBarSet *ongevaccineerden = new QBarSet("ongevaccineerden");
    std::map<std::string, QBarSet*> barsets;
    QValueAxis *axisY_types;

public:
    Simulation *getSimulatie() const;

    const std::stack<Simulation *> &getRedoStack() const;

    const std::stack<Simulation *> &getUndoStack() const;

public:

    /**
     * constructor voor de interface
     * @param parent
     */
    explicit VaccinInterface(QWidget *parent = nullptr);
    ~VaccinInterface();

private slots:

    /**
     * functie die start bij het importeren van een file
     * zet de 2 grafieken klaar en de tabel voor de manuele invoer
     * @post getSimulatie()->correctlyInitialized()
     */
    void on_pushButton_clicked();

    void on_stackedWidget_currentChanged(int arg1);

    /**
     * @pre getSimulatie().correctlyInitialized()
     * doet de simulatie van start tot start+getal uit de nummerbox en vervangt de charts
     */
    void on_Start_clicked();

    /**
     * returnt naar de vorige dag indien mogelijk
     * @pre getSimulatie()->correctlyInitialized()
     * @post getSimulatie()->getDag() -= 1 || -= 0
     * @post  getUndoStack().size() -= 1 || -= 0
     * @post getRedoStack().size() +=1 || += 0
     */
    void on_Vorige_dag_clicked();

    /**
     * returnt naar de volgende dag indien mogelijk, anders simuleert hij een dag
     * @pre getSimulatie()->correctlyInitialized()
     * @post getSimulatie()->getDag() += 1
     * @post  getRedoStack().size() -= 1 || -= 0
     * @post getUndoStack().size() +=1 || += 0
     */
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


    void on_Manueel_2_clicked();

    void on_Gif_export_clicked();

private:
    Ui::VaccinInterface *ui;

    /**
     * doet de simulatie door gebruik te maken van simulatie->simulateDay(), regelt zelf het QT gedeelte
     * @param aantal_dagen
     * @pre aantal_dagen >=0
     * @pre getSimulatie().correctlyInitialized()
     */
    void doSimulation(int aantal_dagen);

    /**
     * vervangt de charts door de gegevens te gebruiken in het object
     * @param gegevens
     * @pre gegevens->correctlyInitialized()
     */
    void replaceChart(const Gegevens *gegevens);

};

#endif // VACCININTERFACE_H
