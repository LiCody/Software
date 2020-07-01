#include "software/gui/robot_diagnostics/widgets/feedback.h"

void setupFeedback(Ui::AutoGeneratedMainWidget *widget) {}

void updateFeedback(Ui::AutoGeneratedMainWidget *widget, const SensorMsg& sensor_msg)
{
    for (const auto& robot_msg : sensor_msg.tbots_robot_msgs())
    {
        // update status progress bars
        widget->progressBar_battery->setValue(
                static_cast<int>(robot_msg.power_status().battery_voltage()));
        widget->progressBar_capacitor->setValue(
                static_cast<int>(robot_msg.power_status().capacitor_voltage()));
        widget->progressBar_dribbler_speed->setValue(
                static_cast<int>(robot_msg.dribbler_status().dribbler_rpm()));
        // break beam reading is from [0,1] and QT doesn't allow non-integers so it is
        // multiplied by 100 to map to [0,100]
        widget->progressBar_break_beam->setValue(
                static_cast<int>(robot_msg.break_beam_status().break_beam_reading() * 100));

        // update temperature progress bars
        widget->progressBar_dribbler_temp->setValue(
                static_cast<int>(robot_msg.temperature_status().dribbler_temperature()));
        widget->progressBar_board_temp->setValue(
                static_cast<int>(robot_msg.temperature_status().board_temperature()));
    }
}