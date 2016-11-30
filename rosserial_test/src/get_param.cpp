#include "ros/ros.h"

namespace rosserial {
#include "rosserial_test/ros.h"
}

#include <gtest/gtest.h>
#include "rosserial_test/fixture.h"

/**
 * Get single int parameter by a rosserial client.
 */
TEST_F(SingleClientFixture, int_param) {
  client_nh.initNode();
  bool got_param = false;
  int int_param;
  int client_int_param;

  nh.getParam("int", int_param);

  while (!client_nh.connected())
  {
    client_nh.spinOnce();
    ros::spinOnce();
    ros::Duration(0.01).sleep();
  }
  got_param = client_nh.getParam("int", &client_int_param);

  EXPECT_TRUE(got_param);
  EXPECT_EQ(int_param, client_int_param);
}

/**
 * Get single float parameter by a rosserial client.
 */
TEST_F(SingleClientFixture, float_param) {
  client_nh.initNode();
  bool got_param = false;
  float float_param;
  float client_float_param;

  nh.getParam("float", float_param);

  while (!client_nh.connected())
  {
    client_nh.spinOnce();
    ros::spinOnce();
    ros::Duration(0.01).sleep();
  }
  got_param = client_nh.getParam("float", &client_float_param);

  EXPECT_TRUE(got_param);
  EXPECT_EQ(float_param, client_float_param);
}

/**
 * Get string parameter by a rosserial client.
 */
TEST_F(SingleClientFixture, string_param) {
  client_nh.initNode();
  bool got_param = false;
  std::string string_param;
  char client_string_param[100];
  char *client_string_list[1] = {client_string_param};

  nh.getParam("string", string_param);

  while (!client_nh.connected())
  {
    client_nh.spinOnce();
    ros::spinOnce();
    ros::Duration(0.01).sleep();
  }
  got_param = client_nh.getParam("string", client_string_list);

  EXPECT_TRUE(got_param);
  EXPECT_STREQ(string_param.c_str(), client_string_param);
}

/**
 * Get int array parameter by a rosserial client.
 */
TEST_F(SingleClientFixture, int_array_param) {
  client_nh.initNode();
  bool got_param = false;
  std::vector<int> int_param;
  int client_int_param[3];

  nh.getParam("int_array", int_param);

  while (!client_nh.connected())
  {
    client_nh.spinOnce();
    ros::spinOnce();
    ros::Duration(0.01).sleep();
  }
  got_param = client_nh.getParam("int_array", client_int_param, 3);

  EXPECT_TRUE(got_param);
  ASSERT_EQ(int_param.size(), 3);
  for (int i=0; i<3; i++)
  {
    EXPECT_EQ(int_param[i], client_int_param[i]);
  }
}

/**
 * Get float array parameter by a rosserial client.
 */
TEST_F(SingleClientFixture, float_array_param) {
  client_nh.initNode();
  bool got_param = false;
  std::vector<float> float_param;
  float client_float_param[3];

  nh.getParam("float_array", float_param);

  while (!client_nh.connected())
  {
    client_nh.spinOnce();
    ros::spinOnce();
    ros::Duration(0.01).sleep();
  }
  got_param = client_nh.getParam("float_array", client_float_param, 3);

  EXPECT_TRUE(got_param);
  ASSERT_EQ(float_param.size(), 3);
  for (int i=0; i<3; i++)
  {
    EXPECT_EQ(float_param[i], client_float_param[i]);
  }
}

/**
 * Get string array parameter by a rosserial client.
 */
TEST_F(SingleClientFixture, string_array_param) {
  client_nh.initNode();
  bool got_param = false;
  std::vector<std::string> string_param;
  char client_string_param1[100];
  char client_string_param2[100];
  char client_string_param3[100];
  char *client_string_list[3] = {client_string_param1, client_string_param2, client_string_param3};

  nh.getParam("string_array", string_param);

  while (!client_nh.connected())
  {
    client_nh.spinOnce();
    ros::spinOnce();
    ros::Duration(0.01).sleep();
  }
  got_param = client_nh.getParam("string_array", client_string_list, 3);

  EXPECT_TRUE(got_param);
  ASSERT_EQ(string_param.size(), 3);
  for (int i=0; i<3; i++)
  {
    EXPECT_STREQ(string_param[i].c_str(), client_string_list[i]);
  }
}

/**
 * Get mixed type array parameter by a rosserial client.
 */
/*
 * Not timing out when asking for an invalid parameter
 *
TEST_F(SingleClientFixture, mixed_array_param) {
  client_nh.initNode();
  bool got_param = true;
  int client_int_array[3];

  while (!client_nh.connected())
  {
    client_nh.spinOnce();
    ros::spinOnce();
    ros::Duration(0.1).sleep();
  }
  got_param = client_nh.getParam("mixed_array", client_int_array, 3);

  EXPECT_FALSE(got_param);
}
*/

/**
 * Get nonexistent parameter by a rosserial client.
 */
 /*
 * Not timing out when asking for nonexisten param
 *
TEST_F(SingleClientFixture, nonexistent_param) {
  client_nh.initNode();
  bool got_param = true;
  int client_int_array;

  while (!client_nh.connected())
  {
    client_nh.spinOnce();
    ros::spinOnce();
    ros::Duration(0.01).sleep();
  }
  got_param = client_nh.getParam("nonexisting", &client_int_array);

  EXPECT_FALSE(got_param);
}
*/


int main(int argc, char **argv){
  ros::init(argc, argv, "test_get_param");
  ros::start();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
