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
        Simulation s = Simulation();
        simulationImporter::importSimulation(fileName.toStdString().c_str(), std::cout, s);
        s.autoSimulationUntilDone();
    }
}
