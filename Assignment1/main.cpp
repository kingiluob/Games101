#include "Triangle.hpp"
#include "rasterizer.hpp"
#include <eigen3/Eigen/Eigen>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>
constexpr double MY_PI = 3.1415926;

//comment mac 0318 002
Eigen::Matrix4f get_view_matrix(Eigen::Vector3f eye_pos)
{
    Eigen::Matrix4f view = Eigen::Matrix4f::Identity();

    Eigen::Matrix4f translate;
    translate << 1, 0, 0, -eye_pos[0], 0, 1, 0, -eye_pos[1], 0, 0, 1,
        -eye_pos[2], 0, 0, 0, 1;

    view = translate * view;

    return view;
}

Eigen::Matrix4f get_model_matrix(float rotation_angle)
{
    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();

    // TODO: Implement this function
    // Create the model matrix for rotating the triangle around the Z axis.
    // Then return it.
    float angle = rotation_angle * MY_PI / 180;
    model(0,0)= cos(angle);
    model(0,1) = -sin(angle);
    model(1,0) = sin(angle);
    model(1,1) = cos(angle);
    return model;
}
Eigen::Matrix4f get_rotation(Vector3f axis,float angle)
{
    float angle_x,angle_y,angle_z;
    float length = sqrt(axis.x() * axis.x() + axis.y()*axis.y()+axis.z()*axis.z());
    angle_x = std::acos(axis.x()/length);
    angle_y = std::acos(axis.y()/length);
    angle_z = std::acos(axis.z()/length);
    Eigen::Matrix4f m1,m2,m3  = Eigen::Matrix4f::Identity();
    m1<<1,0,0,0,0,cos(angle_x),-sin(angle_x),0,0,sin(angle_x),cos(angle_x),0,0,0,0,1;
    m2<<cos(angle_y),0,sin(angle_y),0,0,1,0,0,-sin(angle_y),0,cos(angle_y),0,0,0,0,1;
    m3<<cos(angle_z),-sin(angle_z),0,0,sin(angle_z),cos(angle_z),0,0,0,0,1,0,0,0,0,1;

    Eigen::Matrix4f rotation = Eigen::Matrix4f::Identity();
    rotation =m3*m2*m1*Eigen::Matrix4f::Identity();
    return rotation;
}

Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio,
                                      float zNear, float zFar)
{
    // Students will implement this function

    Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();

    // TODO: Implement this function
    // Create the projection matrix for the given parameters.
    // Then return it.
    float eye_angle = eye_fov *MY_PI / 180;
    float t,b,l,r;
    t = zNear * tan(eye_angle /2);
    r = t * aspect_ratio;
    l = -r;
    b = -t;
    Eigen::Matrix4f PersToOrth = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f m1;
    Eigen::Matrix4f m2;
    Eigen::Matrix4f m3;
    m1<< zNear,0,0,0,0,zNear,0,0,0,0,zNear + zFar,-zNear*zFar,0,0,1,0;
    m2<<1,0,0,0,0,1,0,0,0,0,1,-(zNear+ zFar)/2 ,0,0,0,1;
    m3<<2/(r-l),0,0,0,0,2/(t-b),0,0,0,0,2/(zNear -zFar),0,0,0,0,1;
    projection = m3 * m2 * m1 * projection;

    return projection;
}

int main(int argc, const char** argv)
{
    float angle = 0;
    bool command_line = false;
    std::string filename = "output.png";

    if (argc >= 3) {
        command_line = true;
        angle = std::stof(argv[2]); // -r by default
        if (argc == 4) {
            filename = std::string(argv[3]);
        }
        else
            return 0;
    }

    rst::rasterizer r(700, 700);

    Eigen::Vector3f eye_pos = {0, 0, 5};

    std::vector<Eigen::Vector3f> pos{{2, 0, -2}, {0, 2, -2}, {-2, 0, -2}};

    std::vector<Eigen::Vector3i> ind{{0, 1, 2}};

    auto pos_id = r.load_positions(pos);
    auto ind_id = r.load_indices(ind);

    int key = 0;
    int frame_count = 0;

    if (command_line) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        r.draw(pos_id, ind_id, rst::Primitive::Triangle);
        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);

        cv::imwrite(filename, image);

        return 0;
    }

    while (key != 27) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        r.draw(pos_id, ind_id, rst::Primitive::Triangle);

        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);
        cv::imshow("image", image);
        key = cv::waitKey(10);

        std::cout << "frame count: " << frame_count++ << '\n';

        if (key == 'a') {
            angle += 10;
        }
        else if (key == 'd') {
            angle -= 10;
        }
    }

    return 0;
}
