 #include <iostream>
 #include <pcl/io/pcd_io.h>
 #include <pcl/point_types.h> 
 #include <pcl/io/openni_grabber.h>
 #include <pcl/visualization/cloud_viewer.h>

 class SimpleOpenNIViewer
 {
   public:
     SimpleOpenNIViewer () : viewer ("PCL OpenNI Viewer") {}

      void cloud_cb_ (const pcl::PointCloud<pcl::PointXYZ>::ConstPtr &cloud)
 {
   if (!viewer.wasStopped()){
     viewer.showCloud (cloud);
     // nans are not usually an issue if they appear in a .pcd file:http://stackoverflow.com/questions/19716618/too-many-nans-in-pcd-file-is-it-correct
     // *cloud instead of cloud b/c reference is needed:http://www.pcl-users.org/Compiler-isn-t-seeing-overloaded-savePCDFile-stereo-folder-in-trunk-td4022777.html
     //pcl::io::savePCDFile<pcl::PointXYZRGB> ("test_pcd_XYZRGB.pcd", *cloud);
     //pcl::io::savePCDFile ("test_pcd_Bland.pcd", *cloud)
     pcl::io::savePCDFileBinary ("test_pcd_Binary.pcd", *cloud);
   }
 }

     void run ()
     {
       pcl::Grabber* interface = new pcl::OpenNIGrabber();

       boost::function<void (const pcl::PointCloud<pcl::PointXYZ>::ConstPtr&)> f =
         boost::bind (&SimpleOpenNIViewer::cloud_cb_, this, _1);

       interface->registerCallback (f);

       interface->start ();

       while (!viewer.wasStopped())
       {
         boost::this_thread::sleep (boost::posix_time::seconds (1));
       }

       interface->stop ();
     }

     pcl::visualization::CloudViewer viewer;
 };

 int main ()
 {
   SimpleOpenNIViewer v;
   v.run ();
   return 0;
 }
