#include<cmath>
#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Dense>
#include<iostream>

int main(){
    std::cout <<"------Homework 0-------"<<std::endl;
    //Homework 0
    Eigen::Vector3f origin(2,1,1);
    Eigen::Vector3f point(0,0,0);
    Eigen::Matrix3f transform;
    transform << cos(45),-cos(45),1,-cos(45),cos(45),2,0,0,1;
    point = transform * origin;
    std::cout<<point<<std::endl;

    return 0;
}