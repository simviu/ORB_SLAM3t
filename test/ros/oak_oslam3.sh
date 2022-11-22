source env.sh
rosrun ORB_SLAM3 Stereo ../data/ORBvoc.txt ../data/oak-d-lite.yaml false /camera/left/image_raw:=/stereo_inertial_publisher/left/image_rect /camera/right/image_raw:=/stereo_inertial_publisher/right/image_rect


