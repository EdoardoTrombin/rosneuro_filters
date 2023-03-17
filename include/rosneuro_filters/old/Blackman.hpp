#ifndef ROSNEURO_FILTERS_BLACKMAN_HPP
#define ROSNEURO_FILTERS_BLACKMAN_HPP

#include <Eigen/Dense>
#include "rosneuro_filters/Filter.hpp"
  
namespace rosneuro {

template <typename T>
class Blackman : public Filter<T> {
	public:
		Blackman(void) {};
		~Blackman(void) {};

		bool configure(void);
		bool apply(const NeuroData<T>& data_in, NeuroData<T>& data_out);

	private:
		unsigned int nsamples_;
		Eigen::Matrix<T, Eigen::Dynamic, 1> window_;
		T wnorm_;
		
};


template<typename T>
bool Blackman<T>::configure(void) {

	if (!Filter<T>::getParam(std::string("nsamples"), this->nsamples_)) {
    	ROS_ERROR("[Blackman] Cannot find param nsamples");
		return false;
	}

	this->window_ = Eigen::Matrix<T, Eigen::Dynamic, 1>::Zero(this->nsamples_);

	for(auto i = 0; i<this->nsamples_; i++)
		this->window_(i)   = (42.0 - 50.0*cos((2.0 * M_PI * i)/(this->nsamples_-1)) + 8.0*cos((4.0 * M_PI * i)/(this->nsamples_ - 1))) / 100.0;

	
	this->wnorm_ = (this->window_.array().pow(2)).sum() / this->window_.size();

	return true;
}

template<typename T>
bool Blackman<T>::apply(const NeuroData<T>& data_in, NeuroData<T>& data_out) {
	T* p_in  = const_cast<T*>(data_in.data());
	T* p_out = const_cast<T*>(data_out.data());

	unsigned int ns_in  = data_in.nsamples();
	unsigned int nc_in  = data_in.nchannels();
	unsigned int ns_out = data_out.nsamples();
	unsigned int nc_out = data_out.nchannels();

	if(ns_in != this->nsamples_) {
		ROS_ERROR("[Blackman] Window configured with different number of samples with respect to data in");
		return false;
	}
	
	if(ns_in != ns_out) {
		ROS_ERROR("[Blackman] Different number of samples between data in and data out");
		return false;
	}
	
	if(nc_in != nc_out) {
		ROS_ERROR("[Blackman] Different number of channels between data in and data out");
		return false;
	}

	Eigen::Map<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>> in(p_in, ns_in, nc_in);
	Eigen::Map<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>> out(p_out, ns_out, nc_out);
	
	out = in.array() * this->window_.replicate(1, in.cols()).array();

	return true;
}

}


#endif
