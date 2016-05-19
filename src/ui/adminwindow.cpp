#include "adminwindow.h"

AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    this->service = Search_Save_Services();
    this->makerService = DirMakerService();
    this->scenes_destiny_path = this->makerService.scenes_path;
    ui->setupUi(this);
    ui->statusBar->showMessage(this->status.c_str());
}

AdminWindow::~AdminWindow()
{
    delete ui;
}
//El botón permite realizar una búsqueda de directorios de escenas especificados a través de PathEddit
void AdminWindow::on_searchButtonn_clicked()
{
    this->status = "Status: ";
    ui->statusBar->showMessage(this->status.c_str());
    QString path = ui->PathEddit->text();
    //Comprueba que el texto de PathEddit sea una ruta válida
    if(!matches(path.toStdString(), PATH_REGEX))
        QMessageBox::warning(this, "Ruta no válida", "Ingrese una ruta válida");
    else{
        //Llama al servicio de búsqueda e informa del éxito o fracaso de la búsqueda
        if(this->service.SearchScenesService(path.toStdString(), &this->scene_data_relations)){
            this->queueLength = std::to_string(this->scene_data_relations.GetFilesCount());

            this->status += " " + this->queueLength + " escenas encontradas";
            ui->statusBar->showMessage(this->status.c_str());
        }
        else{
            QMessageBox::warning(this, "No hay escenas", "No se encontraron escenas en la ruta especificada");
        }
    }
}
//El botón permite buscar una ruta por medio de un FileDialog
void AdminWindow::on_toolButton_clicked()
{
    if(ui->PathEddit->text().length() < 1)
        return;
    QString destinyPath = QFileDialog::getExistingDirectory(this, tr("Seleccionar destino"),
                                                            "/home",
                                                            QFileDialog::ShowDirsOnly |
                                                            QFileDialog::DontResolveSymlinks
                                                            );
    ui->PathEddit->setText(destinyPath);
}
//Este botón permite realizar la copia de las escenas encontradas previamente
void AdminWindow::on_addButton_clicked(){
    //Comprueba que existan escenas que copiar
    if(this->scene_data_relations.FileNamesEmpty()){
        QMessageBox::warning(this, "Advertencia", "No hay escenas por añadir");
        return;
    }
    else{
        std::string queueLength = std::to_string(this->scene_data_relations.GetFilesCount());
        std::string Info = "Se copiarán " + queueLength + " escenas";
        QMessageBox::StandardButton reply = QMessageBox::information(this, "Copiando escenas", Info.c_str(),
                                 QMessageBox::Ok, QMessageBox::Cancel);

        if(reply == QMessageBox::Ok){
            //Filtro de escenas para copiar
            DataFilter filter;
            filter.AplyFilter(&this->scene_data_relations, this->service.GetOriginPath());
            //Copiado de escenas al destino predefinido
            copy_service = new Copy_Service(this->scene_data_relations.GetFileNames(), this->makerService.scenes_path, this->service.GetOriginPath(), this->makerService.minis_path);
            connect(copy_service, SIGNAL(started()), this, SLOT(start_copy_service()));
            copy_service->start();
            connect(copy_service, SIGNAL(finished()), this, SLOT(start_process_service()));
        }
    }
}

void AdminWindow::set_end_process_message(){
    this->statusBar()->showMessage(this->end_process_message.c_str());
}

void AdminWindow::set_start_process_message(){
    this->statusBar()->showMessage(this->start_process_message.c_str());
}

void AdminWindow::start_copy_service(){
    CopyBar *newCopyBar = new CopyBar();
    connect(copy_service, SIGNAL(finished()), newCopyBar, SLOT(close()));
    connect(newCopyBar->GetUi()->CancelButton, SIGNAL(clicked(bool)), copy_service, SLOT(terminate()));
    newCopyBar->show();
}

void AdminWindow::start_process_service(){
    //El proceso se encarga de procesar las escenas y almacenar los datos en postgis
    this->scene_process_thread = new ProcessingThread(&this->scene_data_relations, scenes_destiny_path);
    connect(scene_process_thread, SIGNAL(started()), this, SLOT(set_start_process_message()));
    connect(scene_process_thread, SIGNAL(finished()), this, SLOT(set_end_process_message()));
    connect(scene_process_thread, SIGNAL(finished()), this, SLOT(start_node_call_service()));
    scene_process_thread->start();
}

void AdminWindow::start_node_call_service(){
    string command = "node ../postgis/scripts/mongoTransition.js";
    int script_status = system(command.c_str());
    if(script_status != 0)
        cout<<"Script node activado\n";
    else
        cout<<"Script node no activado\n";
}
