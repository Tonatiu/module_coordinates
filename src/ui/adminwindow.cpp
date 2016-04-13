#include "./include/ui/adminwindow.h"
#include "ui_adminwindow.h"
#include <opencv2/opencv.hpp>

AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    this->service = Search_Save_Services();
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
    QString path = ui->PathEddit->text();
    //Comprueba que el texto de PathEddit sea una ruta válida
    if(!matches(path.toStdString(), "(\/[a-zA-Z0-9_]*)+"))
        QMessageBox::warning(this, "Ruta no válida", "Ingrese una ruta válida");
    else{
        //Llama al servicio de búsqueda e informa del éxito o fracaso de la búsqueda
        if(this->service.SearchScenesService(path.toStdString())){
            this->queueLength = std::to_string(this->service.getQueueLength());
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
    if(this->service.QueueisEmpty()){
        QMessageBox::warning(this, "Advertencia", "No hay escenas por añadir");
        return;
    }
    else{
        std::string queueLength = std::to_string(this->service.getQueueLength());
        std::string Info = "Se copiarán " + queueLength + " escenas";
        QMessageBox::StandardButton reply = QMessageBox::information(this, "Copiando escenas", Info.c_str(),
                                 QMessageBox::Ok, QMessageBox::Cancel);

        if(reply == QMessageBox::Cancel)
            return;
    }

    //obtención del usuario actualmente activo en el SO
    struct passwd* pw = getpwuid(getuid());
    std::string user_name( pw->pw_name);
    //Creación de la ruta donde se copiarán las escenas
    std::string scenes_destiny = "/home/" + user_name + "/LandsatScenes";
    std::string makeScenesDir = "mkdir " + scenes_destiny;
    system(makeScenesDir.c_str());
    //Verifica que el servicio de copiado haga bien su trabajo
    if(this->service.CopyService(scenes_destiny)){
        this->service.GetDataService();
        QMessageBox::information(this, "Copiado exitoso", "Las escenas se han añadido correctamente");
    }
    else{
        QMessageBox::warning(this, "Error al copiar", "Algunas escenas no pudieron copiarse a la carpeta de destino");
    }
}

void AdminWindow::on_pushButton_clicked()
{
    /*std::string rutaTIFF_1 = "/home/luis/Documentos/SatellitalImages/LE70270472003048EDC00/LE70270472003048EDC00_B1.TIF";
    std::string rutaTIFF_2 = "/home/luis/Documentos/SatellitalImages/LE70270472003048EDC00/LE70270472003048EDC00_B2.TIF";
    std::string rutaTIFF_3 = "/home/luis/Documentos/SatellitalImages/LE70270472003048EDC00/LE70270472003048EDC00_B3.TIF";
    std::string rutaLena = "/home/luis/Descargas/sample-opencv/lena.jpg";
    * http://docs.opencv.org/3.0-beta/modules/imgcodecs/doc/reading_and_writing_images.html
    flags –
    Flags specifying the color type of a loaded image:

        CV_LOAD_IMAGE_ANYDEPTH - If set, return 16-bit/32-bit image when the input has the corresponding depth, otherwise convert it to 8-bit.
        CV_LOAD_IMAGE_COLOR - If set, always convert image to the color one
        CV_LOAD_IMAGE_GRAYSCALE - If set, always convert image to the grayscale one

        >0 Return a 3-channel color image.
            Note
            In the current implementation the alpha channel, if any, is stripped from the output image. Use negative value if you need the alpha channel.
        =0 Return a grayscale image.
        <0 Return the loaded image as is (with alpha channel).

    cv::Mat inputImage_1 = cv::imread(rutaTIFF_1, 0);
    cv::Mat inputImage_2 = cv::imread(rutaTIFF_2, 0);
    cv::Mat inputImage_3 = cv::imread(rutaTIFF_3, 0);
    cv::Mat inputLena = cv::imread(rutaLena);

    std::vector<cv::Mat> array_to_merge;
    array_to_merge.push_back(inputImage_1); //B
    array_to_merge.push_back(inputImage_2); //G
    array_to_merge.push_back(inputImage_3); //R

    cv::Mat final_color; // aqui queda la imagen a color de las 3 bandas :)

    cv::merge(array_to_merge, final_color);
    cv::imshow("a colorcin",final_color);

    qDebug( "total() es: %d", inputImage_1.total() );
    qDebug( "depth() es: %d", inputImage_1.depth() );
    qDebug( "channels() es: %d", inputImage_1.channels() );
    qDebug( "size().width es: %d", inputImage_1.size().width );
    qDebug( "size().height es: %d", inputImage_1.size().height );
    qDebug( "size().area es: %d", inputImage_1.size().area() );
    //qDebug( "begin() es: %d", inputImage.begin() );
    //qDebug( "end() es: %d", inputImage.end() );

    * Del siguiente link esta la referencia del codigo de lectura :)
     * http://longstryder.com/2014/07/which-way-of-accessing-pixels-in-opencv-is-the-fastest/
     * en el siguiente tambien hay algo de info :) que no es bueno usar .at()
     * http://stackoverflow.com/questions/11977954/opencv-matrix-iteration
     * http://stackoverflow.com/questions/25221421/c-opencv-fast-pixel-iteration
     * http://stackoverflow.com/questions/28423701/efficient-way-to-loop-through-pixels-of-16-bit-mat-in-opencv
     * http://answers.opencv.org/question/38/what-is-the-most-effective-way-to-access-cvmat-elements-in-a-loop/
     * +++++ y como cabe destacar usé la lectura eficient, la segura esta en el siguiente link
     * http://docs.opencv.org/2.4/doc/tutorials/core/how_to_scan_images/how_to_scan_images.html
     * pero es mas lenta xD :D

qDebug( "rows: %d, cols: %d", inputLena.rows, inputLena.cols );
    //vamos a iterar la imagen de 3 bandas
    for (int row = 0; row < inputLena.rows; ++row)
    {
        const uchar *ptr = inputLena.ptr(row);
        for (int col = 0; col < inputLena.cols; ++col)
        {
            const uchar * uc_pixel = ptr;
            int a = uc_pixel[0];
            int b = uc_pixel[1];
            int c = uc_pixel[2];
            if(a != 0 && b != 0 && c != 0)
                qDebug( "b: %d, g: %d, r:%d", a, b, c );
            //sum += a + b + c;
            qDebug( "b: %d, g: %d, r:%d", a, b, c );

            ptr += 3;
        }
    }*/


}
