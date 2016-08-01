#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

#include <pcl/registration/ndt.h>
#include <pcl/filters/approximate_voxel_grid.h>

#include <pcl/visualization/pcl_visualizer.h>
#include <boost/thread/thread.hpp>
#include <pcl/point_types.h>
#include <pcl/registration/icp.h>
#include <pcl/visualization/point_cloud_color_handlers.h>

int
main (int argc, char** argv)
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out (new pcl::PointCloud<pcl::PointXYZ>);
  
  // \brief A point structure representing Euclidean xyz coordinates.
  struct PointXYZ
  {
     float x;
     float y;
     float z;
  };
  // Loading first scan of room.
  pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud (new pcl::PointCloud<pcl::PointXYZ>);
  if (pcl::io::loadPCDFile<pcl::PointXYZ> ("room_scan1.pcd", *cloud_out) == -1)
  {
    PCL_ERROR ("Couldn't read file room_scan1.pcd \n");
    return (-1);
  }
  //std::cout << "Loaded " << target_cloud->size () << " data points from room_scan1.pcd" << std::endl;

  // Loading second scan of room from new perspective.
  pcl::PointCloud<pcl::PointXYZ>::Ptr input_cloud (new pcl::PointCloud<pcl::PointXYZ>);
  if (pcl::io::loadPCDFile<pcl::PointXYZ> ("room_scan2.pcd", *cloud_in) == -1)
  {
    PCL_ERROR ("Couldn't read file room_scan2.pcd \n");
    return (-1);
  }
  //std::cout << "Loaded " << input_cloud->size () << " data points from room_scan2.pcd" << std::endl;
 
   //for (size_t i = 0; i < cloud_in->points.size (); ++i)
    //cloud_out->points[i].x = cloud_in->points[i].x + 0.7f;
   //std::cout << "Transformed " << cloud_in->points.size () << " data points:" << std::endl;
  //for (size_t i = 0; i < cloud_out->points.size (); ++i)
    //std::cout << "    " << cloud_out->points[i].x << " " << cloud_out->points[i].y << " " << cloud_out->points[i].z << std::endl;
  pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
  icp.setInputCloud(cloud_in);
  icp.setInputTarget(cloud_out);
  //pcl::PointCloud<pcl::PointXYZ> Final;
  pcl::PointCloud<pcl::PointXYZ>::Ptr Final (new pcl::PointCloud<pcl::PointXYZ>);
  icp.align(*Final);
  std::cout << "has converged:" << icp.hasConverged() << " score: " <<
  icp.getFitnessScore() << std::endl;
  std::cout << icp.getFinalTransformation() << std::endl;

  //pcl::PointCloud<pcl::PointXYZ>::Ptr Final (new pcl::PointCloud<pcl::PointXYZ>);
  //Final = FinalCloud
  // Saving transformed input cloud.
  //pcl::io::savePCDFileASCII ("room_scan2_transformed.pcd", *Final);

  // Initializing point cloud visualizer
  boost::shared_ptr<pcl::visualization::PCLVisualizer>
  viewer_final (new pcl::visualization::PCLVisualizer ("3D Viewer"));
  viewer_final->setBackgroundColor (255, 255, 255);

  // Coloring and visualizing target cloud (red).
  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ>
  cloud_color1 (cloud_out, 255, 0, 0);
  
  viewer_final->addPointCloud<pcl::PointXYZ> (cloud_out, cloud_color1, "cloud_out");
  viewer_final->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cloud_out");
  
  // Coloring and visualizing transformed input cloud (green).
  //http://docs.pointclouds.org/trunk/classpcl_1_1visualization_1_1_point_cloud_color_handler_custom.html
  //boost::shared_ptr<pcl::PointCloud<pcl::PointXYZ> >(Final);
  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> 
  Final_color (Final, 0, 0, 0);
  viewer_final->addPointCloud<pcl::PointXYZ> (Final, Final_color, "Final");
  viewer_final->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "Final");
  
  // Starting visualizer
  viewer_final->addCoordinateSystem (1.0);
  viewer_final->initCameraParameters ();
 
  // Wait until visualizer window is closed.
  while (!viewer_final->wasStopped ())
  {
    viewer_final->spinOnce (100);
    boost::this_thread::sleep (boost::posix_time::microseconds (100000));
  }
   
  return (0);
}
