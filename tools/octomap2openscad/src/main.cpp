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
      ("output,o", po::value<std::string>(&outputFile)->required(), "output file for openscad (*.scad)")
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
  std::ofstream output(outputFile);
  input.updateInnerOccupancy();
  input.prune();

  auto iter = input.begin_leafs();
  auto iterEnd = input.end_leafs();
  for (; iter != iterEnd; ++iter) {
    // std::cout << iter.getCoordinate() << std::endl;
    // std::cout << "Node value: " << iter->getOccupancy() << std::endl;
    const point3d& pos = iter.getCoordinate();
    bool occupied = iter->getOccupancy() > 0.85;

    if (occupied) {
      // translate([6, 0, 0]) cube([1.0,1.0,1.0], center = true);
      // std::cout << pos << " " << iter.getSize() << std::endl;
      output << "translate([" << pos.x() << "," << pos.y() << "," << pos.z() << "]) cube(" << iter.getSize() << ", center = true);" << std::endl;
    }
  }

}
