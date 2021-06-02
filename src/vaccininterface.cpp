#include "vaccininterface.h"
#include "ui_vaccininterface.h"



VaccinInterface::VaccinInterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VaccinInterface)
{
    textFont = new QFont();
    textFont->setFamily("monospace [Consolas]");
    textFont->setFixedPitch(true);
    textFont->setStyleHint(QFont::TypeWriter);


    ui->setupUi(this);
    ui->textEdit_2->setFont(*textFont);


    simulatie = new Simulation();
}

VaccinInterface::~VaccinInterface()
{
    delete ui;
    delete simulatie;
    delete textFont;
}

void VaccinInterface::on_pushButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"), "./testInput", tr("Image Files ( *.xml)"));
    if (!fileName.isEmpty()) {
        this->on_stackedWidget_currentChanged(1);
        simulationImporter::importSimulation(fileName.toStdString().c_str(), std::cout, *simulatie);
    }
}

void VaccinInterface::on_stackedWidget_currentChanged(int arg1)
{
        this->ui->stackedWidget->setCurrentIndex(arg1);

}



void VaccinInterface::on_Start_clicked()
{
    doSimulation(ui->spinBox->value());
}

void VaccinInterface::doSimulation(int aantal_dagen){
    std::stringstream stringstream;
    Gegevens gegevens = Gegevens();
    QString output_string_text;
    QString output_string_imp;
    int einddag = aantal_dagen + simulatie->getDag();

    while (simulatie->notDone() && simulatie->getDag() != einddag){
        undoStack.push(Simulation(*simulatie));
        while (!redoStack.empty()){
            redoStack.pop();
        }

        stringstream.str(std::string());
        simulatie->simulateDay(gegevens,stringstream);
        output_string_text = QString::fromStdString(stringstream.str());
        ui->textEdit->append(output_string_text);

        stringstream.str(std::string());
        simulatie->impressie(stringstream);
        output_string_imp = QString::fromStdString(stringstream.str());
        ui->textEdit_2->append(output_string_imp);

        dayToString[simulatie->getDag()] = std::make_pair(output_string_text,output_string_imp);
    }
}


void VaccinInterface::on_Vorige_dag_clicked()
{
    int start_day = simulatie->getDag();
    if (!undoStack.empty()){
        redoStack.push(Simulation(*simulatie));
        delete simulatie;
        simulatie = new Simulation(undoStack.top());
        undoStack.pop();

        ui->textEdit->clear();
        ui->textEdit_2->clear();

        for (std::map<int, std::pair<QString,QString>>::const_iterator it = dayToString.begin();
                it != dayToString.end(); it++){
            if (it->first > simulatie->getDag()){
                break;
            }
            else{
                ui->textEdit->append(it->second.first);
                ui->textEdit_2->append(it->second.second);
            }
        }
        int end_day = simulatie->getDag();
        ENSURE(end_day == start_day-1, "end_day != start_day=1");
    }
}

void VaccinInterface::on_Volgende_dag_clicked()
{
    if (!redoStack.empty()){
        undoStack.push(Simulation(*simulatie));
        simulatie = new Simulation(redoStack.top());
        redoStack.pop();
        ui->textEdit->append(dayToString[simulatie->getDag()].first);
        ui->textEdit_2->append(dayToString[simulatie->getDag()].second);
    }
    else{
        doSimulation(1);
    }
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
