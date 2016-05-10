#include "copy_service.h"
#include <opencv2/opencv.hpp>

Copy_Service::Copy_Service(vector<string> *queue, string destiny_path, string origin_path)
{
    this->scene_path_queue = queue;
    this->Destiny_Path = destiny_path;
    this->Origin_Path = origin_path;
}

void Copy_Service::run(){
    if(scene_path_queue->empty())
        return;
    for(int i = 0; (i < scene_path_queue->size()) && this->running; i++){
        string filename = (*this->scene_path_queue)[i];
        CopyThread *copy_thread = new CopyThread(this->Origin_Path, this->Destiny_Path, filename);
        copy_thread->start();
        copy_thread->wait();

        string rutaNombreGen = this->Destiny_Path +"/"+ filename + "/"+filename;
        cout<<"\n"+ rutaNombreGen + "\n";
        string rutaTIFF_B = rutaNombreGen + "_B1.TIF";
        string rutaTIFF_G = rutaNombreGen + "_B2.TIF";
        string rutaTIFF_R = rutaNombreGen + "_B3.TIF";
        cv::Mat inputImage_B = cv::imread(rutaTIFF_B, 0);
        cv::Mat inputImage_G = cv::imread(rutaTIFF_G, 0);
        cv::Mat inputImage_R = cv::imread(rutaTIFF_R, 0);

        std::vector<cv::Mat> array_to_merge;
        array_to_merge.push_back(inputImage_B); //B
        array_to_merge.push_back(inputImage_G); //G
        array_to_merge.push_back(inputImage_R); //R

        cv::Mat final_color; // aqui queda la imagen a color de las 3 bandas :)
        cv::Mat chiquita;
        cout<<"merge\n";
        cv::merge(array_to_merge, final_color);

        cv::resize(final_color, chiquita, cv::Size(350,350), 0, 0, 1);
        vector<int> compression_params;
        compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
        string ruta_NombreThumbNail = "/home/luis/susi/thumbnails/" +filename+".png";
        cv::imwrite(ruta_NombreThumbNail, chiquita, compression_params);
        cout<< ruta_NombreThumbNail + " guardada!! :D \n";
    }
}

bool Copy_Service::GetStatus(){
    return this->copy_status;
}

void Copy_Service::stop_service(){
    this->running = false;
}
