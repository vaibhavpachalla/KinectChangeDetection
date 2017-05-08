Build and run application

Build files
  1. Build pcdNaN.cpp:
    a. run "cp CMakeListsPCDNAN.txt CMakeLists.txt"
    b. run "cd build"
    c. run "cmake ../"
    d. run "make"
  
   2. Build	openni_grabber.cpp:
    a. run "cp CMakeListsOpenniGrabber.txt CMakeLists.txt"
    b. run "cd build"
    c. run "cmake ../"
    d. run "make"
    
   3. Build iterative_closest_point.cpp:
    a. run "cp CMakeListsIcp.txt CMakeLists.txt"
    b. run "cd build"
    c. run "cmake ../"
    d. run "make"
    
Run application
  1. To get our first kinect poiint cloud,run "sudo ./openni_grabber" . A window will pop up when this command that should be showing the point cloud gotten from the Kinect. If this is not the case, press the "R" key until you see a shite point cloud image on a black background. To properly obtain a point cloud from this program, quit the program by pressing the "x" button on the window displaying the Kinect point cloud. There will be a delay between hitting the "x" button on the window and the window closing, but this is alright. If you try and quit the program by typing "^C" into the command prompt, the point cloud you obtain will be incomplete and of low caliber.
  2. When the previous command is run, a file named "test_pcd_Binary.pcd" will no be present in the directory where openni_grabber was run. Run the following command to change the file to its correct file name: "sudo mv test_pcd_Binary.pcd room_scan1.pcd"
  3.  To get our second kinect poiint cloud,run "sudo ./openni_grabber" . I would advise you to change the scene in which you are capturing the point cloud (eg. moving a box or other object the was also in the other point cloud) so that when you compare the two point clouds, you will be able to see how the program shows the differences between the two point clouds. A window will pop up when this command that should be showing the point cloud gotten from the Kinect. If this is not the case, press the "R" key until you see a shite point cloud image on a black background. To properly obtain a point cloud from this program, quit the program by pressing the "x" button on the window displaying the Kinect point cloud. There will be a delay between hitting the "x" button on the window and the window closing, but this is alright. If you try and quit the program by typing "^C" into the command prompt, the point cloud you obtain will be incomplete and of low caliber.

  4. Before comparing the raw point clouds from our kinect, it is necessary to remove the NaN's (not a numbers) from the point cloud files. To do this we will use our pcdNaN executable. The command line arguements for using this program are as follows: "sudo ./pcdNaN <input file> <output file>". To clean up our raw kinect point clouds, run the following commands: "sudo ./pcdNaN room_scan1.pcd room_scan1.pcd", "sudo ./pcdNaN room_scan2.pcd room_scan2.pcd"
  5. To now compare these two point cloud, run "sudo ./iterative_closest_point" . It will take a while to complete this process so don't be alarmed if there is not an immediate result given when running the aforementioned command. When the command has executed, a window displaying two point clouds will be displayed. The red cloud is the input cloud, and the black cloud is the transformed input cloud. If you made any changes to the scene between taking the first and second point clouds, it should be clearly visible in this point cloud viewer. Now look at your console output. "has converged" tells you if the two point clouds you took line up. If you do not move the kinect between taking point clouds, the value next to "has converged" should be "1", else , if the point clouds do not line up, the value next to "has converged" should be "0". This could be the result of moving the kinect between taking your first and second point clouds. "score" refers to a euclidian fitness score. This score reflects how much of a difference there is between the two point clouds you took. If the euclidian fitness score is near zero, then it means that the two point clouds that you took are extremely similar if not the same. If this score is greater than zero by a good amount (~.00001 in this context), than there is most likely a significant change in the scene. The 4x4 grid of numbers represent an identity matrix. If your were to compare identical point clouds, it would look something like this:
                         1 0 0 0
                         0 1 0 0
                         0 0 1 0
                         0 0 0 1
                         
    In this identity matrix, there are ones going diagonally from the top left corner to the bottom right corner, and all of the other values are zero.
    
    
  FAQ:
      Q: I am seeing graph axis and/or red, green, and black squares. How do I see the point cloud?
      A: Press the "R" key until you see the point cloud
      
      Q: Why am I getting the below errors when I run "./openni_grabber"?
          Warning: USB events thread - failed to set priority. This might cause loss of data...
          terminate called after throwing an instance of 'pcl::IOException'
            what():  : [pcl::PCDWriter::writeBinary] Error during open!
          Aborted (core dumped)

          openni_grabber: /usr/include/boost/smart_ptr/shared_ptr.hpp:646: typename boost::detail::sp_dereference<T>::type boost::shared_ptr<T>::operator*() const [with T = xn::NodeInfo; typename boost::detail::sp_dereference<T>::type = xn::NodeInfo&]: Assertion `px != 0' failed.
          Aborted (core dumped)
      A: Use sudo (eg. "sudo ./openni_grabber")
      
      Q: What to do with these errors: "cp: cannot open 'room_scan1.pcd' for reading: Permission denied" and/or "cp: cannot open 'room_scan2.pcd' for reading: Permission denied" 
      A: Use sudo for the cp command
