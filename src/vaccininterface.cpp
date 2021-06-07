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
    int aantal_types = 0;
    QBarSet * qBarSet;
    QStackedBarSeries *types = new QStackedBarSeries();
    if (!fileName.isEmpty()) {
        initializeTmp();

        this->on_stackedWidget_currentChanged(1);
        simulationImporter::importSimulation(fileName.toStdString().c_str(), std::cout, *simulatie);

        for (std::vector<Hub*>::const_iterator hub_it = simulatie->getHubs().begin(); hub_it != simulatie->getHubs().end(); hub_it++){
            aantal_rows++;
            aantal_types += (*hub_it)->getTypes().size();

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

            for (std::map<std::string,VaccinType*>::const_iterator type_it = (*hub_it)->getTypes().begin();type_it != (*hub_it)->getTypes().end();type_it++)  {
                qBarSet = new QBarSet(QString::fromStdString(type_it->first));
//                std::cout << type_it->first <<std::endl;

                barsets[type_it->first] = qBarSet;
                *(barsets[type_it->first]) << 0;
                types->append(barsets[type_it->first]);

            }
        }
        *volledig_gevaccineerden << 0;
        *gevaccineerden << 0;
        *ongevaccineerden << simulatie->getAantalInwoners();
        QStackedBarSeries *progress = new QStackedBarSeries();

        progress->append(volledig_gevaccineerden);
        progress->append(gevaccineerden);
        progress->append(ongevaccineerden);

        QChart *chart = new QChart();
        chart->addSeries(progress);
        chart->setTitle("Progress");
        chart->setAnimationOptions(QChart::SeriesAnimations);
        chart->setBackgroundVisible(false);
        QValueAxis * axisY = new QValueAxis();
        axisY->setLabelFormat("%.0i");
        chart->addAxis(axisY, Qt::AlignLeft);
        progress->attachAxis(axisY);
        chart->legend()->setVisible(false);
//        chart->legend()->setAlignment(Qt::AlignRight);
//        chart->legend()->font().setPointSize(1);
//        chart->legend()->setVisible(false);
        QChartView *chartView;
        QChartView *chartView_2;

        chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        ui->Grafiek->insertWidget(0,chartView);
        chartView->show();
        chartView->resize(ui->Grafiek->size());

        QChart *chart_types = new QChart();
        chart_types->addSeries(types);
        chart_types->setTitle("Types/1000");
        chart_types->setAnimationOptions(QChart::SeriesAnimations);
        chart_types->setBackgroundVisible(false);
        axisY_types = new QValueAxis();
//        axisY_types->setLabelFormat("%.0f");
        chart_types->addAxis(axisY_types, Qt::AlignLeft);
        types->attachAxis(axisY_types);
        chart_types->legend()->setVisible(true);
        chart_types->legend()->setAlignment(Qt::AlignRight);
//        chart_types->legend()->font().setPointSize(1);
//        chart_types->legend()->setVisible(false);
        chartView_2 = new QChartView(chart_types);
        chartView_2->setRenderHint(QPainter::Antialiasing);
        ui->Grafiek_2->insertWidget(0,chartView_2);
        chartView_2->show();
        chartView_2->resize(ui->Grafiek_2->size());


    }
}

void VaccinInterface::on_stackedWidget_currentChanged(int arg1)
{
        this->ui->stackedWidget->setCurrentIndex(arg1);
}



void VaccinInterface::on_Start_clicked()
{
    int start = simulatie->getDag();
    doSimulation(ui->spinBox->value());
    replaceChart(simulatie->getGegevens(simulatie->getDag()-1));
    ENSURE(start + ui->spinBox->value() == simulatie->getDag(), "simulatie is niet ver genoeg doorgelopen");
}

