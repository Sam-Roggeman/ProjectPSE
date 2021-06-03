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
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
    QTableWidgetItem * qTableWidgetItem;
    int aantal_rows = 0;
    int current_row = -1;
    QString zero("0");
    QString centrumnaam("");
    QString hubnaam("");

    if (!fileName.isEmpty()) {
        this->on_stackedWidget_currentChanged(1);
        simulationImporter::importSimulation(fileName.toStdString().c_str(), std::cout, *simulatie);

        for (std::vector<Hub*>::const_iterator hub_it = simulatie->getHubs().begin(); hub_it != simulatie->getHubs().end(); hub_it++){
            aantal_rows++;
            for (std::map<std::string,Vaccinatiecentrum*>::const_iterator vac_it = (*hub_it)->getVaccinatiecentra().begin();
            vac_it != (*hub_it)->getVaccinatiecentra().end(); vac_it++) {
                aantal_rows++;
            }
        }

        ui->tableWidget->setRowCount(aantal_rows);
        for(int i = 0; i < ui->tableWidget->rowCount(); i++){
            qTableWidgetItem = new QTableWidgetItem();
            ui->tableWidget->setItem(i,1,qTableWidgetItem);

            qTableWidgetItem = new QTableWidgetItem();
            ui->tableWidget->setItem(i,0,qTableWidgetItem);

        }
        ui->tableWidget->horizontalHeaderItem(0)->setText("VaccinatieCentra");
        ui->tableWidget->horizontalHeaderItem(1)->setText("Aantal Vaccins");

        for (std::vector<Hub*>::const_iterator hub_it = simulatie->getHubs().begin(); hub_it != simulatie->getHubs().end(); hub_it++){
            current_row++;
            hubnaam = QString::fromStdString("Hub "+std::to_string((*hub_it)->getID()));
            qTableWidgetItem = ui->tableWidget->item(current_row,0);
            qTableWidgetItem->setText(hubnaam);
            qTableWidgetItem->setFlags(qTableWidgetItem->flags() & Qt::ItemIsEditable);
            qTableWidgetItem->setTextColor(QColor("black"));
            qTableWidgetItem->setBackgroundColor(QColor("lightGrey"));
            qTableWidgetItem = ui->tableWidget->item(current_row,1);
            qTableWidgetItem->setFlags(qTableWidgetItem->flags() & Qt::ItemIsEditable);
            qTableWidgetItem->setBackgroundColor(QColor("lightGrey"));


            for (std::map<std::string,Vaccinatiecentrum*>::const_iterator vac_it = (*hub_it)->getVaccinatiecentra().begin();
                 vac_it != (*hub_it)->getVaccinatiecentra().end(); vac_it++) {
                current_row++;
                centrumnaam = QString::fromStdString((*vac_it).first);
                qTableWidgetItem = ui->tableWidget->item(current_row,0);
                qTableWidgetItem->setText(centrumnaam);
                qTableWidgetItem->setFlags(qTableWidgetItem->flags() & Qt::ItemIsEditable);
                qTableWidgetItem->setTextColor(QColor("black"));
                qTableWidgetItem->setBackgroundColor(QColor("lightGrey"));

                ui->tableWidget->item(current_row,1)->setText(zero);

            }
        }
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

void VaccinInterface::on_Confirm_clicked()
{

    undoStack.push(Simulation(*simulatie));
    while (!redoStack.empty()){
        redoStack.pop();
    }



    int hub_counter = 0;
    int tot_vac;
    int hub;
    std::string key;
    std::string key1;
    // vaccincentrum_naam -> hubID-> aantal_vaccins
    std::map<std::string,std::map<int,int>> vaccins_to_centra;
    QMessageBox messageBox;
    std::stringstream out;
    Gegevens gegevens;



//    out << "DAG " << dag << ":" << std::endl;

    for(int i = 0; i < ui->tableWidget->rowCount(); i++){
        key = this->ui->tableWidget->item(i,0)->text().toStdString();
        key1 = key.substr(0,key.find_last_of(' '));
        if (key1 == "Hub"){
            hub_counter = std::atoi((key.substr(key.find_last_of(' ')+1,key.size())).c_str());
        }
        else{
//            if (simulatie->getHubs().at(hub_counter)->getVaccinatiecentra().find()) {
            vaccins_to_centra[key][hub_counter] = std::atoi(this->ui->tableWidget->item(i, 1)->text().toStdString().c_str());
//            }
        }
    }

    for (std::map<std::string,std::map<int,int>>::const_iterator it = vaccins_to_centra.begin(); it!= vaccins_to_centra.end(); it++){
        tot_vac = 0;
        for(std::map<int,int>::const_iterator hub_it = (*it).second.begin(); hub_it != (*it).second.end(); hub_it++){
            tot_vac += hub_it->second;
            hub = hub_it->first;
        }

        if (!simulatie->isAllowed(tot_vac, hub,it->first)){
            messageBox.critical(0,"Capaciteit overschreden",QString::fromStdString(std::string("Capaciteit in " + it->first + " overschreden")));
            messageBox.setFixedSize(500,200);
            messageBox.open();
            return;
        }
    }


    out.str(std::string(""));
    simulatie->simulateManual(vaccins_to_centra, gegevens,out);
    ui->textEdit->append(QString::fromStdString(out.str()));
    out.str(std::string(""));
    simulatie->impressie(out);

    ui->textEdit_2->append(QString::fromStdString(out.str()));


}

void VaccinInterface::on_pushButton_5_clicked()
{
    on_Impressies_currentChanged(2);
}

void VaccinInterface::on_pushButton_6_clicked()
{
    on_Impressies_currentChanged(2);
}

void VaccinInterface::on_pushButton_3_clicked()
{
    on_Impressies_currentChanged(0);
}

void VaccinInterface::on_pushButton_4_clicked()
{
    on_Impressies_currentChanged(1);
}

void VaccinInterface::on_Statististische_gegevens_clicked()
{
    on_Impressies_currentChanged(3);
}

void VaccinInterface::on_Statistische_gegevens_2_clicked()
{
    on_Impressies_currentChanged(3);
}

void VaccinInterface::on_Statistische_gegevens_3_clicked()
{
    on_Impressies_currentChanged(3);
}

void VaccinInterface::on_Normale_impressie_2_clicked()
{
    on_Impressies_currentChanged(0);
}

void VaccinInterface::on_Grafische_impressie_2_clicked()
{
    on_Impressies_currentChanged(1);
}

void VaccinInterface::on_Manuele_vaccins_clicked()
{
    on_Impressies_currentChanged(2);
}
