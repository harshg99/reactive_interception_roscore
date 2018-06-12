#ifndef DEPTH_CALC_H
#define DEPTH_CALC_H

#include <disp_cv/cv_defs_xtion.h>

class depth{
  private:
    ros::NodeHandle nh_;
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;
    image_transport::Publisher image_pub_;
  public:

};

#endif // DEPTH_CALC_H