void VaccinInterface::replaceChart(const Gegevens* gegevens)
{
    REQUIRE(gegevens->correctlyInitialized(), "gegevens moet correct geinitializeerd zijn bij oproep van replacechart");
    this->gevaccineerden->replace(0,gegevens->getGevaccineerden());
    this->ongevaccineerden->replace(0,simulatie->getAantalInwoners() - gegevens->getGevaccineerden( )- gegevens->getGevaccineerden());
    this->volledig_gevaccineerden->replace(0, gegevens->getVolledigGevaccineerden());
//    QBarSet * curr_barset;
    int totaal = 0;
    for (std::map<std::string, int>::const_iterator it = gegevens->getGeleverdType().begin(); it != gegevens->getGeleverdType().end(); it++){
        barsets[it->first]->replace(0,(it->second+500)/1000);
        totaal += (it->second+500)/1000;
    }
    axisY_types->setMax(totaal);


}

void VaccinInterface::doSimulation(int aantal_dagen){
    REQUIRE(aantal_dagen >= 0, "aantal_dagen moet positief zijn");
    REQUIRE(simulatie->correctlyInitialized(),"simulatie moet correct geinitializeerd zijn bij oproep van doSimulation");

    std::stringstream stringstream;
    QString output_string_text;
    QString output_string_imp;
    int einddag = aantal_dagen + simulatie->getDag();

    while (simulatie->notDone() && simulatie->getDag() != einddag){
        undoStack.push(new Simulation(simulatie));
        while (!redoStack.empty()){
            redoStack.pop();
        }

        stringstream.str(std::string());
        simulatie->simulateDay(stringstream);
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
    REQUIRE(simulatie->correctlyInitialized(),"simulatie is niet geinitializeerd bij oproep van vorige dag");
    unsigned int start_und = undoStack.size();
    unsigned int start_redo = redoStack.size();
    unsigned int start_day = simulatie->getDag();
    unsigned int end_day = start_day;
    if (!undoStack.empty()){
        redoStack.push(new Simulation(simulatie));
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
        end_day = simulatie->getDag();
        replaceChart(simulatie->getGegevens(end_day-1));
    }
    ENSURE(end_day == start_day-1 || end_day == start_day, "end_day != start_day-1 && end_day != start_day");
    ENSURE(start_und == undoStack.size() || start_und == undoStack.size()+1, "undoStack is niet gepopt/constant gebleven");
    ENSURE(start_redo == redoStack.size() || start_redo+1 == redoStack.size(), "redoStack is niet gepusht/constant gebleven");

}

void VaccinInterface::on_Volgende_dag_clicked()
{
    unsigned int start_und = undoStack.size();
    unsigned int start_redo = redoStack.size();
    unsigned int start_day = simulatie->getDag();
    if (!redoStack.empty()){
        undoStack.push(new Simulation(simulatie));
        simulatie = new Simulation(redoStack.top());
        redoStack.pop();
        ui->textEdit->append(dayToString[simulatie->getDag()].first);
        ui->textEdit_2->append(dayToString[simulatie->getDag()].second);
    }
    else{
        doSimulation(1);
    }
    replaceChart(simulatie->getGegevens(simulatie->getDag()-1));
    ENSURE((unsigned int)simulatie->getDag() == start_day+1, "end_day != start_day+1 && end_day != start_day");
    ENSURE(start_redo == redoStack.size() || start_redo == redoStack.size()+1, "redoStack is niet gepopt/constant gebleven");
    ENSURE(start_und+1 == undoStack.size(), "undoStack is niet gepusht");

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

    undoStack.push(new Simulation(simulatie));
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
    simulatie->simulateManual(vaccins_to_centra, out);
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

void VaccinInterface::on_Manueel_2_clicked()
{
    on_Impressies_currentChanged(2);
}

Simulation *VaccinInterface::getSimulatie() const {
    return simulatie;
}

const std::stack<Simulation *> &VaccinInterface::getRedoStack() const {
    return redoStack;
}

const std::stack<Simulation *> &VaccinInterface::getUndoStack() const {
    return undoStack;
}

void VaccinInterface::on_Gif_export_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save gif"), "./",
                                                    tr("Gif ( *.gif)"));
    if(!fileName.isEmpty()){
        simulatie->exportToGif(fileName.toStdString(), "./tmp");
//        on_stackedWidget_currentChanged(0);


    }
}

