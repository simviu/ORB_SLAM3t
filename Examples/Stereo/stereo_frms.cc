/**
* This file is part of ORB-SLAM3
*
* Copyright (C) 2017-2021 Carlos Campos, Richard Elvira, Juan J. Gómez Rodríguez, José M.M. Montiel and Juan D. Tardós, University of Zaragoza.
* Copyright (C) 2014-2016 Raúl Mur-Artal, José M.M. Montiel and Juan D. Tardós, University of Zaragoza.
*
* ORB-SLAM3 is free software: you can redistribute it and/or modify it under the terms of the GNU General Public
* License as published by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ORB-SLAM3 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
* the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with ORB-SLAM3.
* If not, see <http://www.gnu.org/licenses/>.
*/

#include<iostream>
#include<algorithm>
#include<fstream>
#include<iomanip>
#include<chrono>

#include<opencv2/core/core.hpp>

#include<System.h>

using namespace std;


int main(int argc, char **argv)
{  
    if(argc < 3)
    {
        cerr << endl << "Usage: ./stereo_frms voc_file cfg_file" << endl;

        return 1;
    }


    cout << endl << "-------" << endl;
    cout.precision(17);

    // Create SLAM system. It initializes all system threads and gets ready to process frames.
    ORB_SLAM3::System SLAM(argv[1],argv[2],ORB_SLAM3::System::STEREO, true);

    cv::Mat imLeft, imRight;


    // Seq loop
    int i=0;
    double t = 0;
    double FPS = 30.0;
    double dt = t/FPS;
    while(1)
    {
        i++;
        // Read left and right images from file
        string sf = std::to_string(i)+".png";
        string sfL = "frms/L/"+sf;
        string sfR = "frms/R/"+sf;
        imLeft  = cv::imread(sfL, cv::IMREAD_UNCHANGED); //,cv::IMREAD_UNCHANGED);
        imRight = cv::imread(sfR, cv::IMREAD_UNCHANGED); //,cv::IMREAD_UNCHANGED);

        if(imLeft.empty() || imRight.empty())
            break;




        // Pass the images to the SLAM system
        SLAM.TrackStereo(imLeft,imRight,t, vector<ORB_SLAM3::IMU::Point>(), sfL);




        t += dt;
        usleep(dt*1e6); // 1e6
    }


    // Stop all threads
    SLAM.Shutdown();

    SLAM.SaveTrajectoryEuRoC("frms/cam_pose.txt");
    SLAM.SaveKeyFrameTrajectoryEuRoC("frms/keyfrms.txt");


    return 0;
}

