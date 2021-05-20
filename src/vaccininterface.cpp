#include "vaccininterface.h"
#include "ui_vaccininterface.h"



VaccinInterface::VaccinInterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VaccinInterface)
{
    ui->setupUi(this);
}

VaccinInterface::~VaccinInterface()
{
    delete ui;
}

void VaccinInterface::on_pushButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"), "/home/jana", tr("Image Files ( *.xml)"));
    if (!fileName.isEmpty()) {
        this->on_stackedWidget_currentChanged(1);
        Simulation s = Simulation();
        simulationImporter::importSimulation(fileName.toStdString().c_str(), std::cout, s);
        s.autoSimulationUntilDone();
        if(this->ui->pushButton->isEnabled()){
            std::cout << "hallo";
        }

    }
}

void VaccinInterface::on_stackedWidget_currentChanged(int arg1)
{
        this->ui->stackedWidget->setCurrentIndex(arg1);

}
