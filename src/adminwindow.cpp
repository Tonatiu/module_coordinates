#include "adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    this->service = Search_Save_Services();
    ui->setupUi(this);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}
//El botón permite realizar una búsqueda de directorios de escenas especificados a través de PathEddit
void AdminWindow::on_searchButtonn_clicked()
{
    QString path = ui->PathEddit->text();
    //Comprueba que el texto de PathEddit sea una ruta válida
    if(!this->service.matches(path.toStdString(), "(\/[a-zA-Z0-9_]*)+"))
        QMessageBox::warning(this, "Ruta no válida", "Ingrese una ruta válida");
    else{
        //Llama al servicio de búsqueda e informa del éxito o fracaso de la búsqueda
        if(this->service.SearchScenesService(path.toStdString())){
            QMessageBox::information(this, "Escenas encontradas", "Se encontraron x escenas");
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
void AdminWindow::on_addButton_clicked()
{   //Comprueba que existan escenas que copiar
    if(this->service.QueueisEmpty()){
        QMessageBox::warning(this, "Advertencia", "No hay escenas por añadir");
        return;
    }
    //obtención del usuario actualmente activo en el SO
    struct passwd* pw = getpwuid(getuid());
    std::string user_name( pw->pw_name);
    //Creación de la ruta donde se copiarán las escenas
    std::string scenes_path = "/home/" + user_name + "/LandsatScenes";
    std::string makeScenesDir = "mkdir " + scenes_path;
    system(makeScenesDir.c_str());
    //Verifica que el servicio de copiado haga bien su trabajo
    if(this->service.CopyService(scenes_path)){
        QMessageBox::information(this, "Copiado exitoso", "Las escenas se han añadido correctamente");
    }
    else{
        QMessageBox::warning(this, "Error al copiar", "Algunas escenas no pudieron copiarse a la carpeta de destino");
    }
}
