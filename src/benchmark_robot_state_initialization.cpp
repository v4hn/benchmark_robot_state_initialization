#include <ros/ros.h>
#include <moveit/robot_state/robot_state.h>
#include <moveit/robot_model_loader/robot_model_loader.h>

#include <chrono>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "benchmark_robot_state_initialization");
    ros::AsyncSpinner spinner(1);
    spinner.start();

    ros::NodeHandle nh{ "~" };

    int const runs{ nh.param<int>("runs", 1000) };
    int const warmup{ nh.param<int>("warmup", 100) };

    ros::console::set_logger_level("ros.moveit_core.robot_model", ros::console::levels::Warn);

    robot_model_loader::RobotModelLoader robot_model_loader("robot_description");
    robot_model::RobotModelPtr robot_model = robot_model_loader.getModel();

    std::cout << runs << "," << warmup << ",";

    auto start{std::chrono::system_clock::now()};

    for (int i = 0; i < runs+warmup; ++i)
    {
        if(i == warmup)
        {
            start = std::chrono::system_clock::now();
        }
        robot_state::RobotState robot_state{robot_model};
        robot_state.setToDefaultValues();
        robot_state.update();
    }

    auto end{std::chrono::system_clock::now()};

    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << elapsed_seconds.count() << "\n";

    return 0;
}