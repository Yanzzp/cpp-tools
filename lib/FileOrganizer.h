
#ifndef CPP_TOOLS_H
#define CPP_TOOLS_H



#include "tools.h"


#define print "print"
#define txt "txt"
#define copy "copy"


class FFmpegTool;


class FileOrganizer : public Tools{
private:



    int imageCount = 0;
    int videoCount = 0;
    int audioCount = 0;

    std::vector<std::string> folder_info = {"", "", "", ""};

    uintmax_t folderSize = 0;
    std::mutex fileSizeMutex;



public:
    friend class FFmpegTool;



    uintmax_t get_file_size(std::string path);

    void print_all_files(const std::string &folderPath, int depth = 0);

//    void delete_files(const std::string &path, const std::string &name, bool isDelete = false, bool isPrint = true);

    void delete_files(const std::string &path, const std::vector<std::string> &names, bool isDelete = false, bool isPrint = true);

    void count_imgs_videos_and_audio(const std::string &folderPath, const std::string& option = "");

    void get_folder_size(const std::string &folderPath, bool isPrint = true, bool printAll = false, bool keepData = false);

    void multithread_get_folder_size(const std::string &folderPath, bool isPrint = true);

    void get_folder_info(const std::string &folderPath);

    void change_files_extension(const std::string &folderPath, std::string newExtension, std::string oldExtension = "",
                                bool isChange = false, bool option = false);

    void move_files_to_main_folder(const std::string &folderPath, bool isMove = false);

};


#endif
