# Usage: ./stereo_euroc 
#       path_to_vocabulary 
#       path_to_settings 
#       path_to_sequence_folder_1 
#       path_to_times_file_1 
#       (path_to_image_folder_2 
#       path_to_times_file_2 ... 
#       path_to_image_folder_N path_to_times_file_N) 
#       (trajectory_file_name)

../bin/stereo_euroc \
    ../data/ORBvoc.txt \
    ../data/EuroC.yaml \
    ../data/MH05/mav0 \
    ../data/EuRoC_TimeStamps
    
