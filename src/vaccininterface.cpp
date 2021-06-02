#include "vaccininterface.h"
#include "ui_vaccininterface.h"



VaccinInterface::VaccinInterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VaccinInterface)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
        simulatie = &s;
    }
}

void VaccinInterface::on_stackedWidget_currentChanged(int arg1)
{
        this->ui->stackedWidget->setCurrentIndex(arg1);

}



void VaccinInterface::on_Start_clicked()
{
    unsigned int sleep_delay = 3;
    std::stringstream stringstream;
    std::stringstream stringstream1;
    Gegevens gegevens = Gegevens();

    int dag = ui->spinBox->value() + simulatie->getDag();


    while (simulatie->notDone() && simulatie->getDag() != dag){

        stringstream.clear();
        simulatie->simulateDay(gegevens,stringstream);
        simulatie->impressie(stringstream1);
        ui->textEdit->setText(QString::fromStdString(stringstream.str()));
        ui->textEdit_2->setText(QString::fromStdString(stringstream1.str()));
        sleep(sleep_delay);
    }
}

void VaccinInterface::on_Vorige_dag_clicked()
{

}

void VaccinInterface::on_Volgende_dag_clicked()
{

}

void VaccinInterface::on_Grafische_impressie_clicked()
{
    on_Impressies_currentChanged(1);
}

void VaccinInterface::on_Normale_impressie_clicked()
{
    on_Impressies_currentChanged(0);
}

void VaccinInterface::on_Exit_clicked()
{
    this->close();
}

void VaccinInterface::on_Impressies_currentChanged(int arg1)
{
    this->ui->Impressies->setCurrentIndex(arg1);
}

void VaccinInterface::on_Confirm_clicked()
{

}
