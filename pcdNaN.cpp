#include <pcl/io/pcd_io.h>
#include <pcl/console/print.h>
#include <pcl/console/parse.h>
#include <pcl/console/time.h>
#include <pcl/filters/filter.h>

using namespace pcl;
using namespace pcl::io;
using namespace pcl::console;

typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

void
printHelp (int, char **argv)
{
        print_error ("Syntax is: %s [-format 0|1] input.pcd output.pcd\n", argv[0]);
}

bool
loadCloud (const std::string &filename, PointCloudT &cloud)
{
        TicToc tt;
        print_highlight ("Loading "); print_value ("%s ", filename.c_str ());

        tt.tic ();
        if (loadPCDFile (filename, cloud) < 0)
                return (false);
        print_info ("[done, "); print_value ("%g", tt.toc ()); print_info (" ms : "); print_value ("%d", cloud.width * cloud.height); print_info (" points]\n");
        print_info ("Available dimensions: "); print_value ("%s\n", pcl::getFieldsList (cloud).c_str ());

        return (true);
}

void
saveCloud (const std::string &filename, const PointCloudT &cloud, bool binary)
{
        TicToc tt;
        tt.tic ();

        print_highlight ("Saving "); print_value ("%s ", filename.c_str ());
       
        pcl::io::savePCDFile (filename, cloud, binary);
       
        print_info ("[done, "); print_value ("%g", tt.toc ()); print_info (" ms : "); print_value ("%d", cloud.width * cloud.height); print_info (" points]\n");
}

/* ---[ */
int
main (int argc, char** argv)
{
        print_info ("Remove NaN values from pcd format. For more information, use: %s -h\n", argv[0]);

        if (argc < 3)
        {
                printHelp (argc, argv);
                return (-1);
        }

        // Parse the command line arguments for .pcd and .pcd files
        std::vector<int> pcd_file_indices = parse_file_extension_argument (argc, argv, ".pcd");
        if (pcd_file_indices.size () != 2)
        {
                print_error ("Need one input pcd file and one output pcd file.\n");
                return (-1);
        }
        // Command line parsing
        bool format = true;
        parse_argument (argc, argv, "-format", format);
        print_info ("pcd output format: "); print_value ("%s, ", (format ? "binary" : "ascii"));

        // Load the first file
        PointCloudT cloud;
        if (!loadCloud (argv[pcd_file_indices[0]], cloud))
                return (-1);

        std::vector< int > index;
        removeNaNFromPointCloud (cloud, cloud, index);
        PCL_WARN ("Removing NaN values; density will be lost !\n");

        // Save
        saveCloud (argv[pcd_file_indices[1]], cloud, format);

        return (0);
} 
