#pragma once

#include <QtCore/QTimer>
#include <QtWidgets/QMainWindow>
#include <boost/bind.hpp>
#include <memory>

// .ui files are autogenerated to 'ui_<filename>.h`
#include "software/gui/generic_widgets/robot_status/robot_status.h"
#include "software/gui/robot_diagnostics/ui/ui_main_widget.h"
#include "software/gui/robot_diagnostics/widgets/chicker.h"
#include "software/gui/robot_diagnostics/widgets/dribbler.h"
#include "software/gui/robot_diagnostics/widgets/drive.h"
#include "software/gui/robot_diagnostics/widgets/leds.h"
#include "software/gui/robot_diagnostics/widgets/robot_selection.h"
#include "software/gui/robot_diagnostics/widgets/sensor_status.h"
#include "software/multithreading/thread_safe_buffer.h"
#include "software/primitive/primitive.h"
#include "software/proto/sensor_msg.pb.h"

// Forward declare the name of the top-level GUI class defined in main_widget.ui
namespace Ui
{
    class AutoGeneratedMainWidget;
}

/**
 * This is the main window for the robot diagnostics.
 *
 * This class uses ThreadSafeBuffers to send/receive new data, and updates the GUI with
 * the new data at a defined rate using a timer.
 */
class RobotDiagnosticsGUI : public QMainWindow
{
    Q_OBJECT

   public:
    /**
     * Creates a new RobotDiagnosticsGUI MainWindow
     *
     * @param sensor_msg_buffer The buffer used to receive new SensorMsgs
     * @param primitive_buffer The buffer used to send new Primitives
     * @param parent parent widget
     */
    explicit RobotDiagnosticsGUI(
        std::shared_ptr<ThreadSafeBuffer<SensorMsg>> sensor_msg_buffer,
        std::shared_ptr<ThreadSafeBuffer<std::unique_ptr<Primitive>>> primitive_buffer,
        QWidget* parent = nullptr);

   private:
    /**
     * Push new primitive to buffer using new values received
     *
     * @param new values
     */
    void onChickerStateChanged(double chicker_power, ChargeMode charge_mode,
                               ChickMode chick_mode);
    void onDirectPerWheelPowerChanged(double direct_per_wheel_power,
                                      DirectPerWheelMode direct_per_wheel_mode);
    void onDirectVelocityPowerChanged(double direct_per_wheel_power,
                                      DirectVelocityMode direct_velocity_mode);
    void onDribblerPowerChanged(double dribbler_power);

    void createAndSendPrimitive();

    /**
     * Setup widgets
     */
    void setupWidgets();

    /**
     * Update components based on new information from the buffers
     */
    void updateRobotDiagnostics();

    // Indicates which robot we're communicating with
    unsigned int robot_selection;
    std::string led_mode;
    // The "parent" of each of these widgets is set during construction; meaning that
    // the Qt system takes ownership of the pointer and is responsible for de-allocating
    // it; so we don't have to
    Ui::AutoGeneratedMainWidget* main_widget;
    std::shared_ptr<ThreadSafeBuffer<std::unique_ptr<Primitive>>> primitive_buffer;
    std::shared_ptr<ThreadSafeBuffer<SensorMsg>> sensor_msg_buffer;
    QTimer* update_timer;
    const Duration update_timer_interval;
};
