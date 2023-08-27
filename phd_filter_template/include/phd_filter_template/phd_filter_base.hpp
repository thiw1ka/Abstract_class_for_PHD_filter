#include <iostream>

#include "ros/ros.h"
/*
 * @brief PhdFilter class serve as a abstract template for PHD (Probability Hypothesis Density) Filter.
 *        Contains the basic structure of a phd filter. 
 * 
 * 
 * @author Thivanka_perera <thiva@uri.edu> 
 * 
 */
class PhdFilter {

    public :

        PhdFilter(ros::NodeHandle n, ros::Rate filter_freq);

        virtual void timeUpdate() = 0;

        virtual void measurementUpdate() = 0;

        virtual void pruningStep() = 0;

        virtual void mergingStep() = 0;

    private:

        ros::NodeHandle n_;

        ros::Rate r_;

        int filter_state;

        enum FILTER_STEPS {
            INIT = 0,
            TIMEUPDATE = 1,
            MEASUREMENTUPDATE = 2,
            OTHER = 3
        };

        /**
         * @brief function pointers to time update and measurment update
         * 
         */
        typedef void(PhdFilter::* FilterFunctionPtr)();

        
    


};