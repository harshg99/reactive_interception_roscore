
#include<disp_cv/regression.h>
#include<disp_cv/traj_predictor.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "traj");
  predict var1;
  regression var2;
  ros::spin();
  return 0;
}
