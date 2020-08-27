#include "software/gui/robot_diagnostics/widgets/robot_diagnostics_gui.h"

RobotDiagnosticsGUI::RobotDiagnosticsGUI(
    std::shared_ptr<ThreadSafeBuffer<SensorProto>> sensor_msg_buffer,
    std::shared_ptr<ThreadSafeBuffer<std::unique_ptr<TbotsProto::PrimitiveSet>>>
        primitive_buffer,
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
            &RobotDiagnosticsGUI::updateRobotDiagnostics);
    update_timer->start(static_cast<int>(update_timer_interval.getMilliseconds()));

    setupWidgets();
}

void RobotDiagnosticsGUI::onChickerStateChanged(double chicker_power,
                                                ChargeMode charge_mode,
                                                ChickMode chick_mode)
{
    // TODO (Issue #1420): push primitive set msg to buffer
}

void RobotDiagnosticsGUI::onDirectVelocityPowerChanged(
    double direct_per_wheel_power, DirectVelocityMode direct_velocity_mode)
{
    // TODO (Issue #1420): push primitive set msg to buffer
}

void RobotDiagnosticsGUI::onDirectPerWheelPowerChanged(
    double direct_per_wheel_power, DirectPerWheelMode direct_per_wheel_mode)
{
    // TODO (Issue #1420): push primitive set msg to buffer
}

void RobotDiagnosticsGUI::onDribblerPowerChanged(double dribbler_power)
{
    // TODO (Issue #1420): push primitive set to buffer
}

void RobotDiagnosticsGUI::createAndSendPrimitive()
{
    //std::make_unique<DirectControlPrimitive>

    // primitive_buffer->push(primitive);
}

void RobotDiagnosticsGUI::setupWidgets()
{
    setupChicker(main_widget, boost::bind(&RobotDiagnosticsGUI::onChickerStateChanged,
                                          this, _1, _2, _3));
    setupDribbler(main_widget,
                  boost::bind(&RobotDiagnosticsGUI::onDribblerPowerChanged, this, _1));
    setupDrive(
        main_widget,
        boost::bind(&RobotDiagnosticsGUI::onDirectPerWheelPowerChanged, this, _1, _2),
        boost::bind(&RobotDiagnosticsGUI::onDirectVelocityPowerChanged, this, _1, _2));
    setupSensorStatus(main_widget);
    setupLEDs(main_widget, led_mode);
    setupRobotSelection(main_widget, robot_selection);
    setupRobotStatusTable(main_widget->robot_status_table_widget);
}

void RobotDiagnosticsGUI::updateRobotDiagnostics()
{
    std::optional<SensorProto> sensor_msg =
        sensor_msg_buffer->popLeastRecentlyAddedValue();
    while (sensor_msg)
    {
        updateSensorStatus(main_widget, sensor_msg.value());

        // update robot status table
        for (const auto& robot_msg : sensor_msg.value().robot_status_msgs())
        {
            main_widget->robot_status_table_widget->updateRobotStatus(robot_msg);
        }

        sensor_msg = sensor_msg_buffer->popLeastRecentlyAddedValue();
    }
}
