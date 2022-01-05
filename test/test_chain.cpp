#include <ros/ros.h>
#include <ros/console.h>
#include "rosneuro_data/NeuroData.hpp"
#include "rosneuro_filters/FilterChain.hpp"

int main(int argc, char** argv) {


	ros::init(argc, argv, "test_chain");

	if( ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME, ros::console::levels::Debug) ) {
	   ros::console::notifyLoggerLevelsChanged();
	}

	rosneuro::FilterChain<float> chain("float");

	if(chain.configure("ChainCfgTest") == false) {
		ROS_ERROR("Chain configuration failed");
		return false;
	}
	ROS_INFO("Chain configuration succeeded");

	//rosneuro::NeuroData<float> in(4, 3, "EEG");
	//rosneuro::NeuroData<float> out(4, 3, "EEG");
	//		
	//Eigen::MatrixXf data = Eigen::MatrixXf::Random(4, 3);
	//std::cout<<data<<std::endl;
	//std::copy(data.data(), data.data() + data.size(), in.data());

	//if(dc->apply(in, out) == false) {
	//	std::cout<<"Dc filter failed"<<std::endl;
	//	ros::shutdown();
	//	return -1;
	//}
	//	
	//std::cout<<"Dc filter succesfully applied"<<std::endl;
	//Eigen::Map<Eigen::MatrixXf> eout(out.data(), 4, 3);

	//std::cout<<eout<<std::endl;

	ros::shutdown();
	return 0;

}
