## 这是我个人的C++关于管理文件的工具

## 安装

在Linux环境下使用一下命令来安装所需要的库：

``` sh
chmod +x ./shells/install_packets.sh
```



## 工具类介绍

### MyTools Library 

MyTools is a utility library that provides a set of functions to manipulate and retrieve information about files and directories on your filesystem. With MyTools, you can perform a variety of file operations like printing all files in a directory, deleting files, counting media files, changing file extensions, and more. 

#### Features 

- **windows_path_to_linux_path**: Convert Windows-style paths to Linux-style. 
- **copy_to_clipboard**: Copy a given string to the system clipboard. 
- **get_file_size**: Retrieve the size of a file.
- **print_all_files**: Print all files in a directory in a tree-like format. 
- **delete_files**: Delete files or directories containing specific names within a directory.
- **count_imgs_videos_and_audio**: Count the number of image, video, and audio files in a directory. 
- **get_folder_size**: Calculate the total size of a directory. 
- **multithread_get_folder_size**: Calculate the total size of a directory using multithreading for efficiency. 
- **get_folder_info**: Get a summary of media file counts and folder size, then copy the information to the clipboard. 
- **change_files_extension**: Change the file extension of all matching files in a directory. 
- **move_files_to_main_folder**: Move all files from subdirectories to the main directory.



### FFmpegTool 

Class The `FFmpegTool` class is part of a C++ library that interfaces with FFmpeg, a powerful multimedia framework. This class provides a suite of methods for interacting with video files, enabling operations such as retrieving video durations, moving short videos, and checking video properties. It's designed to work in both Linux and Windows environments with ease.

#### Features 

- **get_single_video_time**: Retrieve the duration of a single video file. 
- **get_folder_videos_time**: Calculate the total duration of all video files within a specified folder. 
- **move_short_videos**: Move videos shorter than a specified duration to a different location. 
- **check_video_properties**: Extract various properties from a video file, such as codec, resolution, and frame rate. 
- **get_folder_video_properties**: Gather and list properties of all video files within a specified folder. 



