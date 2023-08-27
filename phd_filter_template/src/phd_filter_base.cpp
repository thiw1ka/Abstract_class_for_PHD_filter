#include "phd_filter_template/phd_filter_base.hpp"

PhdFilter::PhdFilter(ros::NodeHandle n, ros::Rate filter_freq) : n_(n), r_(filter_freq) {

    FilterFunctionPtr timeUpdateFunctionPtr = &PhdFilter::timeUpdate;
    FilterFunctionPtr  measurementUpdateFunctionPtr = &PhdFilter::measurementUpdate;
    filter_state = FILTER_STEPS::INIT;
    try{
        while (ros::ok){

            if (filter_state == FILTER_STEPS::INIT) {
                // timeUpdatePtr = &PhdFilter::timeUpdate;
                // measurementUpdatePtr = &PhdFilter::measurementUpdate;

                filter_state = FILTER_STEPS::TIMEUPDATE;
            }

            else if (filter_state == FILTER_STEPS::TIMEUPDATE) {

                (this ->* timeUpdateFunctionPtr) ();
                filter_state = FILTER_STEPS::MEASUREMENTUPDATE;
            }

            else if (filter_state == FILTER_STEPS::MEASUREMENTUPDATE) {
                (this ->* measurementUpdateFunctionPtr) ();
                filter_state = FILTER_STEPS::OTHER;
            }

            else if (filter_state == FILTER_STEPS::OTHER) {

                filter_state = FILTER_STEPS::TIMEUPDATE;
            }

            r_.sleep();
        }
    }
    catch(std::exception& e) {
        std::cout << "[Filter] Error in  filter execution" << std::endl;
        std::cout << "[Filter] standard exception: " << e.what() << std::endl;
        std::cout << "[Filter] exiting from filter....." << std::endl;
        exit(0);
    }
}