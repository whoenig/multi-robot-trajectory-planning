// Boost
#include <boost/program_options.hpp>

// YAML
#include <yaml-cpp/yaml.h>

// Octomap
#include <octomap/octomap.h>
#include <octomap/OcTree.h>

using namespace std;
using namespace octomap;

int main(int argc, char** argv)
{
  namespace po = boost::program_options;
  // Declare the supported options.
  po::options_description desc("Allowed options");
  std::string inputFile;
  std::string outputFile;
  // double occupancyThreshold;
  desc.add_options()
      ("help", "produce help message")
      ("input,i", po::value<std::string>(&inputFile)->required(), "input file octomap (*.bt))")
  ;
  po::variables_map vm;

  try
  {
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
      std::cout << desc << "\n";
      return 0;
    }
  }
  catch(po::error& e)
  {
    std::cerr << e.what() << std::endl << std::endl;
    std::cerr << desc << std::endl;
    return 1;
  }

  OcTree input(inputFile);
  input.updateInnerOccupancy();
  input.prune();

  double freeVolume = 0;
  double occupiedVolume = 0;

  auto iter = input.begin_leafs();
  auto iterEnd = input.end_leafs();
  for (; iter != iterEnd; ++iter) {
    if (input.isNodeOccupied(*iter)) {
      occupiedVolume += pow(iter.getSize(), 3);
    } else {
      freeVolume += pow(iter.getSize(), 3);
    }
  }

  double minx, miny, minz, maxx, maxy, maxz;
  input.getMetricMin(minx, miny, minz);
  input.getMetricMax(maxx, maxy, maxz);

  std::cout << "Resolution: " << input.getResolution() << " m" << std::endl;
  std::cout << "# leaf nodes: " << input.getNumLeafNodes() << std::endl;
  std::cout << "Size: " << maxx - minx << " x " << maxy - miny << " x " << maxz - minz << " m" << std::endl;

  std::cout << "Bounding box: " << std::endl;
  std::cout << minx << "," << maxx << std::endl;
  std::cout << miny << "," << maxy << std::endl;
  std::cout << minz << "," << maxz << std::endl;

  std::cout << "occupied: " << occupiedVolume / (occupiedVolume + freeVolume) * 100.0 << " %" << std::endl;

}
