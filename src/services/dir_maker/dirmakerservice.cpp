#include "dirmakerservice.h"

DirMakerService::DirMakerService()
{
    //obtención del usuario actualmente activo en el SO
    struct passwd* pw = getpwuid(getuid());
    string user_name( pw->pw_name);
    string susi_path = "/home/" + user_name + "/SusiCST";
    this->scenes_path = susi_path + "/" + "landsatScenes";
    this->minis_path = susi_path + "/" + "thumbnails";

    string create_susi = "mkdir " + susi_path;
    string create_scenes_dir = "mkdir " + this->scenes_path;
    string create_tumbnails_dir = "mkdir " + this->minis_path;

    system(create_susi.c_str());
    system(create_scenes_dir.c_str());
    system(create_tumbnails_dir.c_str());
}
