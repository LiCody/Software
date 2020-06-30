#include "software/gui/robot_diagnostics/widgets/robot_diagnostics.h"

RobotDiagnostics::RobotDiagnostics(
    std::shared_ptr<ThreadSafeBuffer<SensorMsg>> sensor_msg_buffer,
    std::shared_ptr<ThreadSafeBuffer<std::unique_ptr<Primitive>>> primitive_buffer,
    QWidget* parent)
    : QMainWindow(parent),
      main_widget(new Ui::AutoGeneratedMainWidget()),
      primitive_buffer(primitive_buffer),
      sensor_msg_buffer(sensor_msg_buffer),
      update_timer(new QTimer(this)),
      update_timer_interval(Duration::fromSeconds(1.0 / 60.0))
{
    // Handles all the setup of the generated UI components and adds the components
    // to this widget
    main_widget->setupUi(this);

    // StrongFocus means that the widget will more aggressively capture focus when
    // clicked. Specifically, we do this so that when the user clicks outside of the
    // QLineEdits used for Parameters, the QLineEdit will lose focus.
    // https://www.qtcentre.org/threads/41128-Need-to-implement-in-place-line-edit-unable-to-get-lose-focus-of-QLineEdit
    setFocusPolicy(Qt::StrongFocus);

    connect(update_timer, &QTimer::timeout, this,
            &RobotDiagnostics::updateRobotDiagnostics);
    update_timer->start(static_cast<int>(update_timer_interval.getMilliseconds()));

    setupWidgets();
    update();
}

void RobotDiagnostics::onChickerStateChanged(double chicker_power, ChargeMode charge_mode,
                                             ChickMode chick_mode)
{
    // TODO (Issue #1420): push primitive to buffer
}

void RobotDiagnostics::onDirectVelocityPowerChanged(
    double direct_per_wheel_power, DirectVelocityMode direct_velocity_mode)
{
    // TODO (Issue #1420): push primitive to buffer
}

void RobotDiagnostics::onDirectPerWheelPowerChanged(
    double direct_per_wheel_power, DirectPerWheelMode direct_per_wheel_mode)
{
    // TODO (Issue #1420): push primitive to buffer
}

void RobotDiagnostics::onDribblerPowerChanged(double dribbler_power)
{
    // TODO (Issue #1420): push primitive to buffer
}

void RobotDiagnostics::setupWidgets()
{
    setupChicker(main_widget,
                 boost::bind(&RobotDiagnostics::onChickerStateChanged, this, _1, _2, _3));
    setupDribbler(main_widget,
                  boost::bind(&RobotDiagnostics::onDribblerPowerChanged, this, _1));
    setupDrive(
        main_widget,
        boost::bind(&RobotDiagnostics::onDirectPerWheelPowerChanged, this, _1, _2),
        boost::bind(&RobotDiagnostics::onDirectVelocityPowerChanged, this, _1, _2));
    setupFeedback(main_widget);
    setupLEDs(main_widget, led_mode);
    setupRobotSelection(main_widget, robot_selection);
    setupRobotStatusTable(main_widget->robot_status_table_widget);
}

void RobotDiagnostics::updateRobotDiagnostics()
{
    std::optional<SensorMsg> sensor_msg = sensor_msg_buffer->popLeastRecentlyAddedValue();
    while (sensor_msg)
    {
        // TODO (Issue #1421): Update robot status log and feedback widget using
        // `sensor_msg.value()`

        updateFeedback(main_widget, sensor_msg);
        // update robot status table
        for (const auto& robot_msg : sensor_msg.value().tbots_robot_msgs())
        {
            main_widget->robot_status_table_widget->updateTbotsRobotMsg(robot_msg);
        }
        sensor_msg = sensor_msg_buffer->popLeastRecentlyAddedValue();
    }
}
