#include "icp.hpp"

icp::icp(std::string config_path)
: config__(config_path)
{
    builder__.ICP_options.loadFromConfigFile(config__, "MappingApplication");
    builder__.ICP_params.loadFromConfigFile(config__, "ICP");
    builder__.setVerbosityLevel(mrpt::utils::VerbosityLevel::LVL_INFO);
    builder__.initialize();
}

void icp::save()
{
    builder__.getCurrentlyBuiltMetricMap()
                   ->m_octoMaps[0]->saveMetricMapRepresentationToFile("map.bt");
}
