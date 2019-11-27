// Boost
#include <boost/program_options.hpp>

// YAML
#include <yaml-cpp/yaml.h>

// Octomap
#include <octomap/octomap.h>
#include <octomap/OcTree.h>

using namespace std;
using namespace octomap;

void updateNode(OcTree& tree, const point3d& pos, bool occupied, double resolution, bool shift)
{
  if (shift) {
    const double o = resolution / 4;
    point3d p1(pos.x() - o, pos.y() - o, pos.z() - o);
    tree.updateNode(p1, occupied);
    point3d p2(pos.x() - o, pos.y() - o, pos.z() + o);
    tree.updateNode(p2, occupied);
    point3d p3(pos.x() - o, pos.y() + o, pos.z() - o);
    tree.updateNode(p3, occupied);
    point3d p4(pos.x() - o, pos.y() + o, pos.z() + o);
    tree.updateNode(p4, occupied);
    point3d p5(pos.x() + o, pos.y() - o, pos.z() - o);
    tree.updateNode(p5, occupied);
    point3d p6(pos.x() + o, pos.y() - o, pos.z() + o);
    tree.updateNode(p6, occupied);
    point3d p7(pos.x() + o, pos.y() + o, pos.z() - o);
    tree.updateNode(p7, occupied);
    point3d p8(pos.x() + o, pos.y() + o, pos.z() + o);
    tree.updateNode(p8, occupied);
  } else {
    tree.updateNode(pos, occupied);
  }
}

int main(int argc, char** argv)
{
  namespace po = boost::program_options;
  // Declare the supported options.
  po::options_description desc("Allowed options");
  std::string mapFile;
  std::string outputFile;
  double resolution = 1.0;
  bool shift;
  double xoffset, yoffset, zoffset;
  desc.add_options()
      ("help", "produce help message")
      ("map,m", po::value<std::string>(&mapFile)->required(), "input file for map (YAML)")
      ("output,o", po::value<std::string>(&outputFile)->required(), "output file with octomap")
      ("resolution,r", po::value<double>(&resolution)->default_value(1.0), "Grid cell resolution")
      ("shift", po::bool_switch(&shift)->default_value(false), "Shift cells by resolution/2")
      ("xoffset", po::value<double>(&xoffset)->default_value(0.0), "xoffset")
      ("yoffset", po::value<double>(&yoffset)->default_value(0.0), "yoffset")
      ("zoffset", po::value<double>(&zoffset)->default_value(0.0), "zoffset")
  ;

  try
  {
    po::variables_map vm;
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

  OcTree tree (shift ? resolution / 2 : resolution);

  YAML::Node map = YAML::LoadFile(mapFile);
  const auto& dimensions = map["map"]["dimensions"];
  double dimx = dimensions[0].as<double>() * resolution;
  double dimy = dimensions[1].as<double>() * resolution;
  double dimz = 1;
  if (dimensions.size() > 2) {
    dimz = dimensions[2].as<double>() * resolution;
  }

  for (double x = 0; x < dimx; x+=resolution) {
    for (double y = 0; y < dimy; y+=resolution) {
      for (double z = 0; z < dimz; z+=resolution) {
        point3d pos(x + xoffset, y + yoffset, z + zoffset);
        updateNode(tree, pos, false, resolution, shift);
      }
    }
  }

  // read obstacles
  for (const auto& obstacle : map["map"]["obstacles"]) {
    // read position
    point3d pos(
      obstacle[0].as<double>() * resolution + xoffset,
      obstacle[1].as<double>() * resolution + yoffset,
      obstacle.size() > 2 ? obstacle[2].as<double>() * resolution + zoffset : zoffset);
    updateNode(tree, pos, true, resolution, shift);
  }

  tree.prune();
  tree.writeBinary(outputFile);
}
