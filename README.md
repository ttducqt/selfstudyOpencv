# selfstudyOpencv
- My setup:
  - OS: Ubuntu 16
  - Tools/Packages: pkg-config, g++, c++11
  - Libs: opencv4
## 1. haar_face_detector.cpp <br />
- Compile: ```g++ -std=c++11 haar_face_detector -o main `pkg-config --cflags --libs opencv4` ```<br />
- Run in workspace:
  - Detect in video: ```./main {dir of video}```
  - Detect camera realtime: ```./main```
- How code work:
  - Capture frame from camera or video 
  - Load the cascade                 
  - Detect                
  - Draw rectange
  - Show the result                 
![](https://raw.githubusercontent.com/ttducqt/selfstudyOpencv/master/resource/face.png)
## 2. simple_motion_detector:
  - Compile: ```g++ -std=c++11 simple_motion_detector -o main `pkg-config --cflags --libs opencv4` ```<br />
  - Run in work space:
    - Detect in video: ```./main {dir of video}```
  - How code work:
    - Capture frame from video
    - Blur frame
    - Convert frame to fray
    - Apply background substractor
    - Draw rectangle
    - Show result 
<br />![](https://media.giphy.com/media/MXKXNfp9ACoCTj0gAa/giphy.gif) <br />
Video link: https://youtu.be/9TnoByBmnvE

    




